#include "../include/Order.h"

Order ::Order(int _id, int _customerId, int _distance) id(_id), customerId(_customerId), distance(_dist), status(PENDING), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER)
{
}
int Order ::getId() const
{
  return id;
}
int Order ::getCustomerId() const
{
  return cusotmerId;
}
int Order ::getDistance() const
{
  return distance;
};
void Order ::setStatus(OrderStatus status)
{
  this->status = status;
};
void Order ::setCollectorId(int collectorId)
{
  this->collectorId = collectorId;
}
void Order ::setDriverId(int driverId)
{
  this->driverId = driverId;
}
int Order ::getCollectorId() const
{
  return collectorId;
};
int Order ::getDriverId() const
{
  return driverId;
};
OrderStatus Order ::getStatus() const
{
  return status;
};
const string Order ::toString() const {

};