#include <iostream>
#include <iomanip>
#include "bitmap.h"
#include "steganography.h"

using namespace std;

int main(){
    bitmap::bitmap image;
    if(image.load_image("photo.bmp")){
        image.save_image("output.bmp");
        cout << "loaded successfully" << endl;
        for(int y = 0; y < image.height(); y++){
            cout << '|';
            for(int x = 0; x < image.width(); x++){
                bitmap::pixel temp_pixel = image[x][y];
                cout << setw(3) << (int)temp_pixel.r << ' ' << setw(3) << (int)temp_pixel.g << ' ' << setw(3) << (int)temp_pixel.b << '|';
            }
            cout << endl;
        }

        steganography::image_hider image_modifier;
        cout << "File can fit " << image_modifier.max_fit_size(image, 2) << " bytes" << endl;
        image_modifier.encrypt(image, "file.txt");
        
        cout << endl;
        for(int y = 0; y < image.height(); y++){
            cout << '|';
            for(int x = 0; x < image.width(); x++){
                bitmap::pixel temp_pixel = image[x][y];
                cout << setw(3) << (int)temp_pixel.r << ' ' << setw(3) << (int)temp_pixel.g << ' ' << setw(3) << (int)temp_pixel.b << '|';
            }
            cout << endl;
        }
    }else{
        cout << "load image failed" << endl;
    }
    return 0;
}