#include "element.hpp"


Element::Element(std::string s, double d)
{params[s] = d;}

Element::Element(const std::map<std::string,double>& p) : params(p)
{}

double& Element::operator[] (const std::string& name)
{return params[name];}

double Element::operator[] (const std::string& name) const
{return params.find(name)->second;}

double Element::get(const std::string& name) const
{return params.find(name)->second;}

void Element::set(const std::string name, double val)
{params[name]=val;}

const std::map<std::string,double>& Element::get_dict() const
{return params;}
