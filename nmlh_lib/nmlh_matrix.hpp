#include <cstddef>
#include <cstring>
#include <functional>

#define NMLH_MAT_OP(op) matrix<C>& operator##op##=(const matrix<C>& add_rhs){                                   \
        for(C* this_it = this->begin(), * rhs_it = add_rhs.begin(); this_it != this->end(); this_it++, rhs_it++)\
            *this_it ##op##= *rhs_it;                                                                           \
        return *this;                                                                                           \
    }                                                                                                           \
    matrix<C> operator##op##(const matrix<C>& add_rhs) const {                                                  \
        matrix<C> result{*this};                                                                                \                                              
        result ##op##= add_rhs;                                                                                 \
        return result;                                                                                          \
    }



namespace nmlh{
    template <class C>
    class matrix{
        private:
            std::size_t m_rows;
            std::size_t m_columns;
            std::size_t m_size;
            C* m_data;
        public:
            matrix(std::size_t rows, std::size_t columns)
                : m_rows{rows}, m_columns{columns}, m_size{rows * columns}, m_data{new C[m_size]}{
            }

            matrix(std::size_t rows, std::size_t columns, C* init_data)
                : m_rows{rows}, m_columns{columns}, m_size{rows * columns}, m_data{new C[m_size]}{
                std::memcpy(this->m_data, init_data, sizeof(C) * m_size);
            }

            matrix(const matrix<C>& cpy_src)
                : m_rows{cpy_src.m_rows}, m_columns{cpy_src.m_columns}, m_size{cpy_src.m_size}, m_data{new C[m_size]}{
                std::memcpy(this->m_data, cpy_src.m_data, sizeof(C) * cpy_src.m_size);
            }

            matrix(matrix<C>&& mve_src)
                : m_rows{mve_src.m_rows}, m_columns{mve_src.m_columns}, m_size{mve_src.m_size}, m_data{mve_src.m_data}{
                mve_src.m_data = nullptr;
            }

            ~matrix() {
                delete[] m_data;
            }

            matrix<C>& operator=(const matrix<C>& cpy_rhs) {
                if(this != &cpy_rhs) {
                    this->m_rows = cpy_rhs.m_rows;
                    this->m_columns = cpy_rhs.m_columns;
                    this->m_size = cpy_rhs.m_size;

                    delete[] this->m_data;
                    this->m_data = new C[this->m_size];
                    std::memcpy(this->m_data, cpy_rhs.m_data, sizeof(C) * cpy_rhs.m_size);
                }
                return *this;
            }

            matrix<C>& operator=(matrix<C>&& mve_rhs) {
                if(this != &mve_rhs) {
                    this->m_rows = mve_rhs.m_rows;
                    this->m_columns = mve_rhs.m_columns;
                    this->m_size = mve_rhs.m_size;
                    this->m_data = mve_rhs.m_data;
                    mve_rhs.m_data = nullptr;
                }
                return *this;
            }

            inline C* begin() const {return m_data;}
            inline C* end() const {return m_data + m_size;}
            inline std::size_t rows() const {return this->m_rows;}
            inline std::size_t columns() const {return this->m_columns;}
            inline std::size_t size() const {return this->m_size;} 

            NMLH_MAT_OP(+)
            NMLH_MAT_OP(-)
            NMLH_MAT_OP(/)
            NMLH_MAT_OP(*)
            
            matrix<C> transpose() const {
                matrix<C> result{this->m_columns, this->m_rows};
                for(){
                    result
                }
                return result;
            }

            C& operator[](std::size_t index){
                return this->m_data[index * columns];
            }
            
    };
}

#undef NMLH_MAT_OP