#include "places.h"

places::places(int id,string name,string location)
{
    this->name = name;
    this->id = id;
    this->location = location;
}

int places:: get_id(){
    return this->id;
}

string places:: get_name(){
    return this->name;
}

string places:: get_location(){
    return this->location;
}