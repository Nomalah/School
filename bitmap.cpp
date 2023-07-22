#include <fstream>
#include <iostream>
#include "bitmap.h"

// Bitmap file
bitmap::bitmap(){
    this->file_header = {};
    this->info_header = {};
    this->image = nullptr;
}

bitmap::bitmap(int width, int height){
    this->file_header = {
        0x4D42, // File type (BM)
        0x0, // File size
        0x0, // Reserved 1 (0)
        0x0, // Reserved 2 (0)
        0x0, // Offset
    };
    this->info_header = {
        0x28, // Header size (40)
        width, // Image width
        height, // Image height
        0x1, // Number of planes (1)
        0x18, // Color Depth (24)
        0x0, // Compression (0)
        (width * (unsigned)sizeof(pixel24) + 3) / 4 * 4 * height, // Array size
        0x0, // PPM of x (0)
        0x0, // PPM of y (0)
        0x0, // Colors used (0)
        0x0, // Important colors (0)
    };
    this->file_header.size = sizeof(file_header) + sizeof(info_header) + this->info_header.size;
    this->file_header.offset = sizeof(file_header) + sizeof(info_header);

    std::cout << "size: " << this->file_header.size << std::endl;
    std::cout << "offset: " << this->file_header.offset << std::endl;
    this->image = new pixel24*[width];
    for(int i = 0; i < width; i++)
        this->image[i] = new pixel24[height]{};
}

bitmap::bitmap(const bitmap& copy_src){
    this->file_header = copy_src.file_header;
    this->info_header = copy_src.info_header;
    this->image = new pixel24*[this->info_header.width];
    for(int i = 0; i < this->info_header.width; i++){
        this->image[i] = new pixel24[this->info_header.height];
        memcpy(this->image[i], copy_src.image[i], this->info_header.height * sizeof(pixel24));
    }
}

bitmap::bitmap(bitmap&& move_src){
    this->file_header = move_src.file_header;
    this->info_header = move_src.info_header;
    this->image = move_src.image;
    move_src.image = nullptr;
}

bitmap& bitmap::operator=(const bitmap& copy_rhs){
    if(this != &copy_rhs){
        this->file_header = copy_rhs.file_header;
        this->info_header = copy_rhs.info_header;
        this->image = new pixel24*[this->info_header.width];
        for(int i = 0; i < this->info_header.width; i++){
            this->image[i] = new pixel24[this->info_header.height];
            memcpy(this->image[i], copy_rhs.image[i], this->info_header.height * sizeof(pixel24));
        }
    }
    return *this;
}

bitmap& bitmap::operator=(bitmap&& move_rhs){
    if(this != &move_rhs){
        this->file_header = move_rhs.file_header;
        this->info_header = move_rhs.info_header;
        this->image = move_rhs.image;
        move_rhs.image = nullptr;
    }
    return *this;
}
            

bitmap::~bitmap(){
    if(this->image != nullptr){
        for(int i = 0; i < info_header.width; i++)
            delete[] this->image[i];
        delete[] this->image;
    }
 }

pixel24* bitmap::operator[](unsigned int index){
    return this->image[index];
}

unsigned int bitmap::width(){
    return this->info_header.width;
}

unsigned int bitmap::height(){
    return this->info_header.height;
}

// Function for loading images
bool bitmap::load_image(const char* file_name){
    // Open the image file
    std::ifstream image_file(file_name, std::ios_base::in | std::ios_base::binary);

    // If the file is not open, return false
    if(!image_file.is_open()){
        std::cerr << "Could not open file - load_image\n";
        return false;
    }

    // Read in the file header
    image_file.read((char*)&(this->file_header), sizeof(file_header));

    // Check if file is a bitmap
    if(this->file_header.type != 0x4D42){
        std::cerr << "File is not a bitmap file - load_image\n";
        std::cerr << "\tFile Type: " << this->file_header.type << '\n';
        image_file.close();
        return false;
    }

    image_file.read((char*)&(this->info_header), sizeof(info_header));
    
    // Currently only supports BITMAPINFOHEADER which is 40 bytes long
    if(this->info_header.header_size != 40){
        std::cerr << "Bitmap DIB header is not BITMAPINFOHEADER - load_image\n";
        std::cerr << "\tHeader Size: " << this->info_header.header_size << '\n';
        image_file.close();
        return false;
    }

    // Currently only supports 24-bit color depth
    if(this->info_header.color_depth != 24){
        std::cerr << "Color depth is not 24-bit - load_image\n";
        std::cerr << "\tColor depth: " << this->info_header.color_depth << '\n';
        image_file.close();
        return false;
    }

    // Currently does not support any compression method
    if(this->info_header.compression != 0){
        std::cerr << "Image is compressed - load_image\n";
        std::cerr << "\tCompression type: " << this->info_header.compression << '\n';
        image_file.close();
        return false;
    }

    // Allocate for the number of columns
    this->image = new pixel24*[this->info_header.width];

    // Allocate for each column
    for(int i = 0; i < this->info_header.width; i++)
        this->image[i] = new pixel24[this->info_header.height];

    image_file.seekg(file_header.offset);

    for(int row = this->info_header.height - 1; row >= 0; row--){        
        for(int column = 0; column < this->info_header.width; column++){
            image_file.read((char*)&(this->image[column][row]), sizeof(pixel24));
        }
        short padding_size = (4 - this->info_header.width * sizeof(pixel24)) % 4;
        char* padding = new char[padding_size];
        image_file.read(padding, padding_size);
    }

    image_file.close();
    return true;
}

bool bitmap::save_image(const char* file_name){
    // Open the image file
    std::ofstream image_file(file_name, std::ios_base::out | std::ios_base::binary);

    // If the file is not open, return false
    if(!image_file.is_open())
        return false;

    image_file.write((char*)&(this->file_header), sizeof(file_header));

    //info_header.height = -info_header.height;
    image_file.write((char*)&(this->info_header), sizeof(info_header));
    //info_header.height = -info_header.height;

    unsigned gap_size = file_header.offset - sizeof(file_header) - sizeof(info_header);
    char* gap = new char[gap_size]{};
    image_file.write(gap, gap_size);
    delete[] gap;

    short padding_size = (4 - this->info_header.width * sizeof(pixel24)) % 4;
    char* padding = new char[padding_size];
    for(int row = this->info_header.height - 1; row >= 0; row--){        
        for(int column = 0; column < this->info_header.width; column++){
            image_file.write((char*)&(this->image[column][row]), sizeof(pixel24));
        }
        image_file.write(padding, padding_size);
    }
    delete[] padding;
    image_file.close();
    return true;
}