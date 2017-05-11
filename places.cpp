#include "places.h"

places::places(int id,QString name,QString location)
{
    this->name = name;
    this->id = id;
    this->location = location;
}

int places:: get_id(){
    return this->id;
}

QString places:: get_name(){
    return this->name;
}

QString places:: get_location(){
    return this->location;
}
