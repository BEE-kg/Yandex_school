#include "config.h"
#include "utils.h"



bool Parser_For_Commands(std::string cmd, values& battle_ship){

    std::vector<std::string> string = Split_String(cmd);

    for (int i = 0; i < string.size(); i++){

        if (string[i] == "exit"){

            std::cout << "ok" << std::endl;
            return false;
        }

        else if (string[i] == "ping")
            std::cout << "pong" << std::endl;

        else if (string[i] == "create" && i + 1 < string.size() && (string[i + 1] == "slave" || string[i + 1] == "master")){

            std::cout << "ok" << std::endl;

            if (string[i + 1] == "master"){

                battle_ship.set_width_int = Random_Number(10, 10);
                battle_ship.set_height_int = Random_Number(10, 10);

                battle_ship.set_count_1 = Random_Number(0, 6);
                battle_ship.set_count_2 = Random_Number(2, 4);
                battle_ship.set_count_3 = Random_Number(2, 3);
                battle_ship.set_count_4 = Random_Number(1, 2);
            }
        }

        else if (string[i] == "start"){

            battle_ship.start_value = true;

            battle_ship.start_value_one = true;
        }

        else if (string[i] == "stop"){

            std::cout << "ok" << std::endl;

            battle_ship.start_value = false;
        }

        else if (string[i] == "set" && string[i + 1] == "width" && i + 2 < string.size()){

            if (!Is_Digit(string[i + 2]))
                std::cout << "failed" << std::endl;

            else{

                battle_ship.set_width_int = std::stoi(string[i + 2]);

                std::cout << "ok" << std::endl;
            }
        }

        else if (string[i] == "get" && string[i + 1] == "width")
            std::cout << battle_ship.set_width_int << std::endl;

        else if (string[i] == "set" && string[i + 1] == "height" && i + 2 < string.size()){

            if (!Is_Digit(string[i + 2]))
                std::cout << "failed" << std::endl;

            else{

                battle_ship.set_height_int = std::stoi(string[i + 2]);

                std::cout << "ok" << std::endl;
            }
        }

        else if (string[i] == "get" && string[i + 1] == "height")
            std::cout << battle_ship.set_height_int << std::endl;

        else if (string[i] == "set" && string[i + 1] == "count" && i + 3 < string.size()){

            if (!Is_Digit(string[i + 2]) || !Is_Digit(string[i + 3]))
                std::cout << "failed" << std::endl;

            else {

                std::cout << "ok" << std::endl;

                if (string[i + 2] == "1")
                    battle_ship.set_count_1 = std::stoi(string[i + 3]);

                else if (string[i + 2] == "2")
                    battle_ship.set_count_2 = std::stoi(string[i + 3]);

                else if (string[i + 2] == "3")
                    battle_ship.set_count_3 = std::stoi(string[i + 3]);

                else if (string[i + 2] == "4")
                    battle_ship.set_count_4 = std::stoi(string[i + 3]);
            }
        }

        else if (string[i] == "get" && string[i + 1] == "count" && i + 2 < string.size()){

            if (string[i + 2] == "1")
                std::cout << battle_ship.set_count_1 << std::endl;

            else if (string[i + 2] == "2")
                std::cout << battle_ship.set_count_2 << std::endl;

            else if (string[i + 2] == "3")
                std::cout << battle_ship.set_count_3 << std::endl;

            else if (string[i + 2] == "4")
                std::cout << battle_ship.set_count_4 << std::endl;
        }

        else if (string[i] == "set" && string[i + 1] == "strategy"\
        && (string[i + 2] == "ordered" || string[i + 2] == "custom") && i + 2 < string.size()){

            std::cout << "ok" << std::endl;

            battle_ship.set_strategy = string[i + 2];
        }

        else if (string[i] == "shot" && i + 2 < string.size()){
            
            if (battle_ship.who_shot == 0 || battle_ship.who_shot == 1000){
            
                battle_ship.shot_user_value = true;

                battle_ship.shotting_user_x = std::stoi(string[i + 1]);
                battle_ship.shotting_user_y = std::stoi(string[i + 2]);

                battle_ship.who_shot = 1;
            }

            else
                std::cout << "You don't shot second" << std::endl;
        }

        else if (string[i] == "shot"){

            if (battle_ship.shot_set_result){

                std::cout << "Please, set result for shot" << std::endl;

                continue;
            }

            if (battle_ship.who_shot == 1 || battle_ship.who_shot == 1000){

                battle_ship.shot_computer_value = true;
                battle_ship.shot_set_result = true;
                battle_ship.who_shot = 0;
            }
            
            else
                std::cout << "You don't shot second" << std::endl;
        }

        else if (string[i] == "set" && string[i + 1] == "result" && i + 2 < string.size()){

            std::cout << "ok" << std::endl;

            battle_ship.set_result = string[i + 2];

            if (battle_ship.shot_set_result)
                battle_ship.shot_set_result = false;

            if (battle_ship.set_result == "kill")
                battle_ship.count_computer_kill_ship++;
        }

        else if (string[i] == "finished"){

            if (battle_ship.start_value)
                std::cout << "yes" << std::endl;

            else
                std::cout << "no" << std::endl;
        }

        else if (string[i] == "win"){

            if (battle_ship.win_user_value && !battle_ship.win_computer_value)
                std::cout << "yes" << std::endl;

            else if (!battle_ship.win_user_value && battle_ship.win_computer_value)
                std::cout << "no" << std::endl;
        }

        else if (string[i] == "lose"){

            if (battle_ship.win_computer_value && !battle_ship.win_user_value)
                std::cout << "yes" << std::endl;

            else if (battle_ship.win_user_value && !battle_ship.win_computer_value)
                std::cout << "no" << std::endl;
        }

        else if (string[i] == "dump" && i + 1 < string.size()){

            std::cout << "ok" << std::endl;

            battle_ship.dump_path = string[i + 1];
            battle_ship.dump_path_value = true;
        }

        else if (string[i] == "load" && i + 1 < string.size()){

            std::cout << "ok" << std::endl;

            battle_ship.load_path = string[i + 1];
            battle_ship.load_path_value = true;
        }
    }

    return true;
}