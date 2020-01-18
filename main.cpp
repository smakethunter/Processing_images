#include <cstdlib>
#include <functional>
#include <string>
#include <map>

#include "bitmap.h"
#include "improc.hpp"

int main() {
    std::string img_root = "imgs/";

    std::string input_filename = img_root + "lena.bmp";
    BITMAPINFO* bitmap_info = nullptr;
    Image image_array = load_bitmap(input_filename, &bitmap_info);
    save_bitmap(img_root + "out.bmp", image_array, bitmap_info);

    // Czyszczenie.

    typedef struct{
    std::string input_root;
    std::function<Image(Image&)> function_to_call;
    std::string output_root;
    } OPERATION;

    std::map<std::string,OPERATION> queue;
    OPERATION info,info2;
    info.function_to_call=transform;
    info2.function_to_call=filter;
    info.input_root=input_filename;
    info.output_root=img_root + "out.bmp";
    info2.input_root=input_filename;
    info2.output_root=img_root + "out2.bmp";

    queue.insert(std::make_pair("first",info));
    queue.insert(std::make_pair("second",info2));


    //int h = bitmap_info->bmiHeader.biHeight;


//    if (image_array.size()) {
//        for (int i = 0; i < h; i++) {
//            free(image_array[i]);
//        }
//
//        free(image_array);
//        image_array = nullptr;
//    }
//
//    if (bitmap_info) {
//        free(bitmap_info);
//    }

    return EXIT_SUCCESS;
}
