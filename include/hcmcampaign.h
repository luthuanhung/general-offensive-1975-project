/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 2
 * Programming Fundamentals Spring 2025
 * Date: 02.02.2025
 */

// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_HCM_CAMPAIGN_H_
#define _H_HCM_CAMPAIGN_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class Unit;
class UnitList;
class Army;
class TerrainElement;

class Vehicle;
class Infantry;

class LiberationArmy;
class ARVN;

class Position;

class Road;
class Mountain;
class River;
class Urban;
class Fortification;
class SpecialZone;

class BattleField;

class HCMCampaign;
class Configuration;

enum VehicleType
{
    TRUCK,
    MORTAR,
    ANTIAIRCRAFT,
    ARMOREDCAR,
    APC,
    ARTILLERY,
    TANK
};
enum InfantryType
{
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY
};

class Army {
protected:
    int LF;        
    int EXP;       
    string name;
    BattleField* battlefield;
     UnitList *unitList;
public:


  
   
static void setlimit(int& value,int max,int min) {
    if(value > max) {
        value = max;
    }
    else if(value < min) {
        value = min;
    }
    return;
    
}
    UnitList * GetunitList() const { return unitList; }
   
    Army(Unit **unitArray, int size, string name,BattleField* battlefield);
    virtual ~Army();
    virtual void fight(Army *enemy, bool defense = false) = 0;
    virtual string str() const = 0;
  
   int getLF() const { return LF; }
   int getEXP() const { return EXP; }
   void setLF(int value) { LF = value; }
  void setEXP(int value) { EXP = value; }
   void updateScore(bool check = false);
};

class Position
{
private:
    int r, c;

public:
    Position(int r = 0, int c = 0);
    Position(const string &str_pos);
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    string str() const;
};

class Unit
{
protected:
    int quantity, weight;
    Position pos;
    int attackScore = 0;

public:
    Unit(int quantity, int weight, Position pos);
    virtual ~Unit() = default;
    virtual int getAttackScore() = 0;
    int getAttackScoreinFight(){
        return attackScore;
    }
    void setAttackScore(int score) { attackScore = score; }
    Position getCurrentPosition() const;
    virtual string str() const = 0;

    int getQuantity() { return quantity; }
    int getWeight() { return weight; }
    void setQuantity(int quantity);
        
    
    void setWeight(int weight);
        void setCurrentPosition(Position pos);
    
};
class Vehicle : public Unit
{
protected:
    VehicleType vehicleType;  

public:
   
    Vehicle(int quantity, int weight, Position pos, VehicleType vehicleType);

   
    int getAttackScore() override;

    string str() const override;

 
    VehicleType getVehicleType() const { return vehicleType; }
    void setVehicleType(VehicleType value) { vehicleType = value; }

    static string vehicleTypeToString(VehicleType vt) {
        switch(vt)
        {
            case TRUCK:         return "TRUCK";
            case MORTAR:        return "MORTAR";
            case ANTIAIRCRAFT:  return "ANTIAIRCRAFT";
            case ARMOREDCAR:    return "ARMOREDCAR";
            case APC:           return "APC";
            case ARTILLERY:     return "ARTILLERY";
            case TANK:          return "TANK";
            default:            return "UNKNOWN";
        }
    }

};
class Infantry : public Unit
{
protected:
    InfantryType infantryType; 

public:

    Infantry(int quantity, int weight, Position pos, InfantryType infantryType);

    
    int getAttackScore() override;
    int getAttackScorewithoutmodify();

    
    string str() const override;

    InfantryType getInfantryType() const { return infantryType; }
    int getQuantity() const { return quantity; }
    int getWeight() const { return weight; }
    Position getPosition() const { return pos; }

    void setQuantity(int value) { quantity = value; }
    void setWeight(int value) { weight = value; }
    void setPosition(Position value) { pos = value; }

    static string infantryTypeToString(InfantryType it)
    {
        switch(it)
        {
            case SNIPER:              return "SNIPER";
            case ANTIAIRCRAFTSQUAD:     return "ANTIAIRCRAFTSQUAD";
            case MORTARSQUAD:           return "MORTARSQUAD";
            case ENGINEER:              return "ENGINEER";
            case SPECIALFORCES:         return "SPECIALFORCES";
            case REGULARINFANTRY:       return "REGULARINFANTRY";
            default:                    return "UNKNOWN";
        }
    }
 bool sochinhphuong(int n) {
    return sqrt(n) * sqrt(n) == n;
}
int sumofdigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
int socanhan(int n) {
    int sum = sumofdigits(n) + sumofdigits(1975);
    while (sum >= 10) {
        sum = sumofdigits(sum);
    }
    return sum;
}
};


class UnitList
{
private:
    int capacity;
   
    
   vector<Unit *> units;
    

public:
bool isSpecial(int num,int base) {
    vector <int> powers;
    int power = 1;
    while(power <= num) {
        powers.push_back(power);
        power *= base;
    }
    for(int i = 0; i < powers.size();i++) {
        for(int j = i; j < powers.size();j++) {
            if(powers[i] + powers[j] == num) {
                return true;
            }
        }
    }
    return false;
}
 bool isSpecialNumber(int S) {
    vector <int> primes = {2,3,5,7};
    for(int i = 0; i < primes.size();i++) {
        if(isSpecial(S,primes[i])) {
            return true;
        }
    }
    return false;
 }
int size = 0;
int countVehicle = 0;
    int countInfantry = 0;
 struct Node {
        Unit *unit;
        Node *next;
        Node(Unit*unit) :unit(unit),  next(nullptr) {}
     };
      Node *head = nullptr;
     Node *tail = nullptr;
    UnitList(int capacity);
    bool insert(Unit *unit);
    bool isContain(VehicleType vehicleType);
    bool isContain(InfantryType infantryType);
   
    string str() const;
    void reduceQuantity(int percent);
    void reduceWeight(int percent);
    void clear() {}
    void setUnits(vector<Unit *> units);
    void remove(Unit *unit);
    vector<Unit*>& getUnits() {
        return units;
    }
    void removeUnits(vector<Unit*>& unitsToRemove);
    Node* getHead() const { return head; }
        Node* getTail() const { return tail; }
};
class LiberationArmy : public Army
{
private:
    Unit **unitArray;      
      
    int nearestFibonacci(int value);
    vector<Unit*> findcombo(vector<Unit*> units, int maxScore);
    Unit* cloneUnit(Unit* unit);
    

public:

    LiberationArmy(Unit **unitArray, int size, string name,BattleField* battlefield);
       LiberationArmy(Unit **unitArray, int size, string name,int dum);

    void fight(Army *enemy, bool defense) override;
    string str() const override;
};
class ARVN : public Army
{
   
public:
    ARVN(Unit** unitArray, int size, string name,BattleField* battlefield);
    ARVN(Unit** unitArray, int size, string name,int dum);
  
    void fight(Army* enemy, bool defense=false) override;
    string str() const;
    vector<Unit*> findcombo(vector<Unit*> units, int minScore);
    
    
   
};
class TerrainElement {
protected:
    Position pos; 

    double calculateDistance(const Position& pos1, const Position& pos2) {
        int rowDiff = pos1.getRow() - pos2.getRow();
        int colDiff = pos1.getCol() - pos2.getCol();
        return (sqrt(double(rowDiff * rowDiff + colDiff * colDiff)));
    }
   
public:

    TerrainElement(Position);
    virtual ~TerrainElement();
    
    virtual void getEffect(Army *army) = 0;
};

class Road : public TerrainElement {
public:
    Road(Position pos) : TerrainElement(pos) {}
   
    void getEffect(Army *army);
};

class Mountain : public TerrainElement {
public:

    Mountain(Position pos) : TerrainElement(pos) {}
   
    void getEffect(Army *army);
};

class River : public TerrainElement {
public:
    River(Position pos) : TerrainElement(pos) {}
   
    void getEffect(Army *army);
};

class Urban : public TerrainElement {
public:
    Urban(Position pos) : TerrainElement(pos) {}
   
    void getEffect(Army *army);
};

class Fortification : public TerrainElement {
public:
    Fortification(Position pos) : TerrainElement(pos) {}

    void getEffect(Army *army);
};

class SpecialZone : public TerrainElement {
public:
    SpecialZone(Position pos) : TerrainElement(pos) {}
    
    void getEffect(Army *army);
};

class BattleField {
private:
    int n_rows, n_cols;
   
    TerrainElement ***terrain;
public:
   
    BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone);
    BattleField(int n_rows, int n_cols );
    ~BattleField();
    
  
    TerrainElement* getElement(int r, int c) const;
    int getNumRows() const { return n_rows; }
    int getNumCols() const { return n_cols; }
    
    string str() const;
};
class Configuration {
private:
    int num_rows;
    int num_cols;
    vector<Position*> arrayForest;
    vector<Position*> arrayRiver;
    vector<Position*> arrayFortification;
    vector<Position*> arrayUrban;
    vector<Position*> arraySpecialZone;

        vector<Unit*> liberationUnits;
    vector<Unit*> ARVNUnits;
    Unit** liberationArmy;
    Unit** ARVNArmy;
    
    int eventCode;
public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
    
   
    int getNumRows() const { return num_rows; }
    int getNumCols() const { return num_cols; }
   vector<Unit*>& getLiberationUnits() { return liberationUnits; }
    vector<Unit*>& getARVNUnits() { return ARVNUnits; }
    const vector<Position*>& getForestPositions() const { return arrayForest; }
    const vector<Position*>& getRiverPositions() const { return arrayRiver; }
    const vector<Position*>& getFortificationPositions() const { return arrayFortification; }
    const vector<Position*>& getUrbanPositions() const { return arrayUrban; }
    const vector<Position*>& getSpecialZonePositions() const { return arraySpecialZone; }
    int getEventCode() const { return eventCode; }
    
    InfantryType stringToType(const std::string &typeStr);
   VehicleType stringToVehicleType(const std::string &typeStr);
   Unit** vectorToArray(const vector<Unit*>& vec, int& size) {
    Unit** arr = new Unit*[vec.size()];
    for(int i = 0; i < vec.size(); ++i) {
        arr[i] = vec[i];
    }
    size = vec.size();
    return arr;
}
      int findNth(const std::string& str, char ch, int n) {
    int count = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        if(str[i] == ']') {
            return -5;
        }
        if (str[i] == ch) {
            ++count;
            if (count == n) return i;
        }
    }
    return -5;
}
};
class HCMCampaign {
private:
    Configuration* config;
    BattleField* battleField;
    LiberationArmy* liberationArmy;
    ARVN* arvnArmy;
    
public:
int sizelibe = 0;
int sizeARVN = 0;
    HCMCampaign(const string & config_file_path);
    ~HCMCampaign();
    void run();
   
    string printResult();
    
};

#endif