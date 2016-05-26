#ifndef VERIFIER_ORDER_HPP
#define VERIFIER_ORDER_HPP


#include <vector>


struct Order
{
    std::vector<double> leg_angles;
    std::vector<double> leg_to_foot_angles;
};

class Timed_Order
{
    public:
        Timed_Order(const Order& state, double d) : state_at_start(state), delay(d) {}

        Order state_at_start;
        double delay;
};

class Verifier_and_Order
{
    public:
        bool add_order(const Order& angles, double begin);

    private:
        std::vector<Timed_Order> orders;
};

#endif
