#include "hcmcampaign.h"
//!----------------------------------------------
//! Lớp Position
//!----------------------------------------------
Position::Position(int r, int c) : r(r), c(c) {}
int Position::getRow() const { return r; }
int Position::getCol() const { return c; }
void Position::setRow(int r) { 
    this->r = r;
}
void Position::setCol(int c) { 
    this->c = c;
}
string Position::str() const {
    stringstream ss;
    ss << "(" << r << "," << c << ")";
    return ss.str();
}



//!Added function
Position::Position(const string &str_pos) {
    // TODO: Implement
    string str = str_pos;
    for(int i=0;i<str.length();i++){
        if(str[i] == '(' || str[i] == ')' || str[i] == ','){
            str[i] = ' ';
        }
    }
    stringstream ss(str); 
    ss>>r>>c;
}
//!----------------------------------------------
//! Lớp Unit
//!----------------------------------------------
Unit::Unit(int quantity, int weight, Position pos)
{
    this->quantity = max(1,quantity);
    this->weight = max(1,weight);
    this->pos = pos;
}



//!Added function
void Unit::setWeight(int weight) {
    // TODO: Implement
    this->weight = weight;
}

void Unit::setQuantity(int quantity) {
    // TODO: Implement
    this->quantity = quantity;
}
Position Unit::getCurrentPosition() const
{
    // TODO: Implement
    return pos;
}
int Unit::getAttackScoreinFight(){
    return this->attackScore;
}
void Unit::setAttackScore(int score){
    this->attackScore = score;
}
Unit::~Unit(){

}
//!----------------------------------------------
//! Lớp Infantry
//!----------------------------------------------
Infantry::Infantry(int quantity, int weight, Position pos, InfantryType infantryType)
    : Unit(quantity, weight, pos), infantryType(infantryType)
{
}

int Infantry::getAttackScore() {
    int score = infantryType * 56 +  quantity * weight;
    if(infantryType == InfantryType::SPECIALFORCES && isPerfectSquare(weight)){
        score+=75;
    }
    int pn = computeSingleDigit(score,1975);
    int change = 0;
    if(pn > 7){
        this->quantity = safeCeil(quantity*1.2);
    }
    else if(pn <3){
        this->quantity = safeCeil(quantity*0.9);
    }
    score = infantryType * 56 +  quantity * weight;
    attackScore = score;
    return score;
}
string Infantry::str() const {
    string it = "";
    if(infantryType == InfantryType::SNIPER){
        it = "SNIPER";
    }
    else if(infantryType == InfantryType::ANTIAIRCRAFTSQUAD){
        it = "ANTIAIRCRAFTSQUAD";
    }
    else if(infantryType == InfantryType::MORTARSQUAD){
        it = "MORTARSQUAD";
    }
    else if(infantryType == InfantryType::ENGINEER){
        it = "ENGINEER";
    }
    else if(infantryType == InfantryType::SPECIALFORCES){
        it = "SPECIALFORCES";
    }
    else if(infantryType == InfantryType::REGULARINFANTRY){
        it = "REGULARINFANTRY";
    }
    stringstream ss;
    ss<<"Infantry[infantryType="<<it;
    ss<<",quantity="<<quantity;
    ss<<",weight="<<weight;
    ss<<",position="<<pos.str()<<"]";
    return ss.str();
}



//!Added function
int Infantry::safeCeil(double value) {
    // TODO: Implement
    int intval=round(value);
    double diff=value-intval;
    if (abs(diff) < 1e-7){
        return intval;
    }
    return ceil(value);
}
// ? Kiểm tra n có phải là số chính phương không
bool Infantry::isPerfectSquare(int n) {
    // TODO: implement
    int root = sqrt(n);
    if(root * root == n){
        return true;
    }
    return false;
}

// ? Tính tổng các chữ số của n
int Infantry::sumDigits(int n) {
    // TODO: implement
    int num = n;
    int sd = 0;
    while(num>0){
        sd+=num%10;
        num = num/10;
    }
    return sd;
}

// ? Tính “số cá nhân”: tổng các chữ số của score và năm (1975), sau đó tiếp tục tính đến khi ra 1 chữ số.
int Infantry::computeSingleDigit(int score, int year) {
    // TODO: implement
    int num = score;
    num *= 10000;
    num += year;
    int pn = num;
    while(pn>=10){
        pn = sumDigits(num);
        num = pn;
    }
    return pn;
}
//!----------------------------------------------
//! Lớp Vehicle
//!----------------------------------------------
Vehicle::Vehicle(int quantity, int weight, Position pos, VehicleType vehicleType)
    : Unit(quantity, weight, pos), vehicleType(vehicleType)
{
    
}

int Vehicle::getAttackScore()
{
    // TODO: Implement
    const double THIRSTY = 30.0000 ;
    double score = (vehicleType *304 + quantity * weight) / THIRSTY;
    score = safeCeil(score);
    attackScore = score;
    return score;
}


/* 
@Fix
 */
string Vehicle::str() const
{
    // TODO: Implement
    string vt = "";
    if(vehicleType == VehicleType::TRUCK){
        vt = "TRUCK";
    }
    else if(vehicleType == VehicleType::MORTAR){
        vt = "MORTAR";
    }
    else if(vehicleType == VehicleType::ANTIAIRCRAFT){
        vt = "ANTIAIRCRAFT";
    }
    else if(vehicleType == VehicleType::ARMOREDCAR){
        vt = "ARMOREDCAR";
    }
    else if(vehicleType == VehicleType::APC){
        vt = "APC";
    }
    else if(vehicleType == VehicleType::ARTILLERY){
        vt = "ARTILLERY";
    }
    else if(vehicleType == VehicleType::TANK){
        vt = "TANK";
    }
    stringstream ss;
    ss<<"Vehicle[vehicleType="<<vt;
    ss<<",quantity="<<quantity;
    ss<<",weight="<<weight;
    ss<<",position="<<pos.str()<<"]";
    return ss.str();
}



//!Added function
int Vehicle::safeCeil(double value) {
    // TODO: Implement
    int intval=round(value);
    double diff=value-intval;
    if (abs(diff) < 1e-7){
        return intval;
    }
    return ceil(value);
}
//!----------------------------------------------
//! Lớp UnitList
//!----------------------------------------------
UnitList::UnitList(int capacity)
{
    // TODO: Implement
    // Truyền S = EXP + LF
    // Hint: Bạn có thể sử dụng hàm isSpecial() tự định nghĩa để kiểm tra xem S có phải là số chính phương hay không.
    // if (this->isSpecial(S)) this->capacity = 12;
    // else this->capacity = 8;
    this->capacity = capacity;
    //!Added code
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
    this->countVehicle = 0;
    this->countInfantry = 0;
}

bool UnitList::insert(Unit *unit)
{
    if(unit==nullptr){
        return false;
    }
    Vehicle* vehicle1 = dynamic_cast<Vehicle*>(unit);
    Infantry* infantry1 = dynamic_cast<Infantry*>(unit);

    Node* mark = this->head;
    while(mark!=nullptr){
        Vehicle* vehicle2 = dynamic_cast<Vehicle*>(mark->data);
        Infantry* infantry2 = dynamic_cast<Infantry*>(mark->data);
        if(vehicle1 !=nullptr && vehicle2 != nullptr && vehicle1->getVehicleType()==vehicle2->getVehicleType()){
            int quantity1 = vehicle1->getQuantity();
            int quantity2 = vehicle2->getQuantity();
            int weight1 = vehicle1->getWeight();
            int weight2 = vehicle2->getWeight();
            vehicle2->setQuantity(quantity1+quantity2);
            vehicle2->setWeight( max(weight1,weight2) );
            vehicle2->getAttackScore();
            return false;
        }
        if(infantry1 !=nullptr && infantry2 != nullptr && infantry1->getInfantryType() ==infantry2->getInfantryType()){
            int quantity1 = infantry1->getQuantity();
            int quantity2 = infantry2->getQuantity();
            int weight1 = infantry1->getWeight();
            int weight2 = infantry2->getWeight();
            infantry2->setQuantity(quantity1+quantity2);
            infantry2->setWeight( max(weight1,weight2) );
            infantry2->getAttackScore();
            return false;
        }
        mark = mark->next;
    }
    
    if(size >= capacity){
        return false;
    }

    if(vehicle1!=nullptr){
        Node* newNode = new Node(unit);
        if(tail!=nullptr){
            tail->next = newNode;
            tail = tail->next;
        }
        else{
            head = tail = newNode;
        }
        ++countVehicle;
        ++size;
        return true;
    }
    else if(infantry1!=nullptr){
        Node* newNode = new Node(unit);
        newNode -> next = head;
        head = newNode;
        if(tail == nullptr){
            tail = newNode;
        }
        ++countInfantry;
        ++size;
        return true;
    }
    return false;
}

bool UnitList::isContain(VehicleType vehicleType)
{
    Node* mark = head;
    while(mark!=nullptr){
        Vehicle* vehicle1 = dynamic_cast<Vehicle*>(mark->data);
        if(vehicle1!= nullptr && vehicle1->getVehicleType() == vehicleType){
            return true;
        }
        mark = mark->next;
    }
    return false;
}

bool UnitList::isContain(InfantryType infantryType)
{
    Node* mark = head;
    while(mark!=nullptr){
        Infantry* infantry1 = dynamic_cast<Infantry*>(mark->data);
        if(infantry1!= nullptr && infantry1->getInfantryType() == infantryType){
            return true;
        }
        mark = mark->next;
    }
    return false;
}

/* vector<Unit *>& UnitList::getUnits() {
    return units;
} */

string UnitList::str() const
{
    stringstream ss;
    ss<<"UnitList[count_vehicle="<<this->countVehicle;
    ss<<";count_infantry="<<this->countInfantry;
    if(countVehicle>0 || countInfantry>0){
        ss<<";";
    }
    Node* mark = head;
    while(mark!=nullptr){
        ss<<mark->data->str();
        if(mark!=tail){
            ss<<",";
        }
        mark = mark->next;
    }
    ss<<"]";
    return ss.str();
}



//!Added funtion
void UnitList::remove(Unit *unit) {
    // TODO: Implement
    if(unit==nullptr || head == nullptr){
        return;
    }
    Vehicle* vehicle1 = dynamic_cast<Vehicle*>(unit);
    Infantry* infantry1 = dynamic_cast<Infantry*>(unit);
    Node* prev = nullptr;
    Node* mark = head;
    while(mark!=nullptr){
        Vehicle* vehicle2 = dynamic_cast<Vehicle*>(mark->data);
        Infantry* infantry2 = dynamic_cast<Infantry*>(mark->data);
        bool matched = false;
        if(vehicle1 !=nullptr && vehicle2 != nullptr && vehicle1->getVehicleType()==vehicle2->getVehicleType()){
            int quantity1 = vehicle1->getQuantity();
            int quantity2 = vehicle2->getQuantity();
            vehicle2->setQuantity(quantity2-quantity1);
            matched = true;
        }
        else if(infantry1 !=nullptr && infantry2 != nullptr && infantry1->getInfantryType() ==infantry2->getInfantryType()){
            int quantity1 = infantry1->getQuantity();
            int quantity2 = infantry2->getQuantity();
            infantry2->setQuantity(quantity2-quantity1);
            matched = true;
        }

        if(matched){
            int quantity;
            if(vehicle2!=nullptr){
                quantity = vehicle2->getQuantity();
            }
            else if(infantry2 !=nullptr){
                quantity = infantry2->getQuantity();
            }
            if(quantity<=0){
                if(mark == head){
                    head = mark->next;
                    if(mark == tail){ //?Have 1 element
                        tail = nullptr;
                    }
                }
                else if(mark == tail){
                    prev->next = nullptr;
                    tail = prev;
                }
                else{
                    prev->next = mark->next;
                }
                delete mark;
                --size;
                if(vehicle2!=nullptr){
                    --countVehicle;
                }
                else if(infantry2 !=nullptr){
                    --countInfantry;
                }
            }
            return;
        }
        prev = mark;
        mark = mark->next;
    }
}
UnitList::Node* UnitList::getUnits(){
    return head;
}
UnitList::~UnitList(){
    Node* mark = head;
    while(mark!=nullptr){
        Node* next = mark->next;
        delete mark;
        mark = next;
    }
    head = nullptr;
    tail = nullptr;
    for(int i = 0;i<saveClone.size();i++){
        delete saveClone[i];
    }
}
UnitList::UnitList(const UnitList& other) {
    if(this!=&other){
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
        this->capacity = other.capacity;
        this->countVehicle = 0;
        this->countInfantry = 0;
        Node* mark2 = other.head;
        while(mark2!=nullptr){
            Unit* clone = this->cloneUnit(mark2->data);
            if(clone){
                this->insert(clone);
            }
            mark2 = mark2->next;
        }
    }
}
UnitList& UnitList::operator=(const UnitList& other) {
    if (this == &other) return *this;

    Node* mark2 = other.head;
    while(mark2!=nullptr){
        Unit* clone = this->cloneUnit(mark2->data);
        if(clone){
            this->insert(clone);
        }
        mark2 = mark2->next;
    }

    return *this;
}
Unit* UnitList::cloneUnit(Unit* unit) {
    // TODO: Implement
    Vehicle* vehicle = dynamic_cast<Vehicle*>(unit); 
    Infantry* infantry = dynamic_cast<Infantry*>(unit);
    Unit* clone;
    if(vehicle != nullptr){
        clone = new Vehicle(*vehicle);
        saveClone.push_back(clone);
        return clone;
    }
    else if(infantry != nullptr){
        clone = new Infantry(*infantry);
        saveClone.push_back(clone);
        return clone;
    }
    return nullptr;
}
//!----------------------------------------------
//! Lớp Army
//!----------------------------------------------
Army::Army(Unit **unitArray, int size, string name, BattleField *battleField) : name(name),battleField(battleField)
{
    // TODO: Implement
    int LFsum = 0, EXPsum = 0;
    for(int i=0;i<size;i++){
        Vehicle* vehicle = dynamic_cast<Vehicle*>(unitArray[i]); 
        Infantry* infantry = dynamic_cast<Infantry*>(unitArray[i]); 
        if(vehicle != nullptr){
            LFsum += vehicle ->getAttackScore();
        }
        else if(infantry != nullptr){
            EXPsum += infantry ->getAttackScore();
        }
    }
    this->LF = max(0,min(LFsum,1000));
    this->EXP = max(0,min(EXPsum,500));
    int capacity; //? Update 27/5
    if (this->isSpecial(LF+EXP)) capacity = 12;
    else capacity = 8;
    this->unitList =  new UnitList(capacity);
    for(int i=0;i<size;i++){
        this->unitList->insert(unitArray[i]);
    }
}

Army::~Army() {
    if(unitList!=nullptr){
        delete unitList;
    }
}

void Army::fight(Army* enemy, bool defense) {
}

string Army::str() const {
    return "Army[name=" + name + ",LF=" + to_string(LF) + ",EXP=" + to_string(EXP) + "]";
}



//!Added function
int Army::safeCeil(double value) {
    // TODO: Implement
    int intval=round(value);
    double diff=value-intval;
    if (abs(diff) < 1e-7){
        return intval;
    }
    return ceil(value);
}

void Army::updateScore(bool update){
    // TODO: Implement
    UnitList::Node* mark = unitList->getUnits();
    int LFsum = 0, EXPsum = 0;
    while(mark!=nullptr){
        Vehicle* vehicle = dynamic_cast<Vehicle*>(mark->data); 
        Infantry* infantry = dynamic_cast<Infantry*>(mark->data); 
        if(vehicle != nullptr){
            int score = vehicle ->getAttackScore();
            if(score < 0){
                score = 0;
            }
            LFsum += score;
        }
        else if(infantry != nullptr){
            int score = infantry ->getAttackScore();
            if(score < 0){
                score = 0;
            }
            EXPsum += score;
        }
        mark = mark->next;
    }
    this->LF = max(0,min(LFsum,1000));
    this->EXP = max(0,min(EXPsum,500));
}

int Army::getEXP(){
    return this->EXP;
}
void Army::setEXP(int EXP){
    this->EXP = EXP;
}
int Army::getLF(){
    return this->LF;
}
void Army::setLF(int LF){
    this->LF = LF;
}
bool Army::IsBase(int N, int p) {
    int num = N;
    if(p<=1) {
        return false;
    }
    vector<int> expo;
    int power = 0;
    while (num > 0) {
        if ( (num % p != 0 ) && (num % p != 1)) {     
            return false;
        }
        expo.push_back(power);
        num /= p;
        power++;
    }
    return true;
}
bool Army::IsPrime(int N){
    for(int i=2;i<=N/2;i++){
        if(N%i == 0){
            return false;
        }
    }
    return true;
}
bool Army::isSpecial(int N){
    if(N<0){
        return false;
    }
    else if(N==1){
        return true;
    }
    for(int i=2;i<10;i++){
        if(IsPrime(i) && IsBase(N,i) && (i%2 == 1) ){
            return true;
        }
    }
    return false;
}
//!----------------------------------------------
//! CLASS LiberationArmy
//!----------------------------------------------
LiberationArmy::LiberationArmy(Unit **unitArray, int size, string name, BattleField *battleField)
                                                : Army(unitArray,size,name, battleField) {
}

void LiberationArmy::fight(Army *enemy, bool defense){
    //?Create vector
    UnitList::Node* mark = unitList->getUnits();
    if(defense == false){
        this->LF = max(0,min(safeCeil(this->LF *= 1.5),1000));
        this->EXP = max(0,min(safeCeil(this->EXP *= 1.5),500));
        vector<Unit*> Infantry_U;
        vector<Unit*> Vehicle_U;
        int sum_infantry = 0;
        int sum_vehicle = 0;
        while(mark!=nullptr){
            Vehicle* vehicle = dynamic_cast<Vehicle*>(mark->data); 
            Infantry* infantry = dynamic_cast<Infantry*>(mark->data); 
            if(vehicle != nullptr){
                Vehicle_U.push_back(vehicle);
            }
            else if(infantry != nullptr){
                Infantry_U.push_back(infantry);
            }
            mark = mark->next;
        }
        vector<Unit*> A_combination = knapsack(Infantry_U,enemy->getEXP());
        for(int i=0;i<A_combination.size();i++){
            sum_infantry += A_combination[i] ->getAttackScoreinFight();
        }
        vector<Unit*> B_combination = knapsack(Vehicle_U,enemy->getLF());
        for(int i=0;i<B_combination.size();i++){
            sum_vehicle += B_combination[i] ->getAttackScoreinFight();
        }
        bool check1 = sum_infantry>enemy->getEXP();
        bool check2 = sum_vehicle>enemy->getLF();
        bool win =false;
        if(check1 && check2){
            win = true;
            for(int i=0;i<A_combination.size();i++){
                unitList->remove(A_combination[i]);
            }
            for(int i=0;i<B_combination.size();i++){
                unitList->remove(B_combination[i]);
            }
            this->updateScore(true);
        }
        else if(check2 && this->EXP>enemy->getEXP()){
            win = true;
            for(int i=0;i<B_combination.size();i++){
                unitList->remove(B_combination[i]);
            }
            for(int i=0;i<Infantry_U.size();i++){
                unitList->remove(Infantry_U[i]);
            }
        }
        else if(check1 && this->LF>enemy->getLF()){
            win = true;
            for(int i=0;i<A_combination.size();i++){
                unitList->remove(A_combination[i]);
            }
            for(int i=0;i<Vehicle_U.size();i++){
                unitList->remove(Vehicle_U[i]);
            }
        }
        else{
            mark = unitList->getUnits();
            while(mark!=nullptr){
                mark->data->setWeight(safeCeil(mark->data->getWeight() * 0.9));
                mark = mark->next;
            }
            updateScore(true);
            return;
        }
        if(win){
            UnitList::Node* enemy_mark = enemy->unitList->getUnits();
            vector<Unit*> enemy_units;
            while(enemy_mark!=nullptr){
                enemy_units.push_back(enemy_mark->data);
                enemy_mark = enemy_mark->next;
            }
            for(int i=enemy_units.size()-1;i>=0;i--){
                Unit* clone = cloneUnit(enemy_units[i]);
                bool check =  unitList->insert(clone);
                Vehicle* vehicle_unit = dynamic_cast<Vehicle*>(clone); 
                Infantry* infantry_unit = dynamic_cast<Infantry*>(clone);
                if(vehicle_unit != nullptr && unitList->isContain(vehicle_unit->getVehicleType())){
                    enemy->unitList->remove(enemy_units[i]);
                }
                else if(infantry_unit != nullptr && unitList->isContain(infantry_unit->getInfantryType())){
                    enemy->unitList->remove(enemy_units[i]);
                }
            }
            this->LiberWin = true;
            this->updateScore(true);
            enemy->updateScore(true); //?enemy updatescore
        }
        else{
            this->updateScore(true);
        }
    }
    else if(defense == true){
        this->LF = max(0,min(safeCeil(this->LF * 1.3),1000));
        this->EXP= max(0,min(safeCeil(this->EXP * 1.3),500));
        bool checkLF = (this->LF >= enemy->getLF());
        bool checkEXP = (this->EXP >= enemy->getEXP());
        while(!checkEXP &&  !checkLF){
            mark = unitList->getUnits();
            while(mark!=nullptr){
                int old_quantity = mark->data->getQuantity();
                int nearFibo =  nearestFibonacci(old_quantity);
                mark->data->setQuantity(nearFibo);
                mark = mark->next;
            }
            this->updateScore(true);
            this->LF = max(0,min(safeCeil(this->LF),1000));
            this->EXP = max(0,min(safeCeil(this->EXP),500));
            checkEXP = (EXP >= enemy->getEXP());
            checkLF = (LF >= enemy->getLF());
        }
        if(checkEXP && checkLF){
            return;
        }
        else if(checkEXP ||  checkLF){
            mark = unitList->getUnits();
            while(mark!=nullptr){
                mark->data->setQuantity(safeCeil(mark->data->getQuantity() * 0.9));
                mark = mark->next;
            }
            this->updateScore(true);
            return;
        }
    }
}

string LiberationArmy::str() const {
    stringstream ss;
    ss<<"LiberationArmy[LF="<<LF;
    ss<<",EXP="<<EXP;
    ss<<",unitList="<<unitList->str();
    ss<<",battleField=";
    if(battleField!=nullptr){
        ss<<battleField->str();
    }
    ss<<"]";
    return ss.str();
}



//!Added function
int LiberationArmy::nearestFibonacci(int value) {
    // TODO: Implement
    int small = 1;
    int big = 1;
    while(big<=value){
        int temp = big;
        big += small;
        small = temp;
    }
    return big;
}

vector<Unit*> LiberationArmy::knapsack(vector<Unit*> units, int minScore) {
    // TODO: Implement
    int n = units.size();
    vector<Unit*> bestSubset;

    int bestScore = INT_MAX;
    int bestSize = INT_MAX;

    for (int mask = 0; mask < (1 << n); ++mask) {
        vector<Unit*> subset;
        int score = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subset.push_back(units[i]);
                Vehicle* vehicle = dynamic_cast<Vehicle*>(units[i]);
                Infantry* infantry = dynamic_cast<Infantry*>(units[i]);
                if (vehicle != nullptr) {
                    score += vehicle->getAttackScoreinFight();
                } else if (infantry != nullptr) {
                    score += infantry->getAttackScoreinFight();
                }
            }
        }

        if (subset.size()>0 && score > minScore) {
            if (score < bestScore || (score == bestScore && subset.size() < bestSize)) {
                bestScore = score;
                bestSize = subset.size();
                bestSubset = subset;
            }
        }
    }

    return bestSubset;
}

Unit* LiberationArmy::cloneUnit(Unit* unit) {
    // TODO: Implement
    Vehicle* vehicle = dynamic_cast<Vehicle*>(unit); 
    Infantry* infantry = dynamic_cast<Infantry*>(unit);
    Unit* clone;
    if(vehicle != nullptr){
        clone = new Vehicle(*vehicle);
        saveClone.push_back(clone);
        return clone;
    }
    else if(infantry != nullptr){
        clone = new Infantry(*infantry);
        saveClone.push_back(clone);
        return clone;
    }
    return nullptr;
}

LiberationArmy::~LiberationArmy() {
    // TODO: Implement
    for(int i=0;i<saveClone.size();i++){
        delete saveClone[i];
    }
}
//!----------------------------------------------
//! CLASS ARVN
//!----------------------------------------------
ARVN::ARVN(Unit** unitArray, int size, string name, BattleField *battleField) 
        : Army(unitArray, size, name, battleField) {
}

void ARVN::fight(Army* enemy, bool defense) {
    UnitList::Node* mark = unitList->getUnits();
    if(defense == false){
        while(mark!=nullptr){
            mark->data->setQuantity(safeCeil(mark->data->getQuantity() * 0.8));
            mark = mark->next;
        }
        updateScores();
    }
    else if(defense == true){
        if(this->LiberWin){
            while(mark!=nullptr){
                mark->data->setWeight(safeCeil(mark->data->getWeight() * 0.8));
                mark = mark->next;
            }
            updateScores();
        }  
    }
}

string ARVN::str() const {
        stringstream ss;
        ss<<"ARVN[LF="<<LF;
        ss<<",EXP="<<EXP;
        ss<<",unitList="<<unitList->str();
        ss<<",battleField=";
        if(battleField!=nullptr){
            ss<<battleField->str();
        }
        ss<<"]";
        return ss.str();
}



//!Added function
void ARVN::updateScores() {
    // TODO: Implement
    UnitList::Node* mark = unitList->getUnits();
    int LFsum = 0, EXPsum = 0;
    while(mark!=nullptr){
        UnitList::Node* nextnode = mark->next;
        if(mark->data->getQuantity() <= 1){
            mark->data->setQuantity(0);
            unitList->remove(mark->data);
        }
        mark = nextnode;
    }
    this->updateScore(true);
}
ARVN::~ARVN(){

}
//!-----------------------------------------------------
//! Lớp TerrainElement và các lớp con
//!-----------------------------------------------------
// Constructor và Destructor của TerrainElement
TerrainElement::TerrainElement(Position pos) : pos(pos)
{}

TerrainElement::~TerrainElement() {
    // Giải phóng tài nguyên nếu có
}

// Road: không có hiệu ứng
void Road::getEffect(Army *army) {
    // Không gây ảnh hưởng cho quân đội.
}

// Mountain: stub – áp dụng hiệu ứng cho các đơn vị trong bán kính ảnh hưởng (theo đề bài, hiệu ứng có thể là:
// tăng EXP của bộ binh và giảm LF của phương tiện, tùy thuộc vào khoảng cách)
void Mountain::getEffect(Army *army) {
    LiberationArmy* liberation = dynamic_cast<LiberationArmy*>(army);
    ARVN* arvn = dynamic_cast<ARVN*>(army);
    if (liberation != nullptr) {
        UnitList::Node* mark = liberation->unitList->getUnits();
        while(mark!=nullptr){
            Position pos2 = mark->data->getCurrentPosition();
            double distance = calculateDistance(pos,pos2);
            if(distance<=2.0){
                Vehicle* vehicle = dynamic_cast<Vehicle*>(mark->data); 
                Infantry* infantry = dynamic_cast<Infantry*>(mark->data); 
                if(infantry != nullptr){
                    int attackscore = infantry->getAttackScoreinFight();
                    int bonus = safeCeil(0.3*attackscore);
                    int sum = max(0,min(liberation->getEXP() + bonus,500));
                    liberation->setEXP(sum);
                }
                else if(vehicle != nullptr){
                    int attackscore = vehicle->getAttackScoreinFight();
                    int penalty = safeCeil(0.1*attackscore);
                    int minus = max(0,min(liberation->getLF() - penalty,1000));
                    liberation->setLF(minus);
                }
            }
            mark = mark->next;
        }
    } else if (arvn != nullptr) {
        UnitList::Node* mark = arvn->unitList->getUnits();
        while(mark!=nullptr){
            Position pos2 = mark->data->getCurrentPosition();
            double distance = calculateDistance(pos,pos2);
            if(distance<=4.0){
                Vehicle* vehicle = dynamic_cast<Vehicle*>(mark->data); 
                Infantry* infantry = dynamic_cast<Infantry*>(mark->data); 
                if(infantry != nullptr){
                    int attackscore = infantry->getAttackScoreinFight();
                    int bonus = safeCeil(0.2*attackscore);
                    int sum = max(0,min(arvn->getEXP() + bonus,500));
                    arvn->setEXP(sum);
                }
                else if(vehicle != nullptr){
                    int attackscore = vehicle->getAttackScoreinFight();
                    int penalty = safeCeil(0.05*attackscore);
                    int minus = max(0,min(arvn->getLF() - penalty,1000));
                    arvn->setLF(minus);
                }
            }
            mark = mark->next;
        }
    }
}

// River: stub – giảm EXP của lực lượng bộ binh 10% nếu nằm trong bán kính 2 đơn vị
void River::getEffect(Army *army) {
    LiberationArmy* liberation = dynamic_cast<LiberationArmy*>(army);
    ARVN* arvn = dynamic_cast<ARVN*>(army);
    if (liberation != nullptr) {
        UnitList::Node* mark = liberation->unitList->getUnits();
        while(mark!=nullptr){
            Position pos2 = mark->data->getCurrentPosition();
            double distance = calculateDistance(pos,pos2);
            if(distance<=2.0){
                Vehicle* vehicle = dynamic_cast<Vehicle*>(mark->data); 
                Infantry* infantry = dynamic_cast<Infantry*>(mark->data); 
                if(infantry != nullptr){
                    int attackscore = infantry->getAttackScoreinFight();
                    int penalty = safeCeil(-0.1*attackscore);
                    infantry->setAttackScore(attackscore+penalty);
                }
            }
            mark = mark->next;
        }
    } else if (arvn != nullptr) {
        UnitList::Node* mark = arvn->unitList->getUnits();
        while(mark!=nullptr){
            Position pos2 = mark->data->getCurrentPosition();
            double distance = calculateDistance(pos,pos2);
            if(distance<=2.0){
                Vehicle* vehicle = dynamic_cast<Vehicle*>(mark->data); 
                Infantry* infantry = dynamic_cast<Infantry*>(mark->data); 
                if(infantry != nullptr){
                    int attackscore = infantry->getAttackScoreinFight();
                    int penalty = safeCeil(-0.1*attackscore);
                    infantry->setAttackScore(attackscore+penalty);
                }
            }
            mark = mark->next;
        }
    }
}

// Urban: stub – hiệu ứng khu dân cư có thể thay đổi attackScore của bộ binh hoặc phương tiện tùy vào loại
void Urban::getEffect(Army *army) {
    LiberationArmy* liberation = dynamic_cast<LiberationArmy*>(army);
    ARVN* arvn = dynamic_cast<ARVN*>(army);
    if (liberation != nullptr) {
        UnitList::Node* mark = liberation->unitList->getUnits();
        while(mark!=nullptr){
            Position pos2 = mark->data->getCurrentPosition();
            double distance = calculateDistance(pos,pos2);
            Vehicle* vehicle = dynamic_cast<Vehicle*>(mark->data); 
            Infantry* infantry = dynamic_cast<Infantry*>(mark->data); 
            if(infantry != nullptr){
                int attackscore = infantry->getAttackScoreinFight();
                string infantrytype = infantry->infantryTypeToString(infantry->getInfantryType());
                if( (infantrytype == "SPECIALFORCES" || infantrytype == "REGULARINFANTRY") && distance<=5.0){
                    int bonus;
                    if(distance != 0){
                        bonus = safeCeil((2*attackscore)/distance);
                    }
                    else{
                        bonus = 0;
                    }
                    infantry->setAttackScore( attackscore +  bonus);
                }
            }
            else if(vehicle != nullptr){
                int attackscore = vehicle->getAttackScoreinFight();
                string vehicletype = vehicle->vehicleTypeToString(vehicle->getVehicleType());
                if(vehicletype == "ARTILLERY" && distance<=2.0){
                    int penalty = safeCeil(-0.5 * attackscore);
                    vehicle->setAttackScore(attackscore + penalty);
                }
            }
            mark = mark->next;
        }
    } else if (arvn != nullptr) {
        UnitList::Node* mark = arvn->unitList->getUnits();
        while(mark!=nullptr){
            Position pos2 = mark->data->getCurrentPosition();
            double distance = calculateDistance(pos,pos2);
            Vehicle* vehicle = dynamic_cast<Vehicle*>(mark->data); 
            Infantry* infantry = dynamic_cast<Infantry*>(mark->data); 
            if(infantry != nullptr){
                int attackscore = infantry->getAttackScoreinFight();
                string infantrytype = infantry->infantryTypeToString(infantry->getInfantryType());
                if( infantrytype == "REGULARINFANTRY" && distance<=3.0){
                    int bonus;
                    if(distance != 0){
                        bonus = safeCeil( (3*attackscore)/(2*distance) );
                    }
                    else{
                        bonus = 0;
                    }
                    infantry->setAttackScore( attackscore + bonus );
                }
            }
            mark = mark->next;
        }
    }
}

// Fortification: stub – hiệu ứng chiến hào, áp dụng cho cả hai quân đội với các thay đổi nhất định
void Fortification::getEffect(Army *army) {
    LiberationArmy* liberation = dynamic_cast<LiberationArmy*>(army);
    ARVN* arvn = dynamic_cast<ARVN*>(army);
    if (liberation != nullptr) {
        UnitList::Node* mark = liberation->unitList->getUnits();
        while(mark!=nullptr){
            Position pos2 = mark->data->getCurrentPosition();
            double distance = calculateDistance(pos,pos2);
            if(distance<=2.0){
                Vehicle* vehicle = dynamic_cast<Vehicle*>(mark->data); 
                Infantry* infantry = dynamic_cast<Infantry*>(mark->data); 
                if(infantry != nullptr){
                    int attackscore = infantry->getAttackScoreinFight();
                    int penalty = safeCeil(-0.2*attackscore);
                    infantry->setAttackScore(attackscore + penalty);
                }
                else if(vehicle != nullptr){
                    int attackscore = vehicle->getAttackScoreinFight();
                    int penalty = safeCeil(-0.2*attackscore);
                    vehicle->setAttackScore(attackscore + penalty);
                }
            }
            mark = mark->next;
        }
    } else if (arvn != nullptr) {
        UnitList::Node* mark = arvn->unitList->getUnits();
        while(mark!=nullptr){
            Position pos2 = mark->data->getCurrentPosition();
            double distance = calculateDistance(pos,pos2);
            if(distance<=2.0){
                Vehicle* vehicle = dynamic_cast<Vehicle*>(mark->data); 
                Infantry* infantry = dynamic_cast<Infantry*>(mark->data); 
                if(infantry != nullptr){
                    int attackscore = infantry->getAttackScoreinFight();
                    int bonus = safeCeil(0.2*attackscore);
                    infantry->setAttackScore(attackscore + bonus);
                }
                else if(vehicle != nullptr){
                    int attackscore = vehicle->getAttackScoreinFight();
                    int bonus = safeCeil(0.2*attackscore);
                    vehicle->setAttackScore(attackscore + bonus);
                }
            }
            mark = mark->next;
        }
    }
}

// SpecialZone: stub – các đơn vị trong bán kính 1 đơn vị có attackScore = 0
void SpecialZone::getEffect(Army *army) {
    LiberationArmy* liberation = dynamic_cast<LiberationArmy*>(army);
    ARVN* arvn = dynamic_cast<ARVN*>(army);
    if (liberation != nullptr) {
        UnitList::Node* mark = liberation->unitList->getUnits();
        while(mark!=nullptr){
            Position pos2 = mark->data->getCurrentPosition();
            double distance = calculateDistance(pos,pos2);
            if(distance<=1.0){
                Vehicle* vehicle = dynamic_cast<Vehicle*>(mark->data); 
                Infantry* infantry = dynamic_cast<Infantry*>(mark->data); 
                if(infantry != nullptr){
                    int attackscore = infantry->getAttackScoreinFight();
                    infantry->setAttackScore(0);
                }
                else if(vehicle != nullptr){
                    int attackscore = vehicle->getAttackScoreinFight();
                    vehicle->setAttackScore(0);
                }
            }
            mark = mark->next;
        }
    } else if (arvn != nullptr) {
        UnitList::Node* mark = arvn->unitList->getUnits();
        while(mark!=nullptr){
            Position pos2 = mark->data->getCurrentPosition();
            double distance = calculateDistance(pos,pos2);
            if(distance<=1.0){
                Vehicle* vehicle = dynamic_cast<Vehicle*>(mark->data); 
                Infantry* infantry = dynamic_cast<Infantry*>(mark->data); 
                if(infantry != nullptr){
                    int attackscore = infantry->getAttackScoreinFight();
                    infantry->setAttackScore(0);
                }
                else if(vehicle != nullptr){
                    int attackscore = vehicle->getAttackScoreinFight();
                    vehicle->setAttackScore(0);
                }
            }
            mark = mark->next;
        }
    }
}
//!----------------------------------------------
//! CLASS BattleField
//!----------------------------------------------
BattleField::BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                         const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                         const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone)
    : n_rows(n_rows), n_cols(n_cols)
{
    this->terrain = new TerrainElement**[n_rows];
    for(int i=0;i<n_rows;i++){
        terrain[i] = new TerrainElement*[n_cols];
        for(int j=0;j<n_cols;j++){
            Position pos(i,j);
            terrain[i][j] = new Road(pos);
        }
    }

    for(int i=0;i<arrayForest.size();i++){
        const Position* pos = arrayForest[i];
        int r = pos->getRow();
        int c = pos->getCol();
        if(r>=0 && c>=0 && r<n_rows && c<n_cols && dynamic_cast<Road *>(terrain[r][c])){
            delete terrain[r][c];
            terrain[r][c] = new Mountain(*pos);
        }
    }

    for(int i=0;i<arrayRiver.size();i++){
        const Position* pos = arrayRiver[i];
        int r = pos->getRow();
        int c = pos->getCol();
        if(r>=0 && c>=0 && r<n_rows && c<n_cols && dynamic_cast<Road *>(terrain[r][c])){
            delete terrain[r][c];
            terrain[r][c] = new River(*pos);
        }
    }

    for(int i=0;i<arrayFortification.size();i++){
        const Position* pos = arrayFortification[i];
        int r = pos->getRow();
        int c = pos->getCol();
        if(r>=0 && c>=0 && r<n_rows && c<n_cols && dynamic_cast<Road *>(terrain[r][c])){
            delete terrain[r][c];
            terrain[r][c] = new Fortification(*pos);
        }
    }

    for(int i=0;i<arrayUrban.size();i++){
        const Position* pos = arrayUrban[i];
        int r = pos->getRow();
        int c = pos->getCol();
        if(r>=0 && c>=0 && r<n_rows && c<n_cols && dynamic_cast<Road *>(terrain[r][c])){
            delete terrain[r][c];
            terrain[r][c] = new Urban(*pos);
        }
    }

    for(int i=0;i<arraySpecialZone.size();i++){
        const Position* pos = arraySpecialZone[i];
        int r = pos->getRow();
        int c = pos->getCol();
        if(r>=0 && c>=0 && r<n_rows && c<n_cols && dynamic_cast<Road *>(terrain[r][c])){
            delete terrain[r][c];
            terrain[r][c] = new SpecialZone(*pos);
        }
    }
}

BattleField::~BattleField() {
    for(int i=0;i<n_rows;i++){
        for(int j=0;j<n_cols;j++){
            delete terrain[i][j];
        }
    }
    for(int i=0;i<n_rows;i++){
        delete[] terrain[i];
    }
    delete [] terrain;
}

TerrainElement* BattleField::getElement(int r, int c) const {
    if(r<0 || c<0 || r>=n_rows || c>=n_cols){
        return nullptr;
    }
    return terrain[r][c];
}

string BattleField::str() const {
    stringstream ss;
    ss<<"BattleField[";
    ss<<"n_rows="<<n_rows<<",";
    ss<<"n_cols="<<n_cols;
    ss<<"]";
    return ss.str();
}
//!-----------------------------------------------------
//! CLASS Configuration
//!-----------------------------------------------------
Configuration::Configuration(const std::string &filepath) {
    //? Handle pointer level 2
    this->liberationUnits = nullptr;
    this->ARVNUnits = nullptr;
    this->liberationUnits_size = 0;
    this->ARVNUnits_size = 0;
    ifstream ifs;
    ifs.open(filepath);
    //?Check file open
    if(!ifs.is_open()){
        cerr<<"Cannot open file "<<filepath<<endl;
    }
    //?  Read file
    int numLines=0;
    const int MAX_LINES=100;
    string data[MAX_LINES];
    
    vector<vector<string>> vec(11);
    while (getline(ifs,data[numLines]))
    {  
      numLines++;
    }
    ifs.close();
    //? Extract value
    int idx=-1;
    bool insideBlock = false;
    for(int i=0;i<numLines;i++){
        if (!insideBlock) {
            idx = FindBegin(data[i]);
            if (idx != -1) {
                vec[idx].push_back(data[i]);
                if (data[i].find('[') != string::npos && data[i].find(']') == string::npos) {
                    //? A block not a line
                    insideBlock = true;
                }
            }
        } else {
            //? Inside block
            vec[idx].push_back(data[i]);
            if (data[i].find(']') != string::npos) {
                insideBlock = false;
                idx = -1;
            }
        }
    }
    
    vector<int>arr(9999);

    //?Nummber
    ReadNumber(arr,vec[1][0]);
    num_rows=arr[0];
    ReadNumber(arr,vec[2][0]);
    num_cols=arr[0];
    ReadNumber(arr,vec[3][0]);
    //?Check event code
    arr[0] = max(arr[0],0);
    if(arr[0]>99){
        arr[0]=arr[0]%100;
    }
    eventCode=arr[0];

    //?Array
    ArrayLocate(arr,vec[4][0],arrayForest);
    ArrayLocate(arr,vec[5][0],arrayRiver);
    ArrayLocate(arr,vec[6][0],arrayFortification);
    ArrayLocate(arr,vec[7][0],arrayUrban);
    ArrayLocate(arr,vec[8][0],arraySpecialZone);

    //?Unit List
    for(int i=0;i<vec[0].size();i++){
        UnitListExtract(arr,vec[0][i]);
    }
}

Configuration::~Configuration() {
    // Giải phóng các đối tượng Position đã được cấp phát
    for (int i = 0; i < arrayForest.size(); ++i)
    {
        delete arrayForest[i];
    }
    for (int i = 0; i < arrayRiver.size(); ++i)
    {
        delete arrayRiver[i];
    }
    for (int i = 0; i < arrayFortification.size(); ++i)
    {
        delete arrayFortification[i];
    }
    for (int i = 0; i < arrayUrban.size(); ++i)
    {
        delete arrayUrban[i];
    }
    for (int i = 0; i < arraySpecialZone.size(); ++i)
    {
        delete arraySpecialZone[i];
    }
    for (int i = 0; i < liberationUnits_size; ++i)
    {
        delete liberationUnits[i];
    }
    for (int i = 0; i < ARVNUnits_size; ++i)
    {
        delete ARVNUnits[i];
    }
    if(liberationUnits!=nullptr){
        delete [] liberationUnits;
    }
    if(ARVNUnits!=nullptr){
        delete [] ARVNUnits;
    }
}

string Configuration::str() const {
    // TODO
    stringstream ss;
    string str="";
    ss<<"[";
    ss<<"num_rows="<<num_rows<<",";
    ss<<"num_cols="<<num_cols<<",";
    ss<<"arrayForest=[";
    for(int i=0;i<arrayForest.size();i++){
        ss<<arrayForest[i]->str();
        if(i<arrayForest.size()-1){
            ss<<",";
        }
    }
    ss<<"],";
    ss<<"arrayRiver=[";
    for(int i=0;i<arrayRiver.size();i++){
        ss<<arrayRiver[i]->str();
        if(i<arrayRiver.size()-1){
            ss<<",";
        }
    }
    ss<<"],";
    ss<<"arrayFortification=[";
    for(int i=0;i<arrayFortification.size();i++){
        ss<<arrayFortification[i]->str();
        if(i<arrayFortification.size()-1){
            ss<<",";
        }
    }
    ss<<"],";
    ss<<"arrayUrban=[";
    for(int i=0;i<arrayUrban.size();i++){
        ss<<arrayUrban[i]->str();
        if(i<arrayUrban.size()-1){
            ss<<",";
        }
    }
    ss<<"],";
    ss<<"arraySpecialZone=[";
    for(int i=0;i<arraySpecialZone.size();i++){
        ss<<arraySpecialZone[i]->str();
        if(i<arraySpecialZone.size()-1){
            ss<<",";
        }
    }
    ss<<"],";
    ss<<"liberationUnits=[";
    for(int i=0;i<liberationUnits_size;i++){
        ss<<liberationUnits[i]->str();
        if(i<liberationUnits_size-1){
            ss<<",";
        }
    }
    ss<<"],";
    ss<<"ARVNUnits=[";
    for(int i=0;i<ARVNUnits_size;i++){
        ss<<ARVNUnits[i]->str();
        if(i<ARVNUnits_size-1){
            ss<<",";
        }
    }
    ss<<"],";
    ss<<"eventCode="<<eventCode<<"]";
    return ss.str();
}



//!Added function
int Configuration::ReadNumber(vector<int>& arr,string s){
    for(int i=0;i<s.length();i++){
        if( !isdigit(s[i]) && (s[i] != '-') && (s[i] != '+') ){
            s[i]=' ';
        }
    }
    stringstream ss(s);
    int num,count=0;
    while(ss >> num){
        if(count>= (arr.size()/2) ){
            arr.resize(arr.size()*2);
        }
        arr[count] = num;
        ++count;
    }
    return count;
}
string Configuration::ReadAlphabet(string s){
    string result="";
    for(int i=0;i<s.length();i++){
        if(s[i]=='='){
            break;
        }
        if(isalpha(s[i]) || s[i]=='_'){
            result.push_back(s[i]);
        }
    }
    return result;
}
int Configuration::FindBegin(string s){
    string begin[9] = {"UNIT_LIST","NUM_ROWS","NUM_COLS","EVENT_CODE","ARRAY_FOREST","ARRAY_RIVER","ARRAY_FORTIFICATION",
        "ARRAY_URBAN","ARRAY_SPECIAL_ZONE"};
    string startstring = ReadAlphabet(s);
    for(int i=0;i<9;i++){
        if(startstring==begin[i]){
            return i;
        }
    }
    return -1; 
}
void Configuration::ArrayLocate(vector<int>& arr,string s, vector<Position*>& array){
    int count = ReadNumber(arr,s);
    for(int i=0;i<count/2;i++){
        int x=-1,y=-1;
        x=arr[2*i];
        y=arr[2*i+1];
        Position* pos = new Position(x,y);
        array.push_back(pos);
    }
}
void Configuration::UnitListExtract(vector<int> &arr,string s){
    int count = ReadNumber(arr,s);
    vector<int> quantity;
    vector<int> weight;
    vector<int> position_x;
    vector<int> position_y;
    vector<int> armyBelong;
    vector<Position> pos;
    for(int i = 0;i<count/5;i++){
        quantity.push_back(     arr[5*i+0]);
        weight.push_back(       arr[5*i+1]);
        position_x.push_back(   arr[5*i+2]);
        position_y.push_back(   arr[5*i+3]);
        armyBelong.push_back(   arr[5*i+4]);
        Position temp_pos(position_x[i],position_y[i]);
        pos.push_back(temp_pos);
    }
    vector<string> open;
    int idx = 0;
    string subopen = "";
    s = s.substr(10);
    while( (idx+5) <s.length()){
        s = s.substr(idx);
        subopen=ReadAlphabet2(s,idx);
        open.push_back(subopen);
    }
    liberationUnits = new Unit*[open.size()];
    ARVNUnits = new Unit*[open.size()];
    for(int i =0;i<open.size();i++){
        Unit* unit = nullptr;
        int unittype = 2;
        //?Case Infantry
        InfantryType infantrytype;
        if(open[i]=="SNIPER"){
            infantrytype=InfantryType::SNIPER;
            unittype = 0;
        }
        else if(open[i]=="ANTIAIRCRAFTSQUAD"){
            infantrytype=InfantryType::ANTIAIRCRAFTSQUAD;
            unittype = 0;
        }
        else if(open[i]=="MORTARSQUAD"){
            infantrytype=InfantryType::MORTARSQUAD;
            unittype = 0;
        }
        else if(open[i]=="ENGINEER"){
            infantrytype=InfantryType::ENGINEER;
            unittype = 0;
        }
        else if(open[i]=="SPECIALFORCES"){
            infantrytype=InfantryType::SPECIALFORCES;
            unittype = 0;
        }
        else if(open[i]=="REGULARINFANTRY"){
            infantrytype=InfantryType::REGULARINFANTRY;
            unittype = 0;
        }
        //?Case Vehicle
        VehicleType vehicletype;
        if(open[i]=="TANK"){
            vehicletype=VehicleType::TANK;
            unittype = 1;
        }
        else if(open[i]=="ARTILLERY"){
            vehicletype=VehicleType::ARTILLERY;
            unittype = 1;
        }
        else if(open[i]=="ARMOREDCAR"){
            vehicletype=VehicleType::ARMOREDCAR;
            unittype = 1;
        }
        else if(open[i]=="APC"){
            vehicletype=VehicleType::APC;
            unittype = 1;
        }
        else if(open[i]=="TRUCK"){
            vehicletype=VehicleType::TRUCK;
            unittype = 1;
        }
        else if(open[i]=="MORTAR"){
            vehicletype=VehicleType::MORTAR;
            unittype = 1;
        }
        else if(open[i]=="ANTIAIRCRAFT"){
            vehicletype=VehicleType::ANTIAIRCRAFT;
            unittype = 1;
        }
        //?Handle
        if(unittype==0){
            unit = new Infantry(quantity[i],weight[i],pos[i],infantrytype);
        }
        else if(unittype==1){
            unit = new Vehicle(quantity[i],weight[i],pos[i],vehicletype);
        }
        if(armyBelong[i] == 0){
            liberationUnits[liberationUnits_size] = unit;
            ++liberationUnits_size;
        }
        else {
            ARVNUnits[ARVNUnits_size] = unit;
            ++ARVNUnits_size;
        }
    }
}
string Configuration::ReadAlphabet2(string s,int& idx){
    string result="";
    int countdown = 2;
    for(int i=0;i<s.length();i++){
        if(s[i]==')'){
            --countdown;
            if(countdown<=0){
                idx = i +1;
                break;
            }
        }
        if(isalpha(s[i]) || s[i]=='_'){
            result.push_back(s[i]);
        }
    }
    return result;
}
//!-----------------------------------------------------
//! Lớp HCMCampaign
//!-----------------------------------------------------
HCMCampaign::HCMCampaign(const string & config_file_path){
    //?Configuration
    config = new Configuration(config_file_path);
    int n_rows = config->getNumRows();
    int n_cols = config->getNumCols();
    vector<Position*> arrayForest = config->getForestPositions();
    vector<Position*> arrayRiver = config->getRiverPositions();
    vector<Position*> arrayFortification = config->getFortificationPositions();
    vector<Position*> arrayUrban = config->getUrbanPositions();
    vector<Position*> arraySpecialZone = config->getSpecialZonePositions();
    Unit** liberationUnits = config->getLiberationUnits();
    Unit** ARVNUnits = config->getARVNUnits();
    int eventCode = config->getEventCode();
    //?BattleField
    battleField = new BattleField(n_rows,n_cols,arrayForest,arrayRiver,arrayFortification,arrayUrban,arraySpecialZone);
    //?LiberationArmy
    int libersize = config->getLiberationUnitsSize();
    this->liberunitArray = new Unit*[libersize];
    for(int i = 0;i<libersize;i++){
        liberunitArray[i] = liberationUnits[i];
    }
    liberationArmy = new LiberationArmy(liberunitArray, libersize,"LiberationArmy", battleField);
    //?ARVN
    int ARVNsize = config->getARVNUnitsSize();
    this->ARVNunitArray = new Unit*[ARVNsize];
    for(int i = 0;i<ARVNsize;i++){
        ARVNunitArray[i] = ARVNUnits[i];
    }
    arvnArmy = new ARVN(ARVNunitArray, ARVNsize,"ARVN", battleField);
}
HCMCampaign::~HCMCampaign(){
    delete config;
    delete battleField;
    delete liberationArmy;
    delete arvnArmy;
    delete [] liberunitArray;
    delete [] ARVNunitArray;
}
void HCMCampaign::run(){
    //?GetEffect
    int num_rows = config->getNumRows();
    int num_cols = config->getNumCols();
    for (int type = 0; type < 6; ++type) {
        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                TerrainElement* element = battleField->getElement(i, j);
                if (element) {
                    bool match = false;
                    switch (type) {
                        case 0: match = dynamic_cast<Road*>(element) != nullptr; break;
                        case 1: match = dynamic_cast<Mountain*>(element) != nullptr; break;
                        case 2: match = dynamic_cast<River*>(element) != nullptr; break;
                        case 3: match = dynamic_cast<Urban*>(element) != nullptr; break;
                        case 4: match = dynamic_cast<Fortification*>(element) != nullptr; break;
                        case 5: match = dynamic_cast<SpecialZone*>(element) != nullptr; break;
                    }
                    if (match) {
                        element->getEffect(liberationArmy);
                        element->getEffect(arvnArmy);
                    }
                }
            }
        }
    }
    //?Fight
    int eventCode = config->getEventCode();
    if(eventCode<75){
        liberationArmy->fight(arvnArmy,false);
        arvnArmy->fight(liberationArmy,true);
    }
    else{
        arvnArmy->fight(liberationArmy,false);
        liberationArmy->fight(arvnArmy,true);
        liberationArmy->fight(arvnArmy,false);
        arvnArmy->fight(liberationArmy,true);
    }
    //?Attackscore <= 5
    UnitList::Node* mark = liberationArmy->unitList->getUnits();
    while(mark!=nullptr){
        UnitList::Node* nextnode = mark->next; 
        if(mark->data->getAttackScoreinFight() <= 5){
            liberationArmy->unitList->remove(mark->data);
        }
        mark = nextnode;
    }
    UnitList::Node* mark2 = arvnArmy->unitList->getUnits();
    while(mark2!=nullptr){
        UnitList::Node* nextnode2 = mark2->next;
        if(mark2->data->getAttackScoreinFight() <= 5){
            arvnArmy->unitList->remove(mark2->data);
        }
        mark2 = nextnode2;
    }
    liberationArmy->updateScore(true);
    arvnArmy->updateScore(true);
}
string HCMCampaign::printResult(){
    stringstream ss;
    ss<<"LIBERATIONARMY[";
    ss<<"LF="<<liberationArmy->getLF();
    ss<<",EXP="<<liberationArmy->getEXP();
    ss<<"]-ARVN[";
    ss<<"LF="<<arvnArmy->getLF();
    ss<<",EXP="<<arvnArmy->getEXP();
    ss<<"]";
    return ss.str();
}