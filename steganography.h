/*
This file declares the namespace and classes that deal with encrypting & decrypting files
Written by Dallas Hart
Copyright May 15 2020
*/

#include <fstream>
#include "bitmap.h"

namespace steganography{
    class image_hider{
        private:
            std::ofstream err_file;
        public:
            image_hider();
            ~image_hider();
            unsigned max_fit_size(bitmap::bitmap&, unsigned = 2);
            void encrypt(bitmap::bitmap&, const char*, unsigned = 2);
            void decrypt(bitmap::bitmap&, const char*, unsigned = 2);
    };
}