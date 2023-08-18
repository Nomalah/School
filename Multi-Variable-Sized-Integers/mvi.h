#ifndef MULTI_VARIABLE_SIZED_INTEGERS
#define MULTI_VARIABLE_SIZED_INTEGERS

class mvi{
    public:
        unsigned char* data;
        int num_of_bytes;

        void print();

        mvi();
        mvi(int init_num_of_bytes, std::string initializer = "");
        mvi(int init_num_of_bytes, unsigned int initializer);
        mvi(const mvi& mvi_copy_src);
        mvi(mvi&& mvi_move_src);
        mvi& operator=(const mvi& mvi_copy_rhs);
        mvi& operator=(mvi&& mvi_move_rhs);
        ~mvi();

        mvi operator+(const mvi& mvi_add_rhs);
        mvi operator-(const mvi& mvi_sub_rhs);

};

mvi operator~(const mvi& mvi_neg_rhs);

unsigned char from_hex(const char hex_character);
char to_hex(const unsigned char int_character);
std::string to_hex(const mvi& integer);

#endif // MULTI_VARIABLE_SIZED_INTEGERS