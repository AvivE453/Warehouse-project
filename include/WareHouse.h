#pragma once
#include <string>
#include <vector>
#include "Parse.h"
#include "Order.h"
#include "Customer.h"
#include "Volunteer.h"

class BaseAction;
class Volunteer;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.

class WareHouse
{

public:
    WareHouse(const string &configFilePath);
    void start();
    void addOrder(Order *order);
    void addCustomer(Customer *costumer);
    void addAction(BaseAction *action);
    Customer &getCustomer(int customerId) const;
    Volunteer &getVolunteer(int volunteerId) const;
    Order &getOrder(int orderId) const;
    const vector<BaseAction *> &getActions() const;
    void close();
    void open();
    int assignCustomerId();
    int assignVolunteerId();
    int assignOrderId();
    int getCustomerCounter() const;
    int getOrderCounter() const;
    void addPendingOrderToList(Order *order);
    void addInProcessOrderToList(Order *order);
    void addCompletedOrderToList(Order *order);
    void removePendingOrderFromList(Order *order);
    void removeInProcessOrderFromList(Order *order);
    void removeCompletedOrderFromList(Order *order);
    const vector<Order *> &getPendingOrders() const;
    const vector<Order *> &getInProcessOrders() const;
    const vector<Order *> &getCompletedOrders() const;
    const vector<Volunteer *> &getVolunteersList() const;
    void removeVolunteerFromList(Volunteer *vulenteer);

private:
    bool isOpen;
    Parse parse;
    vector<BaseAction *> actionsLog;
    vector<Volunteer *> volunteers;
    vector<Order *> pendingOrders;
    vector<Order *> inProcessOrders;
    vector<Order *> completedOrders;
    vector<Customer *> customers;
    int customerCounter;  // For assigning unique customer IDs
    int volunteerCounter; // For assigning unique volunteer IDs
    int orderCounter;     // For assigning unique order IDs
};