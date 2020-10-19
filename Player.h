#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

using namespace std;

class Player
{
public:
    Player( int m, int v,  int g, int s, int d,int doc, int r ,int j){
        mafia_members = m;
        villager_members = v;
        godfather_members = g;
        silencer_members = s;
        detective_members = d;
        doctor_members = doc;
        rouintan_members = r;
        joker_members = j;
    }
    Player () {
        
    }

    int get_mafia_members(){return mafia_members;}
    int get_villager_members(){return villager_members;}
    int get_godfather_members(){return godfather_members;}
    int get_silencer_members(){return silencer_members;}
    int get_detective_members(){return detective_members;}
    int get_doctor_members(){return doctor_members;}
    int get_rouintan_members(){return rouintan_members;}
    int get_joker_members(){return joker_members;}


    void set_mafia_members(){ mafia_members--;}
    void set_villager_members(){ villager_members--;}
    void set_godfather_members(){ godfather_members--;}
    void set_silencer_members(){ silencer_members--;}
    void set_detective_members(){ detective_members--;}
    void set_doctor_members(){ doctor_members--;}
    void set_rouintan_members(){ rouintan_members--;}


private:
    int mafia_members;
    int villager_members;
    int godfather_members;
    int silencer_members;
    int detective_members;
    int doctor_members;
    int rouintan_members;
    int joker_members;
};


class Mafia : public Player{

public:
    Mafia(vector<string> v){
        for(int i = 0 ; i < v.size() ; i++)
            username.push_back(v[i]);
    }
    Mafia( ){
        username.push_back(" ");
    }

    vector<string> get_mafia_usernames(){return username;}
    void set_mafia_usernames(int x){username.erase(username.begin() + x);}
    
private:
    vector<string> username;
};




class Villager : public Player{

public:
    Villager(vector<string> v){
        for(int i = 0 ; i < v.size() ; i++)
            username.push_back(v[i]);
    }
    Villager( ){
        username.push_back(" ");

    }

    vector<string> get_villager_usernames(){return username;}
    void set_villager_usernames(int x){username.erase(username.begin() + x);}

private:
    vector<string> username;
};


class GodFather : public  Mafia{

public:
    GodFather(vector<string> v){
        for(int i = 0 ; i < v.size() ; i++)
            username.push_back(v[i]);
    }
    GodFather( ){
        username.push_back(" ");

    }
    
    vector<string> get_godfather_usernames(){return username;}
    void set_godfather_usernames(int x){username.erase(username.begin() + x);}

private:
    vector<string> username;
};


class Silencer : public  Mafia{

public:
    Silencer(vector<string> v){
        for(int i = 0 ; i < v.size() ; i++)
            username.push_back(v[i]);
    }
    Silencer( ){
        username.push_back(" ");

    }
    
    vector<string> get_silencer_usernames(){return username;}
    void set_silencer_usernames(int x){username.erase(username.begin() + x);}

private:
    vector<string> username;
};


class Detective : public  Villager{

public:
    Detective(vector<string> v){
        for(int i = 0 ; i < v.size() ; i++)
            username.push_back(v[i]);
    }
    Detective( ){
        username.push_back(" ");

    }
    
    vector<string> get_detective_usernames(){return username;}
    void set_detective_usernames(int x){username.erase(username.begin() + x);}

private:
    vector<string> username;
};


class Doctor : public  Villager{

public:
    Doctor(vector<string> v) {
        for(int i = 0 ; i < v.size() ; i++)
            username.push_back(v[i]);
    }
    Doctor( ){
        username.push_back(" ");
    }
    
    vector<string> get_doctor_usernames(){return username;}
    void set_doctor_usernames(int x){username.erase(username.begin() + x);}

private:
    vector<string> username;
};


class RouinTan : public Villager{

public:
    RouinTan(vector<string> v){
        for(int i = 0 ; i < v.size() ; i++)
            username.push_back(v[i]);
    }
    RouinTan( ){
        username.push_back(" ");
    }
    vector<string> get_rouintan_usernames(){return username;}
    void set_rouintan_usernames(int x){username.erase(username.begin() + x);}

private:
    vector<string> username;
};



class Joker : public Player {

public:
    Joker(vector<string> v){
        for(int i = 0 ; i < v.size() ; i++)
            username.push_back(v[i]);
    }
    Joker( ){
        username.push_back(" ");
    }
    vector<string> get_joker_usernames(){return username;}
private:
    vector<string> username;

};


#endif



