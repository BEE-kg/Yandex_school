#include "config.h"
#include "utils.h"



// создание поля компьютера

void Create_Field(values& battle_ship){

    for (int j = 4; j > 0; j--){

        int ship_count = 0;

        if (j == 4) ship_count = battle_ship.set_count_4;
        else if (j == 3) ship_count = battle_ship.set_count_3;
        else if (j == 2) ship_count = battle_ship.set_count_2;
        else if (j == 1) ship_count = battle_ship.set_count_1;

        for (int i = 0; i < ship_count; i++) {

            bool flag_for_add = false;

            while (!flag_for_add) {

                int x = Random_Number(0, battle_ship.set_width_int - 1);
                int y = Random_Number(0, battle_ship.set_height_int - 1);
                char orient = Random_Char();

                ship temp_ship(x, y, orient, j);
                temp_ship.scattering(); 

                bool temp_flag_for_add = true;

                for (uint64_t q = 0; q < temp_ship.coordin.size(); q++) {

                    const auto& coord = temp_ship.coordin[q];
                    
                    if (coord.x < 0 || coord.x >= battle_ship.set_width_int ||
                        coord.y < 0 || coord.y >= battle_ship.set_height_int) {

                        temp_flag_for_add = false;
                        
                        break;
                    }

                    for (uint64_t w = 0; w < battle_ship.armada.size(); w++) {
                        for (uint64_t e = 0; e < battle_ship.armada[w].coordin.size(); e++) {
                            
                            const auto& other_coord = battle_ship.armada[w].coordin[e];

                            if ((coord.x == other_coord.x && coord.y == other_coord.y) ||
                                (abs(coord.x - other_coord.x) <= 1 && abs(coord.y - other_coord.y) <= 1)) {
                                
                                temp_flag_for_add = false;
                                break;
                            }
                        }

                        if (!temp_flag_for_add) break;
                    }

                    if (!temp_flag_for_add) break;
                }

                if (temp_flag_for_add) {

                    flag_for_add = true;

                    battle_ship.armada.push_back(temp_ship);
                }
            }
        }
    }
}



// реализация выстрелов компьютера

void Shot_Computer(values& battle_ship){

    uint64_t x;
    uint64_t y;

    if (battle_ship.set_strategy == "custom"){

        bool flag_for_repeat = false;

        while (!flag_for_repeat){

            x = Random_Number(0, battle_ship.set_width_int - 1);
            y = Random_Number(0, battle_ship.set_height_int - 1);

            bool temp_flag_for_repeat = true;

            for (int i = 0; i < battle_ship.shotting_computer.size(); i++){

                if (x == battle_ship.shotting_computer[i].x && y == battle_ship.shotting_computer[i].y){

                    temp_flag_for_repeat = false;
                    break;
                }
            }

            if (temp_flag_for_repeat){

                flag_for_repeat = true;
                battle_ship.shotting_computer.push_back(coordinations(x, y));
            }
        }
    }

    else if (battle_ship.set_strategy == "ordered"){

        bool flag_for_repeat = false;

        while (!flag_for_repeat){

            if (battle_ship.lab_shot_x != battle_ship.set_width_int){

                x = battle_ship.lab_shot_x;
                battle_ship.lab_shot_x++;

                y = battle_ship.lab_shot_y;
            }

            else {

                x = 0;
                battle_ship.lab_shot_x = 1;

                battle_ship.lab_shot_y++;
                y = battle_ship.lab_shot_y;
            }

            bool temp_flag_for_repeat = true;

            for (int i = 0; i < battle_ship.shotting_computer.size(); i++){

                if (x == battle_ship.shotting_computer[i].x && y == battle_ship.shotting_computer[i].y){

                    temp_flag_for_repeat = false;
                    break;
                }
            }

            if (temp_flag_for_repeat){

                flag_for_repeat = true;
                battle_ship.shotting_computer.push_back(coordinations(x, y));
            }
        }
    }

    std::cout << battle_ship.shotting_computer.back().x << ' ' << battle_ship.shotting_computer.back().y << std::endl;
}



// реализация выстрелов пользователя

void Shot_User(values& battle_ship, int x, int y){

    bool flag_for_shots_user = false;
    int life_for_ship;

    for (int i = 0; i < battle_ship.armada.size(); i++){

        for (int w = 0; w < battle_ship.armada[i].coordin.size(); w++){

            if (x == battle_ship.armada[i].coordin[w].x && y == battle_ship.armada[i].coordin[w].y){
                
                flag_for_shots_user = true;
                life_for_ship = battle_ship.armada[i].life - 1;

                battle_ship.armada[i].life--;

                break;
            }
        }

        if (flag_for_shots_user)
            break;
    }

    if (!flag_for_shots_user)
        std::cout << "miss" << std::endl;

    else{

        if (life_for_ship != 0)
            std::cout << "hit" << std::endl;
        
        else{

            std::cout << "kill" << std::endl;

            battle_ship.count_user_kill_ship++;
        }
    }
}