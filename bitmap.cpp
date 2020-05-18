#include <fstream>
//#include <iostream>
#include "bitmap.h"

// Bitmap file
bitmap::bitmap::bitmap(){
    this->file_header = {};
    this->info_header = {};
    this->image = nullptr;
    this->err_file.open("bitmap_errors.txt", std::ios_base::out);
}

bitmap::bitmap::bitmap(const bitmap& copy_src){
    this->file_header = copy_src.file_header;
    this->info_header = copy_src.info_header;
    this->image = new pixel*[this->info_header.width];
    for(int i = 0; i < this->info_header.width; i++){
        this->image[i] = new pixel[this->info_header.height];
        memcpy(this->image[i], copy_src.image[i], this->info_header.height * sizeof(pixel));
    }
}

bitmap::bitmap::bitmap(bitmap&& move_src){
    this->file_header = move_src.file_header;
    this->info_header = move_src.info_header;
    this->image = move_src.image;
    move_src.image = nullptr;
}

bitmap::bitmap& bitmap::bitmap::operator=(const bitmap& copy_rhs){
    if(this != &copy_rhs){
        this->file_header = copy_rhs.file_header;
        this->info_header = copy_rhs.info_header;
        this->image = new pixel*[this->info_header.width];
        for(int i = 0; i < this->info_header.width; i++){
            this->image[i] = new pixel[this->info_header.height];
            memcpy(this->image[i], copy_rhs.image[i], this->info_header.height * sizeof(pixel));
        }
    }
    return *this;
}

bitmap::bitmap& bitmap::bitmap::operator=(bitmap&& move_rhs){
    if(this != &move_rhs){
        this->file_header = move_rhs.file_header;
        this->info_header = move_rhs.info_header;
        this->image = move_rhs.image;
        move_rhs.image = nullptr;
    }
    return *this;
}
            

bitmap::bitmap::~bitmap(){
    if(this->image != nullptr){
        for(int i = 0; i < info_header.width; i++)
            delete[] this->image[i];
        delete[] this->image;
    }
    this->err_file.close();
}

bitmap::pixel* bitmap::bitmap::operator[](unsigned int index){
    return this->image[index];
}

unsigned int bitmap::bitmap::width(){
    return this->info_header.width;
}

unsigned int bitmap::bitmap::height(){
    return this->info_header.height;
}

// Function for loading images
bool bitmap::bitmap::load_image(const char* file_name){
    // Open the image file
    std::ifstream image_file(file_name, std::ios_base::in | std::ios_base::binary);

    // If the file is not open, return false
    if(!image_file.is_open()){
        err_file << "Could not open file - load_image\n";
        return false;
    }

    // Read in the file header
    image_file.read((char*)&(this->file_header), sizeof(file_header));

    // Check if file is a bitmap
    if(this->file_header.type != 0x4D42){
        err_file << "File is not a bitmap file - load_image\n";
        err_file << "\tFile Type: " << this->file_header.type << '\n';
        image_file.close();
        return false;
    }

    image_file.read((char*)&(this->info_header), sizeof(info_header));
    
    // Currently only supports BITMAPINFOHEADER which is 40 bytes long
    if(this->info_header.header_size != 40){
        err_file << "Bitmap DIB header is not BITMAPINFOHEADER - load_image\n";
        err_file << "\tHeader Size: " << this->info_header.header_size << '\n';
        image_file.close();
        return false;
    }

    // Currently only supports 24-bit color depth
    if(this->info_header.color_depth != 24){
        err_file << "Color depth is not 24-bit - load_image\n";
        err_file << "\tColor depth: " << this->info_header.color_depth << '\n';
        image_file.close();
        return false;
    }

    // Currently does not support any compression method
    if(this->info_header.compression != 0){
        err_file << "Image is compressed - load_image\n";
        err_file << "\tCompression type: " << this->info_header.compression << '\n';
        image_file.close();
        return false;
    }

    // Allocate for the number of columns
    this->image = new pixel*[this->info_header.width];

    // If allocation fails then loading the image fails
    if(this->image == nullptr){
        err_file << "Allocation Failed - load_image\n";
        image_file.close();
        return false;
    }
    // Allocate for each column
    for(int i = 0; i < this->info_header.width; i++){
        this->image[i] = new pixel[this->info_header.height];
        
        // If an allocation fails, deallocate all previous successful allocations
        if(this->image[i] == nullptr){
            err_file << "Allocation Failed - load_image\n";
            for(int j = 0; j < i; j++)
                delete[] this->image[j];
            delete[] this->image;
            image_file.close();
            return false;
        }
    }

    image_file.seekg(file_header.offset);

    for(int row = 0; row < this->info_header.height; row++){        
        for(int column = 0; column < this->info_header.width; column++){
            image_file.read((char*)&(this->image[column][row]), sizeof(pixel));
        }
        char* padding = new char[3];
        short padding_size;
        switch(this->info_header.width * sizeof(pixel) % 4){
            case 0:
                padding_size = 0;
                break;
            case 1:
                padding_size = 3;
                break;
            case 2:
                padding_size = 2;
                break;
            case 3:
                padding_size = 1;
                break;
        }
        image_file.read(padding, padding_size);
    }

    image_file.close();
    return true;
}

bool bitmap::bitmap::save_image(const char* file_name){
    // Open the image file
    std::ofstream image_file(file_name, std::ios_base::out | std::ios_base::binary);

    // If the file is not open, return false
    if(!image_file.is_open())
        return false;

    image_file.write((char*)&(this->file_header), sizeof(file_header));
    image_file.write((char*)&(this->info_header), sizeof(info_header));

    unsigned gap_size = file_header.offset - sizeof(file_header) - sizeof(file_header);
    char* gap = new char[gap_size]{};
    image_file.write(gap, gap_size);
    delete[] gap;

    for(int row = 0; row < this->info_header.height; row++){        
        for(int column = 0; column < this->info_header.width; column++){
            image_file.write((char*)&(this->image[column][row]), sizeof(pixel));
        }
        char* padding = new char[3]{};
        short padding_size;
        switch(this->info_header.width * sizeof(pixel) % 4){
            case 0:
                padding_size = 0;
                break;
            case 1:
                padding_size = 3;
                break;
            case 2:
                padding_size = 2;
                break;
            case 3:
                padding_size = 1;
                break;
        }
        image_file.write(padding, padding_size);
    }

    image_file.close();
    return true;
}