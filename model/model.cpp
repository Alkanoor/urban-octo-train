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
    bool ret = false;
    if(elements.count(name))
        ret = true;
    lasts_updated[name] = elem;
    elements[name] = elem;
    return ret;
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
    update_views();
}

void Model::update_views()
{
    for(auto updatable : updatable_objects)
        updatable->update(elements.last_modified());
}

const std::map<std::string,Element>& Model::get_updated()
{return elements.last_modified();}

const std::map<std::string,Element>& Model::get_all_elements() const
{return elements.current_elements();}

void Model::empty_last_elements()
{elements.empty_last_elements();}

#include <iostream>
void Model::add_updatable(std::shared_ptr<Updatable> updatable)
{
    if(updatable)
    {
        updatable->update(elements.current_elements());
        updatable_objects.push_back(updatable);
    }
}
