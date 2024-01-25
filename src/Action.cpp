#include "../include/Action.h"
#include <iostream>
#include "../include/WareHouse.h"
#include "../include/Order.h"
#include "../include/Volunteer.h"
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
  status = ActionStatus::COMPLETED;
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
AddOrder::AddOrder(int id) : customerId(id)
{
}
AddOrder::AddOrder(const AddOrder &other) : customerId(other.customerId)
{
}

void AddOrder::act(WareHouse &wareHouse)
{
  wareHouse.addAction(this);
  Customer *customer = &wareHouse.getCustomer(customerId);
  if (customerId < wareHouse.getCustomerCounter() && customer->canMakeOrder())
  {
    Order *order = new Order(wareHouse.assignOrderId(), customerId,
                             customer->getCustomerDistance());
    wareHouse.addOrder(order);
  }
  else
    cout << "Cannot place this order" << endl;
}
string AddOrder::toString() const {};
AddOrder *AddOrder::clone() const
{
  return new AddOrder(*this);
}

SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps) {}
void SimulateStep::act(WareHouse &wareHouse)
{
  for (int step = 1; step < numOfSteps; step++)
  {
    vector<Volunteer *> voulnteers = wareHouse.getVolunteersList();
    for (Order *order : wareHouse.getPendingOrders())
    {

      for (int i = 0; i < voulnteers.size(); i++)
      {
        if (voulnteers[i]->canTakeOrder(*order))
        {
          voulnteers[i]->acceptOrder(*order);
          if (order->getStatus() == OrderStatus::PENDING)
            order->setStatus(OrderStatus::COLLECTING);
        }

        wareHouse.removePendingOrderFromList(order);
      }
      for (int i = 0; i < voulnteers.size(); i++)
      {
        voulnteers[i]->step();
        if (voulnteers[i]->hasFininshed())
        {
          if (order->getStatus() == OrderStatus::DELIVERING)
          {
            wareHouse.addCompletedOrderToList(order);
            order->setStatus(OrderStatus::COMPLETED);
          }
          else
          {
            wareHouse.addPendingOrderToList(order);
          }
          wareHouse.removeInProcessOrderFromList(order);
          if (typeid(voulnteers[i]) == typeid(LimitedCollectorVolunteer) || typeid(voulnteers[i]) == typeid(LimitedDriverVolunteer))
          {
            if (!voulnteers[i]->hasOrdersLeft())
            {
              wareHouse.removeVolunteerFromList(voulnteers[i]);
            }
          }
        }
      }
    }
  }
}
std::string SimulateStep::toString() const {}
SimulateStep *SimulateStep::clone() const {}

PrintOrderStatus::PrintOrderStatus(int id) : orderId(id) {}
void PrintOrderStatus::act(WareHouse &wareHouse)
{
  if (orderId >= 0 && orderId < wareHouse.getOrderCounter())
  {
    Order order(wareHouse.getOrder(orderId));
    cout << "OrderId: " << orderId << endl;
    string status;
    switch (order.getStatus())
    {
    case OrderStatus::PENDING:
      status = "Pending";
      break;
    case OrderStatus::DELIVERING:
      status = "Delivering";
      break;
    case OrderStatus::COLLECTING:
      status = "Collecting";
      break;
    case OrderStatus::COMPLETED:
      status = "Completed";
      break;
    }
    cout << "OrderStatus: " << status << endl;
    cout << "CustomerID: " << order.getCustomerId() << endl;
    string collectorId = order.getStatus() != OrderStatus::PENDING ? to_string(order.getCollectorId()) : "None";
    cout << "CollectorID: " << collectorId << endl;
    string driverId = order.getStatus() == OrderStatus::DELIVERING || order.getStatus() == OrderStatus::COMPLETED ? to_string(order.getDriverId()) : "None";
    cout << "DriverID: " << driverId << endl;
  }
  else
  {
    cout << "Order doesn't exist" << endl;
  }
}
PrintOrderStatus *PrintOrderStatus::clone() const {};
string PrintOrderStatus::toString() const {};