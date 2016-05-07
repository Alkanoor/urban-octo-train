

class Modified_Set
{
    public:
        const std::map<std::string,Element>& last_modified();
        const std::map<std::string,Element>& current_elements() const;

        bool modify(const std::string& name, const Element& elem);
        bool modify_parameter(const std::string& name, const std::string& param_name, double val);
        void update_all();

    private:
        std::map<std::string,Element> lasts_updated_temp_reference;
        std::map<std::string,Element> lasts_updated;
        std::map<std::string,Element> elements;
};

class Model
{
    public:
        void update(); //calls update_all (virtual) and update every updatable object

        virtual void update_() = 0;
        virtual void update_element(const std::string& name, Element& elem) = 0; //method is declared virtual in order to allow specifications (update of the whole model or not, ...)
        virtual void update_parameter(const std::string& name, const std::string& param_name, double val) = 0; //method is declared virtual in order to allow specifications (update of the whole model or not, ...)

        const std::map<std::string,Element>& get_updated() const;
        const std::map<std::string,Element>& get_all_elements() const;

    private:
        Modified_Set elements;
        std::vector<std::shared_ptr<Updatable> > updatable_objects;
};
