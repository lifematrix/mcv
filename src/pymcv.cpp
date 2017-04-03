//
// Created by Steven on 17/4/3.
//

#include <mcv/core.h>
#include <mcv/conv.h>
#include <mcv/pymcv.h>

#include <stdio.h>

void c_gas_blur(float *img_data, size_t n_rows, size_t n_cols, size_t n_channels, float sigma, float *dest_data) {
    mcv::Matrix<float> orig_img, dest_img;
    printf("%p, %p\n", dest_img.data, dest_data); fflush(stdout);

    orig_img.assign(n_rows, n_cols, n_channels, img_data);
    dest_img.assign(n_rows, n_cols, n_channels, dest_data);

    printf("data: %p, %p\n", dest_img.data, dest_data); fflush(stdout);
    printf("matrix: %p, %p\n", &orig_img, &dest_img); fflush(stdout);

    mcv::gas_blur(orig_img, (double) sigma, dest_img);

    printf("matrix: %p, %p\n", &orig_img, &dest_img); fflush(stdout);
    printf("[0,0]: %10.8f\n", dest_img.at(0,0)); fflush(stdout);
    printf("[0,0]: %10.8f\n", dest_data[0]); fflush(stdout);

    printf("%p, %p\n", dest_img.data, dest_data);

}
