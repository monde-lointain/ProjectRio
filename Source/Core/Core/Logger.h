
#pragma once 

#include <string>
#include <array>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <iostream>
#include <fstream>
#include "Common/FileUtil.h"
#include "Common/FileSearch.h"

class Logger{
    // Create Log file
    std::string log_file_path = File::GetUserPath(D_STATELOGGER_IDX) + file_name + ".txt";
    // std::string json = getHUDJSON(std::to_string(m_game_info.event_num) + "a", m_game_info.getCurrentEvent(), m_game_info.previous_state, true);

public:
    // Constructor
    Logger(std::string in_file_name){
        file_name = in_file_name;
    };    
    std::string file_name;

    void writeToFile(std::string in_string) {
        File::WriteStringToFile(log_file_path, in_string + '\n');
    };

    void writeToTerminal(std::string in_string) {
        std::cout << in_string + "\n";
    };
};

