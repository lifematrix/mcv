//
// Created by Steven on 17/4/3.
//

#ifndef MCV_CORE_H
#define MCV_CORE_H

#include <stdlib.h>

namespace  mcv {
    template<typename T>
    struct Matrix {
        int n_rows;
        int n_cols;
        int n_channels;
        int n_size;
        T *data;

    public:
        Matrix() {
            n_rows = 0;
            n_cols = 0;
            n_channels = 0;
            n_size = 0;
            data = NULL;
        }

        Matrix(int n_rows, int n_cols, int n_channels = 1) {
            set_size(n_rows, n_cols, n_channels);
            allocate();
        }

        ~Matrix() {
            if (this->data != NULL) {
                free(this->data);
                this->data = NULL;
            }
        }

        void set_size(int n_rows, int n_cols, int n_channels) {
            n_rows = n_rows;
            n_cols = n_cols;
            n_channels = n_channels;

            n_size = this->n_rows * this->n_cols * this->n_channels;
        }

        void allocate() {
            if (this->data != NULL) {
                free(this->data);
                this->data = malloc(n_size * sizeof(T));
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
        inline const T& at(size_t x, size_t y, size_t c) {
            int index = n_channels * (x * this->n_cols + y) + c;
            return &data[index];
        }

        inline const T& at(size_t x, size_t y) {
            int index = x * this->n_cols + y;
            return &data[index];
        }

    };
}
#endif //MCV_MCV_CORE_H
