#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Room.h"
#include "Player.h" 

using namespace std;

class Invalid_role_name {};
class Invalid_room_name {};
class Invalid_special_members {};
class Many_users {};
class User_Already_Died {};
class User_Not_joind {};
class Detective_Has_Already_asked{};
class User_Can_Not_ask {};
class Person_Is_Dead {};
class This_User_Can_Not_Vote {};
class Doctor_Has_Already_Healed {};
class User_Can_Not_Heal {};
class User_Can_Not_Silence {};

template < typename T>
std::pair<bool, int > findInVector(const std::vector<T>  & vecOfElements, const T  & element);
void create_room();
void switch_room();
bool is_equal(vector<string> usernames);
void join();
void end_vote(int max_index);
int vote();
void detect();
void heal();
void silent();
void end_match();
void get_room_state();
void order(string str);

#endif
