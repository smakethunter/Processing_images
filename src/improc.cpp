#include "improc.hpp"
#include "bitmap.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <functional>
#include <math.h>
Image load_bitmap(const std::string& filename, BITMAPINFO **BitmapInfo)
{

        BITMAPFILEHEADER header;
        byte *bitmapBytes = LoadDIBitmap(filename.c_str(), BitmapInfo, &header);

        if (!bitmapBytes) {
            // Błąd podczas odczytu danych z pliku.

            throw

                    std::runtime_error(("blad odczytu pliku"));
        }

        else{
            auto h = (size_t) (*BitmapInfo)->bmiHeader.biHeight;
            auto w = (size_t) (*BitmapInfo)->bmiHeader.biWidth;
            int bits_per_pixel = (*BitmapInfo)->bmiHeader.biBitCount;

            /* see: https://en.wikipedia.org/wiki/BMP_file_format#Pixel_storage */
            size_t row_size = (bits_per_pixel * w + 31) / 32 * 4;

            printf("Successfully loaded a %lux%lu image - %s.\n\n", h, w, filename.c_str());

            Image image_array = Image(h,w,row_size,header,*BitmapInfo);


            byte* reader = bitmapBytes;

            // The order of the pixels in BMP file is as follows: from left to right, from bottom to top (first pixel is from
            // lower left corner of the picture).
            for (size_t i = 0; i < h; ++i) {
                for (size_t j = 0; j < w; ++j) {
                    image_array[h - i - 1][j] = *reader++;
                }

                reader += row_size - w;
            }
            free(reader);
            free(bitmapBytes);

            return image_array;
        }
}

int save_bitmap(const std::string& filename, Image image_array, BITMAPINFO* BitmapInfo)
{
    const size_t h = BitmapInfo->bmiHeader.biWidth;
    const size_t w = BitmapInfo->bmiHeader.biHeight;
    const int bits_per_pixel = BitmapInfo->bmiHeader.biBitCount;
    const size_t row_size = (bits_per_pixel * w + 31) / 32 * 4;

    byte* bitmapBytes = new byte[BitmapInfo->bmiHeader.biSizeImage];
    byte* writer = bitmapBytes;

    const size_t padding = row_size - w;

    for (size_t i = 0; i < h; ++i) {

        /* Przepisz wartosci pikseli wiersza obrazu. */
        for (size_t j = 0; j < w; j++) {
            *writer++ = image_array[h - i - 1][j];
        }

        /* Ustaw bajty wyrownania. */
        for (size_t j = 0; j < padding; j++) {
            *writer++ = 0;
        }
    }

    int status = SaveDIBitmap(filename.c_str(), BitmapInfo, bitmapBytes);
    delete[] bitmapBytes;

    return status;
}



Image::Image(int h, int w, byte v, BITMAPFILEHEADER bh, BITMAPINFO *bmi):Matrix<byte>(w,h,v) {
    size_t bitmap_info_size = bh.bfOffBits - sizeof(BITMAPFILEHEADER);
    auto* bitmap_i = (BITMAPINFO *) malloc(bitmap_info_size);
    std::memcpy(bitmap_i, bmi, bitmap_info_size);
    file_header=bh;
    bitmap_info=bitmap_i;

}


std::function<double(double)> negative = [](double x){return 255-x;};
Image transform_image(Image& image,std::function<double(double)>& f){

    for(auto& i:image){
        for(auto& j: i){
            j=f(j);
        }
    }
    return image;
}
Mask GenerateMask(int size){
    return Mask(size,size,1/std::pow(size,2));

}
std::function<Image(Image&)>  img_to_neg=[](Image& img){
    return transform_image(img,negative);
};
std::function<Image(Image&)> filter_image=[](Image& image){
int k=(image.size()-1)/2;
Mask mask=GenerateMask(3);
Image output_image;
    for(int y=0;y<image.size();y++){
        for(int x=0;x<image.size();x++){
            for(int i=-k;i<=k;i++){
                for(int j=-k;j<=k;j++){
                    if (y+1<image.size() && x+1<image.size()) {
                        output_image[y][x] += image[y + i][x + j] * mask[i + k][j + k];
                    }
                    else{
                        output_image[y][x]=0;
                    }
                    }
            }
            }
    }
    return output_image;
};
