//
// Created by Steven on 17/4/3.
//

#ifndef MCV_PYMCV_H
#define MCV_PYMCV_H

extern "C"
void c_gas_blur(float *img_data, size_t n_rows, size_t n_cols, size_t n_channels, float sigma, float *dest_data);

#endif //MCV_PYMCV_H
