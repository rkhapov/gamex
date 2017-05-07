#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>

#include "my_string.h"

namespace gamex
{
    template <typename T>
    class Matrix
    {
    public:
        Matrix(int n, int m);
        Matrix(const Matrix<T>& matrix);
        virtual ~Matrix();

        std::pair<int, int> getSize() const;
        void resize(int n, int m);

        T& get(int i, int j);
        const T& get(int i, int j) const;

        void set(int i, int j, const T& val);

        Matrix<T>& operator =(const Matrix<T>& matrix);

    private:
        T **_matrix;
        int _n;
        int _m;

        void _copyFrom(const Matrix<T>& matrix);
        void _allocateMemory(int n, int m);
        void _freeMemory();
        void _checkIndexes(int i, int j) const;
    };


    template <typename T>
    Matrix<T>::Matrix(int n, int m)
    {
        _matrix = nullptr;
        _allocateMemory(n, m);
    }

    template <typename T>
    Matrix<T>::Matrix(const Matrix<T> &matrix)
    {
        _matrix = nullptr;
        _copyFrom(matrix);
    }

    template <typename T>
    Matrix<T>::~Matrix()
    {
        _freeMemory();
    }

    template <typename T>
    std::pair<int, int> Matrix<T>::getSize() const
    {
        return std::make_pair(_n, _m);
    }

    template <typename T>
    void Matrix<T>::resize(int n, int m)
    {
        Matrix<T> buffer = *this;
        _freeMemory();
        _allocateMemory(n, m);

        for (int i = 0;
             i < std::min(buffer.getSize().first, _n);
             i++)
        {
            for (int j = 0;
                 j < std::min(buffer.getSize().second, _m);
                 j++)
            {
                this->_matrix[i][j] = buffer._matrix[i][j];
            }
        }
    }

    template <typename T>
    T& Matrix<T>::get(int i, int j)
    {
        _checkIndexes(i, j);
        return _matrix[i][j];
    }

    template <typename T>
    const T& Matrix<T>::get(int i, int j) const
    {
        _checkIndexes(i, j);
        return _matrix[i][j];
    }

    template <typename T>
    void Matrix<T>::set(int i, int j, const T &val)
    {
        _checkIndexes(i, j);
        _matrix[i][j] = val;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator =(const Matrix<T>& matrix)
    {
        if (this != &matrix)
            _copyFrom(matrix);
        return *this;
    }

    template <typename T>
    void Matrix<T>::_allocateMemory(int n, int m)
    {
        _matrix = new T*[n];

        for (int i = 0; i < n; i++)
        {
            _matrix[i] = new T[m];
        }

        _n = n;
        _m = m;
    }

    template <typename T>
    void Matrix<T>::_freeMemory()
    {
        for (int i = 0; i < _n; i++)
            delete[] _matrix[i];

        delete[] _matrix;

        _n = _m = 0;
        _matrix = nullptr;
    }

    template <typename T>
    void Matrix<T>::_checkIndexes(int i, int j) const
    {
        if (i < 0 || i >= _n ||
            j < 0 || j >= _m)
        {
            std::string format = "Matrix index [%d, %d] out of range [0..%d, 0..%d]";
            std::string errMsg = constructMessage(format.c_str(), i, j, _n - 1, _m - 1);
            throw std::out_of_range(errMsg);
        }
    }

    template <typename T>
    void Matrix<T>::_copyFrom(const Matrix<T>& matrix)
    {
        if (_matrix != nullptr)
            _freeMemory();

        _allocateMemory(matrix._n, matrix._m);

        for (int i = 0; i < _n; i++)
        {
            for (int j = 0; j < _m; j++)
            {
                _matrix[i][j] = matrix._matrix[i][j];
            }
        }
    }
}
#endif // MATRIX_H
