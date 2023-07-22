#pragma once

namespace nmlh{
    template<class T>
    class stack{
        private:
            T* m_Data;
            unsigned long long m_Count;
            unsigned long long m_Pointer;
        public:
            stack(unsigned long long stackCount) : m_Data(new T[stackCount]), m_Count(stackCount), m_Pointer(0){}

            ~stack(){
                delete[] m_Data;
            }

            inline bool push(T value){
                if(m_Pointer == m_Count)
                    return false;
                
                m_Data[m_Pointer++] = value;
                return true;
            }

            inline bool pop(){
                if(m_Pointer == 0)
                    return false;
                
                m_Pointer--;
                return true;
            }

            inline T top(){
                if(m_Pointer == 0)
                    return {};
                
                return m_Data[m_Pointer - 1];
            }

            inline unsigned long long count(){return m_Count;}
            inline unsigned long long size(){return m_Count * sizeof(T);}
            inline unsigned long long stored(){return m_Pointer;}
    };
}