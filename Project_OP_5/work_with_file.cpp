#include "config.h"
#include "utils.h"



// реализация dump

void Dump(values& battle_ship, std::string dump_path){

    std::ofstream dump_file(dump_path);

    dump_file << battle_ship.set_width_int << ' ' << battle_ship.set_height_int << std::endl;

    for (int i = 0; i < battle_ship.armada.size(); i++){

        dump_file << battle_ship.armada[i].length << ' ' << battle_ship.armada[i].orient << ' ' <<\
        battle_ship.armada[i].x << ' ' << battle_ship.armada[i].y << std::endl;
    }

    dump_file.close();
}



// реализация load

void Load(values& battle_ship, std::string load_path){

    std::ifstream load_file(load_path);

    uint64_t width;
    uint64_t height;

    load_file >> width >> height;

    battle_ship.set_width_int = width;
    battle_ship.set_height_int = height;

    int length;
    char orient;
    uint64_t x, y;

    while (load_file >> length >> orient >> x >> y){

        ship temp_ship(x, y, orient, length);
        temp_ship.scattering(); 

        battle_ship.armada.push_back(temp_ship);
    }

    for (int i = 0; i < battle_ship.armada.size(); i++){

        if (battle_ship.armada[i].length == 1)
            battle_ship.set_count_1++;

        else if (battle_ship.armada[i].length == 2)
            battle_ship.set_count_2++;

        else if (battle_ship.armada[i].length == 3)
            battle_ship.set_count_3++;

        else
            battle_ship.set_count_4++;
    }
}