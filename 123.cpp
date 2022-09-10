#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;
#define MIN_N -100
#define MAX_N 100
#define ABS(X) (((X)>0)?(X):-(X))

template<typename T>
T* createArray(T *ar, int size);
template<typename T>
T** createArray(T **ar, int rows, int cols);
template<typename T>
void fillArray(T *ar, int size);
template<typename T>
void fillArray(T **ar, int rows, int cols);
template<typename T>
void printArray(T *ar, int size);
template<typename T>
void printArray(T **ar, int rows, int cols);
template<typename T>
void deleteArray(T *ar);
template<typename T>
void deleteArray(T **ar, int rows);
template<typename T>
T* appendElement(T *ar, int size, T el);
template<typename T>
T* insertElement(T *ar, int size, T el, int ind);
template<typename T>
T* deleteElement(T *ar, int size, int ind);

bool isPrime(int n);
int* nonPrimes(int *ar, int size);

template<typename T>
T** separateElements(T *ar, int size);



int main() {
	srand(time(NULL));
	int *ar { };
	int **ar2 { };
	int size { 5 }, rows { 3 }, cols { 5 };
	ar = createArray(ar, size);
	fillArray(ar, size);
	printArray(ar, size);
	ar = appendElement(ar, size, 2);
	size++;
	printArray(ar, size);
	ar = insertElement(ar, size, -21, 2);
	size++;
	printArray(ar, size);
	ar = deleteElement(ar, size, 1);
	size--;
	printArray(ar, size);
	ar = nonPrimes(ar, size);
	printArray(ar, size);
	cout << endl;
	ar2 = createArray(ar2, rows, cols);
	fillArray(ar2, rows, cols);
	printArray(ar2, rows, cols);
	cout << endl;

	deleteArray(ar);
	deleteArray(ar2);

	size = 25;
	cols = size;
	int *longar { };
	longar = createArray(longar, size);
	fillArray(longar, size);
	printArray(longar, size);
	int **sep { };
	sep = separateElements(longar, size);
	printArray(sep, rows, cols);
	deleteArray(longar);
	deleteArray(sep, rows);

	return 0;
}

/*
 * Задание 1. Написать следующие функции для работы
 с динамическим массивом:
 ■ ■ Функция распределения динамической памяти.
 ■ ■ Функция инициализации динамического массива.
 ■ ■ Функция печати динамического массива.
 ■ ■ Функция удаления динамического массива.
 ■ ■ Функция добавления элемента в конец массива.
 ■ ■ Функция вставки элемента по указанному индексу.
 ■ ■ Функция удаления элемента по указанному индексу.
 *
 */

//■ ■ Функция распределения динамической памяти.
template<typename T>
T* createArray(T *ar, int size) {
	ar = new T[size] { };
	return ar;
}

template<typename T>
T** createArray(T **ar, int rows, int cols) {
	ar = new T*[rows] { };
	for (int i = 0; i < rows; i++)
		ar[i] = createArray(ar[i], cols);
	return ar;
}

//■ ■ Функция инициализации динамического массива.
template<typename T>
void fillArray(T *ar, int size) {
	for (int i = 0; i < size; i++)
		ar[i] = MIN_N + (MAX_N - MIN_N) * ((double) rand() / RAND_MAX);
}

template<typename T>
void fillArray(T **ar, int rows, int cols) {
	for (int i = 0; i < rows; i++)
		fillArray(ar[i], cols);
}

//■ ■ Функция печати динамического массива.
template<typename T>
void printArray(T *ar, int size) {
	for (int i = 0; i < size; i++) {
		cout << ar[i] << " ";
	}
	cout << endl;
}

template<typename T>
void printArray(T **ar, int rows, int cols) {
	for (int i = 0; i < rows; i++)
		printArray(ar[i], cols);
}

//■ ■ Функция удаления динамического массива.
template<typename T>
void deleteArray(T *ar) {
	delete[] ar;
}

template<typename T>
void deleteArray(T **ar, int rows) {
	for (int i = 0; i < rows; i++)
		deleteArray(ar[i]);
	delete[] ar;
}

//■ ■ Функция добавления элемента в конец массива.
template<typename T>
T* appendElement(T *ar, int size, T el) {
	T *r { };
	r = createArray(r, size + 1);
	for (int i = 0; i < size; i++) {
		r[i] = ar[i];
	}
	r[size] = el;
	deleteArray(ar);
	return r;
}

//■ ■ Функция вставки элемента по указанному индексу.
template<typename T>
T* insertElement(T *ar, int size, T el, int ind) {
	if (ind >= size)
		return appendElement(ar, size, el);
	T *r { };
	r = createArray(r, size + 1);
	for (int i = 0; i < ind; i++) {
		r[i] = ar[i];
	}
	r[ind] = el;
	for (int i = ind + 1; i < size + 1; i++) {
		r[i] = ar[i - 1];
	}
	deleteArray(ar);
	return r;
}

//■ ■ Функция удаления элемента по указанному индексу.
template<typename T>
T* deleteElement(T *ar, int size, int ind) {
	if (ind >= size)
		return ar;
	T *r { };
	r = createArray(r, size - 1);
	for (int i = 0; i < ind; i++)
		r[i] = ar[i];
	for (int i = ind; i < size - 1; i++)
		r[i] = ar[i + 1];
	deleteArray(ar);
	return r;
}

/*
 * Задание 2. Написать функцию, которая получает ука-
 затель на динамический массив и его размер. Функция
 должна удалить из массива все простые числа и вернуть
 указатель на новый динамический массив.
 *
 * (Задание 2 не осмысленно на нецелых числах, поэтому не делаю шаблонами)
 */
bool isPrime(int n) {
	if (ABS(n) == 2)
		return true;
	if (!(n % 2))
		return false;
	for (int i = 3; i < ABS(n / 2); i += 2)
		if (!(n % i))
			return false;
	return true;
}

int* nonPrimes(int *ar, int size) {
	int *r { };
	r = createArray(r, size);
	int *ptr = r;
	for (int i = 0; i < size; i++)
		if (!isPrime(ar[i])) {
			*ptr = ar[i];
			ptr++;
		}
	deleteArray(ar);
	return r;
}

/*
 * Задание 3. Написать функцию, которая получает указатель
 на статический массив и его размер. Функция распреде-
 ляет положительные, отрицательные и нулевые элементы
 в отдельные динамические массивы.
 *(Я понял задание так, что надо распределить не сами элементы, а их индексы.
 *Иначе массив с нулями выглядит совсем бесполезным)
 */
template<typename T>
T** separateElements(T *ar, int size) {
	enum fields {
		Z, P, N
	};
	T **sep { };
	sep = createArray(sep, 3, size);
	T *z = sep[Z];
	T *p = sep[P];
	T *n = sep[N];
	for (int i = 0; i < size; i++) {
		if (ar[i] == 0) {
			*z = i;
			z++;
		} else if (ar[i] > 0) {
			*p = i;
			p++;
		} else {
			*n = i;
			n++;
		}
	}
	return sep;
}
