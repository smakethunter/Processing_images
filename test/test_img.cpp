//#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "improc.hpp"


#include <functional>
#include <string>
#include <map>







TEST(testProcessing,negativeTest){
//    operation data;

    std:: function<void(int, int, Image&)> filtr = filter;
    std:: function<void(int, int, Image&)> neg =negative;
    struct
    {
        std::string img_root = "/home/smaket/CLionProjects/Processing_images/imgs/";
        std::string input_filename ="lena.bmp" ;

        std::vector< std::string> output_filename;

    }OP;
    OP.output_filename.emplace_back("out_neg.bmp");


    Image image_array = load_bitmap(OP.img_root+OP.input_filename);
    std::map<int,std:: function<void(int, int, Image&)>> queue;
    queue[1] = neg;
    queue[2] = filtr;



        transform(image_array, queue.find(1)->second);
        ASSERT_EQ(118,0+image_array[0][0]);




}

TEST(testProcessing,filterTestisframe){
    std:: function<void(int, int, Image&)> filtr = filter;
    std:: function<void(int, int, Image&)> neg =negative;
    struct
    {
        std::string img_root = "/home/smaket/CLionProjects/Processing_images/imgs/";
        std::string input_filename ="lena.bmp" ;

        std::vector< std::string> output_filename;

    }OP;

    OP.output_filename.emplace_back("out_neg.bmp");
    OP.output_filename.emplace_back("out_filter.bmp");

    Image image_array = load_bitmap(OP.img_root+OP.input_filename);
    std::map<int,std:: function<void(int, int, Image&)>> queue;
    queue[1] = neg;
    queue[2] = filtr;
    OP.output_filename.emplace_back("out_filter.bmp");


    transform(image_array, queue.find(2)->second);
    ASSERT_EQ(0,0+image_array[0][0]);


}
TEST(testProcessing,filterTest){
    std:: function<void(int, int, Image&)> filtr = filter;
    std:: function<void(int, int, Image&)> neg =negative;
    struct
    {
        std::string img_root = "/home/smaket/CLionProjects/Processing_images/imgs/";
        std::string input_filename ="lena.bmp" ;

        std::vector< std::string> output_filename;

    }OP;

    OP.output_filename.emplace_back("out_neg.bmp");
    OP.output_filename.emplace_back("out_filter.bmp");

    Image image_array = load_bitmap(OP.img_root+OP.input_filename);
    std::map<int,std:: function<void(int, int, Image&)>> queue;
    queue[1] = neg;
    queue[2] = filtr;
    OP.output_filename.emplace_back("out_filter.bmp");


    transform(image_array, queue.find(2)->second);
    ASSERT_EQ(77,0+image_array[1][1]);


}
