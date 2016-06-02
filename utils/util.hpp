#ifndef UTIL_HPP
#define UTIL_HPP


#include <ostream>
#include <vector>
#include <map>

#include "../core/element.hpp"


template <typename T, typename U>
std::ostream& operator << (std::ostream& os, const std::map<T,U>& m)
{
    os<<"--->"<<std::endl;
    for(typename std::map<T, U>::const_iterator it = m.begin(); it != m.end(); it++)
        os<<it->first<<" -> "<<it->second<<std::endl;
    os<<"<---";
    return os;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
{
    for(auto it : v)
        os<<*it<<";";
    return os;
}

template <typename T, typename U>
std::ostream& operator << (std::ostream& os, const std::pair<T,U>& p)
{
    os<<"["<<p.first<<";"<<p.second<<"]";
    return os;
}

std::ostream& operator << (std::ostream& os, const Element& e)
{
    os<<e.get_dict();
    return os;
}

#endif
