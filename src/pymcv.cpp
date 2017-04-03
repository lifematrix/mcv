//
// Created by Steven on 17/4/3.
//

#include <mcv/core.h>
#include <mcv/conv.h>
#include <mcv/pymcv.h>

#include <stdio.h>

void c_gas_blur(float *img_data, size_t n_rows, size_t n_cols, size_t n_channels, float sigma, float *dest_data) {
    mcv::Matrix<float> orig_img, dest_img;
    orig_img.assign(n_rows, n_cols, n_channels, img_data);
    dest_img.assign(n_rows, n_cols, n_channels, dest_data);
    mcv::gas_blur(orig_img, (double) sigma, dest_img);
}
