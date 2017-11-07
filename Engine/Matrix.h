#pragma once
#include <cstring>
#include <iostream>
#include <assert.h>



template <class T> class Matrix {
public:
	Matrix<T>(int _rows, int _cols);
	~Matrix<T>();
	void Fill(T val);
	void OutputContents() const;
	int GetRows() const;
	int GetCols() const;
	int GetSize() const;
	T RowSum(int row) const;
	void DotProduct(const Matrix<T>& mult, Matrix<T>& result) const;
	void DotBias(const Matrix<T>& mult, const Matrix<T>& bias, Matrix<T>& result) const;
	T& operator()(int row, int col);
	T& operator()(int row, int col)const;
	T& operator()(int i);
	T& operator()(int i)const;
	void operator=(Matrix<T>& m);
	Matrix<T>& operator=(T * arr);
private:
	T * data;
	int rows, cols, elements;

};
template <class T>
inline Matrix<T>::Matrix(int _rows, int _cols) {
	rows = _rows;
	cols = _cols;
	elements = _rows * _cols;
	data = new T[elements];
}

template<class T>
inline Matrix<T>::~Matrix() {
	delete[] data;
}

template<class T>
inline void Matrix<T>::Fill(T val) {
	for (int i = 0; i < elements; i++) {
		data[i] = val;
	}
}

template<class T>
inline void Matrix<T>::OutputContents() const {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << (*this)(i, j) << "  ";
		}
		std::cout << std::endl;
	}
}

template<class T>
inline int Matrix<T>::GetRows() const {
	return rows;
}

template<class T>
inline int Matrix<T>::GetCols() const {
	return cols;
}

template<class T>
inline int Matrix<T>::GetSize() const {
	return elements;
}

template<class T>
inline T Matrix<T>::RowSum(int row) const {
	T sum = 0;
	T * ptr = this->data + (row * cols);
	for (int i = 0; i < cols; i++) {
		sum += *(ptr + i);
	}
	return sum;
}

template<class T>
inline void Matrix<T>::DotProduct(const Matrix<T>& mult, Matrix<T>& result) const {
	assert(result.GetCols() == 1);
	assert(mult.GetCols() == 1);
	for (int i = 0; i < rows; i++) {
		result(i) = RowSum(i) * mult(i);
	}
}

template<class T>
inline void Matrix<T>::DotBias(const Matrix<T>& mult, const Matrix<T>& bias, Matrix<T>& result) const {
	assert(mult.GetCols() == 1);
	assert(bias.GetCols() == 1);
	assert(result.GetCols() == 1);
	for (int i = 0; i < rows; i++) {
		result(i) = RowSum(i) * mult(i) + bias(i);
	}
}

template<class T>
inline T & Matrix<T>::operator()(int row, int col) {
	return data[cols * row + col];
}

template<class T>
inline T & Matrix<T>::operator()(int row, int col) const {
	return data[cols * row + col];
}

template<class T>
inline T & Matrix<T>::operator()(int i) {
	return data[i];
}

template<class T>
inline T & Matrix<T>::operator()(int i) const {
	return data[i];
}

template<class T>
inline void Matrix<T>::operator=(Matrix<T>& m) {
	delete[] data;
	rows = m.rows;
	cols = m.cols;
	elements = m.elements;
	data = new T[elements];
	std::memcpy(data, m.data, sizeof(T) * elements);
}

template<class T>
inline Matrix<T>& Matrix<T>::operator=(T * arr) {
	//size of dynamic array must equal size of "data"
	std::memcpy(data, arr, sizeof(T) * elements);
	return *this;
}


