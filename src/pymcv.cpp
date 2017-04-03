//
// Created by Steven on 17/4/3.
//

#include <mcv/core.h>
#include <mcv/conv.h>

using namespace mcv;

void c_gas_blur(float *img_data, size_t n_rows, size_t n_cols, size_t n_channels, float sigma, float *dest_data)
{
    Matrix<float> orig_img, dest_img;
    orig_img.assign(n_rows, n_cols, n_channels, img_data);
    dest_img.assign(n_rows, n_cols, n_channels, dest_data);
    gas_blur<float>(orig_img, (double)sigma, dest_img);
}

