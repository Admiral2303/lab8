/** @file
    @brief Generic list abstract data type
*/
#ifndef PLACES_H
#define PLACES_H
#include <string>
using namespace std;

class places
{
    int id;
    string name;
    string location;

public:
    places(int id,string name,string location);
    int get_id();
    string get_name();
    string get_location();
};

#endif // PLACES_H