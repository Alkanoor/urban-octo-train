#include "robot_model.hpp"


#include <iostream>
Robot_model::Robot_model(int n, std::shared_ptr<Camera_model> cam) :
    Robot_model(50,75,100,150.,10.,70.,n,cam)
{}

Robot_model::Robot_model(double body_radius, double leg_length, double foot_length, double body_to_leg_angle, double leg_angle, double leg_to_foot_angle, int n, std::shared_ptr<Camera_model> cam) :
    offset_x(0),
    offset_y(0),
    offset_z(0),
    lowest_point_body_angle(0),
    body_angle(0),
    body_radius(body_radius),
    leg_length(leg_length),
    foot_length(foot_length),
    camera(cam),
    total_time(0)
{
    set_current_leg_as_template(body_to_leg_angle,leg_angle,leg_to_foot_angle,n);
}

void Robot_model::update_time(int t)
{
    if(total_time>0)
        t %= total_time;
    int time = 0, last_time = 0, i = 0;
    for(;i<(int)millis_time_periods.size()&&t>time;i++)
    {
        last_time = time;
        if(millis_time_periods[i])
            time += millis_time_periods[i];
    }
    i--;

    if(i<(int)millis_time_periods.size()&&i>=0)
    {
        Leg& step1 = steps[i];
        Leg step2;
        if(i+1<(int)steps.size())
            step2 = steps[i+1];
        else
            step2 = steps[i];

        if(time!=last_time)
            update_global_parameters(step1,step2,(double)(t-last_time)/(double)(time-last_time));
        else
            update_global_parameters(step1,step2,0);
    }
}

void Robot_model::add_step(const Leg& l, int millis_delay)
{
    steps.push_back(l);
    total_time += millis_delay;
    millis_time_periods.push_back(millis_delay);
}

void Robot_model::update_()
{
    if((int)current_leg.size()!=N)
        return;

    elements.modify("N",Element("val",N));

    foots.resize(3*N);
    for(int i=0;i<N;i++)
    {
        std::array<glm::vec3,3> tmp = compute_relative_positions(current_leg[i]);
        foots[3*i+2] = tmp[0];
        foots[3*i+1] = foots[3*i+2]+tmp[1];
        foots[3*i] = foots[3*i+1]+tmp[2];
    }

    update_for_view();
}

void Robot_model::update_element(const std::string& name, Element& elem)
{}

void Robot_model::update_parameter(const std::string& name, const std::string& param_name, double val)
{}

void Robot_model::update_for_view()
{
    if(!camera)
        return;

    std::map<std::string,double> coords;
    for(unsigned int i=0;i<foots.size();i++)
    {
        glm::vec3 transformed = camera->get_transformed(foots[i]);
        coords["x"] = transformed.x;
        coords["y"] = transformed.y;
        std::string suffix;
        suffix += (char)(i/3+'0');
        if(!(i%3))
            elements.modify("foot"+suffix,Element(coords));
        else if(i%3==1)
            elements.modify("knee"+suffix,Element(coords));
        else
            elements.modify("hip"+suffix,Element(coords));
    }

    update_views();
}

void Robot_model::set_current_leg_as_template(double body_to_leg_angle, double leg_angle, double leg_to_foot_angle, int n)
{
    N = ((n>256)?256:((n<3)?3:n));
    current_leg.resize(N,Leg_angles(0,body_to_leg_angle,leg_angle,leg_to_foot_angle));
    for(int i=0;i<N;i++)
        current_leg[i].body_angle = (float)(i)/(float)N*2.*M_PI;
}

std::array<glm::vec3,3> Robot_model::compute_relative_positions(const Leg_angles& leg)
{
    double theta = leg.body_angle;
    double dir2_x = cos(leg.leg_angle/180.*M_PI+theta);
    double dir2_y = sin(leg.leg_angle/180.*M_PI+theta);
    double beta = leg.body_to_leg_angle/180.*M_PI;
    double gamma = (leg.leg_to_foot_angle-M_PI)/180.*M_PI;

    std::array<glm::vec3,3> ret;
    ret[0] = glm::vec3(cos(theta)*body_radius,sin(theta)*body_radius,0);
    ret[1] = glm::vec3(-leg_length*dir2_x*cos(beta),-leg_length*dir2_y*cos(beta),leg_length*sin(beta));
    ret[2] = glm::vec3(foot_length*dir2_x*cos(gamma),foot_length*dir2_y*cos(gamma),-foot_length*sin(gamma));
    return ret;
}

void Robot_model::update_global_parameters(const Leg& leg1, const Leg& leg2, double ratio)
{
    N = leg1.size();
    if(leg1.size()!=leg2.size())
        current_leg = leg1;
    else
    {
        for(int i=0;i<N;i++)
        {
            current_leg[i].body_angle = leg1[i].body_angle*(1-ratio)+leg2[i].body_angle*ratio;
            current_leg[i].body_to_leg_angle = leg1[i].body_to_leg_angle*(1-ratio)+leg2[i].body_to_leg_angle*ratio;
            current_leg[i].leg_angle = leg1[i].leg_angle*(1-ratio)+leg2[i].leg_angle*ratio;
            current_leg[i].leg_to_foot_angle = leg1[i].leg_to_foot_angle*(1-ratio)+leg2[i].leg_to_foot_angle*ratio;
        }
    }

    std::vector<glm::vec3> current_foots(N);
    for(int i=0;i<N;i++)
    {
        auto rel = compute_relative_positions(current_leg[i]);
        current_foots[i] = rel[0]+rel[1]+rel[2];
    }

    find_coplanar_points(current_foots);

    update_();
}

struct Plane_from_facet {
  Polyhedron_3::Plane_3 operator()(Polyhedron_3::Facet& f) {
      Polyhedron_3::Halfedge_handle h = f.halfedge();
      return Polyhedron_3::Plane_3( h->vertex()->point(),
                                    h->next()->vertex()->point(),
                                    h->opposite()->vertex()->point());
  }
};

#include <glm/gtx/string_cast.hpp>
void Robot_model::find_coplanar_points(const std::vector<glm::vec3>& current_foots)
{
    /*if(current_foots.size()<3)
        return;
    else if(current_foots.size()==3)
        coplanars = {0,1,2};*/


    std::vector<Custom_point> points(current_foots.size());

    for(unsigned int i=0;i<current_foots.size();i++)
        points[i] = Custom_point(i,current_foots[i][0],current_foots[i][1],current_foots[i][2]);

    Polyhedron_3 poly;

    CGAL::convex_hull_3(points.begin(), points.end(), poly);
    std::cout << "The convex hull contains " << poly.size_of_vertices() << " vertices" << std::endl;

    std::transform(poly.facets_begin(), poly.facets_end(), poly.planes_begin(), Plane_from_facet());

    for(auto it = poly.planes_begin(); it != poly.planes_end(); it++)
        std::cout<<it->a()<<" "<<it->b()<<" "<<it->c()<<std::endl;

    for(auto it = poly.facets_begin(); it != poly.facets_end(); it++)
        std::cout<<it->

    /*int index_lowest_point = ;
    std::vector<std::vector<glm::vec3> > convex_hull_at_p(current_foots,index_lowest_point);

    std::map<int,bool> used;
    std::vector<int> cur_index;
    for(unsigned int i=0;i+3<current_foots.size();i++)
    {
        if(!i)
        {
            cur_index.push_back(i);
            cur_index.push_back(i+1);
            cur_index.push_back(i+2);
        }
        Plan p(current_foots[cur_index[0]],current_foots[cur_index[1]],current_foots[cur_index[2]]);
        char type = p.position_from_plan(current_foots[i+3]);
        if(type<=2) //point is at same level : we add it
        {

        }
        else if(type==4) //point is below the plan (vertically) so we create the new lowest plan
        {

        }
    }*/
}
