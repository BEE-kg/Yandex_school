#include "struct.h"
#include "utils.h"



// парс строки по пробелам

std::vector<std::string> Split_String(const std::string& str) {
    std::istringstream iss(str);

    return {std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()};
}



// проверка на интернет

bool Internet_Connection() {

    return std::system("ping -n 1 google.com > nul 2>&1") == 0;
}



// парс строки по кавычкам

std::vector<std::string> Quotation_Mark(const std::string& str) {

    std::vector<std::string> result;
    size_t start = 0;
    bool in_quotes = false;

    for (size_t i = 0; i < str.length(); i++) {

        if (str[i] == '"') {

            if (in_quotes) {

                result.push_back(str.substr(start, i - start));
                in_quotes = false;
            } 
            
            else {

                start = i + 1;
                in_quotes = true;
            }
        }
    }

    return result;
}



// вытаскивание даты

std::string Date(const std::string& datetime) {

    size_t pos = datetime.find('T');

    if (pos != std::string::npos)
        return datetime.substr(0, pos);

    return "";
}



// проверка принадлежности вектору Саратова

bool Near_Saratov(const std::string& value, const std::vector<std::string>& saratov) {
    return std::find(saratov.begin(), saratov.end(), value) != saratov.end();
}



// удаляет кешированные файлы

// void Delete_File(const std::string& file_path, int seconds) {

//     std::this_thread::sleep_for(std::chrono::seconds(seconds));

//     try {

//         if (std::filesystem::exists(file_path))
//             std::filesystem::remove(file_path);

//     } 
    
//     catch (const std::exception& e) {
//         return;
//     }
// }

void DeleteFileWithCmd(const std::string& file_path, int delay_seconds) {
    
    std::string command = "ping -n " + std::to_string(delay_seconds + 1) + " 127.0.0.1"
                          " && echo Удаляю файл: \"" + file_path + "\""
                          " && del \"" + file_path + "\"";

    ShellExecuteA(NULL, "open", "cmd.exe", ("/k " + command).c_str(), NULL, SW_HIDE);
}