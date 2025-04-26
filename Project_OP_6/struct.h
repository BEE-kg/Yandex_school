#pragma once

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <windows.h>



#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <windows.h>



struct Ticket{

    std::string data;

    std::string city_a;
    std::string city_b;

    bool flag_for_transport = false;
    bool plane = false;
    bool train = false;
    bool suburban = false;
    bool bus = false;
    
    bool transfer = false;
};



struct Parametrs{

    std::string code_a = "c2"; // спб
    std::string code_b = "c194"; //саратов
    
    // std::string code_a = "s9605308"; // ртищево
    // std::string code_a = "c213"; // москва

    std::string start_url = "https://api.rasp.yandex.net/v3.0/";
    std::string user_key = "/?apikey=18b5c748-3056-4fad-8b19-eef847043b78";

    std::vector<std::string> saratov = {"Гагарин (Саратов)", "Саратов", "Саратов-1-Пасс.", "Саратов, автовокзал"};
};