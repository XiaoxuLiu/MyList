#include<iostream>
using namespace std;

template<class T>
class MyList{
private:
	T *a;
	int size;
	void double_space()//if the array size is not enough, extend it.
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
	int curSize;//current size.
	
	/* for sort function */
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
	
	MyList(int num, const T &item)//put some item into list, the number is num
	{
		size = 100;
		a = new T [size];
		curSize = 0;
		for (int i = 0; i < num; i++)
		{
			push(item);
		}
	}
	
	MyList(const MyList &l)//copy a list from other one
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
    
	MyList(T* arr, int len)//use the front len-size data from arr to construction a list
	{
		size = 100;
		a = new T [size];
		curSize = 0;
		for (int i = 0; i < len; i++)
		{
			push(arr[i]);
		}
	}

	void push(const T &item)//put item at the last position of list
	{
		if (curSize + 1 > size)
		{
			double_space();
		}
		a[curSize] = item;
		curSize++;
	}
	
	T pop()//delete the last data
	{
		if (curSize <= 0)
		{
			throw curSize;
		}
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
	
	void clean()//clean the list。
	{
		curSize = 0;
	}
	
	int get_size() const//get current size of the list。
	{
		return curSize;
	}
	
	void erase(int start, int end) //delete the data from start to end, include them
	{
		if (start + end > curSize)
			return;
		for (int i = 0; i < curSize - start - end; i++)
		{
			a[start + i] = a[start + end + i];
		}
		curSize = curSize - end;
	}
	
	T get_item(int index) const//return the data at index position
	{
		return a[index];
	}
	
	MyList get_item(int start, int end)//return the data from start to end, include them
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
	
	int count(const T &item)//return the num of the data same as item
	{
		int num = 0;
		for (int i = 0; i < curSize; i++)
		{
			if (item == a[i])
				num++;
		}
		return num;
	}
	
	void remove(const T &item)//delete the first data same as item
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
	
	friend MyList operator + (const MyList &l1, const MyList &l2) //merge two MyList
	{
		MyList<T> temp;
		temp = l1;
		for (int i = 0; i < l2.get_size(); i++)
		{
			temp.push(l2[i]);
		}
		return temp;
	}
    
	friend MyList operator + (const MyList &l1, const T &item) //same as push(T item)
	{
		
		MyList<T> temp;
		temp = l1;
		temp.push(item);
		return temp;
	}
	
	MyList &operator = (const MyList &l)//assignment the list
	{
		for (int i = 0; i < l.get_size(); i++)
		{
			push(l[i]);
		}
		return *this;
	}
	
	MyList &operator += (const T &item)//same as push(T item)
	{
		push(item);
		return *this;
	}
	
	MyList &operator += (const MyList &l)//put one other list at the behind of the list
	{
		for (int i = 0; i < l.get_size(); i++)
		{
			push(l[i]);
		}
		return *this;
	}
	
	T &operator [](int index) const//return the data at index position
	{
		return a[index];
	}
	
	friend ostream & operator<<(ostream &os, const MyList &obj)//print the data in list [1, 2, 5, 4, 1]
	{
		for (int i = 0; i < obj.get_size(); ++i)
			os << obj.get_item(i) << "  ";
		return os;
	}

	void sort(bool less=true)//order the list, if less=true，ascending order，otherwise descending order
	{
		quicksort(a, 0, curSize - 1, less);
	}
	
	void reverse()//reversal the data in list
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

    b = a.get_item(4, -3); // b = []
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