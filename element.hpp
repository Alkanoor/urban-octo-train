#ifndef ELEMENT_HPP
#define ELEMENT_HPP


#include <string>
#include <map>


class Element
{
    public:
        Element(std::string s, double d);
        Element(const std::map<std::string,double>& p=std::map<std::string,double>());

        virtual double& operator[] (const std::string& name);
        virtual double get(const std::string& name);
        void set(const std::string name, double val);

    private:
        std::map<std::string,double> params;
};

#endif
