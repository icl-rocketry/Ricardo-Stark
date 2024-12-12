#pragma once

#include <map>
#include <vector>
#include <exception>

template<typename T,class Interp>
class LuT
{

    public:
        LuT(const std::vector<T> &keys,const std::vector<T> &values,bool extrapolate=true):
        m_container(),
        m_extrapolate(extrapolate)
        {
            updateTable(keys,values); // can return false?
        };

        T get(T xVal)
        {
            if (m_container.size() == 0)
            {
                return {}; //exception?
            }

            auto lb = m_container.lower_bound(xVal); //returns first element strictly not less than x i.e xVal < lb
            auto p1 = lb;
            if (lb == m_container.end()) // no element greater than xVal
            {
                if(m_extrapolate)
                {
                    lb--;
                    p1 = lb;
                    p1--;
                }
                else
                {
                    //return endpoint if we arent extrapolating - fix this later
                    auto &[x,y] = *(lb--);
                    return y;
                }
            }
            if (lb == m_container.begin())
            {
               if (m_extrapolate)
               {
                    p1 = lb++;
               }
               else
               {
                auto &[x,y] = *lb;
                return y;
               }
            }
            // get elements either side
            p1 = lb;
            p1--;
            auto &[x1,y1] = *p1;
            auto &[x2,y2] = *lb;

            return m_interp.calculate(x1,y1,x2,y2,xVal);
        };

        void clear()
        {
            m_container.clear();
        };

        bool updateTable(const std::vector<T> &keys,const std::vector<T> &values)
        {
            //check length
            //keys must be unique for maping
            //throw exceptions?
            if (keys.size() != values.size() || keys.size() < 2)
            {
                // throw std::runtime_error("error key size and value size do not match");
                return false;
            }

            for (auto i_key = 0; i_key < keys.size(); i_key++)
            {
                T key = keys[i_key];
                T val = values[i_key];
                m_container[key] = val;
            }
            return true;
        };

    
    private:

        std::map<T,T> m_container;
        Interp m_interp;
        bool m_extrapolate;
};
