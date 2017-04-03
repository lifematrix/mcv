//
// Created by Steven on 17/4/3.
//

#ifndef MCV_CORE_H
#define MCV_CORE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

namespace  mcv {
    template<typename T>
    struct Matrix {
        int n_rows;
        int n_cols;
        int n_channels;
        int n_size;
        T *data;
        bool is_alloc;

    public:
        Matrix() {
            n_rows = 0;
            n_cols = 0;
            n_channels = 0;
            n_size = 0;
            data = NULL;
            is_alloc = false;

        }

        Matrix(int _rows, int _cols, int _channels = 1) {
            set_size(_rows, _cols, _channels);
            allocate();
        }

        ~Matrix() {
            if (this->data != NULL && is_alloc ) {
                free(this->data);
                this->data = NULL;
            }
        }

        void set_size(int _rows, int _cols, int _channels) {
            n_rows = _rows;
            n_cols = _cols;
            n_channels = _channels;

            n_size = this->n_rows * this->n_cols * this->n_channels;
        }

        void allocate() {
            if (this->data != NULL && is_alloc)
                free(this->data);
            if (n_size > 0) {
                this->data = (T *) malloc(n_size * sizeof(T));
                is_alloc = true;
            }
        }

        void copy_from(Matrix<T>& src) {
            set_size(src.n_rows, src.n_cols, src.n_channels);
            allocate();
            memcpy(data, src.data, n_size*sizeof(T));
        }

        void assign(int _rows, int _cols, int _channels, T * _data) {
            set_size(_rows, _cols, _channels);
            this->data = _data;
        }

        // inline const T &operator[](size_t x, size_t y, size_t c)
        inline T& at(int x, int y, int c) {
            if(x == -1)
                x = n_rows -1;
            if(y == -1)
                y = n_cols - 1;
            if(c == -1)
                c = n_channels - 1;

            int index = x * n_cols * n_channels + y * n_channels + c;

            return data[index];
        }

        inline T& at(int x, int y) {
            // int index = x * n_cols + y;
            // assert(index < n_size);
            // return data[index];
            return at(x, y, 0);
        }

    };
}
#endif //MCV_MCV_CORE_H
