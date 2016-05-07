#include "element.hpp"

class Updatable
{
    public:
        virtual void update(const std::map<std::string,Element>& elements);
}
