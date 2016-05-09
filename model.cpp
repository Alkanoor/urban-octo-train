#include "model.hpp"


const std::map<std::string,Element>& Modified_Set::last_modified()
{
    lasts_updated_temp_reference = lasts_updated;
    lasts_updated.clear();
    return lasts_updated_temp_reference;
}

const std::map<std::string,Element>& Modified_Set::current_elements() const
{return elements;}

void Modified_Set::empty_last_elements()
{lasts_updated.clear();}

bool Modified_Set::modify(const std::string& name, const Element& elem)
{
    if(elements.count(name))
    {
        lasts_updated[name] = elem;
        elements[name] = elem;
        return true;
    }
    else
        return false;
}

bool Modified_Set::modify_parameter(const std::string& name, const std::string& param_name, double val)
{
    if(elements.count(name))
    {
        lasts_updated[name].set(param_name,val);
        elements[name].set(param_name,val);
        return true;
    }
    else
        return false;
}

void Modified_Set::update_all()
{lasts_updated = elements;}



void Model::update()
{
    update_();
    for(auto updatable : updatable_objects)
        updatable->update(elements.last_modified());
}

const std::map<std::string,Element>& Model::get_updated()
{return elements.last_modified();}

const std::map<std::string,Element>& Model::get_all_elements() const
{return elements.current_elements();}

void Model::empty_last_elements()
{elements.empty_last_elements();}
