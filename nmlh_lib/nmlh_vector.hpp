#include <cstddef>

namespace nmlh{
    template <class C>
    class vector{
        private:
            C* data;
            std::size_t size;
        public:
            inline C& operator[](std::size_t index) noexcept {
                return data[index];
            }

            inline const C& operator[](std::size_t index) const noexcept {
                return data[index];
            }
            
           inline C* begin() const noexcept {return data;}
           inline C* end() const noexcept {return data + size;}
           inline std::size_t size() const noexcept {return size;}
    };
}