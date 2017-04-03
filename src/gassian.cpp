//
// Created by Steven on 17/4/3.
//

#include "mcv/conv.h"
#include <math.h>
#include <stdio.h>

namespace mcv {

    double gas_func(double x, double y, double sigma) {
        return exp(-.5 * (x*x + y*y) /(sigma*sigma)) / (2*M_PI*sigma*sigma);
    }

    template<typename T>
    Matrix<T> gas_kernel(double sigma) {
        int b = int(ceil(3 * sigma));
        Matrix<T> kernel(2 * b + 1, 2 * b + 1);

        printf("kernel: %d\n", kernel.n_rows); fflush(stdout);
        for (int i = -b; i < b + 1; i++)
            for (int j = -b; j < b + 1; j++)
                kernel.at(i+b, j+b) = gas_func(i, j, sigma);

        return kernel;
    }

    template<typename T>
    T conv_op(Matrix<T> &img, int x, int y, int c, Matrix<float> &kernel) {
        int b = (kernel.n_rows - 1) / 2;
        x -= b; y -= b;

        T s = 0.0, p;
        for (int i = 0; i < 2 * b + 1; i++) {
            for (int j = 0; j < 2 * b + 1; j++) {
                if (x + i < 0 && y + j < 0)
                    p = img.at(0, 0, c);
                else if (x + i < 0 && y + j >= 0)
                    p = img.at(0, y, c);
                else if (x + i > 0 && j + j < 0)
                    p = img.at(x, 0, c);
                else if (x + i >= img.n_rows && y + j >= img.n_cols)
                    p = img.at(-1, -1, c);
                else if (x + i >= img.n_rows && y + j < img.n_cols)
                    p = img.at(-1, y, c);
                else if (x + i < img.n_rows && y + j >= img.n_cols)
                    p = img.at(x, -1, c);
                else
                    p = img.at(x+i, y+j, c);

                // printf("p: %10.8f\n", p); fflush(stdout);
                s += p * kernel.at(i, j);
            }
        }

        // printf("%10.8f\n", s); fflush(stdout);
        return s;
    }


    void gas_blur(Matrix <float> &img, float sigma, Matrix<float> &dest) {
        Matrix<float> kernel = gas_kernel<float>(sigma);

        if (img.n_rows < kernel.n_rows || img.n_cols < kernel.n_cols)
            return;

        int b = (kernel.n_rows - 1) / 2;
        // printf("b: %d\n", b); fflush(stdout);

        printf("(%d, %d, %d)\n", img.n_rows, img.n_cols, img.n_channels); fflush(stdout);
        for (int x = 0; x < img.n_rows; x++)
            for (int y = 0; y < img.n_cols; y++)
                for (int c = 0; c < img.n_channels; c++)
                    dest.at(x, y, c) = conv_op<float>(img, x, y, c, kernel);
    }
}
