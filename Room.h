#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Room{

public:
    Room(string str){
        room_name = str;
    }

    void set_day_num(){day_num++;}
    void set_night_num(){night_num++;}
    int get_day_num(){return day_num;}
    int get_night_num(){return night_num;}
    bool get_is_day(){return is_day;}
    void set_is_day(bool x){is_day = x;}
    bool get_is_night(){return is_night;}
    void set_is_night(bool x){is_night = x;}
private:
    string room_name;
    int day_num = 0;
    bool is_day = false;
    int night_num = 0;
    bool is_night = false;
};

#endif


