#include <cstdlib>
#include <functional>
#include <string>
#include <map>

#include "bitmap.h"
#include "improc.hpp"

int main() {
    try {
    std::string img_root = "/home/smaket/CLionProjects/img_proc/imgs/";

    std::string input_filename = img_root + "7x7.bmp";
    BITMAPINFO* bitmap_info = nullptr;

        Image image_array = load_bitmap(input_filename, &bitmap_info);
        save_bitmap(img_root + "out.bmp", image_array, bitmap_info);
        if (bitmap_info) {
            free(bitmap_info);
        }
    }
    catch(FileIOError &e) {
        std::cout<<e.getMessage();


    }

//
//    // Czyszczenie.
//
//




//    typedef struct{
//    std::string input_root;
//    std::function<Image(Image&)> function_to_call;
//    std::string output_root;
//    } OPERATION;
//
//    std::map<std::string,OPERATION> queue;
//    OPERATION info,info2;
//    info.function_to_call=img_to_neg;
//    info2.function_to_call=filter_image;
//    info.input_root=input_filename;
//    info.output_root=img_root + "out1.bmp";
//    info2.input_root=input_filename;
//    info2.output_root=img_root + "out2.bmp";
//
//    queue.insert(std::make_pair("first",info));
//    queue.insert(std::make_pair("second",info2));
//    BITMAPINFO* bitmap_info1 = nullptr;
//    Image img1=load_bitmap(queue["first"].input_root,&bitmap_info1);
//    Image img1_out=queue["first"].function_to_call(img1);
//    save_bitmap(queue["first"].output_root,img1_out,bitmap_info1);
//
//
//
//    BITMAPINFO* bitmap_info2 = nullptr;
//    Image img2=load_bitmap(queue["second"].input_root,&bitmap_info2);
//    Image img2_out=queue["second"].function_to_call(img2);
//    save_bitmap(queue["second"].output_root,img2_out,bitmap_info2);
//
//    //int h = bitmap_info->bmiHeader.biHeight;
//
//
////    if (image_array.size()) {
////        for (int i = 0; i < h; i++) {
////            free(image_array[i]);
////        }
////
////        free(image_array);
////        image_array = nullptr;
////    }
////
////    if (bitmap_info) {
////        free(bitmap_info);
////    }

    return 0;
}
