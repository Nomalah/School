/*
This file declares the namespace and classes that deal with bitmap files
Written by Dallas Hart
Copyright May 14 2020
*/

#ifndef BITMAP_H
#define BITMAP_H


struct pixel24{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

struct pixel32{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char alpha;
};

class bitmap{
    private:
        #pragma pack(push, 1)
        struct file_header{
            unsigned short type;        //specifies the file type
            unsigned int   size;        //specifies the size in bytes of the bitmap file
            unsigned short reserved1;   //reserved; must be 0
            unsigned short reserved2;   //reserved; must be 0
            unsigned int   offset;      //species the offset in bytes from the bitmapfileheader to the bitmap bits
        }file_header;
        #pragma pack(pop)

        #pragma pack(push, 1)
        struct info_header{
            unsigned int header_size; // specifies the number of bytes required by the struct
            int width;  // specifies width in pixels
            int height; // species height in pixels
            unsigned short planes;   // specifies the number of color planes, must be 1
            unsigned short color_depth; // specifies the number of bits per pixel
            unsigned int compression; // specifies the type of compression
            unsigned int size; // size of image in bytes
            int ppm_x; // number of pixels per meter in x axis
            int ppm_y; // number of pixels per meter in y axis
            unsigned int colors_used; // number of colors used by the bitmap
            unsigned int important_colors; //number of colors that are important
        }info_header;
        #pragma pack(pop)
        pixel24** image; // Image is stored like this: [x][y]
    public:
        // Constructor
        bitmap(); // Default
        bitmap(int, int);
        //bitmap(int, int, pixel**);
        bitmap(const bitmap&); // Copy
        bitmap(bitmap&&); // Move

        // Assignment
        bitmap& operator=(const bitmap&); // Copy
        bitmap& operator=(bitmap&&); // Move

        // Destructor
        ~bitmap();

        // Load an image into the bitmap (only supports BITMAPINFOHEADER)
        bool load_image(const char*);

        // Save an image into a file
        bool save_image(const char*);

        // Access a column of data
        pixel24* operator[](unsigned int);

        // Functions for getting the width and height
        unsigned int width();
        unsigned int height();

};


#endif // BITMAP_H