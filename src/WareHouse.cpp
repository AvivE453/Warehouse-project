#include "../include/Parse.h"
#include "../include/WareHouse.h"
#include "../include/Customer.h"
#include "../include/Action.h"
#include "../include/Volunteer.h"
#include <iostream>

using namespace std;


WareHouse::WareHouse(const string &configFilePath) : isOpen(true), customerCounter(0), volunteerCounter(0), orderCounter(0)
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

int WareHouse::assignOrderId()
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
int WareHouse::getVolunteerCounter() const
{
    return volunteerCounter;
}
void WareHouse::start()
{
    BaseAction *action = nullptr;
    open();
    while (isOpen)
    {
        string cmd;
        getline(cin, cmd);
        Parse p;
        if (cmd.rfind("customer ", 0) == 0)
        {
            vector<string> words = p.tokenize(cmd, " ");
            action = new AddCustomer(words.at(1), words.at(2), stoi(words.at(3)), stoi(words.at(4)));
        }
        else if (cmd.rfind("customerStatus ", 0) == 0)
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
        else if (cmd.rfind("orderStatus ", 0) == 0)
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
        else if (cmd.rfind("volunteerStatus ", 0) == 0)
        {
            vector<string> words = p.tokenize(cmd, " ");
            int volunteerId(stoi(words[1]));
            action = new PrintVolunteerStatus(volunteerId);
        }
        else if (cmd.rfind("log", 0) == 0)
        {
            action = new PrintActionsLog();
        }
        else if (cmd.rfind("close", 0) == 0)
        {
            action = new Close();
            close();
        }
        else if (cmd.rfind("backup", 0) == 0)
        {
            action = new BackupWareHouse();
        }
        else if (cmd.rfind("restore", 0) == 0)
        {
            action = new RestoreWareHouse();
        }
        else
        {
            continue;
        }
        action->act(*this);
        addAction(action);
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
void WareHouse::addVolunteer(Volunteer *volunteer)
{
    volunteers.push_back(volunteer);
}

const vector<Volunteer *> &WareHouse::getVolunteersList() const
{
    return volunteers;
}
const vector<BaseAction *> &WareHouse::getActionsLog() const
{
    return actionsLog;
}
WareHouse::WareHouse(const WareHouse &other) : isOpen(other.isOpen), parse(other.parse),
                                               customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter),
                                               orderCounter(other.orderCounter)
{
    for (int i = 0; i < other.actionsLog.size(); i++)
    {
        actionsLog.push_back(other.actionsLog.at(i)->clone());
    }
    for (int i = 0; i < other.volunteers.size(); i++)
    {
        volunteers.push_back(other.volunteers.at(i)->clone());
    }
    for (int i = 0; i < other.deletedVolunteers.size(); i++)
    {
        deletedVolunteers.push_back(other.deletedVolunteers.at(i)->clone());
    }
    for (int i = 0; i < other.pendingOrders.size(); i++)
    {
        pendingOrders.push_back(other.pendingOrders.at(i)->clone());
    }
    for (int i = 0; i < other.inProcessOrders.size(); i++)
    {
        inProcessOrders.push_back(other.inProcessOrders.at(i)->clone());
    }
    for (int i = 0; i < other.completedOrders.size(); i++)
    {
        completedOrders.push_back(other.completedOrders.at(i)->clone());
    }
    for (int i = 0; i < other.customers.size(); i++)
    {
        customers.push_back(other.customers.at(i)->clone());
    }
}

WareHouse::WareHouse(WareHouse &&other) : isOpen(other.isOpen), parse(other.parse),
                                          customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter),
                                          orderCounter(other.orderCounter)
{
    for (int i = 0; i < other.actionsLog.size(); i++)
    {
        actionsLog.push_back(other.actionsLog.at(i));
        other.actionsLog.at(i) = nullptr;
    }
    for (int i = 0; i < other.volunteers.size(); i++)
    {
        volunteers.push_back(other.volunteers.at(i)->clone());
        other.volunteers.at(i) = nullptr;
    }
       for (int i = 0; i < other.deletedVolunteers.size(); i++)
    {
        deletedVolunteers.push_back(other.deletedVolunteers.at(i)->clone());
        other.deletedVolunteers.at(i) = nullptr;
    }
    for (int i = 0; i < other.pendingOrders.size(); i++)
    {
        pendingOrders.push_back(other.pendingOrders.at(i)->clone());
        other.pendingOrders.at(i) = nullptr;
    }
    for (int i = 0; i < other.inProcessOrders.size(); i++)
    {
        inProcessOrders.push_back(other.inProcessOrders.at(i)->clone());
        other.inProcessOrders.at(i) = nullptr;
    }
    for (int i = 0; i < other.completedOrders.size(); i++)
    {
        completedOrders.push_back(other.completedOrders.at(i)->clone());
        other.completedOrders.at(i) = nullptr;
    }
    for (int i = 0; i < other.customers.size(); i++)
    {
        customers.push_back(other.customers.at(i)->clone());
        other.customers.at(i) = nullptr;
    }
}

WareHouse *WareHouse::clone() const
{
    return new WareHouse(*this);
}
WareHouse& WareHouse::operator=(const WareHouse &other)
{
    if (&other != this)
    {
        isOpen = other.isOpen;
        parse = other.parse;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        orderCounter = other.orderCounter;
        for (int i = 0; i < actionsLog.size(); i++)
        {
            delete actionsLog.at(i);
        }
        actionsLog.clear();
        for (int i = 0; i < other.actionsLog.size(); i++)
        {
            actionsLog.push_back(other.actionsLog.at(i)->clone());
        }
        for (int i = 0; i < pendingOrders.size(); i++)
        {
            delete pendingOrders.at(i);
        }
        pendingOrders.clear();
        for (int i = 0; i < other.pendingOrders.size(); i++)
        {
            pendingOrders.push_back(other.pendingOrders.at(i)->clone());
        }
        for (int i = 0; i < inProcessOrders.size(); i++)
        {
            delete inProcessOrders.at(i);
        }
        inProcessOrders.clear();
        for (int i = 0; i < other.inProcessOrders.size(); i++)
        {
            inProcessOrders.push_back(other.inProcessOrders.at(i)->clone());
        }
        for (int i = 0; i < completedOrders.size(); i++)
        {
            delete completedOrders.at(i);
        }
        completedOrders.clear();
        for (int i = 0; i < other.completedOrders.size(); i++)
        {
            completedOrders.push_back(other.completedOrders.at(i)->clone());
        }
        for (int i = 0; i < customers.size(); i++)
        {
            delete customers.at(i);
        }
        customers.clear();
        for (int i = 0; i < other.customers.size(); i++)
        {
            customers.push_back(other.customers.at(i)->clone());
        }
        for (int i = 0; i < volunteers.size(); i++)
        {
            delete volunteers.at(i);
        }
        volunteers.clear();
        for (int i = 0; i < other.volunteers.size(); i++)
        {
            volunteers.push_back(other.volunteers.at(i)->clone());
        }
        for (int i = 0; i < deletedVolunteers.size(); i++)
        {
            delete deletedVolunteers.at(i);
        }
        deletedVolunteers.clear();
        for (int i = 0; i < other.deletedVolunteers.size(); i++)
        {
            deletedVolunteers.push_back(other.deletedVolunteers.at(i)->clone());
        }
    }
    return *this;
}

WareHouse& WareHouse::operator=(WareHouse &&other)
{
    if (&other != this)
    {
        isOpen = other.isOpen;
        parse = other.parse;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        orderCounter = other.orderCounter;
        for (int i = 0; i < actionsLog.size(); i++)
        {
            delete actionsLog.at(i);
        }
        actionsLog.clear();
        for (int i = 0; i < other.actionsLog.size(); i++)
        {
            actionsLog.push_back(other.actionsLog.at(i));
            other.actionsLog.at(i) = nullptr;
        }
        for (int i = 0; i < pendingOrders.size(); i++)
        {
            delete pendingOrders.at(i);
        }
        pendingOrders.clear();
        for (int i = 0; i < other.pendingOrders.size(); i++)
        {
            pendingOrders.push_back(other.pendingOrders.at(i));
            other.pendingOrders.at(i) = nullptr;
        }
        for (int i = 0; i < inProcessOrders.size(); i++)
        {
            delete inProcessOrders.at(i);
        }
        inProcessOrders.clear();
        for (int i = 0; i < other.inProcessOrders.size(); i++)
        {
            inProcessOrders.push_back(other.inProcessOrders.at(i));
            inProcessOrders.at(i) = nullptr;
        }
        for (int i = 0; i < completedOrders.size(); i++)
        {
            delete completedOrders.at(i);
        }
        completedOrders.clear();
        for (int i = 0; i < other.completedOrders.size(); i++)
        {
            completedOrders.push_back(other.completedOrders.at(i));
            other.completedOrders.at(i) = nullptr;
        }
        for (int i = 0; i < customers.size(); i++)
        {
            delete customers.at(i);
        }
        customers.clear();
        for (int i = 0; i < other.customers.size(); i++)
        {
            customers.push_back(other.customers.at(i));
            other.customers.at(i) = nullptr;
        }
        for (int i = 0; i < volunteers.size(); i++)
        {
            delete volunteers.at(i);
        }
        volunteers.clear();
        for (int i = 0; i < other.volunteers.size(); i++)
        {
            volunteers.push_back(other.volunteers.at(i));
            other.volunteers.at(i) = nullptr;
        }
        for (int i = 0; i < deletedVolunteers.size(); i++)
        {
            delete deletedVolunteers.at(i);
        }
        deletedVolunteers.clear();
        for (int i = 0; i < other.deletedVolunteers.size(); i++)
        {
            deletedVolunteers.push_back(other.deletedVolunteers.at(i));
            other.deletedVolunteers.at(i) = nullptr;
        }
    }
    return *this;
}
Customer &WareHouse::getCustomer(int customerId) const
{
    for (int i = 0; i < customers.size(); i++)
    {
        if (customers[i]->getId() == customerId)
            return *customers[i];
    }
}
Volunteer &WareHouse::getVolunteer(int volunteerId) const
{
    for (int i = 0; i < volunteers.size(); i++)
    {
        if (volunteers[i]->getId() == volunteerId) 
            return *volunteers[i];        
    }
}
Order &WareHouse::getOrder(int orderId) const
{
    for (int i = 0; i < pendingOrders.size(); i++)
    {
        if (pendingOrders[i]->getId() == orderId)
            return *pendingOrders[i];
    }
    for (int i = 0; i < inProcessOrders.size(); i++)
    {
        if (inProcessOrders[i]->getId() == orderId)
            return *inProcessOrders[i];
    }
    for (int i = 0; i < completedOrders.size(); i++)
    {
        if (completedOrders[i]->getId() == orderId)
            return *completedOrders[i];
    }
}
const vector<BaseAction *> &WareHouse::getActions() const
{
    return actionsLog;
}
void WareHouse::close()
{
    isOpen = false;
}
void WareHouse::open()
{
    isOpen = true;
}

void WareHouse::removePendingOrderFromList(Order *order)
{
    for (int i = 0; i < pendingOrders.size(); i++)
    {
        if (order == pendingOrders[i])
            pendingOrders.erase(pendingOrders.begin() + i);
    }
}
void WareHouse::removeInProcessOrderFromList(Order *order)
{
    for (int i = 0; i < inProcessOrders.size(); i++)
    {
        if (order == inProcessOrders[i])
            inProcessOrders.erase(inProcessOrders.begin() + i);
    }
}
void WareHouse::removeVolunteerFromList(Volunteer *volunteer)
{
    for (int i = 0; i < volunteers.size(); i++)
    {
        if (volunteer == volunteers[i])
        {
            volunteers.erase(volunteers.begin() + i);
            deletedVolunteers.push_back(volunteers[i]);
        }
    }
}

WareHouse::~WareHouse()
{
    for (int i = 0; i < actionsLog.size(); i++)
    {
        delete actionsLog.at(i);
    }
    actionsLog.clear();
    for (int i = 0; i < volunteers.size(); i++)
    {
        delete volunteers.at(i);
    }
    volunteers.clear();
        for (int i = 0; i < deletedVolunteers.size(); i++)
    {
        delete deletedVolunteers.at(i);
    }
    deletedVolunteers.clear();
    for (int i = 0; i < pendingOrders.size(); i++)
    {
        delete pendingOrders.at(i);
    }
    pendingOrders.clear();
    for (int i = 0; i < inProcessOrders.size(); i++)
    {
        delete inProcessOrders.at(i);
    }
    inProcessOrders.clear();
    for (int i = 0; i < completedOrders.size(); i++)
    {
        delete completedOrders.at(i);
    }
    completedOrders.clear();
    for (int i = 0; i < customers.size(); i++)
    {
        delete customers.at(i);
    }
    customers.clear();
}
const vector<Order *> &WareHouse::getPendingOrders() const
{
    return pendingOrders;
}
const vector<Order *> &WareHouse::getInProcessOrders() const
{
    return inProcessOrders;
}
const vector<Order *> &WareHouse::getCompletedOrders() const
{
    return completedOrders;
}