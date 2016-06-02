#ifndef UPDATABLE_HPP
#define UPDATABLE_HPP


#include "element.hpp"


class Updatable
{
    public:
        virtual void update(const std::map<std::string,Element>& elements) = 0;
};

#endif
