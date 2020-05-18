#include <fstream>
#include <vector>
#include "bitmap.h"
#include "steganography.h"

steganography::image_hider::image_hider(){
    err_file.open("steganography.txt", std::ios_base::out);
}

steganography::image_hider::~image_hider(){
    err_file.close();
}

unsigned steganography::image_hider::max_fit_size(bitmap::bitmap& bitmap_image, unsigned bits_to_use){
    if(bits_to_use > 8 || bits_to_use <= 0){
        return 0;
    }
    return bitmap_image.width() * bitmap_image.height() * sizeof(bitmap::pixel) / 4;
}

void steganography::image_hider::encrypt(bitmap::bitmap& bitmap_image, const char* to_encrypt, unsigned bits_to_use){
    std::ifstream input_file(to_encrypt, std::ios_base::in | std::ios_base::binary);
    bitmap::bitmap output_image(bitmap_image);

    input_file.seekg(0, std::ios_base::end);

    unsigned to_encrypt_file_size = input_file.tellg();
    if(max_fit_size(bitmap_image, bits_to_use) < to_encrypt_file_size){
        err_file << "Image cannot fit file";
        input_file.close();
        return;
    }
    input_file.seekg(0, std::ios_base::beg);
    char* to_encrypt_data = new char[to_encrypt_file_size];
    input_file.read(to_encrypt_data, to_encrypt_file_size);
    
    unsigned cur_byte = 0;
    unsigned cur_bit = 0;
    for(int row = 0; row < bitmap_image.height(); row++){
        for(int column = 0; column < bitmap_image.width(); column++){
            bitmap::pixel* cur_pixel = &bitmap_image[column][row];
            char bits;
            for(int i = 0; i < 3; i++){
                if(cur_bit + bits_to_use > 8){

                //bits = 
                }else if(cur_bit + bits_to_use == 8){
                    bits = (to_encrypt_data[cur_byte] << cur_bit) >> (8 - bits_to_use);
                    cur_byte++;
                    cur_bit = 0;
                }else{
                    bits = (to_encrypt_data[cur_byte] << cur_bit) >> (8 - bits_to_use);
                }
                *((unsigned char*)cur_pixel+i) = (*((unsigned char*)cur_pixel+i) & (255 << bits_to_use)) | bits;
                if(cur_byte > to_encrypt_file_size)
                    goto output;
            }
        }
    }
    output:

    input_file.close();
}

void steganography::image_hider::decrypt(bitmap::bitmap& bitmap_image, const char* output_file, unsigned bits_to_use){

}