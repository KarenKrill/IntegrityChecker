#pragma once
#include <MD5.h>
#include <string>

uint16 ReadUint16(std::wifstream &stream, bool bigEndian = false);
uint32 ReadUint32(std::wifstream &stream, bool bigEndian = false);
uint64 ReadUint64(std::wifstream &stream, bool bigEndian = false);
void WriteUint16(std::wofstream &stream, uint16 n, bool bigEndian = false);
void WriteUint32(std::wofstream &stream, uint32 n, bool bigEndian = false);
void WriteUint64(std::wofstream &stream, uint64 n, bool bigEndian = false);
wchar_t* ReadWchars(std::wifstream &stream, uint32 length);
void WriteWchars(std::wofstream &stream, const wchar_t* bytes, uint32 length);
std::wstring ReadWstr(std::wifstream &stream, bool bigEndian = false);
bool WriteWstr(std::wofstream &stream, std::wstring wstr, bool bigEndian = false);

namespace DataIntegrity
{
	class FileInfo
	{
	public:
		std::wstring path;
		std::wstring filename;
		Crypto::Hash::MD5 hash;
		FileInfo();
		FileInfo(std::wstring Path, std::wstring FileName, Crypto::Hash::MD5 Hash);
		~FileInfo();
	};
	#define MAX_DEPTH -1
	
	class IntegrityChecker
	{
		SAL::Tree<FileInfo> tree, standardTree;
		void FSWalking(std::wstring path, SAL::TreeNode<FileInfo> *parent);
		void HashFiles(SAL::TreeNode<FileInfo> *parent);
		bool LoadTreeNode(std::wifstream &stream, SAL::TreeNode<FileInfo> *node, bool bigEndian = false);
		bool SaveTreeNode(std::wofstream &stream, SAL::TreeNode<FileInfo> *node, bool bigEndian = false);
		bool EqualNode(SAL::TreeNode<FileInfo> *a, SAL::TreeNode<FileInfo> *b);
		static bool LessRelation(SAL::TreeNode<FileInfo> *a, SAL::TreeNode<FileInfo> *b);
		void SortTreeNodeChilds(SAL::TreeNode<FileInfo> *parent);
	public:
		IntegrityChecker();
		~IntegrityChecker();
		bool LoadStandard(std::wstring filename);
		bool LoadHashes(std::wstring filename);
		void SortHashes();
		bool SaveStandard(std::wstring filename);
		bool Hash(std::wstring path);
		bool Check();
		SAL::TreeNode<FileInfo> *GetTreeRoot();
		SAL::TreeNode<FileInfo> *GetStandardTreeRoot();
	};
}