#include "config.h"
#include "utils.h"



int main() {

    values battle_ship;

    while(true) {

        std::string cmd;
        std::getline(std::cin, cmd);

        if (!Parser_For_Commands(cmd, battle_ship))
            break;

        if (battle_ship.load_path_value){

            battle_ship.load_path_value = false;
            battle_ship.flag_for_load_of_all_time = true;

            Load(battle_ship, battle_ship.load_path);
        }

        if (battle_ship.start_value && battle_ship.set_width_int != 0 && battle_ship.set_height_int != 0\
        && battle_ship.set_count_1 + battle_ship.set_count_2 + battle_ship.set_count_3 + battle_ship.set_count_4 > 0){

            if (battle_ship.start_value_one){

                std::cout << "ok" << std::endl;

                battle_ship.start_value_one = false;
            }

            if (battle_ship.flag_for_create_field && !battle_ship.flag_for_load_of_all_time){

                battle_ship.flag_for_create_field = false;
                
                Create_Field(battle_ship);
            }

            if (battle_ship.shot_computer_value){

                battle_ship.shot_computer_value = false;

                Shot_Computer(battle_ship);
            }

            if (battle_ship.shot_user_value){

                battle_ship.shot_user_value = false;

                Shot_User(battle_ship, battle_ship.shotting_user_x, battle_ship.shotting_user_y);
            }

            if (battle_ship.count_computer_kill_ship == battle_ship.set_count_1 + battle_ship.set_count_2 +\
            battle_ship.set_count_3 + battle_ship.set_count_4)
                battle_ship.win_computer_value = true;

            if (battle_ship.count_user_kill_ship == battle_ship.set_count_1 + battle_ship.set_count_2 +\
            battle_ship.set_count_3 + battle_ship.set_count_4)
                battle_ship.win_user_value = true;

            if (battle_ship.dump_path_value){

                battle_ship.dump_path_value = false;

                Dump(battle_ship, battle_ship.dump_path);
            }
        }
    }

    return 0;
}