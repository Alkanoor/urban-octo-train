#include <string>
#include <map>


class Element
{
    public:
        Element(const std::map<std::string,double>& p=std::map<std::string,double>());

        virtual double& operator[] (const std::string& name) const;
        virtual double get(const std::string& name) const;
        void set(const std::string name, double val);

    private:
        std::map<std::string,double> params;
};
