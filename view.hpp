#include "updatable.hpp"


class View : public Updatable
{
    public:
        virtual void draw() = 0;
        virtual void update(const std::map<std::string,Element>& elements) = 0;
};
