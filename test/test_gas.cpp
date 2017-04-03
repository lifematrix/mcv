//
// Created by Steven on 17/4/4.
//

#include <mcv/core.h>
#include <mcv/conv.h>

int main(int argc, char *argv[])
{
   mcv::Matrix<float> img(10, 10, 3), dest;
   for(int i=0; i < img.n_rows; i++)
      for(int j=0; j < img.n_cols; j++)
         for(int c=0; c < img.n_channels; c++)
             img.at(i, j, c) = 1.0;

   dest.copy_from(img);
   mcv::gas_blur(img, 1, dest);
}

