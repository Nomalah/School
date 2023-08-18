#include <iostream>
#include <iomanip>
#include "bitmap.h"
#include "steganography.h"

using namespace std;

char hex(unsigned char nibble){
    switch(nibble & 15){
        case 0 ... 9:
            return (nibble & 15) + '0';
        case 10 ... 15:
            return (nibble & 15) + 'A' - 10;
    }
}

string hex(pixel24 pixel){
    string output = "";
    for(int i = 2; i >= 0; i--){
        unsigned char byte = *((unsigned char*)&pixel + i);
        output += hex(byte >> 4);
        output += hex(byte);
    }
    return output;
}

int main(){
    //bitmap image;

    bitmap test = bitmap(10, 10);

    for(int y = 0; y < test.height(); y++){
        cout << '|';
        for(int x = 0; x < test.width(); x++){
            test[x][y].red = (x + y) * 10;
            test[x][y].green = (x + test.height() - y - 1) * 10;
            test[x][y].blue = (test.width() - x + y - 1) * 10;
            //test[x][y] = {0, 0, 255};
            cout << hex(test[x][y]);
            cout << '|';
        }
        cout << endl;
    }

    test.save_image("test.bmp");
    bitmap image;
    if(image.load_image("photo.bmp")){
        image.save_image("output.bmp");
        cout << "loaded successfully" << endl;
        cout << std::dec << max_fit_size(image, 2) << endl;

        //steganography::image_hider image_modifier;
        //cout << "File can fit " << image_modifier.max_fit_size(image) << " bytes" << endl;
        //image_modifier.encrypt(image, "file.txt");
        
    }else{
        cout << "load image failed" << endl;
    }
    return 0;
}