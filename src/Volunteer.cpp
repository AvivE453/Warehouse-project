#include "../include/Parse.h"
#include "../include/WareHouse.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"

Volunteer::Volunteer(int _id, const string &_name) : id(_id), name(_name), activeOrderId(NO_ORDER), completedOrderId(NO_ORDER)
{
}

int Volunteer::getId() const
{
    return id;
}
const string &Volunteer::getName() const
{
    return name;
};
int Volunteer::getActiveOrderId() const
{
    return activeOrderId;
};
int Volunteer::getCompletedOrderId() const
{
    return completedOrderId;
};
bool Volunteer::isBusy() const
{
    return activeOrderId != NO_ORDER;

}; // Signal whether the volunteer is currently processing an order

CollectorVolunteer::CollectorVolunteer(int _id, const string &_name, int _coolDown) : coolDown(_coolDown), Volunteer(_id, _name)
{
}

CollectorVolunteer *CollectorVolunteer::clone() const {

};
void CollectorVolunteer::step(){

};
int CollectorVolunteer::getCoolDown() const
{
    return coolDown;
};
int CollectorVolunteer::getTimeLeft() const
{
    return timeLeft;
};
bool CollectorVolunteer::decreaseCoolDown()
{
    timeLeft--;
    return timeLeft == 0;
}; // Decrease timeLeft by 1,return true if timeLeft=0,false otherwise
bool CollectorVolunteer::hasOrdersLeft() const
{
    return true;
};
bool CollectorVolunteer::canTakeOrder(const Order &order) const
{
    return !isBusy() && hasOrdersLeft();
};
void CollectorVolunteer::acceptOrder(const Order &order)
{
    activeOrderId = order.getId();
    timeLeft = coolDown;
};
string CollectorVolunteer::toString() const {

};

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int _id, const string &_name, int _coolDown, int _maxOrders) : maxOrders(_maxOrders), CollectorVolunteer(_id, _name, _coolDown)
{
}
LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const {

};
bool LimitedCollectorVolunteer::hasOrdersLeft() const
{
    return ordersLeft > 0;
};
bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const
{
    return !isBusy() && hasOrdersLeft();
};
void LimitedCollectorVolunteer::acceptOrder(const Order &order)
{
    CollectorVolunteer::acceptOrder(order);
    ordersLeft--;
};

int LimitedCollectorVolunteer::getMaxOrders() const
{
    return maxOrders;
};
int LimitedCollectorVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
};
string LimitedCollectorVolunteer::toString() const {

};

DriverVolunteer ::DriverVolunteer(int _id, const string &_name, int _maxDistance, int _distancePerStep) : maxDistance(maxDistance), _distancePerStep(_distancePerStep) : Volunteer(_id, _name)
{
}
DriverVolunteer ::DriverVolunteer *clone() const override;

int DriverVolunteer ::getDistanceLeft() const
{
    return distanceLeft;
};
int DriverVolunteer ::getMaxDistance() const
{
    return maxDistance;
};
int DriverVolunteer ::getDistancePerStep() const
{
    distancePerStep;
};
bool DriverVolunteer ::decreaseDistanceLeft()
{ // Decrease distanceLeft by distancePerStep,return true if  distanceLeft<=0,false otherwise
    distanceLeft -= distancePerStep;
    if (distanceLeft <= 0)
    {
        distanceLeft = 0;
        return true;
    }
    return false;
}
bool DriverVolunteer ::hasOrdersLeft() const {
    return true};
bool DriverVolunteer ::canTakeOrder(const Order &order) const // Signal if the volunteer is not busy and the order is within the maxDistance
{
    return !isBusy() && hasOrdersLeft() && order.getDistance() <= maxDistance;
};
void DriverVolunteer ::acceptOrder(const Order &order) // Assign distanceLeft to order's distance
{
    activeOrderId = order.id;
    distanceLeft = order.getDistance();
};
void DriverVolunteer ::step() // Decrease distanceLeft by distancePerStep
{
    decreaseDistanceLeft();
}
string DriverVolunteer ::toString() const
{
}
LimitedDriverVolunteer::LimitedDriverVolunteer(int _id, const string &_name, int _maxDistance, int _distancePerStep, int _maxOrders) : DriverVolunteer(_id, _name, _maxDistance, _distancePerStep), maxOrders(_maxOrders) {}
LimitedDriverVolunteer *clone() const {}
int LimitedDriverVolunteer::getMaxOrders() const
{
    return maxOrders;
}
int LimitedDriverVolunteer::getNumOrdersLeft() const
{
    return getNumOrdersLeft();
};
bool LimitedDriverVolunteer::hasOrdersLeft() const override
{
    return ordersLeft > 0;
};
bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const override; // Signal if the volunteer is not busy, the order is within the maxDistance.
{
    return DriverVolunteer::canTakeOrder(order) && hasOrdersLeft();
}
void LimitedDriverVolunteer::acceptOrder(const Order &order); // Assign distanceLeft to order's distance and decrease ordersLeft
{
    DriverVolunteer::acceptOrder(order);
    ordersLeft--;
}
string LimitedDriverVolunteer::toString() const {

};