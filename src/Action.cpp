#include "../include/Action.h"
#include <iostream>
#include "../include/WareHouse.h"
using namespace std;

BaseAction::BaseAction()
{
}

ActionStatus BaseAction::getStatus() const
{
  return status;
}

void BaseAction::complete()
{
  status = (ActionStatus::COMPLETED);
}

void BaseAction::error(string errorMsg)
{
  status = (ActionStatus::ERROR);
  cout << "Error: " << errorMsg << endl;
  this->errorMsg = errorMsg;
}

string BaseAction::getErrorMsg() const
{
  return errorMsg;
}

AddCustomer::AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders) : customerName(customerName), customerType(convertCustomerType(customerType)), distance(distance), maxOrders(maxOrders)
{
}

AddCustomer::AddCustomer(const AddCustomer &other) : customerName(other.customerName), customerType(other.customerType), distance(other.distance), maxOrders(other.maxOrders)
{
}

void AddCustomer::act(WareHouse &wareHouse)
{
  Customer *customer;
  if (customerType == CustomerType::Soldier)
  {
    customer = new SoldierCustomer(wareHouse.assignCustomerId(), customerName, distance, maxOrders);
  }
  else
  {
    customer = new CivilianCustomer(wareHouse.assignCustomerId(), customerName, distance, maxOrders);
  }
  wareHouse.addCustomer(customer);
}

AddCustomer *AddCustomer::clone() const
{
  return new AddCustomer(*this);
}
string AddCustomer::toString() const
{
}

CustomerType AddCustomer::convertCustomerType(const string &customerType) const
{
  if (customerType == "soldier")
    return CustomerType::Soldier;
  return CustomerType::Civilian;
}
PrintCustomerStatus::PrintCustomerStatus(int customerId) : customerId(customerId)
{
}

PrintCustomerStatus::PrintCustomerStatus(const PrintCustomerStatus &other) : customerId(other.customerId)
{
}

void PrintCustomerStatus::act(WareHouse &wareHouse)
{
  if (customerId < wareHouse.getCustomerCounter())
  {
    Customer *customer = &wareHouse.getCustomer(customerId);
    cout << customer->toString(wareHouse) << endl;
  }
  else
  {
    cout << "customer doesn't exist " << endl;
  }
}
PrintCustomerStatus *PrintCustomerStatus::clone() const
{
  return new PrintCustomerStatus(*this);
}
string PrintCustomerStatus::toString() const
{
}