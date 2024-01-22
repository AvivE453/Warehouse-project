#include "../include/Parse.h"
#include "../include/WareHouse.h"

WareHouse::WareHouse(const string &configFilePath):isOpen(true), customerCounter(0), volunteerCounter(0){
    parse.ParseFile(configFilePath);

}
