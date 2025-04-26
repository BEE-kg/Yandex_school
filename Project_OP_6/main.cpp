#include "struct.h"
#include "utils.h"



int main(){

    SetConsoleOutputCP(CP_UTF8);

    Ticket current_ticket;
    Parametrs values;

    std::cout << "Enter five parameters: the date of departure in ISO 8601 format; the point of departure; destination; if you need a specific transport - 'true', if not - 'false'; whether you need a transfer - 'true', if not - 'false'. If you specified 'true' to the question about transport, then enter which one exactly after sending the first parameters, but only one." << std::endl;
    
    std::string arguments;
    std::getline(std::cin, arguments);

    if (!Parser_For_Arguments(arguments, current_ticket, values))
        return 1;

    if (current_ticket.flag_for_transport)
        Special_Transport(current_ticket);

    if (Internet_Connection())
        GET_Request_Internet(current_ticket, values);

    else{

        std::cout << std::endl << "If there is no Internet, the information will be taken from the media." << std::endl;

        GET_Request_Nake(current_ticket, values);
    }

    return 0;
}