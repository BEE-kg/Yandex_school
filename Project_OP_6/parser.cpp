#include "struct.h"
#include "utils.h"



bool Parser_For_Arguments(std::string arguments, Ticket& current_ticket, Parametrs& values){

    std::vector<std::string> string = Split_String(arguments);

    if (size(string) == 5){

        for (int index = 0; index < 5; index++){

            switch(index){

                case 0: current_ticket.data = string[index];
                case 1: current_ticket.city_a = string[index];
                case 2: current_ticket.city_b = string[index];
                case 3: 
                    if (string[index] == "true")
                        current_ticket.flag_for_transport = true;
                case 4: 
                    if (string[index] == "true")
                        current_ticket.transfer = true;
                    else
                        current_ticket.transfer = false;
            }
        }

        return true;
    }

    else{

        std::cout << "Error in cmd" << std::endl;

        return false;
    }
}



void Special_Transport(Ticket& current_ticket){

    std::string arguments;
    std::getline(std::cin, arguments);

    std::vector<std::string> string = Split_String(arguments);

    for (int index = 0; index < size(string); index++){

        if (string[index] == "plane")
            current_ticket.plane = true;

        else if (string[index] == "train")
            current_ticket.train = true;

        else if (string[index] == "suburban")
            current_ticket.suburban = true;

        else if (string[index] == "bus")
            current_ticket.bus = true; 
    }
}