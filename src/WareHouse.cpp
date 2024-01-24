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
            addOrder();
        }
        action->act(*this);
    }
}

void addOrder(Order *order);
void addAction(BaseAction *action);
Customer &getCustomer(int customerId) const;
Volunteer &getVolunteer(int volunteerId) const;
Order &getOrder(int orderId) const;
const vector<BaseAction *> &getActions() const;
void close();
void open();
