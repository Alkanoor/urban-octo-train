#ifndef VIEW_HPP
#define VIEW_HPP


#include "updatable.hpp"


class Drawing : public Updatable
{
    public:
        virtual void draw() = 0;
        virtual void update(const std::map<std::string,Element>& elements) = 0;
};

#endif
