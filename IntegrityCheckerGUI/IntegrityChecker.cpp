#include "stdafx.h"
#pragma comment(lib, "MD5.lib")

uint16 ReadUint16(std::wifstream &stream, bool bigEndian)
{
	if (!stream.is_open() || stream.eof()) return 0;
	if (bigEndian) return ((uint16)stream.get()) | (((uint16)stream.get()) << 8);
	else return (((uint16)stream.get()) << 8) | ((uint16)stream.get());
}
uint32 ReadUint32(std::wifstream &stream, bool bigEndian)
{
	if (!stream.is_open() || stream.eof()) return 0;
	if (bigEndian) return ((uint32)ReadUint16(stream, bigEndian)) | (((uint32)ReadUint16(stream, bigEndian)) << 16);
	else return (((uint32)ReadUint16(stream, bigEndian)) << 16) | ((uint32)ReadUint16(stream, bigEndian));
}
uint64 ReadUint64(std::wifstream &stream, bool bigEndian)
{
	if (!stream.is_open() || stream.eof()) return 0;
	if (bigEndian) return ((uint64)ReadUint32(stream, bigEndian)) | (((uint64)ReadUint32(stream, bigEndian)) << 32);
	else return (((uint64)ReadUint32(stream, bigEndian)) << 32) | ((uint64)ReadUint32(stream, bigEndian));
}
void WriteUint16(std::wofstream &stream, uint16 n, bool bigEndian)
{
	if (bigEndian) { stream.put(n & 0xFF); stream.put((n >> 8) & 0xFF); }
	else { stream.put((n >> 8) & 0xFF); stream.put(n & 0xFF); }
}
void WriteUint32(std::wofstream &stream, uint32 n, bool bigEndian)
{
	if (bigEndian) { WriteUint16(stream, n & 0xFFFF, bigEndian); WriteUint16(stream, (n >> 16) & 0xFFFF, bigEndian); }
	else { WriteUint16(stream, (n >> 16) & 0xFFFF, bigEndian); WriteUint16(stream, n & 0xFFFF, bigEndian); }
}
void WriteUint64(std::wofstream &stream, uint64 n, bool bigEndian)
{
	if (bigEndian) { WriteUint32(stream, n & 0xFFFFFFFF, bigEndian); WriteUint32(stream, (n >> 32) & 0xFFFFFFFF, bigEndian); }
	else { WriteUint32(stream, (n >> 32) & 0xFFFFFFFF, bigEndian); WriteUint32(stream, n & 0xFFFFFFFF, bigEndian); }
}
wchar_t* ReadWchars(std::wifstream &stream, uint32 length)
{
	if (length == 0) return NULL;
	wchar_t* res = new wchar_t[length + 1];
	stream.read(res, length);
	res[length] = 0;
	return res;
}
void WriteWchars(std::wofstream &stream, const wchar_t* bytes, uint32 length){ stream.write(bytes, length); }
std::wstring ReadWstr(std::wifstream &stream, bool bigEndian)
{
	std::wstring res;
	if (!stream.is_open() || stream.eof()) return res;
	uint8 length = stream.get();
	for (uint8 i = 0; i < length; i++)
	{
		if (bigEndian) res += (((wchar_t)stream.get()) | (((wchar_t)stream.get()) << 8));
		else res += ((((wchar_t)stream.get()) << 8) | ((wchar_t)stream.get()));
	}
	return res;
}
bool WriteWstr(std::wofstream &stream, std::wstring wstr, bool bigEndian)
{
	if (!stream.is_open()) return false;
	stream.put(wstr.size());
	for (uint8 i = 0; i < wstr.size(); i++)
	{
		if (bigEndian) { stream.put(wstr[i] & 0xff); stream.put((wstr[i] >> 8) & 0xff); }
		else { stream.put((wstr[i] >> 8) & 0xff); stream.put(wstr[i] & 0xff); }
	}
	return true;
}

using namespace DataIntegrity;
FileInfo::FileInfo(){}
FileInfo::FileInfo(std::wstring Path, std::wstring FileName, Crypto::Hash::MD5 Hash){ path = Path; filename = FileName; hash = Hash; }
FileInfo::~FileInfo(){}

void IntegrityChecker::FSWalking(std::wstring path, SAL::TreeNode<FileInfo> *parent)
{
	if (path.size() == 0 || !parent) return;
	std::wstring truePath = path;
	if (truePath[path.size() - 1] != L'\\') truePath += L"\\";
	WIN32_FIND_DATAW data;
	HANDLE hFile = FindFirstFileW((truePath + L"*").c_str(), &data); //current dir (".")
	if (hFile == INVALID_HANDLE_VALUE) return;
	BOOL res = TRUE;
	if (wcscmp(data.cFileName, L".") == 0)
	{
		FindNextFileW(hFile, &data); //parent dir ("..")
		res = FindNextFileW(hFile, &data);
	}
	SAL::TreeNode<FileInfo> *curNode;
	while (res)
	{
		curNode = parent->Insert(FileInfo(truePath, data.cFileName, Crypto::Hash::MD5::MD5()));
		if (data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			FSWalking(truePath + data.cFileName, curNode);
		}
		res = FindNextFileW(hFile, &data);
	}
	FindClose(hFile);
}
void IntegrityChecker::HashFiles(SAL::TreeNode<FileInfo> *parent)
{
	if (!parent) return;
	SAL::TreeNode<FileInfo> *child;
	for (int i = 0; i < parent->childs.Size(); i++)
	{
		child = parent->childs[i];
		child->value.hash = Crypto::Hash::MD5::FromFileW((child->value.path + child->value.filename).c_str());
		HashFiles(parent->childs[i]);
	}
}
bool IntegrityChecker::LoadTreeNode(std::wifstream &stream, SAL::TreeNode<FileInfo> *node, bool bigEndian)
{
	if (!stream.is_open()) return false;
	node->value.filename = ReadWstr(stream, bigEndian);
	node->value.hash.first = ReadUint64(stream, bigEndian);
	node->value.hash.second = ReadUint64(stream, bigEndian);
	uint childsNumber = ReadUint32(stream, bigEndian);
	SAL::TreeNode<FileInfo> *child;
	for (uint i = 0; i < childsNumber; i++)
	{
		child = SystemCore::Memory::Alloc<SAL::TreeNode<FileInfo>>();
		child->parent = node;
		node->childs.PushBack(child);
		if (!LoadTreeNode(stream, child, bigEndian))
		{
			SystemCore::Memory::FreePtr(child);
			return false;
		}
	}
	return true;
}
bool IntegrityChecker::SaveTreeNode(std::wofstream &stream, SAL::TreeNode<FileInfo> *node, bool bigEndian)
{
	if (!stream.is_open() || !node) return false;
	WriteWstr(stream, node->value.filename, bigEndian);
	WriteUint64(stream, node->value.hash.first, bigEndian);
	WriteUint64(stream, node->value.hash.second, bigEndian);
	WriteUint32(stream, node->childs.Size(), bigEndian);
	for (uint i = 0; i < node->childs.Size(); i++)
	{
		SaveTreeNode(stream, node->childs[i], bigEndian);
	}
	return true;
}
bool IntegrityChecker::EqualNode(SAL::TreeNode<FileInfo> *a, SAL::TreeNode<FileInfo> *b)
{
	if (a->childs.Size() != b->childs.Size()) return false;
	if (a->value.hash != b->value.hash) return false;
	if (a->value.filename != b->value.filename) return false;
	for (uint i = 0; i < a->childs.Size(); i++)
	{
		if (!EqualNode(a->childs[i], b->childs[i])) return false;
	}
	return true;
}
bool IntegrityChecker::LessRelation(SAL::TreeNode<FileInfo> *a, SAL::TreeNode<FileInfo> *b){ return (a->value.filename < b->value.filename); }
void IntegrityChecker::SortTreeNodeChilds(SAL::TreeNode<FileInfo> *parent)
{
	if (!parent) return;
	parent->childs.Sort(&IntegrityChecker::LessRelation);
	for (uint i = 0; i < parent->childs.Size(); i++)
	{
		SortTreeNodeChilds(parent->childs[i]);
	}
}
IntegrityChecker::IntegrityChecker(){}
IntegrityChecker::~IntegrityChecker(){}
bool IntegrityChecker::LoadStandard(std::wstring filename)
{
	std::wifstream stream;
	stream.open(filename, std::ios::in | std::ios::binary);
	if (!stream.is_open()) return false;
	standardTree.SetRoot(FileInfo());
	LoadTreeNode(stream, standardTree.GetRoot());
	stream.close();
	return true;
}
bool IntegrityChecker::LoadHashes(std::wstring filename)
{
	std::wifstream stream;
	stream.open(filename, std::ios::in | std::ios::binary);
	if (!stream.is_open()) return false;
	tree.SetRoot(FileInfo());
	LoadTreeNode(stream, tree.GetRoot());
	stream.close();
	return true;
}
bool IntegrityChecker::SaveStandard(std::wstring filename)
{
	std::wofstream stream;
	stream.open(filename, std::ios::out | std::ios::binary);
	if (!stream.is_open()) return false;
	SAL::TreeNode<FileInfo> *node = tree.GetRoot();
	SaveTreeNode(stream, node);
	stream.close();
	return true;
}
void IntegrityChecker::SortHashes()
{
	SortTreeNodeChilds(tree.GetRoot());
	SortTreeNodeChilds(standardTree.GetRoot());
}
bool IntegrityChecker::Hash(std::wstring path)
{
	Crypto::Hash::MD5::SetMaxRam(0x10000000); //268 435 456 bytes (256 MB)
	SAL::TreeNode<FileInfo> *root = tree.SetRoot(FileInfo(path, path, Crypto::Hash::MD5::MD5()));
	FSWalking(path, root);
	HashFiles(tree.GetRoot());
	return true;
}
bool IntegrityChecker::Check()
{
	if (tree.GetRoot()->childs.Size() != standardTree.GetRoot()->childs.Size()) return false;
	for (uint i = 0; i < tree.GetRoot()->childs.Size(); i++)
	{
		if (!EqualNode(tree.GetRoot()->childs[i], standardTree.GetRoot()->childs[i])) return false;
	}
	return true;
}
SAL::TreeNode<FileInfo>* IntegrityChecker::GetTreeRoot(){ return tree.GetRoot(); }
SAL::TreeNode<FileInfo>* IntegrityChecker::GetStandardTreeRoot(){ return standardTree.GetRoot(); }