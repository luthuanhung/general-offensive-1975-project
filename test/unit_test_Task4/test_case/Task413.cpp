#include "../unit_test_Task4.hpp"
bool UNIT_TEST_Task4::Task413() {
    string name = "Task413";
    
    
    string cfg = "test/unit_test_Task4/test_case/input/config413.txt";
    ofstream ofs(cfg);
    // Units with minimal attackScore removal (<=5)
    ofs << "NUM_COLS=5\n";
    ofs << "NUM_ROWS=5\n";
    ofs << "ARRAY_FOREST=[]\n";
    ofs << "ARRAY_RIVER=[]\n";
    ofs << "ARRAY_FORTIFICATION=[]\n";
    ofs << "ARRAY_URBAN=[]\n";
    ofs << "ARRAY_SPECIAL_ZONE=[]\n";
    ofs << "EVENT_CODE=10\n";
    ofs << "UNIT_LIST=[TANK(1,1,(1,1),0),SNIPER(1,1,(2,2),1)]\n";
    ofs.close();
    HCMCampaign* campaign = nullptr;
    string result;
    try {
        campaign = new HCMCampaign(cfg);
        result = "** Before the fight\n";
        result += campaign->printResult();
        result += "\n** After the fight\n";
        campaign->run();
        result += campaign->printResult();
        delete campaign;
    } catch (exception &e) {
        result = e.what();
    }
    string expect = "** Before the fight\n"
"LIBERATIONARMY[LF=61,EXP=0]-ARVN[LF=0,EXP=1]\n"
"** After the fight\n"
"LIBERATIONARMY[LF=61,EXP=0]-ARVN[LF=0,EXP=0]";
    remove(cfg.c_str());
    
    return printResult(result, expect, name);
}

