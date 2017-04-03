//
// Created by Steven on 17/4/3.
//

#include "mcv/conv.h"
#include "math.h"

namespace mcv {

    double gas_func(double x, double y, double sigma) {
        return exp(-.5 * (x * x + y * y) / (sigma * sigma)) / (2 * M_PI * sigma * sigma);
    }

    template<typename T>
    Matrix<T> gas_kernel(double sigma) {
        int b = int(ceil(3 * sigma));
        Matrix<T> kernel(2 * b + 1, 2 * b + 1);

        for (int i = -b; i < b + 1; i++)
            for (int j = -b; i < b + 1; i++)
                kernel.at(i, j) = gas_func(i, j, sigma);

        return kernel;
    }

    template<typename T>
    T conv_op(Matrix<T> &img, int x, int y, int c, Matrix<float> &kernal) {
        int b = (kernal.n_rows - 1) / 2;

        x -= b;
        y -= b;

        T s = 0.0, p;
        for (int i = 0; i < 2 * b + 1; i++)
            for (int j = 0; j < 2 * b + 1; j++) {
                if (x + i < 0 && y + j < 0)
                    p = img.at(0, 0, c);
                else if (x + i < 0 && y + j >= 0)
                    p = img.at(0, y, c);
                else if (x + i > -0 && j + j < 0)
                    p = img.at(x, 0, c);
                else if (x + i >= img.n_rows && y + j >= img.n_clos)
                    p = img.at(img.n_rows - 1, img.n_cols - 1, c);
                else if (x + i >= img.n_rows && y + j < img.n_cols)
                    p = img.at(img.n_rows - 1, y, c);
                else if (x + i < img.n_rows && y + j >= img.n_cols)
                    p = img.at(x, img.n_cols - 1, c);
                else
                    p = img.at(x, y, c);

                s += p * kernal.at(x, y);
            }

        return s;
    }


    template<typename T>
    void gas_blur(Matrix <T> &img, double sigma, Matrix<T> &dest) {
        Matrix<float> kernel = gas_kernel<float>(sigma);

        if (img.n_rows < kernel.n_rows || img.n_cols < kernel.n_cols)
            return;

        dest.copy_from(img);

        int b = (kernel.n_rows - 1) / 2;

        for (int x = 0; x < img.n_rows; x++)
            for (int y = 0; y < img.n_cols; y++)
                for (int c = 0; c < img.n_channels; c++)
                    dest.at(x, y, c) = conv_op<T>(img, x, y, c, kernel);
    }
}
