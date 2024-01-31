#include "../include/Parse.h"
#include "../include/WareHouse.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"

Volunteer::Volunteer(int id, const string &name) : id(id), name(name), activeOrderId(NO_ORDER), completedOrderId(NO_ORDER)
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
}
bool Volunteer::isBusy() const
{
    return activeOrderId != NO_ORDER;
}
void Volunteer::setActiveOrderId(int orderId)
{
    activeOrderId = orderId;
}

CollectorVolunteer::CollectorVolunteer(int id, const string &name, int coolDown) : coolDown(coolDown), Volunteer(id, name)
{
}

CollectorVolunteer *CollectorVolunteer::clone() const
{
    return new CollectorVolunteer(*this);
}
void CollectorVolunteer::step()
{
    decreaseCoolDown();
}
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
} // Decrease timeLeft by 1,return true if timeLeft=0,false otherwise
bool CollectorVolunteer::hasOrdersLeft() const
{
    return true;
};
bool CollectorVolunteer::canTakeOrder(const Order &order) const
{
    return !isBusy() && hasOrdersLeft() && order.getStatus() == OrderStatus::PENDING;
};
void CollectorVolunteer::acceptOrder(const Order &order)
{

    activeOrderId = order.getId();
    timeLeft = coolDown;
}
bool CollectorVolunteer::hasFininshed()
{
    return timeLeft <= 0;
}

string CollectorVolunteer::toString() const {

};

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int _id, const string &_name, int _coolDown, int _maxOrders) : maxOrders(_maxOrders), ordersLeft(maxOrders), CollectorVolunteer(_id, _name, _coolDown)
{
}
LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const
{
    return new LimitedCollectorVolunteer(*this);
}
void LimitedCollectorVolunteer::step()
{
    CollectorVolunteer::step();
}
bool LimitedCollectorVolunteer::hasOrdersLeft() const
{
    return ordersLeft > 0;
};
bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const
{
    return CollectorVolunteer::canTakeOrder(order) && hasOrdersLeft();
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

DriverVolunteer ::DriverVolunteer(int _id, const string &_name, int _maxDistance, int _distancePerStep) : maxDistance(_maxDistance), distancePerStep(_distancePerStep), Volunteer(_id, _name)
{
}
DriverVolunteer *DriverVolunteer::clone() const
{
    return new DriverVolunteer(*this);
};

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
bool DriverVolunteer ::hasOrdersLeft() const
{
    return true;
}
bool DriverVolunteer ::canTakeOrder(const Order &order) const // Signal if the volunteer is not busy and the order is within the maxDistance
{
    return !isBusy() && hasOrdersLeft() && order.getDistance() <= maxDistance && order.getStatus() == OrderStatus::COLLECTING;
};
void DriverVolunteer ::acceptOrder(const Order &order) // Assign distanceLeft to order's distance
{
    activeOrderId = order.getId();
    distanceLeft = order.getDistance();
}
void DriverVolunteer ::step() // Decrease distanceLeft by distancePerStep
{
    decreaseDistanceLeft();
}
bool DriverVolunteer::hasFininshed()
{
    return distanceLeft <= 0;
}
string DriverVolunteer ::toString() const
{
}
LimitedDriverVolunteer::LimitedDriverVolunteer(int _id, const string &_name, int _maxDistance, int _distancePerStep, int _maxOrders) : DriverVolunteer(_id, _name, _maxDistance, _distancePerStep), ordersLeft(maxOrders), maxOrders(_maxOrders) {}
LimitedDriverVolunteer *LimitedDriverVolunteer::clone() const
{
    return new LimitedDriverVolunteer(*this);
}

void LimitedDriverVolunteer::step()
{
    DriverVolunteer::step();
}
int LimitedDriverVolunteer::getMaxOrders() const
{
    return maxOrders;
}
int LimitedDriverVolunteer::getNumOrdersLeft() const
{
    return getNumOrdersLeft();
};
bool LimitedDriverVolunteer::hasOrdersLeft() const
{
    return ordersLeft > 0;
};
bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const // Signal if the volunteer is not busy, the order is within the maxDistance.
{
    return DriverVolunteer::canTakeOrder(order) && hasOrdersLeft();
}
void LimitedDriverVolunteer::acceptOrder(const Order &order) // Assign distanceLeft to order's distance and decrease ordersLeft
{
    DriverVolunteer::acceptOrder(order);
    ordersLeft--;
}
string LimitedDriverVolunteer::toString() const
{
}