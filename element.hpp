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
        virtual double operator[] (const std::string& name) const;
        virtual double get(const std::string& name) const;
        void set(const std::string name, double val);

        const std::map<std::string,double>& get_dict() const;

    private:
        std::map<std::string,double> params;
};

#endif
