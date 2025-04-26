#pragma once



#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <ctime>



struct coordinations{

    uint64_t x;
    uint64_t y;

    coordinations(uint64_t x, uint64_t y) : x(x), y(y) {}
};



struct ship{

    std::vector<coordinations> coordin;
    uint64_t x;
    uint64_t y;
    int life;

    char orient;
    int length;

    ship(uint64_t x, uint64_t y, char o, int l) : x(x), y(y), life(l), orient(o), length(l) {};

    void scattering(){

        if (orient == 'v'){

            for (uint64_t temp_y = y; temp_y < y + length; temp_y++)
                coordin.push_back(coordinations(x, temp_y));
        }

        else {

            for (uint64_t temp_x = x; temp_x < x + length; temp_x++)
                coordin.push_back(coordinations(temp_x, y));
        }
    }
};



struct values{

    bool start_value = false;

    uint64_t set_width_int = 0;
    uint64_t set_height_int = 0;

    uint64_t set_count_1 = 0;
    uint64_t set_count_2 = 0;
    uint64_t set_count_3 = 0;
    uint64_t set_count_4 = 0;

    std::string set_strategy;
    
    bool shot_computer_value = false;
    std::vector<coordinations> shotting_computer;
    uint64_t lab_shot_x = 0;
    uint64_t lab_shot_y = 0;
    std::string set_result;

    uint64_t shotting_user_x;
    uint64_t shotting_user_y;
    bool shot_user_value = false;

    bool win_user_value = false;
    bool win_computer_value = false;

    std::string dump_path;
    std::string load_path;
    bool dump_path_value = false;
    bool load_path_value = false;
    bool flag_for_load_of_all_time = false;

    bool flag_for_create_field = true;

    std::vector<ship> armada;

    int count_computer_kill_ship = 0;
    int count_user_kill_ship = 0;

    bool start_value_one = false;
    bool shot_set_result = false;
    int who_shot = 1000;
};