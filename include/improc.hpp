#ifndef IMAGE_PROCESSOR_IMPROC_HPP
#define IMAGE_PROCESSOR_IMPROC_HPP

#include "bitmap.h"

#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <list>


template <typename T>
class Vector {
public:

    Vector(const Vector&) = default;

    std::size_t size() const { return v_.size(); }



    const T& operator[](std::size_t pos) const { return v_[pos]; }

    T& operator[](std::size_t pos) { return v_[pos]; }

    typename std::vector<T>::const_iterator cbegin() const { return v_.cbegin(); }

    typename std::vector<T>::const_iterator cend() const { return v_.cend(); }

    typename std::vector<T>::iterator begin() { return v_.begin(); }

    typename std::vector<T>::const_iterator begin() const { return v_.cbegin(); }

    typename std::vector<T>::iterator end() { return v_.end(); }

    typename std::vector<T>::const_iterator end() const { return v_.cend(); }


private:
    std::vector<T> v_;
};


template <typename T>
class Matrix {
public:
    explicit  Matrix<T>():matrix_(){}
    Matrix(int h,int w, byte v);


    Vector<T>& operator[](std::size_t pos) { return matrix_[pos]; }

    typename std::vector<Vector<T>>::const_iterator cbegin() const { return matrix_.cbegin(); }

    typename std::vector<Vector<T>>::const_iterator cend() const { return matrix_.cend(); }

    typename std::vector<Vector<T>>::iterator begin() { return matrix_.begin(); }

    typename std::vector<Vector<T>>::const_iterator begin() const { return matrix_.cbegin(); }

    typename std::vector<Vector<T>>::iterator end() { return matrix_.end(); }

    typename std::vector<Vector<T>>::const_iterator end() const { return matrix_.cend(); }

    virtual int size () const {return  matrix_.size();}

    std::vector<Vector<T>> matrix_;
};


template<typename T>
Matrix<T>::Matrix(int h,int w, byte v) {
    for (int i=0;i<h;h++){
        for(int j=0;j<w;j++){
            matrix_[i][j]=v;
        }
    }
}





template class Matrix<byte>;

class Image :public Matrix<byte>{

public:
    Image()=default;
    Image(BITMAPFILEHEADER,BITMAPINFO*);
    Image(int h,int w,byte v,BITMAPFILEHEADER bh,BITMAPINFO* bmi);
    int size() const override { return matrix_.size();}

private:

    BITMAPFILEHEADER file_header;
    BITMAPINFO* bitmap_info;
};
class FileIOError {

public:
    FileIOError( const std::string& msg) : msg_(msg) {}
    ~FileIOError() {}

    std::string getMessage() const {return(msg_);}
private:
    std::string msg_;
};

extern Image load_bitmap(const std::string &filename, BITMAPINFO **BitmapInfo);

extern int save_bitmap(const std::string &filename, Image image_array, BITMAPINFO *BitmapInfo);

extern Image transform_image(Image& image,std::function<double(double)>);
std::function<double (double)> negative=[](double x){return 255-x;};
using Mask=Matrix<double>;
extern Image img_to_neg(Image&);
Mask GenerateMask(int);
 Image filter_image(Image& image);
std::function<Image(Image&)> filter=filter_image;
std::function<Image(Image&)> transform=img_to_neg;

#endif //IMAGE_PROCESSOR_IMPROC_HPP
