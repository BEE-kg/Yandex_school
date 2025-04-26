#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdint>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>



bool Ends_With(const char*, const char*);

bool Starts_With(const char*, const char*);

bool Positive_Integer(const char*);

void create(const char*, uint64_t**, int, int);



struct Arguments{

    char* name_input_file = nullptr;
    char* name_output_path = nullptr;

    long long count_max_iter = pow(2, 62);
    int count_freq = 0;
    int temp_freq = 0;

    int number_bmp_file = 0;
};

#pragma pack(push, 1)

struct BITMAPFILEHEADER {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BITMAPINFOHEADER {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

#pragma pack(pop)



int main(int argc, char* argv[]){


    Arguments current;


    //чтение команд которые ввел и нахождение названия файла логов
    for (int i = 1; i < argc; ++i){

        //input
        if (((strcmp(argv[i], "-i") == 0) || (strcmp(argv[i], "--input") == 0)) && (i+1 < argc)){
            if ((Ends_With(argv[i+1], ".tsv")) || (Ends_With(argv[i+1], ".tab")))
                current.name_input_file = argv[i+1];
            else{
                std::cerr << "Function input - error" << std::endl;
                return 1;
            }
        }

        //output
        else if (((strcmp(argv[i], "-o") == 0) || (strcmp(argv[i], "--output") == 0)) && (i+1 < argc)){
            if (Starts_With(argv[i+1], "C:"))
                current.name_output_path = argv[i+1];
            else{
                std::cerr << "Function output - error" << std::endl;
                return 1;
            }
        }

        //max_iter
        else if (((strcmp(argv[i], "-m") == 0) || (strcmp(argv[i], "--max-iter") == 0)) && (i+1 < argc)){
            if (Positive_Integer(argv[i+1]))
                current.count_max_iter = std::stoi(argv[i+1]);
            else{
                std::cerr << "Function max_iter - error" << std::endl;
                return 1;
            }
        }

        //freq
        else if (((strcmp(argv[i], "-f") == 0) || (strcmp(argv[i], "--freq") == 0)) && (i+1 < argc)){
            if (Positive_Integer(argv[i+1]))
                current.count_freq = std::stoi(argv[i+1]);
            else{
                std::cerr << "Function freq - error" << std::endl;
                return 1;
            }
        }
    }


    //чтение куч
    std::ifstream file(current.name_input_file);

    int16_t x = 0;
    int16_t y = 0;
    uint64_t a = 0;

    int16_t max_borders_x = 0;
    int16_t max_borders_y = 0;

    while (file >> x >> y >> a){

        max_borders_x = std::max(static_cast<short>(std::abs(x)), max_borders_x);
        max_borders_y = std::max(static_cast<short>(std::abs(y)), max_borders_y);
    }

    int NEW_max_borders_y = max_borders_y * 2 + 1;
    int NEW_max_borders_x = max_borders_x * 2 + 1;

    uint64_t** matrix = new uint64_t*[NEW_max_borders_y];
    for (int i = 0; i < NEW_max_borders_y; ++i)
        matrix[i] = new uint64_t[NEW_max_borders_x];

    for (int temp_y = 0; temp_y < NEW_max_borders_y; temp_y++) {
        for (int temp_x = 0; temp_x < NEW_max_borders_x; temp_x++)
            matrix[temp_y][temp_x] = 0;
    }

    int16_t zero_x = max_borders_x;
    int16_t zero_y = max_borders_y;

    file.clear();
    file.seekg(0);

    while (file >> x >> y >> a){

        if ((x < 0) || (x > 0)) {

            if ((y < 0) || (y > 0))
                matrix[zero_y - y][zero_x + x] = a;
            else
                matrix[zero_y][zero_x + x] = a;

        }else{

            if ((y < 0) || (y > 0))
                matrix[zero_y - y][zero_x] = a;
            else
                matrix[zero_y][zero_x] = a;
        }   
    }

    
    // работа с расширением и рассыпанием
    while (current.count_max_iter != 0) {

        int count = 0;

        // вверх
        for (int x = 0; x < NEW_max_borders_x; x++) {
            if (matrix[0][x] >= 4) {
                
                uint64_t** matrix_2 = new uint64_t*[NEW_max_borders_y + 1];
                for (int i = 0; i < NEW_max_borders_y + 1; i++) {
                    matrix_2[i] = new uint64_t[NEW_max_borders_x];
                    std::fill(matrix_2[i], matrix_2[i] + NEW_max_borders_x, 0);
                }

                for (int temp_y = 0; temp_y < NEW_max_borders_y; temp_y++) {
                    for (int temp_x = 0; temp_x < NEW_max_borders_x; temp_x++)
                        matrix_2[temp_y + 1][temp_x] = matrix[temp_y][temp_x];
                }

                for (int i = 0; i < NEW_max_borders_y; i++)
                    delete[] matrix[i];
                delete[] matrix;

                matrix = matrix_2;
                matrix_2 = nullptr;

                NEW_max_borders_y++;

                break;
            }
        }
        
        // вправо
        for (int y = 0; y < NEW_max_borders_y; y++){

            if (matrix[y][NEW_max_borders_x - 1] >= 4){

                uint64_t** matrix_2 = new uint64_t*[NEW_max_borders_y];
                for (int i = 0; i < NEW_max_borders_y; i++) {
                    matrix_2[i] = new uint64_t[NEW_max_borders_x + 1];
                    std::fill(matrix_2[i], matrix_2[i] + NEW_max_borders_x + 1, 0);
                }

                for (int temp_y = 0; temp_y < NEW_max_borders_y; temp_y++) {
                    for (int temp_x = 0; temp_x < NEW_max_borders_x; temp_x++)
                        matrix_2[temp_y][temp_x] = matrix[temp_y][temp_x];
                }

                for (int i = 0; i < NEW_max_borders_y; i++)
                    delete[] matrix[i];
                delete[] matrix;

                matrix = matrix_2;
                matrix_2 = nullptr;

                NEW_max_borders_x++;

                break;
            } 
        }

        // вниз
        for (int x = 0; x < NEW_max_borders_x; x++){
            if (matrix[NEW_max_borders_y - 1][x] >= 4){

                uint64_t** matrix_2 = new uint64_t*[NEW_max_borders_y + 1];
                for (int i = 0; i < NEW_max_borders_y + 1; i++) {
                    matrix_2[i] = new uint64_t[NEW_max_borders_x];
                    std::fill(matrix_2[i], matrix_2[i] + NEW_max_borders_x, 0);
                }

                for (int temp_y = 0; temp_y < NEW_max_borders_y; temp_y++) {
                    for (int temp_x = 0; temp_x < NEW_max_borders_x; temp_x++)
                        matrix_2[temp_y][temp_x] = matrix[temp_y][temp_x];
                }

                for (int i = 0; i < NEW_max_borders_y; i++)
                    delete[] matrix[i];
                delete[] matrix;

                matrix = matrix_2;
                matrix_2 = nullptr;

                NEW_max_borders_y++;

                break;
            }
        }

        // влево
        for (int y = 0; y < NEW_max_borders_y; y++){
            if (matrix[y][0] >= 4){

                uint64_t** matrix_2 = new uint64_t*[NEW_max_borders_y];
                for (int i = 0; i < NEW_max_borders_y; i++) {
                    matrix_2[i] = new uint64_t[NEW_max_borders_x + 1];
                    std::fill(matrix_2[i], matrix_2[i] + NEW_max_borders_x + 1, 0);
                }

                for (int temp_y = 0; temp_y < NEW_max_borders_y; temp_y++) {
                    for (int temp_x = 0; temp_x < NEW_max_borders_x; temp_x++)
                        matrix_2[temp_y][temp_x + 1] = matrix[temp_y][temp_x];
                }

                for (int i = 0; i < NEW_max_borders_y; i++)
                    delete[] matrix[i];
                delete[] matrix;

                matrix = matrix_2;
                matrix_2 = nullptr;

                NEW_max_borders_x++;

                break;
            }
        }

        // рассыпание
        uint64_t** matrix_2 = new uint64_t*[NEW_max_borders_y];
        for (int i = 0; i < NEW_max_borders_y; i++) {
            matrix_2[i] = new uint64_t[NEW_max_borders_x];
            std::fill(matrix_2[i], matrix_2[i] + NEW_max_borders_x, 0);
        }

        for (int y = 0; y < NEW_max_borders_y; y++){
            for (int x = 0; x < NEW_max_borders_x; x++){
                
                if (matrix[y][x] >= 4){

                    matrix_2[y][x] += matrix[y][x] - 4;

                    matrix_2[y - 1][x] += 1; 
                    matrix_2[y][x + 1] += 1;
                    matrix_2[y + 1][x] += 1;
                    matrix_2[y][x - 1] += 1;

                    count++;
                }else
                    matrix_2[y][x] += matrix[y][x];
            }
        }

        for (int i = 0; i < NEW_max_borders_y; i++)
            delete[] matrix[i];
        delete[] matrix;

        matrix = matrix_2;
        matrix_2 = nullptr;

        current.count_max_iter--;

        if ((count != 0) && (current.count_max_iter != 0)){

            if (current.count_freq != 0){

                current.temp_freq++;
                
                if (current.count_freq == current.temp_freq){

                    size_t length_path = strlen(current.name_output_path);
                    int temp_a = current.number_bmp_file;
                    int length_a = 0;
                    while (temp_a != 0) {
                        temp_a /= 10;
                        length_a++;
                    }
                    char complete_filename_path[length_path + length_a];

                    sprintf(complete_filename_path, "%s%d.bmp", current.name_output_path, current.number_bmp_file);

                    current.number_bmp_file++;

                    create(complete_filename_path, matrix, NEW_max_borders_x, NEW_max_borders_y);

                    current.temp_freq = 0;

                }else
                    continue;

            }else
                continue;
            
            
        }else if ((count == 0) || (current.count_max_iter == 0)){
            
            current.count_max_iter = 0;

            size_t length_path = strlen(current.name_output_path);
            int temp_a = current.number_bmp_file;
            int length_a = 0;
            while (temp_a != 0) {
                temp_a /= 10;
                length_a++;
            }
            char complete_filename_path[length_path + length_a];

            sprintf(complete_filename_path, "%s%d.bmp", current.name_output_path, current.number_bmp_file);

            create(complete_filename_path, matrix, NEW_max_borders_x, NEW_max_borders_y);
        }
    }

    return 0;
}



// проверка конца слова
bool Ends_With(const char* file, const char* extension) {

    int file_len = std::strlen(file);
    int extension_len = std::strlen(extension);

    return std::strncmp(file + file_len - extension_len, extension, extension_len) == 0;
}



// проверка начала слова
bool Starts_With(const char* file, const char* prefix) {

    int prefix_len = std::strlen(prefix);

    return std::strncmp(file, prefix, prefix_len) == 0;
}



// проверка - число ли строка чаров
bool Positive_Integer(const char* argv) {

    if (*argv == '\0') 
        return false;

    while (*argv) {
        if (!isdigit(*argv)) 
            return false;
        argv++;
    }

    return true;
}



// реализация преобразования в bmp файл
void create(const char* filename, uint64_t** matrix, int width, int height) {

    int rowSize = ((width + 1) / 2 + 3) & ~3;
    int paddingSize = (4 - (rowSize % 4)) % 4;
    int dataSize = (rowSize + paddingSize) * height;

    BITMAPFILEHEADER fileHeader;
    fileHeader.bfType = 0x4D42;
    fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 5 * 4 + dataSize;
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;
    fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 5 * 4;

    BITMAPINFOHEADER infoHeader;
    infoHeader.biSize = sizeof(BITMAPINFOHEADER);
    infoHeader.biWidth = width;
    infoHeader.biHeight = height;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 4;
    infoHeader.biCompression = 0;
    infoHeader.biSizeImage = dataSize;
    infoHeader.biXPelsPerMeter = 1800;
    infoHeader.biYPelsPerMeter = 1800;
    infoHeader.biClrUsed = 5;
    infoHeader.biClrImportant = 5;

    std::ofstream BMPfile(filename, std::ios::out | std::ios::binary);
    if (!BMPfile) {
        std::cerr << "Not open file for memory bmp" << std::endl;
        return;
    }

    BMPfile.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    BMPfile.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));

    uint8_t palette[5][4] = { 
        {255, 255, 255 ,0},       // белый
        {0, 153, 76, 0},     // зеленый
        {193, 84, 193},     // фиолетовый
        {0, 255, 255, 0},     // желтый
        {0, 0, 0, 0},   // черный
    };

    for (int i = 0; i < 5; ++i)
        BMPfile.write(reinterpret_cast<const char*>(palette[i]), 4);

    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x += 2) {
            
            uint8_t byte = 0;

            int sandCount1 = matrix[y][x];
            byte = (sandCount1 > 3 ? 4 : sandCount1) << 4;

            if (x + 1 < width) {
                int sandCount2 = matrix[y][x + 1];
                byte |= (sandCount2 > 3 ? 4 : sandCount2) & 0x0F;
            }

            BMPfile.put(byte);
        }

        for (int p = 0; p < rowSize - (width + 1) / 2; p++) 
            BMPfile.put(0);
    }

    BMPfile.close();
}
