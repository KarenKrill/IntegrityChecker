
/*---------------------------Structures and Algorithms Library---------------------------*/

#pragma once
#include <exception>

namespace SAL
{
	class SmartPointer
	{
		unsigned int *refNumber;
		void AddRef(){if(refNumber) (*refNumber)++;}
		void Release()
		{
			if(refNumber)
			{
				(*refNumber)--;
				if((*refNumber)==0)
					SystemCore::Memory::FreePtr(refNumber);
				refNumber=NULL;
			}
		}
	public:
		SmartPointer()
		{
			refNumber=SystemCore::Memory::Alloc<unsigned int>();
			if(refNumber) *refNumber=1;
		}
		virtual ~SmartPointer(){Release();}
		//call Assign() in copy constructor and assigment operator
		void Assign(const SmartPointer &ptr)
		{
			if(this!=&ptr)
			{
				if(refNumber&&((*refNumber)>0)) Release();
				refNumber=ptr.refNumber;
				AddRef();
			}
		}
		//if it returns true - free memory (called in the destructor)
		bool IsLastRef()
		{
			return (refNumber&&((*refNumber)==1))?true:false;
		}
	};
	class Container: protected SAL::SmartPointer
	{
	public:
		Container(){}
		virtual ~Container(){}
		virtual bool Reserve(uint NumberOfItems){return true;}
		virtual void Free(){}
	};

	class String: protected SAL::Container
	{
		wchar_t *str;
		static const uint8 symbolSize=sizeof(wchar_t);
		uint length, reserved;
		//Overridden functions
		bool Reserve(uint NumberOfItems=64);
		void Free();
		//Constructors
		void Init();
	public:
		String();
		String(const String &Str);
		String(const wchar_t *Str);
		String(const char *Str);
		String(int n);
		String(SYSTEMTIME &Time);
		~String();
		//Get-functions
		uint GetLength();
		uint8 GetSymbolSize();
		const wchar_t* GetStr() const;
		//Functions
		void Pop();
		void Pop(uint Start, uint Length);
		bool PushAt(const wchar_t *Str, uint Position);
		String Substring(uint Start, uint Length);
		String Clone();
		//Static functions
		template <class T> static uint StrLength(const T *Str);
		static String IntToStr(int Numb);
		static int StrToInt(String &Str);
		static wchar_t* CharToWchar(const char* Cstr);
		//Operators
		wchar_t operator[](uint i);
		bool operator==(String &s);
		bool operator!=(String &s);
		String& operator=(const wchar_t *s);
		String& operator=(const char *s);
		String& operator=(const String &s);
		String& operator=(int n);
		String& operator+=(const wchar_t *s);
		String& operator+=(const char *s);
		String& operator+=(const String &s);
		String& operator+=(int n);
		String operator+(const wchar_t *s);
		String operator+(const char *s);
		String operator+(const String &s);
		String operator+(int n);
	};
	String operator+(const wchar_t *s1, String &s2);
	String operator+(const char *s1, String &s2);
	String operator+(int n, String &s);

	template<typename T> class Array: public SmartPointer
	{
		T* mas;
		uint length;
		void Free()
		{
			if(IsLastRef()) SystemCore::Memory::FreeBuf(mas);
			length=0;
			mas=NULL;
		}
		//Constructors
		bool Init(uint NumberOfItems=0)
		{
			length=0; mas=NULL;
			mas=SystemCore::Memory::Alloc<T>(NumberOfItems);
			if(mas)
			{
				SystemCore::Memory::Clear(mas, NumberOfItems*sizeof(T));
				length=NumberOfItems;
			}
			else return false;
			return true;
		}
	public:
		Array(uint NumberOfItems=0){Init(NumberOfItems);}
		Array(const Array &Arr)
		{
			Assign((const SAL::SmartPointer&)Arr);
			Init();
			length=Arr.length;
			mas=Arr.mas;
		}
		virtual ~Array(){Free();}
		Array Clone() const
		{
			Array arr;
			if(arr.Init(length))
			{
				if(SystemCore::Memory::Copy(mas, arr.mas, length*sizeof(T)))
					arr.length=length;
			}
			return arr;
		}
		T& operator[](uint i)
		{
			if(i>=length) throw SystemCore::Exceptions::OutOfRange();
			return mas[i];
		}
	};

	template<typename T> struct ListNode
	{
		T key;
		ListNode<T> *next;
		ListNode(){next=NULL;}
	};
	template<typename T> class List
	{
		ListNode<T> *head, *tail, *curr;
		uint size;
		bool(*LessRelation)(T a, T b);
		static bool DefaultLessRelation(T a, T b){ return (a < b); }
	public:
		List(){ head = curr = tail = NULL; size = 0; LessRelation = &DefaultLessRelation; }
		List(const List<T> &list)
		{
			head=curr=tail=NULL; size=0;
			ListNode<T> *currentNode;
			currentNode=list.head;
			for(uint i=0; i<list.size; i++)
			{
				if(currentNode)
				{
					this->PushBack(currentNode->key);
					currentNode=currentNode->next;
				}
			}
		}
		~List(){Clear();}
		uint Size(){return size;}
		bool IsEmpty(){return (size==0);}
		void PushBack(T key)
		{
			ListNode<T> *temp;
			temp=new ListNode<T>;
			temp->key=key; temp->next=NULL;
			if(tail) tail->next=temp;
			else head=temp;
			curr=tail=temp;
			size++;
		}
		void PushFront(T key)
		{
			ListNode<T> *temp;
			temp=head;
			head=new ListNode<T>;
			head->key=key; head->next=temp;
			if(!temp) tail=head;
			curr=head;
			size++;
		}
		void Push(T key){PushBack(key);}
		void PushAt(uint pos, T key)
		{
			if(pos>size) return;
			if(pos==size) {PushBack(key); return;}
			if(pos==0) {PushFront(key); return;}
			curr=head;
			while(pos-1&&curr)
			{
				curr=curr->next;
			}
			if(!curr) return;
			ListNode<T> *temp;
			temp=new ListNode<T>;
			temp->key=key; temp->next=curr->next;
			curr->next=temp;
			curr=temp;
			size++;
		}
		void Pop()
		{
			ListNode<T> *temp;
			if(head)
			{
				temp=head->next;
				delete head;
				head=curr=temp;
				size--;
			}
			if(!head) tail=NULL;
		}
		bool Search(T key)
		{
			SetCur();
			for(uint i=0; i<size; i++)
			{
				if(curr->key==key) return true;
				else Next();
			}
			return false;
		}
		bool Remove(T key)
		{
			if(!head) return false;
			ListNode<T> *temp;
			if(head->key==key)
			{
				temp=head->next;
				delete head;
				head=curr=temp;
				if(!head) tail=NULL;
				size--;
				return true;
			}
			curr=head;
			while(curr->next&&curr->next->key!=key) curr=curr->next;
			if(!curr->next) return false;
			temp=curr->next->next;
			delete curr->next;
			curr->next=temp;
			size--;
			if(!temp) tail=curr;
			return true;
		}
		bool RemoveAt(uint i)
		{
			if(i>=size||size==0) return false;
			ListNode<T> *temp;
			if(i==0)
			{
				temp=head->next;
				delete head;
				head=curr=temp;
				if(!head) tail=NULL;
				size--;
				return true;
			}
			curr=head;
			for(uint j=0; j<i-1; j++){curr=curr->next;}
			temp=curr->next->next;
			delete curr->next;
			curr->next=temp;
			size--;
			if(!temp) tail=curr;
			return true;
		}
		bool SetCur(uint i=0)
		{
			if(!head||i>=this->size) return false;
			curr=head;
			for(uint j=0; j<i; j++) {if(curr) curr=curr->next; else return false;}
			return true;
		}
		bool Set(uint i, T key)
		{
			if(!SetCur(i)) return false;
			curr->key=key;
			return true;
		}
		void Swap(uint i, uint j)
		{
			T temp;
			temp = (*this)[i];
			Set(i, (*this)[j]);
			Set(j, temp);
		}
		void Next(){if(curr) curr=curr->next;}
		void Clear()
		{
			uint n=size; 
			for(uint i=0; i<n; i++) Pop();
		}
		T operator [](uint i)
		{
			if(!SetCur(i)) throw SystemCore::Exceptions::OutOfRange();
			else return curr->key;
		}
		int GetPos(T key)
		{
			if(!SetCur()) return -1;
			for(uint i=0; i<size; i++)
			{
				if(curr->key!=key) Next();
				else return i;
			}
			return -1;
		}
		void operator +=(T key){Push(key);}
		void operator -=(T key){Remove(key);}
		void operator = (List<T> &list)
		{
			this->Clear();
			for (uint i = 0; i < list.Size(); i++){ this->Push(list[i]); }
		}
		private:
			//нельзя вызывать без определения функции сравнения
			void QSort(uint left, uint right)
			{
				uint temp;
				if (left<right)
				{
					temp = QSortPartition(left, right);
					if (temp != left /*&& temp!=right*/) QSort(left, temp);
					if (temp + 1 < right) QSort(temp + 1, right);
				}
			}
			//функция возвращающая границу разбиения для функции quickSort
			uint QSortPartition(uint left, uint right)
			{
				//принцип разбиения: a[i]<x | a[i]>=x , где x - произвольное число из массива
				T x;
				uint i = left, j = right, xIndex = left;
				x = (*this)[xIndex];//опорный элемент
				for (;;)
				{
					//находим элемент меньше опорного, идя от правого конца
					while (j != left && !((*LessRelation)((*this)[j], x)))
					{
						j--;//если a[j]<x, то оставляем a[j] на месте и сдивгаем указатель на элемент a[j-1]
					}
					//находим элемент >= опорного, идя от левого конца
					while (i<j && (*LessRelation)((*this)[i], x))
					{
						i++;//если a[i]>=x, то оставляем a[i] на месте и сдивгаем указатель на элемент a[i+1]
					}
					if (i<j) Swap(i, j);//меняем местами меньший элемент a[j] с большим a[i], чтобы справа оказались элементы >x, а слева <=x
					else return j;
				}
			}
		public:
			void Sort(bool(*lessRelation)(T a, T b), bool reverse = false)
			{
				if (!size) return;
				if (lessRelation) LessRelation = lessRelation;
				QSort(0, size - 1);
				if (reverse) Reverse();
			}
			void Reverse()
			{
				if (!size) return;
				for (uint i = 0, j = size - 1; i < j; i++, j--)
				{
					Swap(i, j);
				}
			}
	};

	template<class T> struct Point
	{
		T x, y, z;
		Point(){x=y=z=(T)0;}
		Point(T X, T Y, T Z=0){x=X; y=Y; z=Z;}
		Point operator+(Point<T> &p){return Point(x+p.x, y+p.y, z+p.z);}
		bool operator==(Point<T> &p)
		{
			if(x==p.x&&y==p.y&&z==p.z) return true;
			else return false;
		}
		bool operator!=(Point<T> &p){return !(operator==(p));}
	};
	template<class T> struct Vector3
	{
		T x, y, z;
		Vector3(){ x = y = z = (T)0; }
		Vector3(T X, T Y, T Z = 0){ x = X; y = Y; z = Z; }
		Vector3 operator+(Vector3<T> &v){ return Vector3(x + v.x, y + v.y, z + v.z); }
		Vector3 operator-(Vector3<T> &v){ return Vector3(x - v.x, y - v.y, z - v.z); }
		Vector3 operator+(float n){ return Vector3(x + n, y + n, z + n); }
		Vector3 operator-(float n){ return Vector3(x - n, y - n, z - n); }
		Vector3 operator*(float n){ return Vector3(x*n, y*n, z*n); }
		Vector3 operator/(float n){ return Vector3(x/n, y/n, z/n); }
		bool operator==(Vector3<T> &p)
		{
			if (x == p.x&&y == p.y&&z == p.z) return true;
			else return false;
		}
		bool operator!=(Vector3<T> &p){ return !(operator==(p)); }
	};
	template<class T> struct Size
	{
		T width, height;
		Size(){width=height=(T)0;}
		Size(T Width, T Height){width=Width; height=Height;}
		bool operator==(Size<T> &s)
		{
			if(width==s.width&&height==s.height) return true;
			else return false;
		}
		bool operator!=(Size<T> &s){return !(operator==(s));}
	};
	template<class T> struct Rect
	{
		T top, left, right, bottom;
		Rect(){bottom=left=right=top=(T)0;}
		Rect(T Top, T Left, T Right, T Bottom){top=Top; left=Left; right=Right; bottom=Bottom;}
		Rect(Point<T> &TopLeft, Size<T> &Size){top=TopLeft.y; left=TopLeft.x; bottom=TopLeft.y+Size.height; right=TopLeft.x+Size.width;}
	};

	template<class T> bool IsIntersect(Point<T> &point, Point<T> &location, Size<T> &size)
	{
		if(point.x<location.x||point.y<location.y) return false;
		if(point.x>(location.x+size.width)||point.y>(location.y+size.height)) return false;
		return true;
	}
	template<class T> bool IsIntersect(Point<T> &point, Rect<T> &rect)
	{
		if(point.x<rect.left||point.y<rect.top) return false;
		if(point.x>rect.right||point.y>rect.bottom) return false;
		return true;
	}

	template<class T> struct QTreeNode
	{
		QTreeNode *tl, *tr, *bl, *br;//t - top, b - bottom, l - left, r - right;
		uint8 depth;
		Rect<uint> location;
		List<T*> *objects;
		QTreeNode(){tl=tr=bl=br=NULL; objects=NULL; depth=0;}
		QTreeNode(Rect<uint> &Location, uint8 Depth=0)
		{
			tl=tr=bl=br=NULL;
			objects=NULL;
			location=Rect<uint>::Rect(Location);
			depth=Depth;
		}
		~QTreeNode()
		{
			if(tl) delete tl;
			if(tr) delete tr;
			if(bl) delete bl;
			if(br) delete br;
			tl=tr=bl=br=NULL;
			if(objects) {delete objects; objects=NULL;}
		}
		void Add(T *object)
		{
			if(!objects) objects=new List<T*>;
			objects->Push(object);
		}
	};
	template<class T> class QuaternaryTree
	{
		QTreeNode<T> *root;
		uint8 depth;
		void AddInNode(QTreeNode<T> *node, Rect<uint> &location, T *object)
		{
			if(!node||!object) return;
			if(node->depth<depth)
			{
				uint mvl, mhl;//MiddleVerticalLine, MiddleHorizontalLine;
				mvl=(node->location.right+node->location.left)>>1;// n>>1=n/2
				mhl=(node->location.bottom+node->location.top)>>1;// n>>1=n/2
				Rect<uint> tl, bl, tr, br;
				tl=Rect<uint>::Rect(node->location.top,node->location.left,mvl,mhl);
				bl=Rect<uint>::Rect(mhl,node->location.left,mvl,node->location.bottom);
				tr=Rect<uint>::Rect(node->location.top,mvl,node->location.right,mhl);
				br=Rect<uint>::Rect(mhl,mvl,node->location.right,node->location.bottom);
				if(location.top<mhl)
				{
					if(location.left<mvl)
					{
						AddInNode((node->tl)?node->tl:(node->tl=new QTreeNode<T>(tl,node->depth+1)), location, object);
						if(location.bottom>=mhl) AddInNode((node->bl)?node->bl:(node->bl=new QTreeNode<T>(bl,node->depth+1)), location, object);
						if(location.right>=mvl) AddInNode((node->tr)?node->tr:(node->tr=new QTreeNode<T>(tr,node->depth+1)), location, object);
						if(location.bottom>=mhl&&location.right>=mvl) AddInNode((node->br)?node->br:(node->br=new QTreeNode<T>(br,node->depth+1)), location, object);
					}
					else 
					{
						AddInNode((node->tr)?node->tr:(node->tr=new QTreeNode<T>(tr,node->depth+1)), location, object);
						if(location.bottom>=mhl) AddInNode((node->br)?node->br:(node->br=new QTreeNode<T>(br,node->depth+1)), location, object);
					}
				}
				else
				{
					if(location.left<mvl)
					{
						AddInNode((node->bl)?node->bl:(node->bl=new QTreeNode<T>(bl,node->depth+1)), location, object);
						if(location.right>=mvl) AddInNode((node->br)?node->br:(node->br=new QTreeNode<T>(br,node->depth+1)), location, object);
					}
					else AddInNode((node->br)?node->br:(node->br=new QTreeNode<T>(br,node->depth+1)), location, object);
				}
			}
			else node->Add(object);
		}
		typedef QTreeNode<T> *pQTreeNode;
		void Delete(pQTreeNode &node)
		{
			if(!node) return;
			if(node->tl)
			{
				Delete(node->tl);
				node->tl=NULL;
			}
			if(node->tr)
			{
				Delete(node->tr);
				node->tr=NULL;
			}
			if(node->bl)
			{
				Delete(node->bl);
				node->bl=NULL;
			}
			if(node->br)
			{
				Delete(node->br);
				node->br=NULL;
			}
			delete node;
			node=NULL;
		}
	public:
		QuaternaryTree(){root=NULL; depth=3;}
		QuaternaryTree(uint8 Depth){root=NULL; depth=Depth;}
		~QuaternaryTree(){Clear();}
		void SetRoot(Rect<uint> &location, T *object)
		{
			Clear();
			if(!object) return;
			root=new QTreeNode<T>;
			root->location=location;
			root->depth=0;
			root->Add(object);
		}
		void SetRoot(Point<uint> &position, Size<uint> &size, T *object){SetRoot(Rect<uint>::Rect(position, size), object);}
		void SetDepth(uint8 Depth){depth=Depth;}
		void Add(Rect<uint> &location, T *object)
		{
			if(!object) return;
			if(!root) SetRoot(location, object);
			else AddInNode(root, location, object);
		}
		void Add(Point<uint> &position, Size<uint> &size, T *object){Add(Rect<uint>::Rect(position, size), object);}
		void Clear(){Delete(root);}
		List<T*> *GetObjects(Point<uint> &position)
		{
			if(!root) return NULL;
			QTreeNode<T> *curNode, **region;
			region=&root;
			while(*region)//to eliminate the last unnecessary iteration of the loop, you can use while((*region)->depth<depth), but it's not safe (no check for NULL)
			{
				curNode=*region;
				if(position.x<(curNode->location.right+curNode->location.left)>>1)
				{
					if(position.y<(curNode->location.bottom+curNode->location.top)>>1) region=&curNode->tl;
					else region=&curNode->bl;
				}
				else
				{
					if(position.y<(curNode->location.bottom+curNode->location.top)>>1) region=&curNode->tr;
					else region=&curNode->br;
				}
			}
			if(curNode->objects) return curNode->objects;
			else return root->objects;
		}
	};

	namespace RedBlackTree
	{
		const uint MAX_SIZE=(uint)-1;
		const bool RED=true;
		const bool BLACK=false;
		template<typename Key, typename Data> struct RBTreeNode
		{
			RBTreeNode<Key, Data> *parent;
			RBTreeNode<Key, Data> *left;
			RBTreeNode<Key, Data> *right;
			bool color; //true - red, false - black
			Key key;
			Data data;
			RBTreeNode(){ parent = left = right = NULL; color = false; }
		};
		template<typename Key, typename Data> class RedBlackTree
		{
			RBTreeNode<Key, Data> *root;
			unsigned int size;
		public:
			RedBlackTree(){root=NULL; size=0;}
			~RedBlackTree(){Clear();}
			RBTreeNode<Key, Data> *GetRoot(){ return root; }
			unsigned int GetSize(){return size;}
			void LeftRotate(RBTreeNode<Key, Data> *x)
			{
				if(!x) return;
				RBTreeNode<Key, Data> *y=x->right;
				if(y)
				{
					x->right=y->left;
					if(y->left) y->left->parent=x;
					y->parent=x->parent;
					y->left=x;
				}
				if(x->parent)
				{
					if(x==x->parent->left) x->parent->left=y;
					else x->parent->right=y;
				}
				else root=y;
				x->parent=y;
			}
			void RightRotate(RBTreeNode<Key, Data> *x)
			{
				if(!x) return;
				RBTreeNode<Key, Data> *y = x->left;
				if(y)
				{
					x->left=y->right;
					if(y->right) y->right->parent=x;
					y->parent=x->parent;
					y->right=x;
				}
				if(x->parent)
				{
					if(x==x->parent->left) x->parent->left=y;
					else x->parent->right=y;
				}
				else root=y;
				x->parent=y;
			}
			RBTreeNode<Key, Data>* Min(RBTreeNode<Key, Data> *x=NULL)
			{
				if(!root) return NULL;
				RBTreeNode<Key, Data> *parent=NULL, *current = x;
				if(x==NULL) current=root;
				while(current)
				{
					parent=current;
					current=current->left;
				}
				return parent;
			}
			RBTreeNode<Key, Data>* Max(RBTreeNode<Key, Data> *x=NULL)
			{
				if(!root) return NULL;
				RBTreeNode<Key, Data> *parent, *current = x;
				if(x==NULL) current=root;
				while(current)
				{
					parent=current;
					current=current->right;
				}
				return parent;
			}
			RBTreeNode<Key, Data>* Next(RBTreeNode<Key, Data> *x)
			{
				if(!x) return NULL;
				if(x->right) return Min(x->right);
				RBTreeNode<Key, Data> *parent = x->parent, *current = x;
				while(parent&&current!=parent->left)
				{
					current=parent;
					parent=current->parent;
				}
				return parent;
			}
			RBTreeNode<Key, Data>* Prev(RBTreeNode<Key, Data> *x)
			{
				if(!x) return NULL;
				if(x->left) return Max(x->left);
				RBTreeNode<Key, Data> *parent = x->parent, *current = x;
				while(parent&&current!=parent->right)
				{
					current=parent;
					parent=current->parent;
				}
				return parent;
			}
			void InsertFixup(RBTreeNode<Key, Data> *x)
			{
				RBTreeNode<Key, Data> *y;
				while(x!=root&&x->parent->color==RED)
				{
					if(x->parent==x->parent->parent->left)
					{
						y=x->parent->parent->right;
						if(y&&y->color==RED)
						{
							x->parent->color=BLACK;
							y->color=BLACK;
							x->parent->parent->color=RED;
							x=x->parent->parent;
						}
						else
						{
							if(x==x->parent->right)
							{
								x=x->parent;
								LeftRotate(x);
							}
							x->parent->color=BLACK;
							x->parent->parent->color=RED;
							RightRotate(x->parent->parent);
						}
					}
					else
					{
						y=x->parent->parent->left;
						if(y&&y->color==RED)
						{
							x->parent->color=BLACK;
							y->color=BLACK;
							x->parent->parent->color=RED;
							x=x->parent->parent;
						}
						else
						{
							if(x==x->parent->left)
							{
								x=x->parent;
								RightRotate(x);
							}
							x->parent->color=BLACK;
							x->parent->parent->color=RED;
							LeftRotate(x->parent->parent);
						}
					}
				}
				root->color=BLACK;
			}
			RBTreeNode<Key, Data>* Insert(Key key, Data data)
			{
				if(size==MAX_SIZE) return NULL;
				RBTreeNode<Key, Data> *current, *parent, *x;
				current=root; parent=NULL;
				while(current!=NULL)
				{
					if(key==current->key) return current;
					parent=current;
					current=(key<current->key)?current->left:current->right;
				}
				x = new RBTreeNode<Key, Data>;
				x->data=data;
				x->key = key;
				x->parent=parent;
				x->left=NULL;
				x->right=NULL;
				x->color=RED;
				if(parent)
				{
					if(key<parent->key) parent->left=x;
					else parent->right=x;
				}
				else root=x;
				size++;
				InsertFixup(x);
				return x;
			}
			void DeleteFixup(RBTreeNode<Key, Data> *x)
			{
				if(!x) return;
				while(x!=root&&x->color==BLACK)
				{
					if(x==x->parent->left)
					{
						RBTreeNode<Key, Data> *w = x->parent->right;
						if(w->color==RED)
						{
							w->color=BLACK;
							x->parent->color=RED;
							LeftRotate(x->parent);
							w=x->parent->right;
						}
						if(w->left->color==BLACK&&w->right->color==BLACK)
						{
							w->color=RED;
							x=x->parent;
						}
						else
						{
							if(w->right->color==BLACK)
							{
								w->left->color=BLACK;
								w->color=RED;
								RightRotate(w);
								w=x->parent->right;
							}
							w->color=x->parent->color;
							x->parent->color=BLACK;
							w->right->color=BLACK;
							LeftRotate(x->parent);
							x=root;
						}
					}
					else
					{
						RBTreeNode<Key, Data> *w = x->parent->left;
						if(w->color==RED)
						{
							w->color=BLACK;
							x->parent->color=RED;
							RightRotate(x->parent);
							w=x->parent->left;
						}
						if(w->right->color==BLACK&&w->left->color==BLACK)
						{
							w->color=RED;
							x=x->parent;
						}
						else
						{
							if(w->left->color==BLACK)
							{
								w->right->color=BLACK;
								w->color=RED;
								LeftRotate(w);
								w=x->parent->left;
							}
							w->color=x->parent->color;
							x->parent->color=BLACK;
							w->left->color=BLACK;
							RightRotate(x->parent);
							x=root;
						}
					}
				}
				if(x) x->color=BLACK;
			}
			void DeleteNode(RBTreeNode<Key, Data> *z)
			{
				if(size==0||!z) return;
				RBTreeNode<Key, Data> *x, *y;
				if(!z->left||!z->right) 
				{
					if(z->left)	x=z->left;
					else x=z->right;
					y=z;
					if(x) x->parent=y->parent;
					if(y->parent)
					{
						if(y==y->parent->left) y->parent->left=x;
						else y->parent->right=x;
					}
					else root=x;
					size--;
					if(x&&x->color==RED/*&&y->color==BLACK*/) DeleteFixup(x);
					delete z;
					z=0;
				}
				else 
				{
					y=Next(z);
					z->key = y->key;
					z->data = y->data;
					DeleteNode(y);
				}
			}
			RBTreeNode<Key, Data>* Search(Key key)
			{
				RBTreeNode<Key, Data> *current = root;
				while(current!=NULL)
				{
					if(key==current->key) return current;
					current=(key<current->key)?current->left:current->right;
				}
				return NULL;
			}
			bool Remove(Key key)
			{
				if(size==0) return false;
				RBTreeNode<Key, Data> *temp;
				if((temp=Search(key))==NULL) return false;
				DeleteNode(temp);
				temp=0;
				return true;
			}
			void Clear()
			{
				while (size) { DeleteNode(root); }
				return;
			}
		};
	}

	template<class T> class TreeNode
	{
	public:
		TreeNode<T> *parent;
		List<TreeNode<T>*> childs;
		T value;
		TreeNode(){ parent = NULL; }
		~TreeNode(){}
		TreeNode<T>* Insert(T val)
		{
			TreeNode<T> *child = SystemCore::Memory::Alloc<TreeNode<T>>();
			if (child)
			{
				child->parent = this;
				child->value = val;
				childs.PushBack(child);
			}
			return child;
		}
	};
	template<class T> class Tree
	{
		TreeNode<T> *root;
	public:
		Tree(){ root = NULL; }
		~Tree(){}
		TreeNode<T>* GetRoot(){ return root; }
		TreeNode<T>* SetRoot(T value)
		{
			root = SystemCore::Memory::Alloc<TreeNode<T>>();
			if (root) root->value = value;
			return root;
		}
	};
}