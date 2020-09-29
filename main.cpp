#include <iostream>
#include <ostream>
using namespace std;
 
class Array{
private:
    int size; //размер массива
    int *ptr; //указатель на массив
public:
    Array(); //конструктор без параметров
    Array( const Array & ); // оператор копирования
    const Array &operator= (const Array &); //оператор присваивания
    void setArray(); //вставка в массив
    void getArray(); //вывод массива
    ~Array(); //очистка массива
    int operator[](int idx); //поиск элемента в массиве по индексу через ссылку
};
 
Array::Array(){ // конструктор по умолчанию, без параметров
    size = 10;
    ptr = new int [size]; // выделить место в памяти для массива
    for (int i = 0; i < size; i++) // обнуляем массив
        ptr[i] = 0;
}
 
Array::Array( const Array &ArrayToCopy ):size(ArrayToCopy.size){ //оператор копирования
    ptr = new int [size]; // выделить место в памяти для массива
    for (int i = 0; i < size; i++)
        ptr[i] = ArrayToCopy.ptr[i]; // заполняем массив значениями массива arrayToCopy
}
 
const Array &Array::operator= (const Array &right){ //оператор присваивания
    if (&right != this){ //чтобы не выполнилось не присвоилось само в себя
        if (size != right.size){
            delete [] ptr; //освободить пространство
            size = right.size; //установить нужный размер массива
            ptr = new int [size]; //выделить память под копируемый массив
        }
        for (int i = 0; i < size; i++) {
            ptr[i] = right.ptr[i]; //скопировать массив
        }
    }
    return *this;
}
 
int Array::operator[](int idx){ //поиск элемента в массиве по индексу через ссылку
    return ptr[idx];
}
 
void Array::setArray(){ // заполнение массива
    for (int i = 0; i < size; i++)
        cin >> ptr[i];
}
 
void Array::getArray(){ //вывод массива
    for (int i = 0; i < size; ++i){
        cout << ptr[i] << " ";
    }
    cout << endl;
}
 
Array::~Array(){ // очистка массива
    delete [] ptr; // освободить память, удалив массив
}
 
int main(){
    Array array1;
    int a;
    array1.setArray();
    cin >> a;
    array1.getArray();
    Array array3(array1); //копирование
    Array array2 = array1; //присваивание
    array2.getArray();
    array3.getArray();
    cout << array1.operator[](a);
    return 0;
}
