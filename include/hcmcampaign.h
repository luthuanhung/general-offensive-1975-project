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

//!-----------------------------------------------------
//! CLASS Position
//!-----------------------------------------------------
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

//!-----------------------------------------------------
//! CLASS Unit
//!-----------------------------------------------------
class Unit
{
protected:
    int quantity, weight;
    Position pos;
    // * You can add more attributes if needed
    int attackScore;
public:
    Unit(int quantity, int weight, Position pos);
    virtual ~Unit();
    virtual int getAttackScore() = 0;
    virtual string str() const = 0;
    // * You can add more methods if needed
    int getQuantity() { return quantity; }
    int getWeight() { return weight; }
    void setQuantity(int quantity);
    void setWeight(int weight);
    int getAttackScoreinFight();
    void setAttackScore(int score);
    Position getCurrentPosition() const;
    void setPosition(Position value) { pos = value; }
};

//!-----------------------------------------------------
//! CLASS Infantry : public Unit
//!-----------------------------------------------------
class Infantry : public Unit
{
private:
    InfantryType infantryType;
    // * You can add more attributes if needed
public:
    Infantry(int quantity, int weight, Position pos, InfantryType infantryType);
    ~Infantry(){}
    int getAttackScore() override;
    string str() const override;

    // * You can add more methods if needed
    InfantryType getInfantryType() const { return infantryType; }

    static string infantryTypeToString(InfantryType it)
    {
        switch(it)
        {
            case SNIPER:                return "SNIPER";
            case ANTIAIRCRAFTSQUAD:     return "ANTIAIRCRAFTSQUAD";
            case MORTARSQUAD:           return "MORTARSQUAD";
            case ENGINEER:              return "ENGINEER";
            case SPECIALFORCES:         return "SPECIALFORCES";
            case REGULARINFANTRY:       return "REGULARINFANTRY";
            default:                    return "UNKNOWN";
        }
    }
    //!Added function
    int safeCeil(double value);
    bool isPerfectSquare(int n);
    int sumDigits(int n);
    int computeSingleDigit(int score, int year);
};

//!-----------------------------------------------------
//! CLASS Vehicle : public Unit
//!-----------------------------------------------------
class Vehicle : public Unit
{
private:
    VehicleType vehicleType;
    // * You can add more attributes if needed
public:
    Vehicle(int quantity, int weight, Position pos, VehicleType vehicleType);
    ~Vehicle() {}
    int getAttackScore() override;
    string str() const override;
    // * You can add more methods if needed
    // * Help: Get/Set
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
    //!Added function
    int safeCeil(double value);
};

//!-----------------------------------------------------
//! CLASS UnitList
//!-----------------------------------------------------
class UnitList
{
public:
    //!Added class after
    class Node {
    public:
        Unit* data;
        Node* next;

        Node(Unit* unit) : data(unit), next(nullptr) {}
        Node(Unit* unit,Node* next) : data(unit), next(next) {}
    };
    //!Added class before
    UnitList(int capacity);
    bool insert(Unit *unit);
    bool isContain(VehicleType vehicleType);
    bool isContain(InfantryType infantryType);
    // * You can add more methods if needed
    string str() const;
    void clear() {}
    void remove(Unit *unit);
    // * Additional functions if possible
    Node* getUnits();
    ~UnitList();
    UnitList(const UnitList& other);
    UnitList& operator=(const UnitList& other);
    Unit* cloneUnit(Unit* unit);

private:
    int capacity;
    // * You can add more attributes if needed
    Node* head;     // head pointer
    Node* tail;     //tail pointer
    int size;       // size
    int countVehicle, countInfantry; //Num of vehicle and infantry
    //!Added attribute
    vector<Unit*> saveClone;
};

//!-----------------------------------------------------
//! CLASS Army 
//!-----------------------------------------------------
class Army {
protected:
    int LF;
    int EXP;
    string name;
    BattleField* battleField;
    // * You can add more attributes if needed
    bool LiberWin = false;
public:
    UnitList *unitList;
    Army(Unit **unitArray, int size, string name, BattleField *battleField);
    virtual ~Army();
    virtual void fight(Army *enemy, bool defense = false) = 0;
    virtual string str() const = 0;

    // * You can add more methods if needed
    int safeCeil(double value);
    void updateScore(bool update);
    int getEXP();
    void setEXP(int EXP);
    int getLF();
    void setLF(int LF);
    bool IsBase(int N,int p);
    bool IsPrime(int N);
    bool isSpecial(int N);
};

//!-----------------------------------------------------
//! CLASS LiberationArmy
//!-----------------------------------------------------
class LiberationArmy : public Army
{
private:
    // * You can add more attributes if needed
    // * Hint: Bạn có thể thêm hoặc thay thế các phương thức khác để truy cập các thành viên riêng tư nếu cần thiết.
    int nearestFibonacci(int value);
    vector<Unit*> knapsack(vector<Unit*> units, int maxScore);
    Unit* cloneUnit(Unit* unit);
    //!Added attribute
    vector<Unit*> saveClone;
public:
    LiberationArmy(Unit **unitArray, int size, string name, BattleField *battleField);
    ~LiberationArmy();
    void fight(Army *enemy, bool defense) override;
    string str() const override;
    // * You can add more methods if needed
};

//!-----------------------------------------------------
//! CLASS ARVN
//!-----------------------------------------------------
class ARVN : public Army
{
private:
    // * You can add more attributes if needed
public:
    ARVN(Unit** unitArray, int size, string name, BattleField* battleField);
    ~ARVN();
    void fight(Army* enemy, bool defense=false) override;
    string str() const;

    // * You can add more methods if needed
    void updateScores();
};

//!-----------------------------------------------------
//! CLASS TerrainElement và các lớp dẫn xuất
//!-----------------------------------------------------
class TerrainElement {
protected:
    Position pos;
    // * You can add more attributes if needed
    double calculateDistance(const Position& pos1, const Position& pos2) {
        int rowDiff = pos1.getRow() - pos2.getRow();
        int colDiff = pos1.getCol() - pos2.getCol();
        return (sqrt(double(rowDiff * rowDiff + colDiff * colDiff)));
    }
    int safeCeil(double value) {
        double diff = abs(value - round(value));
        return (diff < 1e-9) ? round(value) : ceil(value);
    }
public:
    TerrainElement(Position);
    virtual ~TerrainElement();
    virtual void getEffect(Army *army) = 0;
    // * You can add more attributes if needed
};

class Road : public TerrainElement {
public:
    Road(Position pos) : TerrainElement(pos) {}
    void getEffect(Army *army);
    // * You can add more methods if needed
};

class Mountain : public TerrainElement {
public:
    Mountain(Position pos) : TerrainElement(pos) {}
    void getEffect(Army *army);
    // * You can add more methods if needed
};

class River : public TerrainElement {
public:
    River(Position pos) : TerrainElement(pos) {}
    void getEffect(Army *army);
    // * You can add more methods if needed
};

class Urban : public TerrainElement {
public:
    Urban(Position pos) : TerrainElement(pos) {}
    void getEffect(Army *army);
    // * You can add more methods if needed
};

class Fortification : public TerrainElement {
public:
    Fortification(Position pos) : TerrainElement(pos) {}
    void getEffect(Army *army);
    // * You can add more methods if needed
};

class SpecialZone : public TerrainElement {
public:
    SpecialZone(Position pos) : TerrainElement(pos) {}
    void getEffect(Army *army);
    // * You can add more methods if needed
};

//!-----------------------------------------------------
//! CLASS BattleField
//!-----------------------------------------------------
class BattleField {
private:
    int n_rows, n_cols;
    TerrainElement ***terrain;
    // * You can add more attributes if needed
public:
    BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone);
    ~BattleField();
    TerrainElement* getElement(int r, int c) const;
    string str() const;
    // * You can add more methods if needed
};

//!-----------------------------------------------------
//! CLASS Configuration
//!-----------------------------------------------------
class Configuration {
private:
    int num_rows;
    int num_cols;
    vector<Position*> arrayForest;
    vector<Position*> arrayRiver;
    vector<Position*> arrayFortification;
    vector<Position*> arrayUrban;
    vector<Position*> arraySpecialZone;
    Unit** liberationUnits;
    Unit** ARVNUnits;
    int eventCode;
    // * You can modify or add more attributes if needed
    int liberationUnits_size;
    int ARVNUnits_size;
public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
    
    // * Getter methods */
    // * You can add more getter methods if needed
    int getNumRows() const { return num_rows; }
    int getNumCols() const { return num_cols; }
    const vector<Position*>& getForestPositions() const { return arrayForest; }
    const vector<Position*>& getRiverPositions() const { return arrayRiver; }
    const vector<Position*>& getFortificationPositions() const { return arrayFortification; }
    const vector<Position*>& getUrbanPositions() const { return arrayUrban; }
    const vector<Position*>& getSpecialZonePositions() const { return arraySpecialZone; }
    int getEventCode() const { return eventCode; }
    Unit** getLiberationUnits() { return liberationUnits; }
    Unit** getARVNUnits() { return ARVNUnits; }
    //!Added function
    int ReadNumber(vector<int>& arr,string s);
    string ReadAlphabet(string s);
    string ReadAlphabet2(string s,int& idx);
    int FindBegin(string s);
    void ArrayLocate(vector<int>& arr,string s, vector<Position*>& array);
    void UnitListExtract(vector<int> &arr,string s);
    int getLiberationUnitsSize() { return liberationUnits_size; }
    int getARVNUnitsSize() { return ARVNUnits_size; }
};

//!-----------------------------------------------------
//! Lớp HCMCampaign
//!-----------------------------------------------------
class HCMCampaign {
private:
    Configuration* config;
    BattleField* battleField;
    LiberationArmy* liberationArmy;
    ARVN* arvnArmy;
    // * You can modify or add more attributes if needed
    Unit** liberunitArray;
    Unit** ARVNunitArray;
public:
    HCMCampaign(const string & config_file_path);
    ~HCMCampaign();
    void run();
    // Phương thức printResult: trả về chuỗi kết quả theo định dạng:
    // "LIBERATIONARMY[LF=<LF>,EXP=<EXP>]-ARVN[LF=<LF>,EXP=<EXP>]"
    string printResult();
    // * You can add more methods if needed
};
#endif