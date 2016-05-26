#include "verifier_order_maker.hpp"


bool Verifier_and_Order::add_order(const Order& angles, double begin)
{
    orders.push_back(Timed_Order(angles,begin));
    return true;
}
