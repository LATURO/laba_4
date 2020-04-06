#include <iostream>
using namespace std;
template <typename D,class U>
class Iterator
{
	U *vec;
	D *index;//курсор
public:

	Iterator(U *v):vec(v){
		index = this->vec->begin();//установка курсора на начало
	}
	D* begin(){
	 return this->vec->begin();
	}
	D* end(){

	 return this->vec->end();
	}
	D* current()const { 
		return index;
	}
	const Iterator& operator++()
    {
    	index = index+1;
        return *this;
    }
	const Iterator& operator--()
    {
    	index = index-1;
        return *this;
    }
    const Iterator& operator--(int)
    {
    	Iterator temp(*this);
    	index = index-1;
        return temp;
    }
    const Iterator& operator++(int)
    {
    	Iterator temp(*this);
    	index = index+1;
        return  temp;
    }
   const D operator *()
   {
      return *index;
   }
    bool operator==(const Iterator& right) const
    {
        return (index==right.index);
    }
    bool operator!=(const Iterator& right) const
    {
        return (index!=right.index);
    }
    void reset(){
 		index = this->vec->begin();   	
    }
};
template <typename T>
class Vector{
private:
	int size_n;//размер массива
	int pos;//индекс указателя до которого все заполнено
	T *array=new T[0];//массив с элементами
public:
	friend class Iterator<T,Vector>;	
	Vector():size_n(0){//конструктор по умолчанию
	}
	Vector(int l):size_n(l){//иницилизация вектора
		if (l>0)
		{
			array =(T*)realloc(array,sizeof(T)*l);//увеличение размера массива под установленный размен
		}
		pos=0;//указание на первый элемент
	}
	Iterator<T, Vector> CreateIterator() {
    return *(new Iterator<T, Vector >(this));
  }
	void add(){
		T item;
		if (pos>size_n)//проверка на нахождение внутри массива
		{
		array=(T*)realloc(array,sizeof(T)* pos);//увеличение массива под подходящий размер
		size_n=pos;//увеличиваем размер под позицию
		}
		array[pos]=item;//присваивание элемента
		
		pos++;//переход позиции
	}
	void add(T item){//аналогично с предыдущей функции
		if (pos>size_n)//увеличение массива если индекс больше размера
		{
		array=(T*)realloc(array,sizeof(T)* pos);
		size_n=pos;
		}
		array[pos]=item;
		pos++;
	}
	int size(){
		return pos;//возвращение размера
	}
	T operator[](int item)
    {
    try{
    	if ((item>=0)&&(item<size_n))
    	{
      	return array[item];//возвращение элемента по скобкам
    	}
    	else{
    	throw 1;
    }
    }
    catch(int a){
      cout<<"Out of array, return 1 element of vector:"<<endl;
      return array[0];
    }
    }

    bool empty(){
    	return ((size_n==0)||(pos==0))?true:false;//проверка на пустоту
    }
    void erase(int k){//удаление элемента по индексу
    	T buf=array[0];
    	if ((k>=0)&&(k<pos))//нахождение индексе внутри возможного массива
    	{
    	for (int i = k; i < size()-1; ++i)//перенос элемента в конец массива с уменьшением размера
    	{
    		buf=array[i];
    		array[i]=array[i+1];
    		array[i+1]=buf;
    	}
    	array=(T*)realloc(array,sizeof(T)*(pos-1));//уменьшение размера
    	size_n-=1;//уменьшение размера
    	pos--;//перенос позиции назад
    	}
    	else{
    		cout<<"Index is not in array"<<endl;//вывод если индекс вне массива
    	}
    }
    T* begin(){
    	return this->array;
    }
    T* end(){
    	return this->array+pos-1;
    }
	~Vector(){
		if (!empty())
		{
			delete [] array;//отчистка не пустого массива
			cout<< "Memory is free"<<endl;
		}

	}
	friend ostream& operator<< (ostream &out, Vector &point){
    if (!point.empty())//определение вывода
    {
    cout<<"---------"<<endl;
     cout<<"Vector list:"<<endl;
     for (int i = 0; i < point.size(); ++i)
     {
     	out<<i+1<<")"<<point.array[i]<<endl;
     } 
    }
    else{
    	out<<"Vector is empty!"<<endl;
    }
    return out;
    }
    friend istream& operator>> (istream &in, Vector &point){
		for (int i = 0; i < point.size_n;i++)
		{
			in>>point.array[i];
		}
		point.pos=point.size_n;
		return in;
	}
};
int main(){
	Vector<double> g1;
	g1.add(5.234);
	g1.add(7.12);
	g1.add(6.123);
	g1.add(7.965);
	g1.add(11);
	g1.add(9.88);
	g1.add(8.005);
	cout<<g1;
	Iterator<double,Vector<double> > it = g1.CreateIterator();
	Iterator<double,Vector<double> > it1 = g1.CreateIterator();
	cout<<"Вывод вектора с помощью итератора:"<<endl;
	for (; it.current() <=it.end() ; it++)
	{
		cout<<*it<<endl;
	}
	it.reset();//перевод курсора в начальное положение
	cout<<"Проверка равенства двух итераторов"<<endl;
	cout<<"it: "<<it.current()<<endl;
	cout<<"it1: "<<it1.current()<<endl;
	if (it==it1)
	{
		cout<<"Итераторы равны"<<endl;
	}
	cout<<"Демонстрирование работы инкрементов"<<endl;
	cout<<"it: "<<it.current()<<endl;
	cout<<"it++: "<<(it++).current()<<endl;
	cout<<"it: "<<it.current()<<endl;
	cout<<"++it: "<<(++it).current()<<endl;
	cout<<"Демонстрирование работы декремент"<<endl;
	cout<<"it: "<<it.current()<<endl;
	cout<<"it--: "<<(it--).current()<<endl;
	cout<<"it: "<<it.current()<<endl;
	cout<<"--it: "<<(--it).current()<<endl;
	cout<<"it.begin():"<<it.begin()<<endl;
	cout<<"it.end():"<<it.end()<<endl;
	Vector<double> g2;
	g2.add(7.965);
	g2.add(11);
	g2.add(9.88);
	g2.add(8.005);
	Iterator<double,Vector<double> > it2 = g2.CreateIterator();	
	if (it!=it2)
	{
		cout<<"Итераторы не равны"<<endl;
	}
	return 0;
}
