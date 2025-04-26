#include "struct.h"
#include "utils.h"



void GET_Request_Internet(Ticket& current_ticket, Parametrs& values){

    std::string url = values.start_url + "search" + values.user_key + "&lang=ru_RU&format=json"\
    + "&date=" + current_ticket.data + "&transfers=true";

    if (current_ticket.city_a == "a")
        url += ("&from=" + values.code_a + "&to=" + values.code_b);
    
    else
        url += ("&from=" + values.code_b + "&to=" + values.code_a);

    if (current_ticket.flag_for_transport){

        if (current_ticket.bus) 
            url += "&transport_types=bus";

        if (current_ticket.plane)
            url += "&transport_types=plane";

        if (current_ticket.suburban)
            url += "&transport_types=suburban";

        if (current_ticket.train)
            url += "&transport_types=train";
    }

    cpr::Response response = cpr::Get(cpr::Url{url});

    if (response.status_code == 200){

        nlohmann::json json = nlohmann::json::parse(response.text);

        std::fstream file_one("C:/Study/OP/Project_OP_6/labwork6-BEE-kg/caching_one.txt", std::ios::in | std::ios::out | std::ios::app);
        std::fstream file_many("C:/Study/OP/Project_OP_6/labwork6-BEE-kg/caching_many.txt", std::ios::in | std::ios::out | std::ios::app);

        int total = json["pagination"]["total"];
        int one_tran_count = 0;
        int many_tran_count = 0;

        for (int index = 0; index < total; index++){

            if (!json["segments"][index].contains("transport_types") && !current_ticket.transfer){

                one_tran_count++;

                if (json["segments"][index]["thread"]["transport_type"] == "train")
                    std::cout << std::endl << "Поезд; номер: " << json["segments"][index]["thread"]["number"] << std::endl << std::endl;
                
                else if (json["segments"][index]["thread"]["transport_type"] == "plane")
                    std::cout << std::endl << "Самолёт; номер, модель: " << json["segments"][index]["thread"]["number"] << ' ' << json["segments"][index]["thread"]["vehicle"] << std::endl << std::endl;

                else if (json["segments"][index]["thread"]["transport_type"] == "suburban")
                    std::cout << std::endl << "Электричка; номер: " << json["segments"][index]["thread"]["number"] << std::endl << std::endl;

                else if (json["segments"][index]["thread"]["transport_type"] == "bus")
                    std::cout << std::endl << "Автобус" << std::endl << std::endl;

                std::cout << "Маршрут транспорта: " << json["segments"][index]["thread"]["title"] << std::endl;
                std::cout << "Начальный и конечный пункты нашего маршрута: " << json["segments"][index]["from"]["title"] << " - " << json["segments"][index]["to"]["title"] << std::endl << std::endl;

                std::cout << "Общее время выезда: " << json["segments"][index]["departure"] << std::endl;
                std::cout << "Общее время прибытия: " << json["segments"][index]["arrival"] << std::endl;
                std::cout << "Время в пути: " << ceil((static_cast<int>(json["segments"][index]["duration"]))/60/60) << "ч." << std::endl << std::endl;

                if (json["segments"][index]["thread"]["transport_type"] == "train"){

                    std::cout << "Контакты перевозчика: " << std::endl;
                    std::cout << json["segments"][index]["thread"]["carrier"]["contacts"] << std::endl;
                    std::cout << json["segments"][index]["thread"]["carrier"]["email"] << std::endl;
                    std::cout << json["segments"][index]["thread"]["carrier"]["url"] << std::endl << "\n\n\n\n\n";

                    std::string line;
                    bool flag = true;
        
                    while (std::getline(file_one, line)) {

                        std::string my_parametrs = '"' + json["segments"][index]["thread"]["number"].get<std::string>()+ '"' + ' ' + '"' +\
                        json["segments"][index]["thread"]["title"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["from"]["title"].get<std::string>() + '"' +\
                        ' ' + '"' + json["segments"][index]["to"]["title"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["departure"].get<std::string>() + '"' +\
                        ' ' + '"' + json["segments"][index]["arrival"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["thread"]["carrier"]["contacts"].get<std::string>() + '"' + \
                        ' ' + '"' + json["segments"][index]["thread"]["carrier"]["email"].get<std::string>() + '"'+ ' ' + '"' + json["segments"][index]["thread"]["carrier"]["url"].get<std::string>() + '"';

                        my_parametrs = "train " + my_parametrs;

                        if (line == my_parametrs) {

                            flag = false;
                            break;
                        }
                    }

                    if (flag) {

                        file_one.clear();
                        file_one.seekp(0, std::ios::end);

                        file_one << "train " << json["segments"][index]["thread"]["number"] << ' ' << json["segments"][index]["thread"]["title"] << ' '\
                        << json["segments"][index]["from"]["title"] << ' ' << json["segments"][index]["to"]["title"] << ' ' << json["segments"][index]["departure"] << ' '\
                        << json["segments"][index]["arrival"] << ' ' << json["segments"][index]["thread"]["carrier"]["contacts"] << ' '\
                        << json["segments"][index]["thread"]["carrier"]["email"] << ' ' << json["segments"][index]["thread"]["carrier"]["url"] << std::endl;
                    }

                    file_one.clear();
                    file_one.seekg(0, std::ios::beg);  
                }

                else if (json["segments"][index]["thread"]["transport_type"] == "plane"){

                    std::cout << "Контакты перевозчика: " << std::endl;
                    std::cout << json["segments"][index]["thread"]["carrier"]["contacts"] << std::endl;
                    std::cout << json["segments"][index]["thread"]["carrier"]["url"] << std::endl << "\n\n\n\n\n";

                    std::string line;
                    bool flag = true;

                    while (std::getline(file_one, line)) {

                        std::string my_parametrs = '"' + json["segments"][index]["thread"]["number"].get<std::string>()+ '"' + ' ' + '"' + json["segments"][index]["thread"]["vehicle"].get<std::string>() + '"' + ' ' + '"' +\
                        json["segments"][index]["thread"]["title"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["from"]["title"].get<std::string>() + '"' +\
                        ' ' + '"' + json["segments"][index]["to"]["title"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["departure"].get<std::string>() + '"' +\
                        ' ' + '"' + json["segments"][index]["arrival"].get<std::string>() + '"' +  ' ' + '"' + json["segments"][index]["thread"]["carrier"]["url"].get<std::string>() + '"';

                        my_parametrs = "plane " + my_parametrs;

                        if (line == my_parametrs) {

                            flag = false;
                            break;
                        }
                    }

                    if (flag) {

                        file_one.clear();
                        file_one.seekp(0, std::ios::end);

                        file_one << "plane " << json["segments"][index]["thread"]["number"] << ' ' << json["segments"][index]["thread"]["vehicle"] << ' ' << json["segments"][index]["thread"]["title"] << ' '\
                        << json["segments"][index]["from"]["title"] << ' ' << json["segments"][index]["to"]["title"] << ' ' << json["segments"][index]["departure"] << ' '\
                        << json["segments"][index]["arrival"] << ' ' << json["segments"][index]["thread"]["carrier"]["url"] << std::endl;
                    }

                    file_one.clear();
                    file_one.seekg(0, std::ios::beg);
                }

                else if (json["segments"][index]["thread"]["transport_type"] == "suburban"){

                    std::cout << "Остановки: " << json["segments"][index]["stops"] << std::endl;
                    std::cout << "Цена: " << json["segments"][index]["tickets_info"]["places"][0]["price"]["whole"] << " RUB" << std::endl << std::endl;
                    std::cout << "Контакты перевозчика: " << std::endl;
                    std::cout << json["segments"][index]["thread"]["carrier"]["contacts"] << std::endl;
                    std::cout << json["segments"][index]["thread"]["carrier"]["email"] << std::endl;
                    std::cout << json["segments"][index]["thread"]["carrier"]["url"] << std::endl << "\n\n\n\n\n";

                    std::string line;
                    bool flag = true;
        
                    while (std::getline(file_one, line)) {

                        std::string my_parametrs = '"' + json["segments"][index]["thread"]["number"].get<std::string>()+ '"' + ' ' + '"' +\
                        json["segments"][index]["thread"]["title"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["from"]["title"].get<std::string>() + '"' +\
                        ' ' + '"' + json["segments"][index]["to"]["title"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["departure"].get<std::string>() + '"' +\
                        ' ' + '"' + json["segments"][index]["arrival"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["stops"].get<std::string>() + '"' +\
                        ' ' + '"' + std::to_string(json["segments"][index]["tickets_info"]["places"][0]["price"]["whole"].get<int>()) + '"' +\
                        ' ' + '"' + json["segments"][index]["thread"]["carrier"]["email"].get<std::string>() + '"'+ ' ' + '"' + json["segments"][index]["thread"]["carrier"]["url"].get<std::string>() + '"';

                        my_parametrs = "suburban " + my_parametrs;

                        if (line == my_parametrs) {

                            flag = false;
                            break;
                        }
                    }

                    if (flag) {

                        file_one.clear();
                        file_one.seekp(0, std::ios::end);

                        file_one << "suburban " << json["segments"][index]["thread"]["number"] << ' ' << json["segments"][index]["thread"]["title"] << ' '\
                        << json["segments"][index]["from"]["title"] << ' ' << json["segments"][index]["to"]["title"] << ' ' << json["segments"][index]["departure"] << ' '\
                        << json["segments"][index]["arrival"] << ' '  << json["segments"][index]["stops"] << ' ' << '"' << json["segments"][index]["tickets_info"]["places"][0]["price"]["whole"] << '"' << ' '\
                        << json["segments"][index]["thread"]["carrier"]["email"] << ' ' << json["segments"][index]["thread"]["carrier"]["url"] << std::endl;
                    }

                    file_one.clear();
                    file_one.seekg(0, std::ios::beg);
                }

                else if (json["segments"][index]["thread"]["transport_type"] == "bus"){

                    if (!json["segments"][index]["tickets_info"]["places"][0]["price"]["whole"].is_null())
                        std::cout << "Цена: " << json["segments"][index]["tickets_info"]["places"][0]["price"]["whole"] << " RUB" << std::endl << std::endl;

                    std::cout << "Контакты перевозчика: " << std::endl;
                    std::cout << json["segments"][index]["thread"]["carrier"]["title"] << std::endl << "\n\n\n\n\n";

                    std::string line;
                    bool flag = true;
        
                    while (std::getline(file_one, line)) {

                        std::string my_parametrs = '"' + json["segments"][index]["thread"]["title"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["from"]["title"].get<std::string>() + '"' +\
                        ' ' + '"' + json["segments"][index]["to"]["title"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["departure"].get<std::string>() + '"' +\
                        ' ' + '"' + json["segments"][index]["arrival"].get<std::string>() + '"' + ' ' + '"' + std::to_string(json["segments"][index]["tickets_info"]["places"][0]["price"]["whole"].get<int>()) + '"';

                        my_parametrs = "bus " + my_parametrs;

                        if (line == my_parametrs) {

                            flag = false;
                            break;
                        }
                    }

                    if (flag) {

                        file_one.clear();
                        file_one.seekp(0, std::ios::end);

                        file_one << "bus " << json["segments"][index]["thread"]["title"] << ' '\
                        << json["segments"][index]["from"]["title"] << ' ' << json["segments"][index]["to"]["title"] << ' ' << json["segments"][index]["departure"] << ' '\
                        << json["segments"][index]["arrival"] << ' ' << '"' << json["segments"][index]["tickets_info"]["places"][0]["price"]["whole"] << '"' << std::endl;
                    }

                    file_one.clear();
                    file_one.seekg(0, std::ios::beg);
                }
            }

            else if (json["segments"][index].contains("transport_types") && current_ticket.transfer){

                many_tran_count++;

                std::string my_parametrs = '"' + json["segments"][index]["departure"].get<std::string>() + '"'\
                + ' ' + '"' + json["segments"][index]["arrival"].get<std::string>() + '"';

                std::cout << std::endl << "Общее время выезда: " << json["segments"][index]["departure"] << std::endl;
                std::cout << "Общее время прибытия: " << json["segments"][index]["arrival"] << std::endl << std::endl;

                int duration = 0;
                int route = 0;

                for (int element = 0; element < json["segments"][index]["details"].size(); element++){

                    duration += static_cast<int>(json["segments"][index]["details"][element]["duration"]);

                    if (element%2 != 1){

                        route++;

                        std::cout << "Рейс: " << route << std::endl;

                        if (json["segments"][index]["details"][element]["thread"]["transport_type"] == "train"){

                            std::cout << "Поезд; номер: " << json["segments"][index]["details"][element]["thread"]["number"] << std::endl << std::endl;

                            my_parametrs = my_parametrs + " train " + '"' + json["segments"][index]["details"][element]["thread"]["number"].get<std::string>() + '"';
                        }
                        else if (json["segments"][index]["details"][element]["thread"]["transport_type"] == "plane"){

                            std::cout << "Самолёт; номер, модель: " << json["segments"][index]["details"][element]["thread"]["number"] << ' ' << json["segments"][index]["details"][element]["thread"]["vehicle"] << std::endl << std::endl;

                            my_parametrs = my_parametrs + " plane " + '"' + json["segments"][index]["details"][element]["thread"]["number"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["details"][element]["thread"]["vehicle"].get<std::string>() + '"';
                        }
                        else if (json["segments"][index]["details"][element]["thread"]["transport_type"] == "suburban"){

                            std::cout << "Электричка; номер: " << json["segments"][index]["details"][element]["thread"]["number"] << std::endl;
                            std::cout << "Остановки: " << json["segments"][index]["details"][element]["stops"] << std::endl << std::endl;

                            my_parametrs = my_parametrs + " suburban " + '"' + json["segments"][index]["details"][element]["thread"]["number"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["details"][element]["stops"].get<std::string>() + '"';

                        }

                        else if (json["segments"][index]["details"][element]["thread"]["transport_type"] == "bus"){

                            std::cout << "Автобус" << std::endl << std::endl;

                            my_parametrs = my_parametrs + " bus ";
                        }

                        std::cout << "Текущий полный маршрут: " << json["segments"][index]["details"][element]["thread"]["title"] << std::endl << std::endl;
                        std::cout << "Пункты пересадок: " << json["segments"][index]["details"][element]["from"]["title"] << " - " << json["segments"][index]["details"][element]["to"]["title"] << std::endl;
                        std::cout << "Текущее время выезда: " << json["segments"][index]["details"][element]["departure"] << std::endl;
                        std::cout << "Текущее время приезда: " << json["segments"][index]["details"][element]["arrival"] << std::endl << std::endl << std::endl;

                        my_parametrs = my_parametrs + ' ' + '"' + json["segments"][index]["details"][element]["thread"]["title"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["details"][element]["from"]["title"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["details"][element]["to"]["title"].get<std::string>() + '"'\
                        + ' ' + '"' + json["segments"][index]["details"][element]["departure"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["details"][element]["arrival"].get<std::string>() + '"';
                    }

                    else{

                        std::cout << "Пересадка в пункте: " << json["segments"][index]["details"][element]["transfer_point"]["title"] << std::endl;
                        std::cout << "Станции: " << json["segments"][index]["details"][element]["transfer_from"]["title"] << " - " << json["segments"][index]["details"][element]["transfer_to"]["title"] << std::endl << std::endl << std::endl;

                        my_parametrs = my_parametrs + ' ' + '"' + json["segments"][index]["details"][element]["transfer_point"]["title"].get<std::string>() +\
                         '"' + ' ' + '"' + json["segments"][index]["details"][element]["transfer_from"]["title"].get<std::string>() + '"' + ' ' + '"' + json["segments"][index]["details"][element]["transfer_to"]["title"].get<std::string>() + '"';
                    }
                }

                std::cout << "Общее время в пути: " << ceil(duration/60/60)  << "ч." << std::endl << "\n\n\n\n\n";

                std::string line;
                bool flag = true;

                file_one.clear();        
                file_one.seekg(0, std::ios::beg);

                while (std::getline(file_many, line)) {

                    if (line == my_parametrs) {

                        flag = false;
                        break;
                    }
                }

                if (flag) {

                    file_many.clear();
                    file_many.seekp(0, std::ios::end);

                    file_many << my_parametrs << std::endl;
                }
            }
        }
        
        if (!current_ticket.transfer){

            if (one_tran_count == 0)
                std::cout << std::endl << "Нет маршрутов по указанным пунктам без пересадок" << std::endl;

            else
                std::cout << std::endl << "Всего маршрутов по указанным пунктам без пересадок: " << one_tran_count << std::endl;
        }

        else{

            if (many_tran_count == 0)
                std::cout << std::endl << "Нет маршрутов по указанным пунктам с пересадками" << std::endl;

            else
                std::cout << "Всего маршрутов по указанным пунктам с пересадами: " << many_tran_count << std::endl;
        }

        std::cout << "\n\n\n\n\n";

        file_one.close();
        file_many.close();

        // std::thread delete_thread_1(Delete_File, "C:/Study/OP/Project_OP_6/labwork6-BEE-kg/caching_one.txt", 5);
        // std::thread delete_thread_2(Delete_File, "C:/Study/OP/Project_OP_6/labwork6-BEE-kg/caching_many.txt", 5);

        // delete_thread_1.join();
        // delete_thread_2.join();
        
        DeleteFileWithCmd("C:\\Study\\OP\\Project_OP_6\\labwork6-BEE-kg\\caching_one.txt", 86400);
        DeleteFileWithCmd("C:\\Study\\OP\\Project_OP_6\\labwork6-BEE-kg\\caching_many.txt", 86400);
    }

    else
        std::cout << "Error. Statuc code: " << response.status_code << std::endl;
}



void GET_Request_Nake(Ticket& current_ticket, Parametrs& values){

    if (!current_ticket.transfer){

        std::ifstream file_one("C:/Study/OP/Project_OP_6/labwork6-BEE-kg/caching_one.txt");

        if (!file_one.is_open()) {

            std::cerr << std::endl << "Error, file_one for cach is not open !!!" << std::endl;

            return;
        }

        std::string line;
        int total = 0;
        
        while (std::getline(file_one, line)) {
            
            std::vector<std::string> quation = Quotation_Mark(line);
            std::vector<std::string> split = Split_String(line);

            if (current_ticket.data == Date(quation[4]) && split[0] == "train" && (!current_ticket.flag_for_transport || current_ticket.train)){
                if (current_ticket.city_a == "a" && Near_Saratov(quation[3], values.saratov) ||\
                current_ticket.city_a == "b" && !Near_Saratov(quation[3], values.saratov)) {
                
                    std::cout << std::endl << "Поезд; номер: " << quation[0] << std::endl << std::endl;
                    std::cout << "Маршрут транспорта: " << quation[1] << std::endl;
                    std::cout << "Начальный и конечный пункты нашего маршрута: " << quation[2] << " - " << quation[3] << std::endl << std::endl;
                    std::cout << "Общее время выезда: " << quation[4] << std::endl;
                    std::cout << "Общее время прибытия: " << quation[5] << std::endl << std::endl;
                    std::cout << "Контакты перевозчика: " << std::endl;
                    std::cout << quation[6] << std::endl;
                    std::cout << quation[7] << std::endl;
                    std::cout << quation[8] << std::endl << "\n\n\n\n\n";

                    total++;
                }
            }
            
            else if (current_ticket.data == Date(quation[5]) && split[0] == "plane" && (!current_ticket.flag_for_transport || current_ticket.plane)){
                if (current_ticket.city_a == "a" && Near_Saratov(quation[4], values.saratov) ||\
                current_ticket.city_a == "b" && !Near_Saratov(quation[4], values.saratov)) {

                    std::cout << std::endl << "Самолёт; номер, модель: " << quation[0] << ' ' << quation[1] << std::endl << std::endl;
                    std::cout << "Маршрут транспорта: " << quation[2] << std::endl;
                    std::cout << "Начальный и конечный пункты нашего маршрута: " << quation[3] << " - " << quation[4] << std::endl << std::endl;
                    std::cout << "Общее время выезда: " << quation[5] << std::endl;
                    std::cout << "Общее время прибытия: " << quation[6] << std::endl << std::endl;
                    std::cout << "Контакты перевозчика: " << std::endl;
                    std::cout << quation[7] << std::endl << "\n\n\n\n\n";

                    total++;
                }
            }

            else if (current_ticket.data == Date(quation[4]) && split[0] == "suburban" && (!current_ticket.flag_for_transport || current_ticket.suburban)){
                if (current_ticket.city_a == "a" && Near_Saratov(quation[3], values.saratov) ||\
                current_ticket.city_a == "b" && !Near_Saratov(quation[3], values.saratov)) {

                    std::cout << std::endl << "Электричка; номер: " << quation[0] << std::endl << std::endl;
                    std::cout << "Маршрут транспорта: " << quation[1] << std::endl;
                    std::cout << "Начальный и конечный пункты нашего маршрута: " << quation[2] << " - " << quation[3] << std::endl << std::endl;
                    std::cout << "Общее время выезда: " << quation[4] << std::endl;
                    std::cout << "Общее время прибытия: " << quation[5] << std::endl << std::endl;
                    std::cout << "Остановки: " << quation[6] << std::endl;
                    std::cout << "Цена билета: " << quation[7] << " RUB" << std::endl << std::endl;
                    std::cout << "Контакты перевозчика: " << std::endl;
                    std::cout << quation[8] << std::endl;
                    std::cout << quation[9] << std::endl << "\n\n\n\n\n";

                    total++;
                }
            }
                    
            else if (current_ticket.data == Date(quation[3]) && split[0] == "bus" && (!current_ticket.flag_for_transport || current_ticket.bus)){
                if (current_ticket.city_a == "a" && Near_Saratov(quation[2], values.saratov) ||\
                current_ticket.city_a == "b" && !Near_Saratov(quation[2], values.saratov)) {

                    std::cout << std::endl << "Автобус" << std::endl << std::endl;
                    std::cout << "Маршрут транспорта: " << quation[0] << std::endl;
                    std::cout << "Начальный и конечный пункты нашего маршрута: " << quation[1] << " - " << quation[2] << std::endl << std::endl;
                    std::cout << "Общее время выезда: " << quation[3] << std::endl;
                    std::cout << "Общее время прибытия: " << quation[4] << std::endl << std::endl;

                    if (quation[5] != "null")
                        std::cout << "Цена билета: " << quation[5] << " RUB" << std::endl << std::endl;

                    total++;
                }
            }
        }

        if (total != 0)
            std::cout << "Всего маршрутов без пересадок, взятых из памяти: " << total << std::endl;

        else
            std::cout << std::endl << "Не существует маршрутов без пересадок, взятых из памяти." << std::endl;

        file_one.close();
    }

    else{

        std::ifstream file_many("C:/Study/OP/Project_OP_6/labwork6-BEE-kg/caching_many.txt");

        if (!file_many.is_open()) {

            std::cerr << std::endl << "Error, file_many for cach is not open !!!" << std::endl;

            return;
        }

        std::string line;
        int total = 0;
        
        while (std::getline(file_many, line)) {
            
            std::vector<std::string> quation = Quotation_Mark(line);
            std::vector<std::string> split = Split_String(line);

            if (current_ticket.data == Date(quation[0]) && split[2] == "train" && (!current_ticket.flag_for_transport || current_ticket.train)){
                if (current_ticket.city_a == "a" && Near_Saratov(quation[quation.size() - 3], values.saratov) ||\
                current_ticket.city_a == "b" && !Near_Saratov(quation[quation.size() - 3], values.saratov)) {

                    int route = 0;

                    std::cout << "\n\n\n\n\n";
                    
                    for (int i = 2; i < quation.size(); i += 9){

                        route++;

                        std::cout << "Рейс: " << route << std::endl << std::endl;

                        std::cout << "Номер поезда: " << quation[i] << std::endl;
                        std::cout << "Маршрут транспорта: " << quation[i+1] << std::endl;
                        std::cout << "Начальный и конечный пункты нашего маршрута: " << quation[i+2] << " - " << quation[i+3] << std::endl << std::endl;
                        std::cout << "Текущее время отъезда: " << quation[i+4] << std::endl;
                        std::cout << "Текущее время приезда: " << quation[i+5] << std::endl << std::endl;

                        if (i+6 != quation.size()){

                            std::cout << "Пересадка в городе - " << quation[i+6] << std::endl;
                            std::cout << "Станции пересадки: " << quation[i+7] << " - " << quation[i+8] << std::endl << std::endl;
                        }
                    }

                    total++;
                }
            }
            
            else if (current_ticket.data == Date(quation[0]) && split[2] == "plane" && (!current_ticket.flag_for_transport || current_ticket.plane)){
                if (current_ticket.city_a == "a" && Near_Saratov(quation[quation.size() - 3], values.saratov) ||\
                current_ticket.city_a == "b" && !Near_Saratov(quation[quation.size() - 3], values.saratov)) {

                    int route = 0;

                    std::cout << "\n\n\n\n\n";
                    
                    for (int i = 2; i < quation.size(); i += 10){

                        route++;

                        std::cout << "Рейс: " << route << std::endl << std::endl;

                        std::cout << "Номер самолёта, модель: " << quation[i] << ' ' <<  quation[i + 1] << std::endl;
                        std::cout << "Маршрут транспорта: " << quation[i+2] << std::endl;
                        std::cout << "Начальный и конечный пункты нашего маршрута: " << quation[i+3] << " - " << quation[i+4] << std::endl << std::endl;
                        std::cout << "Текущее время отъезда: " << quation[i+5] << std::endl;
                        std::cout << "Текущее время приезда: " << quation[i+6] << std::endl << std::endl;

                        if (i+7 != quation.size()){

                            std::cout << "Пересадка в городе - " << quation[i+7] << std::endl;
                            std::cout << "Станции пересадки: " << quation[i+8] << " - " << quation[i+9] << std::endl << std::endl;
                        }
                    }

                    total++;
                }
            }

            else if (current_ticket.data == Date(quation[0]) && split[2] == "suburban" && (!current_ticket.flag_for_transport || current_ticket.suburban)){
                if (current_ticket.city_a == "a" && Near_Saratov(quation[quation.size() - 3], values.saratov) ||\
                current_ticket.city_a == "b" && !Near_Saratov(quation[quation.size() - 3], values.saratov)) {

                    int route = 0;

                    std::cout << "\n\n\n\n\n";
                    
                    for (int i = 2; i < quation.size(); i += 10){

                        route++;

                        std::cout << "Рейс: " << route << std::endl << std::endl;

                        std::cout << "Номер электрички: " << quation[i] << std::endl;
                        std::cout << "Остановки: " << quation[i+1] << std::endl;
                        std::cout << "Маршрут транспорта: " << quation[i+2] << std::endl;
                        std::cout << "Начальный и конечный пункты нашего маршрута: " << quation[i+3] << " - " << quation[i+4] << std::endl << std::endl;
                        std::cout << "Текущее время отъезда: " << quation[i+5] << std::endl;
                        std::cout << "Текущее время приезда: " << quation[i+6] << std::endl << std::endl;

                        if (i+7 != quation.size()){

                            std::cout << "Пересадка в городе - " << quation[i+7] << std::endl;
                            std::cout << "Станции пересадки: " << quation[i+8] << " - " << quation[i+9] << std::endl << std::endl;
                        }
                    }

                    total++;
                }
            }
                    
            else if (current_ticket.data == Date(quation[0]) && split[2] == "bus" && (!current_ticket.flag_for_transport || current_ticket.bus)){
                if (current_ticket.city_a == "a" && Near_Saratov(quation[quation.size() - 3], values.saratov) ||\
                current_ticket.city_a == "b" && !Near_Saratov(quation[quation.size() - 3], values.saratov)) {

                    int route = 0;

                    std::cout << "\n\n\n\n\n";
                    
                    for (int i = 2; i < quation.size(); i += 8){

                        route++;

                        std::cout << "Рейс: " << route << std::endl << std::endl;

                        std::cout << "Автобус" << std::endl;
                        std::cout << "Маршрут транспорта: " << quation[i] << std::endl;
                        std::cout << "Начальный и конечный пункты нашего маршрута: " << quation[i+1] << " - " << quation[i+2] << std::endl << std::endl;
                        std::cout << "Текущее время отъезда: " << quation[i+3] << std::endl;
                        std::cout << "Текущее время приезда: " << quation[i+4] << std::endl << std::endl;

                        if (i+5 != quation.size()){

                            std::cout << "Пересадка в городе - " << quation[i+5] << std::endl;
                            std::cout << "Станции пересадки: " << quation[i+6] << " - " << quation[i+7] << std::endl << std::endl;
                        }
                    }

                    total++;
                }
            }
        }

        if (total != 0)
            std::cout << "Всего маршрутов с пересадками, взятых из памяти: " << total << std::endl;

        else
            std::cout << std::endl << "Не существует маршрутов c пересадками, взятых из памяти." << std::endl;

        file_many.close();
    }

    std::cout << "\n\n\n\n\n";
}