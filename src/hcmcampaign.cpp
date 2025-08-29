#include "hcmcampaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
////////////////////////////////////////////////////////////////////////


//!----------------------------------------------
//! Lớp Position
//!----------------------------------------------


//!----------------------------------------------
//! Lớp Position
//!----------------------------------------------


Unit::Unit(int quantity, int weight, Position pos)
    : quantity(quantity), weight(weight), pos(pos)
{
}
Position Unit:: getCurrentPosition() const {
    return pos;
}
void Unit:: setQuantity(int quantity) {
    this->quantity = max(0, quantity);
}
void Unit:: setWeight(int weight) {
    this->weight = max(0, weight);
}
void Unit:: setCurrentPosition(Position pos) {
    this->pos = pos;
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
    attackScore = ceil((static_cast<int>(vehicleType)* 304 + quantity * weight ) / 30.0);
    return attackScore;
}


/* 
@Fix
 */
string Vehicle::str() const
{
    return "Vehicle[vehicleType=" + vehicleTypeToString(vehicleType)  
    + ",quantity=" +   to_string(quantity) + ",weight=" + to_string(weight)
    + ",position=" + pos.str() + "]";
  ;
}


UnitList::UnitList(int S) : countInfantry(0), countVehicle(0)
{
    if(isSpecialNumber(S)) {
        this->capacity = 12;
    } else {
       this -> capacity = 8;
    }
}
bool UnitList::insert(Unit *unit)
{
    if (!unit) {
        return false;
    }
    Node *cur = head;
    while(cur) {
         
      if(auto v = dynamic_cast<Vehicle *>(unit)) {
        if(auto vv = dynamic_cast<Vehicle *>(cur->unit)) {
            if(v -> getVehicleType() == vv -> getVehicleType() ){
                vv->setQuantity(vv -> getQuantity() + v -> getQuantity());
                int weights = max(vv -> getWeight(), v -> getWeight());
                vv->setWeight(weights);
                vv->getAttackScore();
                return false;
            }
        }
      }
      else if(auto i = dynamic_cast<Infantry *>(unit)) {
        if(auto ii = dynamic_cast<Infantry *>(cur->unit)) {
            if(i -> getInfantryType() == ii -> getInfantryType() ){
                ii->setQuantity(ii -> getQuantity() + i -> getQuantity());
               int weights = max(ii -> getWeight(), i -> getWeight());
                ii->setWeight(weights);
                ii->getAttackScore();
                return false;
            }
        }
      }
      cur = cur -> next;
    }
    if( size >= capacity) {
        return false;
    }
    Node *newNode = new Node(unit);
    if(auto v = dynamic_cast<Vehicle *>(unit)) {
       if(!head) {
        head = newNode;
        tail = newNode;
      
       
       } 
       else {
        tail -> next = newNode;
        tail = newNode;
        
       }
        countVehicle++;
       units.push_back(unit);
       size++;
       
    }
    else if(auto i = dynamic_cast<Infantry *>(unit)) {
        if (!tail) {
            head = tail = newNode;
           
        } else {
            newNode->next = head;
            head = newNode;
            
        }
        countInfantry++;
               units.push_back(unit);
    size++;
  
}
  return true;
}

bool UnitList::isContain(VehicleType vehicleType)
{
    Node *cur = head;
   while(cur != nullptr) {
        if (auto vehicle = dynamic_cast<Vehicle *>(cur->unit)) {
            if (vehicle->getVehicleType() == vehicleType) {
                return true;
            }
        }
        cur=cur->next;
    }
    return false;
}

bool UnitList::isContain(InfantryType infantryType)
{
    Node *cur = head;
    while(cur != nullptr) {
        if (auto it = dynamic_cast<Infantry *>(cur->unit)) {
            if (it->getInfantryType() == infantryType) {
                return true;
            }
        }
        cur = cur->next;
    }
    return false;
}

string UnitList::str() const
{
    stringstream ss;
    ss << "UnitList[count_vehicle=" << countVehicle << ";count_infantry="
     << countInfantry;
    if(countInfantry != 0 || countVehicle != 0) {
        ss << ";";
     }
     Node *curr = head;
     while(curr) {
        ss << curr->unit->str();
        if(curr -> next) {
            ss << ",";
        }
        curr = curr->next;
     }
     ss << "]";
     return ss.str();
}

void UnitList::remove(Unit *unit) {
   Node *cur = head;
   Node *prev = nullptr;
   while(cur) {
if(cur -> unit == unit) {
    if(auto v = dynamic_cast<Vehicle *>(cur->unit)) {
                countVehicle--;
            }
            else if(auto i = dynamic_cast<Infantry *>(cur->unit)) {
                countInfantry--;
            }
            size--; 
if(!prev) {
    head = cur -> next;
    if(!head) {
        tail = nullptr;
    }
    
}
else if (cur == tail) {
    tail = prev;
    tail -> next = nullptr;
}
else {
    prev -> next = cur -> next;
}
delete cur;
return;
}
prev = cur;
cur = cur -> next;
}


}




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
    if(army == nullptr) {
        return; 
    }
bool isLiber = dynamic_cast<LiberationArmy*>(army) != nullptr;
    int radius = isLiber ? 2 : 4;
    UnitList::Node *current = army->GetunitList()->getHead();
    while(current != nullptr) {
        Unit *unit = current->unit;
        
        double distance = calculateDistance(unit->getCurrentPosition(), pos);
        if(distance <= radius) {
            int LF1 = army -> getLF();
            int EXP1 = army -> getEXP();
            if(isLiber) {
                if(auto units = dynamic_cast<Infantry*>(unit)) {
                
              army -> setEXP(ceil(army -> getEXP() + (unit->getAttackScoreinFight()*0.3)));
            }
                else if(auto units = dynamic_cast<Vehicle*>(unit)) {
                   
                    army -> setLF(ceil(army -> getLF() - (unit->getAttackScoreinFight()*0.1)));
                  
                }
              LF1 = army -> getLF();
                EXP1 = army -> getEXP();
            }
        
            else {
                if(auto units = dynamic_cast<Infantry*>(unit)) {
                    army -> setEXP(ceil(army -> getEXP() + ((unit->getAttackScoreinFight()*0.2))));
                }
                else if(auto units = dynamic_cast<Vehicle*>(unit)) {
                    army -> setLF(ceil(army -> getLF() - ((unit->getAttackScoreinFight()*0.05))));
                }
               LF1 = army -> getLF();
                EXP1 = army -> getEXP();
       
            }
                army-> setlimit(LF1,1000,0);
  army -> setlimit(EXP1,500,0);
   army -> setEXP(EXP1);
   army -> setLF(LF1);
}
current = current->next;
}
}

// River: stub – giảm EXP của lực lượng bộ binh 10% nếu nằm trong bán kính 2 đơn vị
void River::getEffect(Army *army) {
    if(army == nullptr) {
        return; 
    }
   UnitList::Node *current = army->GetunitList()->getHead();
    while(current != nullptr) {
        Unit *unit = current->unit;
       
        double distance = calculateDistance(unit->getCurrentPosition(), pos);
        if(distance <= 2) {
            if(auto units = dynamic_cast<Infantry*>(unit)) {

       
            units->setAttackScore(ceil(units->getAttackScoreinFight() *0.9));
            }
           
}
current = current->next;
}
}
// Urban: stub – hiệu ứng khu dân cư có thể thay đổi attackScore của bộ binh hoặc phương tiện tùy vào loại
void Urban::getEffect(Army *army) {
    if(army == nullptr) {
        return; 
    }
    
bool isLiber = dynamic_cast<LiberationArmy*>(army) != nullptr;
    int radiusInfan = isLiber ? 5 : 3;
    int radiusVehic = isLiber ? 2 : 0;
    UnitList::Node *current = army->GetunitList()->getHead();
    while(current != nullptr) {
        Unit *unit = current->unit;
        
        double distance = calculateDistance(unit->getCurrentPosition(), pos);
      
      
            if(isLiber) {
                if(auto units = dynamic_cast<Infantry*>(unit)) {
                    if(distance <= radiusInfan && distance > 0) {
                    if (units->getInfantryType() == SPECIALFORCES || units->getInfantryType() == REGULARINFANTRY) {
                       double delta = ((2 * units ->getAttackScoreinFight()) / distance);
                        units->setAttackScore(ceil(units->getAttackScoreinFight() + delta));
                    }
                    
                }
            }
                else if(auto units = dynamic_cast<Vehicle*>(unit)) {
                    if(distance <= radiusVehic && distance > 0) {
                        
                    if (units->getVehicleType() == ARTILLERY ) {
                       
                        units->setAttackScore(ceil(units->getAttackScoreinFight() *0.5));
                    }
                }
            }

        }
        else {
            if(auto units = dynamic_cast<Infantry*>(unit)) {
                    if(distance <= radiusInfan && distance > 0) {
                    if ( units->getInfantryType() == REGULARINFANTRY) {
                       double delta = (3 * units ->getAttackScoreinFight()) / (2*distance);
                        units->setAttackScore(ceil(units->getAttackScoreinFight() + delta));
                    }
                    
                }
            }
        }
        current = current->next;
    }
}


// Fortification: stub – hiệu ứng chiến hào, áp dụng cho cả hai quân đội với các thay đổi nhất định
void Fortification::getEffect(Army *army) {
    if(army == nullptr) {
        return; 
    }
bool isLiber = dynamic_cast<LiberationArmy*>(army) != nullptr;
    int radius = 2;
 
    UnitList::Node *current = army->GetunitList()->getHead();
    while(current != nullptr) {
        Unit *unit = current->unit;
       
        double distance = calculateDistance(unit->getCurrentPosition(), pos);
        if(distance <= radius) {
            double deta = unit->getAttackScoreinFight() * 0.2;
            if(isLiber) {

                unit->setAttackScore(ceil(unit->getAttackScoreinFight() - deta));
}
else {
                unit->setAttackScore(ceil(unit->getAttackScoreinFight() + deta));
            }
        }
         current = current->next;
    }

} 

// SpecialZone: stub – các đơn vị trong bán kính 1 đơn vị có attackScore = 0
void SpecialZone::getEffect(Army *army) {

    if(army == nullptr) {
        return; 
    }
    int radius = 1;
  
    UnitList::Node *current = army->GetunitList()->getHead();
    while(current != nullptr) {
        Unit *unit = current->unit;
       
        double distance = calculateDistance(unit->getCurrentPosition(), pos);
        if(distance <= radius) {
            unit->setAttackScore(0);
        }  
        current = current->next;     
}

}



//!----------------------------------------------
//! Lớp Position
//!----------------------------------------------
Position::Position(int r, int c) : r(r), c(c) {}
Position::Position(const string &str_pos) 
    {
   string temp = str_pos.substr(1, str_pos.length() - 2);
   stringstream ss(temp);
   char ch;
   ss >> r >> ch >> c;

}
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



LiberationArmy::LiberationArmy(Unit **unitArray, int size, string name,BattleField* battlefield)
                                                : Army(unitArray,size,name,battlefield) {                                                       
    // TODO: Implement
}
LiberationArmy::LiberationArmy(Unit **unitArray, int size, string name,int dum)
                                                : Army(unitArray,size,name,nullptr)    {}                                                
    // TODO: Implement


void LiberationArmy::fight(Army *enemy, bool defense) {
  int newLF = 0;
  int newEXP = 0;
  if (!defense) {
    newLF = ceil(1.5 * LF);
    newEXP = ceil(1.5 * EXP);
  } else {
    newLF = ceil(1.3 * LF);
    newEXP = ceil(1.3 * EXP);
  }
  LF = newLF;
  EXP = newEXP;
  this->setlimit(newLF, 1000, 0);
    this->setlimit(newEXP, 500, 0);

  vector<Unit *> Infantryunit, Vehicleunit;

  UnitList::Node *current = unitList->getHead();
  while (current != nullptr) {
    Unit *units = current->unit;
    current = current->next;
    if (auto v = dynamic_cast<Vehicle *>(units)) {
      Vehicleunit.push_back(v);
    } else if (auto i = dynamic_cast<Infantry *>(units)) {
      Infantryunit.push_back(i);
    }
  }
    

  if (!defense) {
    vector<Unit *> bestInfantry = findcombo(Infantryunit, enemy->getEXP());
    vector<Unit *> bestVehicle = findcombo(Vehicleunit, enemy->getLF());

    bool hasA = !bestInfantry.empty();
    bool hasB = !bestVehicle.empty();
    
    if (hasA && hasB) {
      for (auto unit : bestInfantry) {
        unitList->remove(unit);
      }
      for (auto unit : bestVehicle) {
        unitList->remove(unit);
      } 
      vector<Unit*> capturedUnits;
      current = enemy->GetunitList()->getHead();
      while (current != nullptr) {
        capturedUnits.push_back(cloneUnit(current->unit));
        current = current->next;
      }
   
      
     
    
      
      
       while (enemy->GetunitList()->getHead() != nullptr) {
        UnitList::Node* temp = enemy->GetunitList()->getHead();
        enemy->GetunitList()->head = enemy->GetunitList()->getHead()->next;
        delete temp; 
      }
       enemy->GetunitList()->tail = nullptr;
      enemy->GetunitList()->countVehicle = 0;
      enemy->GetunitList()->countInfantry = 0;
      enemy->GetunitList()->size = 0;
      vector<Unit*> Units1 = enemy->GetunitList()->getUnits();
      Units1.clear();
      for(int i = capturedUnits.size()-1; i >=0;i--) {
        Unit* unit = capturedUnits[i];
        unitList->insert(unit);
      }
      enemy->updateScore();
      LF = newLF;
      EXP = newEXP;
      updateScore();
      this->setlimit(LF, 1000, 0);
      this->setlimit(EXP, 500, 0);

      return;
    } else if ((!hasA && hasB) || (hasA && !hasB)) {
      bool win = false;
      if (!hasA) {
        if(newEXP > enemy->getEXP()) {
          win = true;
        }
      }
      if(!hasB) {
        if(newLF > enemy->getLF()) {
          win = true;
        }
      }
        if(win) {
          if(hasA && !hasB) {
            for (auto unit : bestInfantry) {
              unitList->remove(unit);
            }
            UnitList::Node* current = unitList->getHead();
            vector<Unit*> vehicle_lose;
            while(current != nullptr) {
              Unit *units = current->unit;
               if(auto v = dynamic_cast<Vehicle *>(units)) {
                vehicle_lose.push_back(v);
              }
              current = current->next;
            }
            for (auto unit : vehicle_lose) {
              unitList->remove(unit);
            }
          }
          else if(!hasA && hasB) {
            for (auto unit : bestVehicle) {
              unitList->remove(unit);
            }
            UnitList::Node* current = unitList->getHead();
            vector<Unit*> infantry_lose;
            while(current != nullptr) {
              Unit *units = current->unit;
               if(auto i = dynamic_cast<Infantry *>(units)) {
                infantry_lose.push_back(i);
              }
              current = current->next;
            }
            for (auto unit : infantry_lose) {
              unitList->remove(unit);
            }
          }
        
        
          vector<Unit*> capturedUnits;
        current = enemy->GetunitList()->getHead();
        while (current != nullptr) {
          capturedUnits.push_back(cloneUnit(current->unit));
          current = current->next;
        }
        
    
      
        
        while (enemy->GetunitList()->getHead() != nullptr) {
          UnitList::Node* temp = enemy->GetunitList()->getHead();
          enemy->GetunitList()->head = enemy->GetunitList()->getHead()->next;
          delete temp;
        }
        enemy->GetunitList()->tail = nullptr;
        enemy->GetunitList()->countVehicle = 0;
        enemy->GetunitList()->countInfantry = 0;
        enemy->GetunitList()->size = 0;
        enemy->GetunitList()->getUnits().clear();
      for(int i = capturedUnits.size()-1; i >=0;i--) {
        Unit* unit = capturedUnits[i];
        unitList->insert(unit);
      }
        enemy->updateScore();
    
        this->updateScore();
        this->setlimit(LF, 1000, 0);
        this->setlimit(EXP, 500, 0);
        return;
      }
      else {
        current = unitList->getHead();
        while (current != nullptr) {
          Unit *units = current->unit;
          current = current->next;
          units->setWeight(ceil(0.9 * units->getWeight()));
        }
         updateScore();
      }
       
       
        return; 
    } else if (!hasA && !hasB) {
      current = unitList->getHead(); 
      while (current != nullptr) {
        Unit *units = current->unit;
        current = current->next;
        units->setWeight(ceil(0.9 * units->getWeight()));
      }
      this->updateScore();
    }
    
    
    
    return; 
  } else {
    if (newLF > enemy->getLF() && newEXP > enemy->getEXP()) {
      LF = newLF;
      EXP = newEXP;
      this->setlimit(LF, 1000, 0);
      this->setlimit(EXP, 500, 0);
      return;
    } else if (newLF > enemy->getLF() || newEXP > enemy->getEXP()) {
      current = unitList->getHead(); 
      while (current != nullptr) {
        Unit *units = current->unit;
        current = current->next;
        units->setQuantity(ceil(0.9 * units->getQuantity()));
      }
      this->updateScore();
      return;
    } else if (newLF < enemy->getLF() && newEXP < enemy->getEXP()) {
      while (LF < enemy->getLF() && EXP < enemy->getEXP()) {
        current = unitList->getHead();
        while (current != nullptr) {
          Unit *units = current->unit;
          current = current->next;
          units->setQuantity(nearestFibonacci(units->getQuantity()));
        }
        this->updateScore(true);
       
      }
      
      if (LF > enemy->getLF() && EXP > enemy->getEXP()) {
        LF = ceil(1.3 * LF);
        EXP = ceil(1.3 * EXP);
        this->setlimit(LF, 1000, 0);
        this->setlimit(EXP, 500, 0);
        return;
      } else {
        current = unitList->getHead(); 
        while (current != nullptr) {
          Unit *units = current->unit;
          current = current->next;
          units->setWeight(ceil(0.9 * units->getWeight()));
        }
        this->updateScore();
        return;
      }
    }
    
 
    return;
  }
}
string LiberationArmy::str() const {
  stringstream ss;
  ss << "LiberationArmy[" 
      << "LF=" << LF << ",EXP=" << EXP
      << ",unitList=" << unitList->str()
      << ",battleField=";
      if(battlefield != nullptr) {
        ss << battlefield->str();
      }
      
   
     
     ss << "]";
  return ss.str();
}



// Sup function
int LiberationArmy::nearestFibonacci(int value) {
   if( value < 1) return 1;
   int a = 0, b = 1;
   while(b < value) {
    int next = a + b;
    a = b;
    b = next;
   }
   return b;
}

vector<Unit*> LiberationArmy::findcombo(vector<Unit*> units, int minScore) {
  int n = units.size();
  
 
  vector<Unit*> besttohop;
  int bestSum = INT_MAX;
 


  for (int g = 1;   g < (1 << n); ++g) {
    vector<Unit*> tohop;
    int sum = 0;
      for(int i = 0; i < n;i++) {
        if(g & (1 << i)) {
         tohop.push_back(units[i]);
         sum+= units[i]->getAttackScoreinFight();
       
         
        }
      }
      if( sum < bestSum && sum > minScore) {
        bestSum = sum;
        besttohop = tohop;
      }
}
        
return besttohop;
}

Unit* LiberationArmy::cloneUnit(Unit* unit) {
  if(auto v = dynamic_cast<Vehicle *>(unit)) {
    return new Vehicle(*v);
  }
  else if(auto i = dynamic_cast<Infantry *>(unit)) {
    return new Infantry(*i);
  }
  return nullptr;
}


// TODO: implementnfantry::Infantry(int quantity, int weight, const Position pos, InfantryType infantryType) : Unit(quantity, weight, pos), infantryType(infantryType)
Infantry::Infantry(int quantity, int weight, Position pos, InfantryType infantryType) 
: Unit(quantity, weight, pos), infantryType(infantryType) { }
 
int Infantry::getAttackScore() {
    int score = (static_cast<int>(infantryType) * 56 + quantity * weight);
    if ( infantryType == InfantryType::SPECIALFORCES && sochinhphuong(weight) ) {
        score = score + 75;
    }

    int person_number = socanhan(score);
    if ( person_number > 7) {
        setQuantity(ceil(1.2 * quantity)) ;
     }
     else if (socanhan(score) < 3) {
        setQuantity(ceil(0.9 * quantity)) ;
     }

     score = (static_cast<int>(infantryType) * 56 + quantity * weight);
     attackScore = score;
     return attackScore;
    }
int Infantry::getAttackScorewithoutmodify() {
    int score = (static_cast<int>(infantryType) * 56 + quantity * weight);
    if ( infantryType == InfantryType::SPECIALFORCES && sochinhphuong(weight) ) {
        score = score + 75;
    }
  int quant1;
    int person_number = socanhan(score);
    if ( person_number > 7) {
        quant1 = ceil(1.2 * quantity);
     }
     else if (socanhan(score) < 3) {
       
         quant1 = ceil(0.9 * quantity);
     }

     score = (static_cast<int>(infantryType) * 56 + quant1 * weight);
     attackScore = score;
     return attackScore;
    }

     string Infantry::str() const {
        return "Infantry[infantryType=" + infantryTypeToString(infantryType)  +
         + ",quantity=" +   to_string(quantity) + ",weight=" + to_string(weight)
         + ",position=" + pos.str() + "]";
       
    }








// * Hint: Bạn có thể thêm hoặc thay thế các phương thức khác để truy cập các thành viên riêng tư nếu cần thiết.

InfantryType Configuration::stringToType(const string &typeStr) {
  
 string token = typeStr;
 
    
    if (token == "SNIPER")
        return SNIPER;
    else if (token == "REGULARINFANTRY")
        return REGULARINFANTRY;
    else if (token == "ANTIAIRCRAFTSQUAD")
        return ANTIAIRCRAFTSQUAD;
    else if (token == "MORTARSQUAD")
        return MORTARSQUAD;
    else if (token == "ENGINEER")
        return ENGINEER;
    else if  (token == "SPECIALFORCES")
        return SPECIALFORCES;
   return REGULARINFANTRY;
}
VehicleType Configuration::stringToVehicleType(const string &typeStr) {
    string token = typeStr;

    
    if (token == "TRUCK")
        return TRUCK;
    else if (token == "MORTAR")
        return MORTAR;
    else if (token == "ANTIAIRCRAFT")
        return ANTIAIRCRAFT;
    else if (token == "ARMOREDCAR")
        return ARMOREDCAR;
    else if (token == "APC")
        return APC;
    else if (token == "ARTILLERY")
        return ARTILLERY;
    else if (token == "TANK")
        return TANK;
    return TRUCK;
   
}
Configuration::Configuration(const string &filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filepath);
    }

    string line;
    while (getline(file, line)) {
       
        if (line.empty()) continue;

        istringstream ss(line);
        string value;
        string key;
        
        getline(ss, key, '=');
        getline(ss, value); 
        
    

        if (key == "NUM_ROWS") {
            num_rows = stoi(value);
        } else if (key == "NUM_COLS") {
            num_cols = stoi(value);
        } else if (key.rfind("ARRAY_", 0) == 0) {
            string array_content_str = value.substr(1, value.length() - 2);
            
            vector<int> xst;
            vector<int> yst;
            
            if (!array_content_str.empty()) {
                istringstream iss(array_content_str);
                char open_paren, comma_char, close_paren;
                int r_val, c_val;

                while (iss >> open_paren &&
                       iss >> r_val &&
                       iss >> comma_char &&
                       iss >> c_val &&
                       iss >> close_paren) {
                    xst.push_back(r_val);
                    yst.push_back(c_val);
                    
                    if (iss.peek() == ',') {
                        iss.ignore(); 
                    } else {
                        break; 
                    }
                }
            }
                            
            vector<Position*> result;
            for(size_t j = 0; j < xst.size(); j++) {
                result.push_back(new Position(xst[j], yst[j]));
            }
                
            if (key == "ARRAY_FOREST") {
                arrayForest = result;
            } else if (key == "ARRAY_RIVER") {
                arrayRiver = result;
            } else if (key == "ARRAY_FORTIFICATION") {
                arrayFortification = result;
            } else if (key == "ARRAY_URBAN") {
                arrayUrban = result;
            } else if (key == "ARRAY_SPECIAL_ZONE") {
                arraySpecialZone = result;
            }
        } else if (key == "UNIT_LIST") {
            string unit_list_content_str = value.substr(1, value.length() - 2);
            
            string current_parsing_content = unit_list_content_str;

            while(!current_parsing_content.empty()) {
                int check = findNth(current_parsing_content, ')', 2); 
                if (check == -5) break; 

                string unitStr = current_parsing_content.substr(0, static_cast<size_t>(check) + 1);
                
                if (static_cast<size_t>(check) + 1 < current_parsing_content.length()) {
                    current_parsing_content = current_parsing_content.substr(static_cast<size_t>(check) + 1);
                    if (!current_parsing_content.empty() && current_parsing_content[0] == ',') {
                         current_parsing_content = current_parsing_content.substr(1);
                    }
                } else {
                    current_parsing_content = "";
                }

                istringstream unitStream(unitStr);
                string type_name_str;
                getline(unitStream, type_name_str, '(');

                bool isInfantry = false;
                InfantryType typeEnum_val = REGULARINFANTRY;
                VehicleType typeEnum1_val = TRUCK;

                if(type_name_str == "SNIPER"  || type_name_str == "REGULARINFANTRY"  ||
                    type_name_str == "ANTIAIRCRAFTSQUAD"  || type_name_str == "MORTARSQUAD"  ||
                    type_name_str == "ENGINEER"  || type_name_str == "SPECIALFORCES") {
                    typeEnum_val = stringToType(type_name_str);
                    isInfantry = true;
                } else {
                    typeEnum1_val = stringToVehicleType(type_name_str);
                    isInfantry = false;
                }
            
                string params_inside_unit_paren;
                getline(unitStream, params_inside_unit_paren, '(');
              
                istringstream params_ss(params_inside_unit_paren);
                int quantity_val, weight_val, r_coord_val, c_coord_val, army_idx_val;
                char comma1, comma2, comma4, comma3, close2;

                params_ss >> quantity_val >> comma1
                          >> weight_val >> comma2;
                          
                 params_inside_unit_paren = " ";
                getline(unitStream, params_inside_unit_paren, ')');

                istringstream params_ss1(params_inside_unit_paren);
                params_ss1 >> r_coord_val >> comma3
                          >> c_coord_val;
                             params_inside_unit_paren = " ";
                          getline(unitStream, params_inside_unit_paren, ')');
                          istringstream params_ss2(params_inside_unit_paren);
                            params_ss2 >> comma4 >> army_idx_val;
                Unit* new_unit = nullptr;
                if(isInfantry) {
                    new_unit = new Infantry(quantity_val, weight_val, Position(r_coord_val, c_coord_val), typeEnum_val);
                } else  {
                    new_unit = new Vehicle(quantity_val, weight_val, Position(r_coord_val, c_coord_val), typeEnum1_val);
                }
                
                if (army_idx_val == 0) {
                    
                    liberationUnits.push_back(new_unit);
                } else { 
                    ARVNUnits.push_back(new_unit);
                }
            }    
        } else if (key == "EVENT_CODE") {
            int valueint = stoi(value);
            if(valueint < 0) valueint = 0;
            else if(valueint > 100) {
                valueint = stoi(value.substr(value.size() -2));
            }
            eventCode = valueint;
        }
        } 
    
    file.close();
    }
    // int temp_size_lib, temp_size_arvn;
    // liberationArmy = vectorToArray(liberationUnits, temp_size_lib);
    // ARVNArmy = vectorToArray(ARVNUnits, temp_size_arvn);


Configuration::~Configuration() {
  for(auto pos : arrayForest) {
        delete pos;
    }
    for(auto pos : arrayRiver) {
        delete pos;
    }
    for(auto pos : arrayFortification) {
        delete pos;
    }
    for(auto pos : arrayUrban) {
        delete pos;
    }
    for(auto pos : arraySpecialZone) {
        delete pos;
    }
    for(auto unit : liberationUnits) {
        delete unit;
    }
    for(auto unit : ARVNUnits) {
        delete unit;
    }
}

string Configuration::str() const {
stringstream ss;
    ss << "[num_rows=" << num_rows <<
        ",num_cols=" << num_cols << "," <<
        "arrayForest=[";
        int si = arrayForest.size();
        int g = 0;
        for(auto pos : arrayForest) {
            g++;
            if(g == si) {
                ss << pos->str();
            }
            else {
                ss << pos->str() << ",";
            }
           
        }
        si = arrayRiver.size();
         g = 0;
        ss << "]," << "arrayRiver=[";
        for(auto pos : arrayRiver) {
            g++;
            if(g == si) {
                ss << pos->str();
            }
            else {
                ss << pos->str() << ",";
            }
        }
         si = arrayFortification.size();
         g = 0;
        ss << "],"  << "arrayFortification=[";
        for(auto pos : arrayFortification) {
            g++;
            if(g == si) {
                ss << pos->str();
            }
            else {
                ss << pos->str() << ",";
            }
        }
        ss << "],"  << "arrayUrban=[";
         si = arrayUrban.size();
         g = 0;
        for(auto pos : arrayUrban) {
            g++;
            if(g == si) {
                ss << pos->str();
            }
            else {
                ss << pos->str() << ",";
            }
        }
         si = arraySpecialZone.size();
         g = 0;
        ss << "],"  << "arraySpecialZone=[";
        for(auto pos : arraySpecialZone) {
            g++;
            if(g == si) {
                ss << pos->str();
            }
            else {
                ss << pos->str() << ",";
            }
        }
        ss << "],"  << "liberationUnits=[";
        si = liberationUnits.size();
        g = 0;
        for(auto unit : liberationUnits) {

            g++;
            if(g == si) {
                ss << unit->str();
            }
            else {
                ss << unit->str() << ",";
            }
        }
        ss << "],"  << "ARVNUnits=[";
        si = ARVNUnits.size();
        g = 0;
        for(auto unit : ARVNUnits) {
            g++;
            if(g == si) {
                ss << unit->str();
            }
            else {
                ss << unit->str() << ",";
            }
        }
        ss << "],"  << "eventCode=" << eventCode;
    ss << "]";
    return ss.str();
}

//!-----------------------------------------------------
// CLASS BattleField
//!-----------------------------------------------------


BattleField::BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                         const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                         const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone)
    : n_rows(n_rows), n_cols(n_cols)
{
   terrain = new TerrainElement**[n_rows];
   for (int i = 0; i < n_rows; ++i) {
      terrain[i] = new TerrainElement*[n_cols];
      for (int j = 0; j < n_cols; ++j) {
         terrain[i][j] = new Road(Position(i, j)); 
      }
   }
   for(Position* i : arrayForest) {
    delete terrain[i->getRow()][i->getCol()];
  terrain[i->getRow()][i->getCol()] = new Mountain(*i);
   }
   for(Position* i : arrayRiver) {
    delete terrain[i->getRow()][i->getCol()];
  terrain[i->getRow()][i->getCol()] = new River(*i);
   }
   for(Position* i : arrayFortification) {
    delete terrain[i->getRow()][i->getCol()];
  terrain[i->getRow()][i->getCol()] = new Fortification(*i);
   }
   for(Position* i : arrayUrban) {
    delete terrain[i->getRow()][i->getCol()];
  terrain[i->getRow()][i->getCol()] = new Urban(*i);
   }
   for(Position* i : arraySpecialZone) {
    delete terrain[i->getRow()][i->getCol()];
  terrain[i->getRow()][i->getCol()] = new SpecialZone(*i);
}
}
BattleField::BattleField(int n_rows, int n_cols) 
  : n_rows(n_rows), n_cols(n_cols)
{
   terrain = new TerrainElement**[n_rows];
   for (int i = 0; i < n_rows; ++i) {
      terrain[i] = new TerrainElement*[n_cols];
      for (int j = 0; j < n_cols; ++j) {
         terrain[i][j] = new Road(Position(i, j)); 
      }
    }
  }


BattleField::~BattleField() {
    for(int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            delete terrain[i][j];
        }
        delete[] terrain[i];
}
delete  [] terrain;
    terrain = nullptr;
}
TerrainElement* BattleField::getElement(int r, int c) const {
  if(r < 0 || r >= n_rows || c < 0 || c >= n_cols) {
    return nullptr; 
  }
return terrain[r][c];
}


string BattleField::str() const {
stringstream ss;
    ss << "BattleField[" << "n_rows=" << n_rows << ",n_cols=" << n_cols << "]";
    return ss.str();
}




vector<Unit*> ARVN::findcombo(vector<Unit*> units, int minScore) {
  int n = units.size();
  
 
  vector<Unit*> besttohop;
  int bestSum = INT_MAX;
 


  for (int g = 1;   g < (1 << n); ++g) {
    vector<Unit*> tohop;
    int sum = 0;
      for(int i = 0; i < n;i++) { 
        if(g & (1 << i)) {
         tohop.push_back(units[i]);
         sum+= units[i]->getAttackScore();
       
         
        }
      }
      if( sum < bestSum && sum > minScore) {
        bestSum = sum;
        besttohop = tohop;
      }
}
        
return besttohop;
}
// TODO: Implement
ARVN::ARVN(Unit** unitArray, int size, string name,BattleField* battlefield)
    : Army(unitArray, size, name,battlefield) {
        // TODO: Implement
}
ARVN::ARVN(Unit** unitArray, int size, string name,int dum)
    : Army(unitArray, size, name,nullptr) {
        // TODO: Implement
}
void ARVN::fight(Army* enemy, bool defense) {
  if(!defense) {
 UnitList:: Node* current = unitList->getHead();
        while (current != nullptr) {
            Unit* u = current->unit;
            current = current->next; 
            int q = u->getQuantity();
            int newQ = (int)ceil(q * 0.8);
            if (newQ <= 1) {
                unitList->remove(u);
            } else {
                u->setQuantity(newQ);
            }
        }
    
  
   this->updateScore();
      }
else {
 UnitList:: Node* current = enemy->GetunitList()->getHead();
 vector <Unit *> Infantryunit, Vehicleunit;
        while (current != nullptr) {

Unit* units = current->unit;
  current = current->next;


  if(auto v = dynamic_cast<Vehicle *>(units)) {
    Vehicleunit.push_back(v);
  }
  else if(auto i = dynamic_cast<Infantry *>(units)) {
    Infantryunit.push_back(i);
  }
        }

vector <Unit*> bestInfantry =  findcombo(Infantryunit, EXP);
vector<Unit*> bestVehicle = findcombo(Vehicleunit, LF);

bool hasA = !bestInfantry.empty();
bool hasB = !bestVehicle.empty();
if (hasA && hasB) {
UnitList:: Node* current = unitList->getHead();
 
        while (current != nullptr) {
          Unit* u = current->unit;
          current = current->next;
            u -> setWeight(ceil(0.8*u -> getWeight()));
        }
this->updateScore();
}
else if ((!hasA && hasB) || (hasA && !hasB)) {
  int newLF1 = (int)ceil(enemy->getLF() * 1.5 );
  int newEXP1 = (int)ceil(enemy->getEXP() * 1.5 );
  bool win = false;
  if(!hasA && newEXP1 > EXP) win = true;
  if(!hasB && newLF1 > LF) win = true;
  if(win) {
UnitList:: Node* current = unitList->getHead();
  while (current != nullptr) {
          Unit* u = current->unit;
          current = current->next;
            u -> setWeight(ceil(0.8*u -> getWeight()));
        }
  this->updateScore();
  return;
}

}


}
}





string ARVN::str() const {
  stringstream ss;
  ss << "ARVN[" 
      << "LF=" << LF << ",EXP=" << EXP
      << ",unitList=" << unitList->str()
     << ",battleField=";
     if (battlefield != nullptr) {
         ss << battlefield->str();
      
     }
     
     
      /* code */
     
     
      ss << "]";
      return ss.str();
}




Army::Army(Unit **unitArray, int size, string name,BattleField* battlefield) : name(name), battlefield(battlefield) 
    
{
   LF = 0;
    EXP = 0;
    for(int i = 0; i < size;i++) {
     auto unit = unitArray[i];
       if(auto v = dynamic_cast<Vehicle *>(unit)) {
            LF += v->getAttackScore();
        }
        else if(auto i = dynamic_cast<Infantry *>(unit)) {
            EXP += i->getAttackScore();
        }
        
    }
   this-> setlimit(LF,1000,0);
   this-> setlimit(EXP,500,0);
    unitList = new UnitList(LF+EXP);
    for(int i = 0; i < size;i++) {
        unitList ->insert(unitArray[i]);
    }
}

Army::~Army() {
    UnitList::Node* current = unitList->getHead();
  
    delete unitList;
   

}
void Army::fight(Army* enemy, bool defense) {
    // TODO: Implement
}

string Army::str() const {
    return "Army[name=" + name + ",LF=" + to_string(LF) + ",EXP=" + to_string(EXP) + "]";
}


void Army::updateScore(bool check ){
  {
    if(!check) {
    LF = 0;
    EXP = 0;
    UnitList::Node* current = unitList->getHead();
    while (current != nullptr) {
        Unit* u = current->unit;
        if (auto v = dynamic_cast<Vehicle*>(u)) LF += v->getAttackScore();
        else if (auto i = dynamic_cast<Infantry*>(u)) EXP += i->getAttackScore();
        current = current->next;
    }
      this-> setlimit(LF,1000,0);
   this-> setlimit(EXP,500,0);
}
else {
     LF = 0;
    EXP = 0;
    UnitList::Node* current = unitList->getHead();
    while (current != nullptr) {
        Unit* u = current->unit;
        if (auto v = dynamic_cast<Vehicle*>(u)) LF += v->getAttackScore();
        else if (auto i = dynamic_cast<Infantry*>(u)) EXP += i->getAttackScorewithoutmodify();
        current = current->next;
    }
      this-> setlimit(LF,1000,0);
   this-> setlimit(EXP,500,0);
}
}
}





//!-----------------------------------------------------
//! Lớp HCMCampaign
//!-----------------------------------------------------
HCMCampaign::HCMCampaign(const string & config_file_path) {
    config = new Configuration(config_file_path);
    battleField = new BattleField(config->getNumRows(), config->getNumCols(),
        config->getForestPositions(), config->getRiverPositions(),
        config->getFortificationPositions(), config->getUrbanPositions(),
        config->getSpecialZonePositions());
        sizelibe = config->getLiberationUnits().size();
        sizeARVN = config->getARVNUnits().size();
      Unit** libearmy = config-> vectorToArray(config->getLiberationUnits(), sizelibe);
      Unit** arvnarmy = config-> vectorToArray(config->getARVNUnits(), sizeARVN);
         liberationArmy = new LiberationArmy(libearmy,sizelibe ,"Liberation Army", battleField);
    arvnArmy = new ARVN(arvnarmy,sizeARVN, "ARVN Army", battleField);
}

   
HCMCampaign::~HCMCampaign() {
    delete arvnArmy;
    delete liberationArmy;
    delete battleField;
    delete config;
}
void HCMCampaign::run() {
    for (int r = 0; r < battleField->getNumRows(); ++r) {
    for (int c = 0; c < battleField->getNumCols(); ++c) {
        TerrainElement* elem = battleField->getElement(r, c);
        elem->getEffect(liberationArmy);
        elem->getEffect(arvnArmy);
    }
}
if(config->getEventCode() < 75) {
    liberationArmy->fight(arvnArmy, false);
    arvnArmy->fight(liberationArmy, true);
}
else if(config->getEventCode() >= 75){
    arvnArmy->fight(liberationArmy, false);
    liberationArmy->fight(arvnArmy, true);
    liberationArmy->fight(arvnArmy, false);
    arvnArmy->fight(liberationArmy, true);
    
}
 UnitList::Node* current = liberationArmy->GetunitList()->getHead();
 UnitList::Node* current1 = arvnArmy->GetunitList()->getHead();
    while (current != nullptr) {
        Unit* u = current->unit;
       if(u -> getAttackScoreinFight() <= 5) {
            liberationArmy->GetunitList()->remove(u);
       }
            
        current = current->next;
    }
    while(current1 != nullptr) {
        Unit* u = current1->unit;
       if(u -> getAttackScoreinFight() <= 5) {
            arvnArmy->GetunitList()->remove(u);
       }
            
        current1 = current1->next;
    }
    liberationArmy->updateScore();
    arvnArmy->updateScore();

}

string HCMCampaign::printResult() {
    ostringstream ss;
    ss << "LIBERATIONARMY[LF=" << liberationArmy->getLF()
       << ",EXP=" << liberationArmy->getEXP() << "]-"
       << "ARVN[LF=" << arvnArmy->getLF()
       << ",EXP=" << arvnArmy->getEXP() << "]";
    return ss.str();
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////