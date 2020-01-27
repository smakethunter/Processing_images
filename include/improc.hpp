#ifndef IMAGE_PROCESSOR_IMPROC_HPP
#define IMAGE_PROCESSOR_IMPROC_HPP

#include "bitmap.h"

#include <string>
#include <utility>
#include <vector>
#include <cstring>
#include <iostream>
#include <list>
#include <memory>
#include <functional>

template <typename T>
class Matrix
{
    size_t h, w;
    std::vector < std::vector < T >> m;
public:
    Matrix(size_t X, size_t Y,T val) : w(X), h(Y){

        for(int i = 0; i < X; i++) {
            std::vector<T> v(Y);
            for (int j = 0; j < Y; j++)
                v[j] = val;
            m.push_back(v);
        }
    }
    std::vector<T>& operator[](size_t idx){return m[idx];}
    auto begin(){return m.begin();}
    auto size(){return m.size();}
    auto end(){return m.end();}
    size_t X() { return w; }
    size_t Y() { return h; }
};






using Mask = Matrix<double>;



class Image :public Matrix<byte>{
    BITMAPFILEHEADER header;
    BITMAPINFO* BitmapInfo;
public:

    Image(BITMAPFILEHEADER  head, BITMAPINFO* BMP_I, size_t x, size_t y) : Matrix<byte>(x, y, 0), header(head) {
            size_t bitmap_info_size = header.bfOffBits - sizeof(BITMAPFILEHEADER);
            BitmapInfo = (BITMAPINFO *) malloc(bitmap_info_size);
            std::memcpy(BitmapInfo, BMP_I, bitmap_info_size);}
//  Image(const Image&) = delete;

    BITMAPFILEHEADER give_header(){return header;}
    BITMAPINFO* give_Bmp_I() {return  BitmapInfo;}
    ~Image()
    {
        free(BitmapInfo);
    }
//Tu ma być konstruktor kopiujący

};

extern Image load_bitmap(const std::string &filename);

extern int save_bitmap(const std::string &filename, Image& image_array);


class FileIOError {

public:
    FileIOError( std::string  msg) : msg_(std::move(msg)) {}


    std::string getMessage() const {return(msg_);}
private:
    std::string msg_;
};





extern void filter(int i, int j, Image& img);

extern void negative (int i, int j, Image& pix);





extern Image& transform(Image& img, std::function<void(int, int, Image&)> fun);

extern Mask mask (size_t s);
#endif //IMAGE_PROCESSOR_IMPROC_HPP
