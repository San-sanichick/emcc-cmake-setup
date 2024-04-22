#pragma once

#include <iostream>
#include <array>
#include "debug.hpp"
#include <Logger.h>


namespace math
{
    template<int R, int C, typename T>
    struct Matrix
    {
    private:
        std::array<T, R * C> matrix;

    public:
        Matrix()
        {
            for (size_t i = 0; i < R * C; i++)
            {
                this->matrix[i] = 0;
            }
        }
        
        Matrix(const Matrix& o)
        {
            this->matrix = o.matrix;
        }
        
        // Matrix(Matrix&& o)
        // {
            
        // }
        
        ~Matrix()
        {
            LogInfo << "Destroyed\n";        
        }

        T get(size_t i, size_t j)
        {
            return this->matrix[R * i + j];
        }

        void set(size_t i, size_t j, T val)
        {
            CORE_ASSERT(i < R, "Too many rows");
            CORE_ASSERT(j < C, "Too many columns");
            this->matrix[R * i + j] = val;
        }


        inline friend std::ostream& operator<<(std::ostream& out, const Matrix<R, C, T>& o)
        {
            for (size_t i = 0; i < R; i++)
            {
                for (size_t j = 0; j < C; j++)
                {
                    out << o.matrix[R * i + j] << ' ';
                }
                out << std::endl;
            }
            return out;
        }
    };
}