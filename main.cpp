#include <cstdlib>
#include <functional>
#include <string>
#include <map>


#include "improc.hpp"


std:: function<void(int, int, Image&)> neg =negative;
std:: function<void(int, int, Image&)> filtr = filter;
struct
{
    std::string img_root = "/home/smaket/CLionProjects/Processing_images/imgs/";
    std::string input_filename ="lena.bmp" ;
    std::string output_filename = "out.bmp";

}OP;
int main() {
//    operation data;
// to ma przyjmować pola struktury w nazwach
    Image image_array = load_bitmap(OP.img_root+OP.input_filename);
    std::map<int,std:: function<void(int, int, Image&)>> queue;
    queue[1] = neg;
    queue[2] = filtr;
    for (auto& i: queue)
    {
        transform(image_array, i.second);
    }
    save_bitmap(OP.img_root+OP.output_filename, image_array);

    return EXIT_SUCCESS;
}