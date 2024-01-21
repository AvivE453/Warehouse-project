#include "../include/Parse.h"
#include "../include/WareHouse.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"

Volunteer::Volunteer(int _id, const string &_name): id(_id), name(_name), activeOrderId(NO_ORDER), completedOrderId(NO_ORDER){

}



 int Volunteer::getId() const{
    return id;
 }
 const string& Volunteer::getName() const{
    return name;
 };
 int Volunteer::getActiveOrderId() const{
    return activeOrderId;
 };
 int Volunteer::getCompletedOrderId() const{
    return completedOrderId;
 };
 bool Volunteer::isBusy() const{
    return activeOrderId!=NO_ORDER;

 }; // Signal whether the volunteer is currently processing an order


CollectorVolunteer::CollectorVolunteer(int _id, const string &_name, int _coolDown): coolDown(_coolDown), Volunteer(_id ,_name){

}

CollectorVolunteer *CollectorVolunteer::clone() const{

};
void CollectorVolunteer::step(){

};
int CollectorVolunteer::getCoolDown() const{
     return coolDown;
};
int CollectorVolunteer::getTimeLeft() const{
    return timeLeft;
};
bool CollectorVolunteer::decreaseCoolDown(){
    timeLeft--;
    return timeLeft == 0;
};//Decrease timeLeft by 1,return true if timeLeft=0,false otherwise
bool CollectorVolunteer::hasOrdersLeft() const {
    return true;
};
bool CollectorVolunteer::canTakeOrder(const Order &order) const {
    return !isBusy() && hasOrdersLeft();
};
void CollectorVolunteer::acceptOrder(const Order &order) {
    activeOrderId=order.getId();
    timeLeft=coolDown;
};
string CollectorVolunteer::toString() const {
    
};

  LimitedCollectorVolunteer::LimitedCollectorVolunteer(int _id, const string &_name, int _coolDown ,int _maxOrders):maxOrders(_maxOrders), CollectorVolunteer( _id, _name,_coolDown){

  }
    LimitedCollectorVolunteer* LimitedCollectorVolunteer::clone() const{
            
        };
        bool LimitedCollectorVolunteer::hasOrdersLeft() const {
            return ordersLeft>0;
        };
        bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const{
            return !isBusy() && hasOrdersLeft();
        };
        void LimitedCollectorVolunteer::acceptOrder(const Order &order) {
             CollectorVolunteer::acceptOrder(order);
             ordersLeft--;
        };

        int LimitedCollectorVolunteer::getMaxOrders() const{
                return maxOrders;
        };
        int LimitedCollectorVolunteer::getNumOrdersLeft() const{
            return ordersLeft;
        };
        string LimitedCollectorVolunteer::toString() const{
            
        };