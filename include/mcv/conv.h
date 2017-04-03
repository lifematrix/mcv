//
// Created by Steven on 17/4/3.
//

#ifndef MCV_CONV_H
#define MCV_CONV_H

#include <mcv/core.h>

namespace mcv {
    double gas_func(double x, double y, double sigma);

    template<typename T>
    Matrix<T> gas_kernel(double sigma);


    template<typename T>
    T conv_op(Matrix<T> &img, int x, int y, int c, Matrix<float> &kernal);

    template<typename T>
    void gas_blur(Matrix <T> &img, double sigma, Matrix<T> &dest);
}

#endif //MCV_CONV_H
