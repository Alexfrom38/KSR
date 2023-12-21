#pragma once

#include<iostream>
#include<vector>

template<class T>
class TSquareMatrix
{
protected:
	T a = 0, b = 0, c = 0, d = 0;
	T determinant = 0;
public:
	TSquareMatrix() ;
	TSquareMatrix(T _a, T _b, T _c, T _d) : a(_a), b(_b), c(_c), d(_d), determinant(_a* _d - _b * _c)
	{
	};
	TSquareMatrix(const TSquareMatrix<T>& matrix) : a(matrix.a), b(matrix.b), c(matrix.c), d(matrix.d), determinant(matrix.determinant)
	{
	};
	void print();
	void fill(T _a, T _b, T _c, T _d);
	T& operator [](size_t index);
	TSquareMatrix<T> operator + (const TSquareMatrix<T>& matrix);
	TSquareMatrix<T> operator - (const TSquareMatrix<T>& matrix);
	TSquareMatrix<T> operator * (const TSquareMatrix<T>& matrix);
	TSquareMatrix<T> operator * (T constant);
	std::vector<T> operator * (const std::vector<T>& vector);
	TSquareMatrix<T> operator = (const TSquareMatrix<T>& matrix);
	TSquareMatrix<T> GetReverseMatrix();
	T GetDet();
	~TSquareMatrix() = default;
};

template<class T>
inline TSquareMatrix<T>::TSquareMatrix()
{
}

template<class T>
inline void TSquareMatrix<T>::print()
{
	std::cout << a << ' ' << b << ' ' << c << ' ' << d << std::endl;
}

template<class T>
inline void TSquareMatrix<T>::fill(T _a, T _b, T _c, T _d)
{
	a = _a;
	b = _b;
	c = _c;
	d = _d;
	determinant = a * d - b * c;
}

template<class T>
inline T& TSquareMatrix<T>::operator[](size_t index)
{
	if (index < 0 || index > 4) throw "out of the range";
	else
		switch (index)
		{
		case 0:
			return a;
			break;
		case 1:
			return b;
			break;
		case 2:
			return c;
			break;
		case 3:
			return d;
			break;

		default:
			throw "Bad";
			break;
		}
	return (-1)*99999;
}

template<class T>
inline TSquareMatrix<T> TSquareMatrix<T>::operator+(const TSquareMatrix<T>& matrix)
{
	TSquareMatrix<T> result(*this);
	result.a = result.a + matrix.a;
	result.b = result.b + matrix.b;
	result.c = result.c + matrix.c;
	result.d = result.d + matrix.d;
	result.determinant = result.GetDet();
	return result;
}

template<class T>
inline TSquareMatrix<T> TSquareMatrix<T>::operator-(const TSquareMatrix<T>& matrix)
{
	TSquareMatrix<T> result(*this);
	result.a = result.a - matrix.a;
	result.b = result.b - matrix.b;
	result.c = result.c - matrix.c;
	result.d = result.d - matrix.d;
	result.determinant = result.GetDet();
	return result;
}

template<class T>
inline TSquareMatrix<T> TSquareMatrix<T>::operator*(const TSquareMatrix<T>& matrix)
{
	TSquareMatrix<T> result(*this);
	result.a = (*this).a * matrix.a + (*this).b * matrix.c;
	result.b = (*this).a * matrix.b + (*this).b * matrix.d;
	result.c = (*this).c * matrix.a + (*this).d * matrix.c;
	result.d = (*this).c * matrix.b + (*this).d * matrix.d;
	result.determinant = result.GetDet();
	return result;
}

template<class T>
inline TSquareMatrix<T> TSquareMatrix<T>::operator*(T constant)
{

	TSquareMatrix<T> result(*this);
	result.a = result.a * constant;
	result.b = result.b * constant;
	result.c = result.c * constant;
	result.d = result.d * constant;
	result.determinant = result.determinant * (constant * constant);
	return result;
}

template<class T>
inline std::vector<T> TSquareMatrix<T>::operator*(const std::vector<T>& vector)
{
	std::vector<T> result;
	if (vector.size() != 2)	throw "invalid size";
	else
	{
		double r_a = 0, s_b = 0;
		r_a = a * vector[0] + b * vector[1];
		s_b = c * vector[0] + d * vector[1];
		
		result.push_back(r_a);
		result.push_back(s_b);
	}
	return result;
		
}

template<class T>
inline TSquareMatrix<T> TSquareMatrix<T>::operator=(const TSquareMatrix<T>& matrix)
{
	TSquareMatrix<T> result(*this);
	a = matrix.a;
	b = matrix.b;
	c = matrix.c;
	d = matrix.d;
	determinant = matrix.determinant;
	return(*this);
}

template<class T>
inline TSquareMatrix<T> TSquareMatrix<T>::GetReverseMatrix()
{
	TSquareMatrix<T> result(*this);
	result.fill(d, -b, -c, a);
	result = result * (1.0 / determinant);
	return result;

}

template<class T>
inline T TSquareMatrix<T>::GetDet()
{
	return a * d - b * c;
}
