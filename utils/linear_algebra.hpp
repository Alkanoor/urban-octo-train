#ifndef LINEAR_ALGEBRA_HPP
#define LINEAR_ALGEBRA_HPP


#include <glm/ext.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>
#include <cmath>


class Plan
{
    public:
        Plan(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);

        char position_from_plan(const glm::vec3& p) const; //0 = on the plan; 1 = near from the plan, but up; 2 = near from the plan, but down; 3 = far from the plan, but up; 4 = far from the plan, but down

        static void set_precision(double prec);

    private:
        glm::vec3 origin;
        glm::mat3x3 basis_matrix;

        static double precision;
};

#endif
