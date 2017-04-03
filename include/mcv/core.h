//
// Created by Steven on 17/4/3.
//

#ifndef MCV_CORE_H
#define MCV_CORE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

        Matrix(int rows, int cols, int channels = 1) {
            set_size(rows, cols, channels);
            allocate();
        }

        ~Matrix() {
            if (this->data != NULL && is_alloc ) {
                free(this->data);
                this->data = NULL;
            }
        }

        void set_size(int rows, int cols, int channels) {
            n_rows = rows;
            n_cols = cols;
            n_channels = channels;

            n_size = this->n_rows * this->n_cols * this->n_channels;
            printf("size: %d\n", n_size); fflush(stdout);
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

        void assign(int n_rows, int n_cols, int n_channels, T *data) {
            set_size(n_rows, n_cols, n_channels);
            this->data = data;
        }

        // inline const T &operator[](size_t x, size_t y, size_t c)
        inline T* at(size_t x, size_t y, size_t c) {
            int index = n_channels * (x * this->n_cols + y) + c;
            return data+index;
        }

        inline T* at(size_t x, size_t y) {
            int index = x * this->n_cols + y;
            return data+index;
        }

    };
}
#endif //MCV_MCV_CORE_H
