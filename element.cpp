#include "element.hpp"


Element::Element(const std::map<std::string,double>& p) : params(p)
{}

double& Element::operator[] (const std::string& name) const
{return params[name];}

double Element::get(const std::string& name) const
{return params[name];}

void Element::set(const std::string name, double val)
{params[name]=val;}
