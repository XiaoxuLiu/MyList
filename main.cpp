#include<iostream>
using namespace std;

template<class T>
class MyList{
private:
	T *a;
	int size;
	void double_space();//数组大小不够的时候将数组大小翻倍的操作。
	int curSize;//list当前大小。
	
	/* 用于排序操作 */
	void quicksort(T * a, int left, int right, bool less)
	{
		if(left >= right)
		{
			return ;
		}
		int i = left;
		int j = right;
		T key = a[left];
		while(i < j)
		{
			if (true == less)
			{
				while(i < j && key <= a[j])
				{
					j--;
				}
				a[i] = a[j];
				while(i < j && key >= a[i])
				{
					i++;
				}
				a[j] = a[i];
			} else {
				while(i < j && key >= a[j])
				{
					j--;
				}
				a[i] = a[j];
				while(i < j && key <= a[i])
				{
					i++;
				}
				a[j] = a[i];
			}
		}
		a[i] = key;
		quicksort(a, left, i - 1, less);
		quicksort(a, i + 1, right, less);
	}
public:
	MyList(){
		size = 100;
		a = new T [size];
		curSize = 0;
	}
	
	MyList(int num, const T &item)//将item重复num次填入数组中。
	{
		size = 100;
		a = new T [size];
		curSize = 0;
		for (int i = 0; i < num; i++)
		{
			push(item);
		}
	}
	
	MyList(const MyList &l)//深复制另外一个MyList。
	{
		size = 100;
		a = new T [size];
		curSize = 0;
		for (int i = 0; i < l.get_size(); i++)
		{
			//a[i] = l[i];
			push(l[i]);
		}
	}
    
	MyList(T* arr, int len)//以arr的前len个元素构造数组
	{
		size = 100;
		a = new T [size];
		curSize = 0;
		for (int i = 0; i < len; i++)
		{
			push(arr[i]);
		}
	}

	void push(const T &item)//将item添加在MyList最后。
	{
		if (curSize + 1 > size)
		{
			T *temp = a;
			size = size + size;
			a = new T [size];
			for (int i = 0; i < curSize; i++)
			{
				a[i] = temp[i];
			}
			delete [] temp;
		}
		a[curSize] = item;
		curSize++;
	}
	
	T pop()//将MyList中最后一个元素删除，并返回这个删除的元素。
	{
		T temp = a[curSize];
		curSize--;
		return temp;
	}
	
	void insert(int index, const T &item)//将item插入到place处。
	{
		push(item);
		for (int i = 1; i < curSize - index; i++)
		{
			a[curSize - i] = a[curSize - i - 1];
		}
		//curSize++;
		//for (int i = 0; i < curSize - index; i++)
		//{
		//	a[curSize - i] = a[curSize - i - 1];
		//}			
		a[index] = item;
	}
	
	void clean()//清空数组。
	{
		curSize = 0;
	}
	
	int get_size() const//返回MyList中元素的数量。
	{
		return curSize;
	}
	
	void erase(int start, int end) //删除MyList中从start开始end个元素，包括两边。
	{
		if (start + end > curSize)
			return;
		for (int i = 0; i < curSize - start - end; i++)
		{
			a[start + i] = a[start + end + i];
		}
		curSize = curSize - end;
	}
	
	T get_item(int index) const//返回第index个元素。
	{
		return a[index];
	}
	
	MyList get_item(int start, int end)//返回MyList中第start到第end位的元素，包括两边。此处需要像python一样接受负数，具体见测试代码。
	{
		MyList<T> temp;
		if (end == -1)
			end = curSize - 1;
		if (start > end)
			return temp;
		for (int i = 0; i < end - start + 1; i++)
		{
			temp.push(a[start + i]);
		}
		return temp;
	}
	
	int count(const T &item)//返回MyList中和item相等的元素的个数。
	{
		int num = 0;
		for (int i = 0; i < curSize; i++)
		{
			if (item == a[i])
				num++;
		}
		return num;
	}
	
	void remove(const T &item)//删除MyList中第一个和item相等的元素。
	{
		for (int i = 0; i < curSize; i++)
		{
			if (item == a[i])
			{
				for (int j = 0; j < curSize - i;j++)
				{
					a[i + j] = a[i + j + 1];
				}
				curSize--;
				return;
			}
		}
	}
	
	friend MyList operator + (const MyList &l1, const MyList &l2) //合并两个MyList
	{
		MyList<T> temp;
		temp = l1;
		for (int i = 0; i < l2.get_size(); i++)
		{
			temp.push(l2[i]);
		}
		return temp;
	}
    
	friend MyList operator + (const MyList &l1, const T &item) //同push(T item)，但不修改l1，返回一个新数组
	{
		
		MyList<T> temp;
		temp = l1;
		temp.push(item);
		return temp;
	}
	
	MyList &operator = (const MyList &l)//赋值
	{
		for (int i = 0; i < l.get_size(); i++)
		{
			push(l[i]);
		}
		return *this;
	}
	
	MyList &operator += (const T &item)//同push(T item)
	{
		push(item);
		return *this;
	}
	
	MyList &operator += (const MyList &l)//将一个MyList加入到本个MyList之后。
	{
		for (int i = 0; i < l.get_size(); i++)
		{
			push(l[i]);
		}
		return *this;
	}
	
	T &operator [](int index) const//返回第index个元素。
	{
		return a[index];
	}
	
	friend ostream & operator<<(ostream &os, const MyList &obj)//如果T是可以直接cout的类的话（比如int），按Python数组的格式输出MyList中的每一个元素，例如：
    // [1, 2, 5, 4, 1]
	{
		for (int i = 0; i < obj.get_size(); ++i)
			os << obj.get_item(i) << "  ";
		return os;
	}

	void sort(bool less=true)//实现一个快速排序或归并排序，对支持比较运算符（>=<）的类进行排序。
    // 若less=true，按照从小到大排列，否则按从大到小排列
	{
		quicksort(a, 0, curSize - 1, less);
	}
	
	void reverse()//将MyList的元素倒过来。
	{
		T temp;
		for(int i = 0; i < (curSize - 1) / 2; i++)
		{
			temp = a[i];
			a[i] = a[curSize - 1 - i];
			a[curSize - 1 - i] = temp;
		}
	}

	~MyList(){delete [] a;}
};

int main(){
	MyList<int> a, b;
	int i;
	for (i = 0; i < 5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4]
    cout << "This test should be: a = [0, 1, 2, 3, 4]" << endl;
	for (i = 0; i < a.get_size(); ++i)
		cout << a.get_item(i) << "  ";
	cout << endl << endl;

	a[3] = 15; // a = [0, 1, 2, 15, 4]
    cout << "This test should be: a = [0, 1, 2, 15, 4]" << endl;
	for (i = 0; i < a.get_size(); ++i)
		cout << a.get_item(i) << "  ";
	cout << endl << endl;

	a.sort(); // a = [0, 1, 2, 4, 15]
    cout << "This test should be: a = [0, 1, 2, 4, 15]" << endl;
	for (i = 0; i < a.get_size(); ++i)
		cout << a.get_item(i) << "  ";
	cout << endl << endl;

	a.reverse(); // a = [15, 4, 2, 1, 0]
    cout << "This test should be: a = [15, 4, 2, 1, 0]" << endl;
	for (i = 0; i < a.get_size(); ++i)
		cout << a.get_item(i) << "  ";
	cout << endl << endl;

	a += 12; // a = [15, 4, 2, 1, 0, 12]
    cout << "This test should be: a = [15, 4, 2, 1, 0, 12]" << endl;
	for (i = 0; i < a.get_size(); ++i)
		cout << a.get_item(i) << "  ";
	cout << endl << endl;

    b = a.get_item(4, -3); // b = [] *若start > end，返回空数组
    cout << "This test should be: b = []" << endl;
	for (i = 0; i < b.get_size(); ++i)
		cout << b.get_item(i) << "  ";
	cout << endl << endl;

	b = a.get_item(3, -1); // b = [1, 0, 12] 
    cout << "This test should be: b = [1, 0, 12]" << endl;
	for (i = 0; i < b.get_size(); ++i)
		cout << b.get_item(i) << "  ";
	cout << endl << endl;

	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
    cout << "This test should be: a = [15, 4, 2, 1, 0, 12, 1, 0, 12]" << endl;
	for (i = 0; i < a.get_size(); ++i)
		cout << a.get_item(i) << "  ";
	cout << endl << endl;

    cout << "This test should be: a.count(5) = 0" << endl;
	cout << a.count(5) << endl << endl;

	b.clean(); // b = []
    cout << "This test should be: b.get_size() = 0" << endl;
	cout << b.get_size() << endl << endl;

	a.erase(2, 5); // a = [15, 4, 0, 12]
    cout << "This test should be: a = [15, 4, 0, 12]" << endl;
	for (i = 0; i < a.get_size(); ++i)
		cout << a.get_item(i) << "  ";
	cout << endl << endl;

	b = a + a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
    cout << "This test should be: b = [15, 4, 0, 12, 15, 4, 0, 12]" << endl;
	for (i = 0; i < b.get_size(); ++i)
		cout << b.get_item(i) << "  ";
	cout << endl << endl;

	b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
    cout << "This test should be: b = [15, 4, 0, 116, 12, 15, 4, 0, 12]" << endl;
	for (i = 0; i < b.get_size(); ++i)
		cout << b.get_item(i) << "  ";
	cout << endl << endl;

	b.remove(4); // b = [15, 0, 116, ...]
    cout << "This test should be: b = [15, 0, 116, 12, 15, 4, 0, 12]" << endl;
	cout << b << endl << endl;

	MyList<double> c(10, 3.14);
	for (i = 0; i < 100; ++i)
		c.push(1.1 * i);
    cout << "This test should be: c.get_item(100, 105) = [99, 100.1, 101.2, 102.3, 103.4, 104.5]" << endl;
	cout << c.get_item(100, 105) << endl;
	
	system("pause");
	return 0;
}