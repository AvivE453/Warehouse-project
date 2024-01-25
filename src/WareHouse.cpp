#include "../include/Parse.h"
#include "../include/WareHouse.h"
#include "../include/Customer.h"
#include "../include/Action.h"
#include <iostream>

using namespace std;

WareHouse::WareHouse(const string &configFilePath) : isOpen(true), customerCounter(0), volunteerCounter(0)
{
    parse.ParseFile(configFilePath, *this);
}
void WareHouse::addCustomer(Customer *customer)
{
    customers.push_back(customer);
}

int WareHouse::assignCustomerId()
{
    int id = customerCounter;
    customerCounter++;
    return id;
}

int WareHouse::assignCustomerId()
{
    int id = orderCounter;
    orderCounter++;
    return id;
}

int WareHouse::assignVolunteerId()
{
    int id = volunteerCounter;
    volunteerCounter++;
    return id;
}

int WareHouse::getCustomerCounter() const
{
    return customerCounter;
}

int WareHouse::getOrderCounter() const
{
    return orderCounter;
}

void WareHouse::start()
{
    BaseAction *action;
    while (isOpen)
    {
        string cmd;
        cin >> cmd;
        Parse p;
        if (cmd.rfind("customer ", 0) == 0)
        {
            vector<string> words = p.tokenize(cmd, " ");
            action = new AddCustomer(words[1], words[2], stoi(words[3]), stoi(words[4]));
        }
        else if (cmd.rfind("customerStatus", 0) == 0)
        {
            vector<string> words = p.tokenize(cmd, " ");
            action = new PrintCustomerStatus(stoi(words[1]));
        }
        else if (cmd.rfind("order ", 0) == 0)
        {
            vector<string> words = p.tokenize(cmd, " ");
            int customerid(stoi(words[1]));
            action = new AddOrder(customerid);
        }
        else if (cmd.rfind("orderStatus", 0) == 0)
        {
            vector<string> words = p.tokenize(cmd, " ");
            int orderId(stoi(words[1]));
            action = new PrintOrderStatus(orderId);
        }
        else if (cmd.rfind("step ", 0) == 0)
        {
            vector<string> words = p.tokenize(cmd, " ");
            int numOfStepsstoi(stoi(words[1]));
            action = new SimulateStep(numOfStepsstoi);
        }
        action->act(*this);
    }
}
void WareHouse::addPendingOrderToList(Order *order)
{
    pendingOrders.push_back(order);
}
void WareHouse::addInProcessOrderToList(Order *order)
{
    inProcessOrders.push_back(order);
}
void WareHouse::addCompletedOrderToList(Order *order)
{
    completedOrders.push_back(order);
}
void WareHouse::addOrder(Order *order)
{
    getCustomer(order->getCustomerId()).addOrder(order->getId());
    addPendingOrderToList(order);
}
void WareHouse::addAction(BaseAction *action)
{
    actionsLog.push_back(action);
}
const vector<Order *> &WareHouse::getPendingOrders() const
{
    return pendingOrders;
}
const vector<Volunteer *> &WareHouse::getVolunteersList() const
{
    return volunteers;
}
Customer &getCustomer(int customerId) const;
Volunteer &getVolunteer(int volunteerId) const;
Order &getOrder(int orderId) const;
const vector<BaseAction *> &getActions() const;
void close();
void open();
