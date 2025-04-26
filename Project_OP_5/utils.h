#pragma once

#include "config.h"



std::vector<std::string> Split_String(const std::string&);

bool Parser_For_Commands(std::string, values&);

bool Is_Digit(const std::string&);

int Random_Number(int, int);

void Create_Field(values&);

char Random_Char();

void Shot_Computer(values&);

void Shot_User(values&, int, int);

void Dump(values&, std::string);

void Load(values&, std::string);
