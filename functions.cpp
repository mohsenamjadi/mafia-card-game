#include "functions.h"

vector<Player*> player;
vector<Room*> rooms;
vector<string> rooms_name;
vector<Mafia*> mafia;
vector<Villager*> villager;
vector<GodFather*> godfather;
vector<Silencer*> silencer;
vector<Detective*> detective;
vector<Doctor*> doctor;
vector<RouinTan*> rouintan;
vector<Joker*> joker;
string role_name[8]={"-Joker","-Villager","-Detective","-Doctor","-RouinTan","-Mafia","-GodFather","-Silencer"};
int current_room = 0;
vector<string> votee_name_vec;
vector<string> killed_usernames;
vector<string> killed_by_mafia;
vector<string> silenced_usernames;
int m_i;

template < typename T>
std::pair<bool, int > findInVector(const std::vector<T>  & vecOfElements, const T  & element)
{
    std::pair<bool, int > result;
 
    auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
 
    if (it != vecOfElements.end())
    {
        result.second = distance(vecOfElements.begin(), it);
        result.first = true;
    }
    else
    {
        result.first = false;
        result.second = -1;
    }
 
    return result;
}

void create_room(){

    string x;
    cin >> x;
    for(int i = 0 ; i < rooms_name.size() ; i++){
        if(x == rooms_name[i])
            throw Invalid_room_name();
    }
    rooms.push_back ( new Room ( x ) );
    rooms_name.push_back(x);


      pair<bool, int> result2 = findInVector<string>(rooms_name, x);
    if (result2.first)
        current_room = result2.second;
    else
        cout << "element not found" << endl;



    vector <string> roles;
    string line, role;
    getline(cin, line);
    stringstream iss(line);
    while(iss >> role) {
        roles.push_back(role);
    }

    line.erase(line.begin());

    for (int i=0;i<roles.size();i+=2) {
        bool flag = false;
        for(int j =0; j<8 ; j++){
            if(roles[i] == role_name[j] ){
                flag = true;   }
        }
        if (flag == false){
            throw Invalid_role_name();
        }
    }


    int m=0,v=0,g=0,s=0,d=0,doc=0,r=0,j=0;
   
    for(int i = 0 ; i < roles.size() ; i+=2){
        if(roles[i] == "-Mafia"){
            m = stoi(roles[i+1]);
        }
        else if(roles[i] == "-Villager"){
            v = stoi(roles[i+1]);
        }
        else if(roles[i] == "-GodFather"){
            g = stoi(roles[i+1]);
        }
        else if(roles[i] == "-Silencer"){
            s = stoi(roles[i+1]);
        }
        else if(roles[i] == "-Detective"){
            d = stoi(roles[i+1]);
        }
        else if(roles[i] == "-Doctor"){
            doc = stoi(roles[i+1]);
        }
        else if(roles[i] == "-RouinTan"){
            r = stoi(roles[i+1]);
        }
        else if(roles[i] == "-Joker"){
            j = stoi(roles[i+1]);
        }
        else{
            throw Invalid_role_name();
        }
    }

    //cout << " m = " << m << endl;
    //cout << " v = " << v << endl;


    if(g + s <= m && d + doc + r <= v)
        player.push_back ( new Player (m, v, g, s, d, doc, r, j) );
    else
        throw Invalid_special_members();

    //cout << player[current_room] -> get_mafia_members();

    roles.clear();
}

void switch_room(){

    string str;
    cin >> str;

    bool check = false;
    for(int i = 0 ; i < rooms_name.size() ; i++){
        if(str == rooms_name[i])
            check = true;
    }
    if(check == false)
        throw Invalid_room_name();
        
    pair<bool, int> result = findInVector<string>(rooms_name, str);
    if (result.first)
        current_room = result.second;
    else
        cout << "Element Not Found" << endl;



    //cout << player[current_room] -> get_mafia_members();

}

bool is_equal(vector<string> usernames){

    int sum_0f_members = 0;


    sum_0f_members = player[current_room] -> get_mafia_members() + player[current_room] -> get_villager_members()
    + player[current_room] -> get_godfather_members() + player[current_room] -> get_silencer_members()
    + player[current_room] -> get_detective_members() + player[current_room] -> get_doctor_members()
    + player[current_room] -> get_rouintan_members() + player[current_room] -> get_joker_members ();

    if(sum_0f_members == usernames.size())
        return true;
    else if(sum_0f_members < usernames.size())
        throw Many_users();
    else
        return false;

}

void join(){

    vector <string> usernames;
    vector <string> mafia_usernames;
    vector <string> villager_usernames;
    vector <string> godfather_usernames;
    vector <string> silencer_usernames;
    vector <string> detective_usernames;
    vector <string> doctor_usernames;
    vector <string> rouintan_usernames;
    vector <string> joker_usernames;


    string line, user;
    getline(cin, line);
    stringstream iss(line);
    while(iss >> user) {
        usernames.push_back(user);
    }

    try {
     if(is_equal(usernames))
    
    {   
        int n = usernames.size (); 
        if(player[current_room] -> get_mafia_members() != 0){     
            for(int i = usernames.size()-1 ; i >= n - (player[current_room] -> get_mafia_members()) ; i-- ){
                mafia_usernames.push_back(usernames[i]);
                usernames.pop_back();
            }
        }

        n -= player[current_room] -> get_mafia_members();

        if(player[current_room] -> get_villager_members() != 0){     
            for(int i = usernames.size()-1 ; i >= n - (player[current_room] -> get_villager_members()) ; i-- ){
                villager_usernames.push_back(usernames[i]);
                usernames.pop_back();
            }
        }

        n -= player[current_room] -> get_villager_members();

        if(player[current_room] -> get_godfather_members() != 0){     
            for(int i = usernames.size()-1 ; i >= n - (player[current_room] -> get_godfather_members()) ; i-- ){
                godfather_usernames.push_back(usernames[i]);
                usernames.pop_back();
            }
        }

        n -= player[current_room] -> get_godfather_members();

        if(player[current_room] -> get_silencer_members() != 0){     
            for(int i = usernames.size()-1 ; i >= n - (player[current_room] -> get_silencer_members()) ; i-- ){
                silencer_usernames.push_back(usernames[i]);
                usernames.pop_back();
            }
        }

        n -= player[current_room] -> get_silencer_members();

        if(player[current_room] -> get_detective_members() != 0){     
            for(int i = usernames.size()-1 ; i >= n - (player[current_room] -> get_detective_members()) ; i-- ){
                detective_usernames.push_back(usernames[i]);
                usernames.pop_back();
            }
        }

        n -= player[current_room] -> get_detective_members();

        if(player[current_room] -> get_doctor_members() != 0){     
            for(int i = usernames.size()-1 ; i >= n - (player[current_room] -> get_doctor_members()) ; i-- ){
                doctor_usernames.push_back(usernames[i]);
                usernames.pop_back();
            }
        }

        n -= player[current_room] -> get_doctor_members();

        if(player[current_room] -> get_rouintan_members() != 0){     
            for(int i = usernames.size()-1 ; i >= n - (player[current_room] -> get_rouintan_members()) ; i-- ){
                rouintan_usernames.push_back(usernames[i]);
                usernames.pop_back();
            }
        }

        n -= player[current_room] -> get_rouintan_members();

        if(player[current_room] -> get_joker_members() != 0){     
            for(int i = usernames.size()-1 ; i >= n - (player[current_room] -> get_joker_members()) ; i-- ){
                joker_usernames.push_back(usernames[i]);
                usernames.pop_back();
            }
        }
    }
    } catch (Many_users m_u) {
        cout << "Many User\n";
        return;
    }
    if(player[current_room] -> get_mafia_members() != 0){
        mafia.push_back ( new Mafia ( mafia_usernames ) );
    }
    else{
         mafia.push_back ( new Mafia ( ) );
    }

    if(player[current_room] -> get_villager_members() != 0){
        villager.push_back ( new Villager ( villager_usernames ) );
    }
    else{
         villager.push_back ( new Villager ( ) );
    }

    if(player[current_room] -> get_godfather_members() != 0){
        godfather.push_back ( new GodFather ( godfather_usernames ) );
    }
    else{
         godfather.push_back ( new GodFather ( ) );
    }

    if(player[current_room] -> get_silencer_members() != 0){
        silencer.push_back ( new Silencer ( silencer_usernames ) );
    }
    else{
         silencer.push_back ( new Silencer ( ) );
    }

    if(player[current_room] -> get_detective_members() != 0){
        detective.push_back ( new Detective ( detective_usernames ) );
    }
    else{
         detective.push_back ( new Detective ( ) );
    }

    if(player[current_room] -> get_doctor_members() != 0){
        doctor.push_back ( new Doctor ( doctor_usernames ) );
    }
    else{
         doctor.push_back ( new Doctor ( ) );
    }

    if(player[current_room] -> get_rouintan_members() != 0){
        rouintan.push_back ( new RouinTan ( rouintan_usernames ) );
    }
    else{
         rouintan.push_back ( new RouinTan ( ) );
    }

    if(player[current_room] -> get_joker_members() != 0){
        joker.push_back ( new Joker ( joker_usernames ) );
    }
    else{
         joker.push_back ( new Joker ( ) );
    }


    srand (time(NULL));
    int random;

    if(player[current_room] -> get_mafia_members() != 0){
        for(int i = 0 ; i < mafia_usernames.size() ; i++){
            //random = rand() % mafia_usernames.size();
            cout << mafia_usernames[i] << " is Mafia" << endl;
        }
    }

    if(player[current_room] -> get_villager_members() != 0){
        for(int i = 0 ; i < villager_usernames.size() ; i++){
            //random = rand() % villager_usernames.size();
            cout << villager_usernames[i] << " is Villager" << endl;
        }
    }

    if(player[current_room] -> get_godfather_members() != 0){
        for(int i = 0 ; i < godfather_usernames.size() ; i++){
            cout << godfather_usernames[i] << " is GodFather" << endl;
        }
    }

    if(player[current_room] -> get_silencer_members() != 0){
        for(int i = 0 ; i < silencer_usernames.size() ; i++){
            cout << silencer_usernames[i] << " is Silencer" << endl;
        }
    }

    if(player[current_room] -> get_detective_members() != 0){
        for(int i = 0 ; i < detective_usernames.size() ; i++){
            cout << detective_usernames[i] << " is Detective" << endl;
        }
    }

    if(player[current_room] -> get_doctor_members() != 0){
        for(int i = 0 ; i < doctor_usernames.size() ; i++){
            cout << doctor_usernames[i] << " is Doctor" << endl;
        }
    }

    if(player[current_room] -> get_rouintan_members() != 0){
        for(int i = 0 ; i < rouintan_usernames.size() ; i++){
            cout << rouintan_usernames[i] << " is RouinTan" << endl;
        }
    }

    if(player[current_room] -> get_joker_members() != 0){
        for(int i = 0 ; i < joker_usernames.size() ; i++){
            cout << joker_usernames[i] << " is Joker" << endl;
        }
    }

    mafia_usernames.clear();
    villager_usernames.clear();
    godfather_usernames.clear();
    silencer_usernames.clear();
    detective_usernames.clear();
    doctor_usernames.clear();
    rouintan_usernames.clear();
    joker_usernames.clear();

    rooms[current_room] -> set_is_day(true);
    rooms[current_room] -> set_day_num();
    cout << "Day " << rooms[current_room] -> get_day_num() << endl;
    //cout << "get is day = " << rooms[current_room] -> get_is_day() << endl;
}

int counter = 0;

void end_vote(int max_index){

    string killed_username;

    killed_username = votee_name_vec[max_index];


    std::pair<bool, int> joker_search = findInVector<string>(joker[current_room] -> get_joker_usernames(), killed_username);
    if(joker_search.first){
        cout << "Do I look like a guy with a plan?" <<endl;
        exit(0);
    }

    killed_usernames.push_back(killed_username);

    cout << "Died " << killed_username << endl;
    rooms[current_room] -> set_is_day(false);
    rooms[current_room] -> set_is_night(true);
    rooms[current_room] -> set_night_num();
    counter = 0;
    cout << "Night " << rooms[current_room] -> get_night_num() << endl;

    votee_name_vec.clear();

    std::pair<bool, int> m_search = findInVector<string>(mafia[current_room] -> get_mafia_usernames(), killed_username);
    std::pair<bool, int> v_search = findInVector<string>(villager[current_room] -> get_villager_usernames(), killed_username);
    std::pair<bool, int> g_search = findInVector<string>(godfather[current_room] -> get_godfather_usernames(), killed_username);
    std::pair<bool, int> s_search = findInVector<string>(silencer[current_room] -> get_silencer_usernames(), killed_username);
    std::pair<bool, int> de_search = findInVector<string>(detective[current_room] -> get_detective_usernames(), killed_username);
    std::pair<bool, int> doc_search = findInVector<string>(doctor[current_room] -> get_doctor_usernames(), killed_username);
    std::pair<bool, int> r_search = findInVector<string>(rouintan[current_room] -> get_rouintan_usernames(), killed_username);

    if(m_search.first){
        mafia[current_room] -> set_mafia_usernames(m_search.second);
        player[current_room] -> set_mafia_members();
    }
    if(v_search.first){
        villager[current_room] -> set_villager_usernames(v_search.second);
        player[current_room] -> set_villager_members();
    }
    if(g_search.first){
        godfather[current_room] -> set_godfather_usernames(g_search.second);
        player[current_room] -> set_godfather_members();
    }
    if(s_search.first){
        silencer[current_room] -> set_silencer_usernames(s_search.second);
        player[current_room] -> set_silencer_members();
    }
    if(de_search.first){
        detective[current_room] -> set_detective_usernames(de_search.second);
        player[current_room] -> set_detective_members();
    }
    if(doc_search.first){
        doctor[current_room] -> set_doctor_usernames(doc_search.second);
        player[current_room] -> set_doctor_members();
    }
    if(r_search.first){
        rouintan[current_room] -> set_rouintan_usernames(r_search.second);
        player[current_room] -> set_rouintan_members();
    }
}

int vote(){
    string x,y;
    cin >> x >> y;

    std::pair<bool, int> result2 = findInVector<string>(killed_usernames, y);
    if(result2.first)
        throw User_Already_Died();


    vector<int> count(100,0);
    int max_element_index;
    if(rooms[current_room] -> get_is_day() == true)
    {
        std::pair<bool, int> result = findInVector<string>(votee_name_vec, y);
        if (result.first)
            count[result.second]++;
        else
            votee_name_vec.push_back(y);

        max_element_index = max_element(count.begin(),count.end()) - count.begin();
        return max_element_index;
    }

    vector<int> count_night(100,0);
    int max_element_index_for_night_vote;
    if(rooms[current_room] -> get_is_night() == true)
    {
        std::pair<bool, int> for_mafia = findInVector<string>(mafia[current_room] -> get_mafia_usernames(), x);
        std::pair<bool, int> for_godfather = findInVector<string>(godfather[current_room] -> get_godfather_usernames(), x);
        std::pair<bool, int> for_silencer = findInVector<string>(silencer[current_room] -> get_silencer_usernames(), x);

        if(for_mafia.first == false && for_godfather.first == false && for_silencer.first == false)
            throw This_User_Can_Not_Vote();
        
        std::pair<bool, int> result3 = findInVector<string>(votee_name_vec, y);
        if (result3.first){
            count_night[result3.second]++;
            counter++;
        }
        else{
            votee_name_vec.push_back(y);
            counter++;
        }
        max_element_index_for_night_vote = max_element(count_night.begin(),count_night.end()) - count_night.begin();
        int sum = player[current_room] -> get_mafia_members() + player[current_room] -> get_godfather_members() + player[current_room] -> get_silencer_members();

        if (counter == sum ){
           cout << "Mafia try to kill " << votee_name_vec[max_element_index_for_night_vote] << endl;
           killed_usernames.push_back(votee_name_vec[max_element_index_for_night_vote]);
           killed_by_mafia.push_back(votee_name_vec[max_element_index_for_night_vote]);
           votee_name_vec.clear();
        }
    }
}


void detect(){
    if(rooms[current_room] -> get_is_night() == true){
        string detective_name , suspect_name;
        vector<string> asked_detective;
        int c = 0;
        cin >> detective_name >> suspect_name;

        std::pair<bool, int> d_search = findInVector<string>(asked_detective, detective_name);
        if(d_search.first)
            throw Detective_Has_Already_asked();
        else
            asked_detective.push_back(detective_name);



        std::pair<bool, int> dete_search = findInVector<string>(killed_usernames, detective_name);
        std::pair<bool, int> other_search = findInVector<string>(detective[current_room] -> get_detective_usernames(), detective_name);
        if(dete_search.first == true || other_search.first == false  )
            throw User_Can_Not_ask();


        std::pair<bool, int> sus_search = findInVector<string>(killed_usernames, suspect_name);
        if(sus_search.first)
            throw Person_Is_Dead();


        c++;

        std::pair<bool, int> m_search = findInVector<string>(mafia[current_room] -> get_mafia_usernames(), suspect_name);
        std::pair<bool, int> s_search = findInVector<string>(silencer[current_room] -> get_silencer_usernames(), suspect_name);

        if(m_search.first == true || s_search.first == true)
            cout << "Yes" << endl;
        else
            cout << "No" << endl; 

        if(c == player[current_room] -> get_detective_members())
            asked_detective.clear();

    }
}


void heal(){
    string doctor_name, person_name;
    vector<string> doctor_names;
    cin >> doctor_name >> person_name;

    std::pair<bool, int> doci_search = findInVector<string>(doctor_names, doctor_name);
    if(doci_search.first)
        throw Doctor_Has_Already_Healed();
    else
        doctor_names.push_back(doctor_name);


    std::pair<bool, int> oth_search = findInVector<string>(doctor[current_room] -> get_doctor_usernames(), doctor_name);
    if(!oth_search.first)
        throw User_Can_Not_Heal();
    std::pair<bool, int> kill_search = findInVector<string>( killed_usernames, doctor_name);
    if(kill_search.first)
        throw User_Can_Not_Heal();
   


    std::pair<bool, int> dead_search = findInVector<string>(killed_usernames, person_name);
    if(dead_search.first)
        throw Person_Is_Dead();


    std::pair<bool, int> heal_search = findInVector<string>(killed_by_mafia, person_name);
    if(heal_search.first)
        killed_by_mafia.erase(killed_by_mafia.begin() + heal_search.second);


}


void silent(){
    
    string silencer_name, person;
    vector<string> silencer_names;
    cin >> silencer_name >> person;


    std::pair<bool, int> oth_search = findInVector<string>(silencer[current_room] -> get_silencer_usernames(), silencer_name);
    if(!oth_search.first)
        throw User_Can_Not_Silence();
    std::pair<bool, int> kill_search = findInVector<string>( killed_usernames, silencer_name);
    if(kill_search.first)
        throw User_Can_Not_Silence();
    std::pair<bool, int> kill_mafia_search = findInVector<string>( killed_by_mafia, silencer_name);
    if(kill_mafia_search.first)
        throw User_Can_Not_Silence();


    std::pair<bool, int> dead_search = findInVector<string>(killed_usernames, person);
    if(dead_search.first)
        throw Person_Is_Dead();


    silenced_usernames.push_back(person);




}


void end_match(){

    int mafia_numbers = player[current_room] -> get_mafia_members() + player[current_room] -> get_godfather_members() + player[current_room] -> get_silencer_members();
    int villager_numbers = player[current_room] -> get_villager_members() + player[current_room] -> get_detective_members() + player[current_room] -> get_doctor_members() + player[current_room] -> get_rouintan_members();

    if(mafia_numbers == 0){
        cout << "Victory!"<<endl;
        exit (0);
    }

    if(villager_numbers <= mafia_numbers){
        cout << "Loose!" << endl;
        exit (0);
    }
}



void get_room_state(){

    int mafia_number = player[current_room] -> get_mafia_members() + player[current_room] -> get_godfather_members() + player[current_room] -> get_silencer_members();
    int villager_number = player[current_room] -> get_villager_members() + player[current_room] -> get_detective_members() + player[current_room] -> get_doctor_members() + player[current_room] -> get_rouintan_members();

    cout << "Mafia = " << mafia_number<< endl;
    cout << "Villager = " << villager_number << endl;

}



void order(string str){
    try {
        if (str == "Create_room"){
            create_room();
            end_match();
        } else if (str == "Switch_room") {
            end_match();
            switch_room();
        }
        else if (str == "Join"){
            end_match();
            join ();

        }
        else if (str == "Vote"){
            end_match();
            m_i = vote ();

        }
        else if (str == "End_vote"){
            end_match();
            end_vote (m_i);

        }
        else if (str == "Detect"){
            end_match();
            detect();

        }
        else if (str == "Heal"){
            end_match();
            heal();
        }
        else if (str == "Silent"){
            end_match();
            silent();

        }
        else if (str == "Get_room_state‬‬"){
            end_match();
            get_room_state();
        }
        else{
            cout << "invalid_input"<<endl;
            getline (cin, str);
        }
    }catch(Invalid_room_name rn){
        cout << "Invalid_room_name" << endl;
    }catch(Invalid_role_name rn){
        cout << "Invalid_role_name" << endl;
    }catch(Invalid_special_members sm){
        cout << "special members are more than usuall members" << endl;
    }catch(User_Already_Died u_a_d){
        cout << "User is already died" << endl;
    }catch(Detective_Has_Already_asked d_a){
        cout << "Detective has already asked" << endl;
    }catch(Person_Is_Dead p_d){
        cout << "Person is dead" << endl;
    }catch(User_Can_Not_ask u_c){
        cout << "User can not ask" << endl;
    }catch(This_User_Can_Not_Vote t_u){
        cout << "This user can not vote" << endl;
    }catch(Doctor_Has_Already_Healed d_h){
        cout << "Doctor has already healed" << endl;
    }catch(User_Can_Not_Heal u_h){
        cout << "User can not heal" << endl;
    }catch(User_Can_Not_Silence u_s){
        cout << "User can not silent" << endl;
    }
   
}

