#ifndef PLACES_H
#define PLACES_H
#include <QString>

class places
{
    int id;
    QString name;
    QString location;

public:
    places(int id,QString name,QString location);
    int get_id();
    QString get_name();
    QString get_location();
};

#endif // PLACES_H
