#pragma once
#include <string>
#include <vector>
#include "WareHouse.h"
using std::string;
using std::vector;
class Customer
{
public:
    Customer(int id, const string &name, int locationDistance, int maxOrders);
    const string &getName() const;
    Customer(const Customer &other);
    int getId() const;
    int getCustomerDistance() const;
    int getMaxOrders() const;  // Returns maxOrders
    int getNumOrders() const;  // Returns num of orders the customer has made so far
    bool canMakeOrder() const; // Returns true if the customer didn't reach max orders
    const vector<int> &getOrdersIds() const;
    int addOrder(int orderId); // return OrderId if order was added successfully, -1 otherwise
    string toString(WareHouse &wareHouse);
    virtual Customer *clone() const = 0; // Return a copy of the customer

private:
    const int id;
    const string name;
    const int locationDistance;
    const int maxOrders;
    vector<int> ordersId;
};

class SoldierCustomer : public Customer
{
public:
    SoldierCustomer(int id, const string &name, int locationDistance, int maxOrders);
    SoldierCustomer(const SoldierCustomer &other);
    SoldierCustomer *clone() const override;

private:
};

class CivilianCustomer : public Customer
{
public:
    CivilianCustomer(int id, const string &name, int locationDistance, int maxOrders);
    CivilianCustomer(const CivilianCustomer &other);
    CivilianCustomer *clone() const override;

private:
};