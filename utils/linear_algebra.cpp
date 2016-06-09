#include "linear_algebra.hpp"


double Plan::precision = 0.00000000001;

Plan::Plan(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3)
{
    origin = p1;
    glm::vec3 v1 = p2-p1, v2 = p3-p1, v3 = glm::cross(v1,v2);
    if(v3.z<0)
        v3 *= -1;
    basis_matrix = glm::transpose(glm::mat3x3(v1.x,v1.y,v1.z,v2.x,v2.y,v2.z,v3.x,v3.y,v3.z));
}

char Plan::position_from_plan(const glm::vec3& p) const
{
    glm::vec3 v = basis_matrix*(p-origin);
    double tmp = v.z;
    if(tmp<-precision)
        return 4;
    else if(tmp>precision)
        return 3;
    else if(tmp<0)
        return 2;
    else if(tmp>0)
        return 1;
    else
        return 0;
}

void Plan::set_precision(double prec)
{precision = prec;}
