#pragma once

#include "struct.h"



std::vector<std::string> Split_String(const std::string&);

bool Parser_For_Arguments(std::string, Ticket&, Parametrs&);

void GET_Request_Internet(Ticket&, Parametrs&);

void Special_Transport(Ticket&);

bool Internet_Connection();

void GET_Request_Nake(Ticket&, Parametrs&);

std::vector<std::string> Quotation_Mark(const std::string&);

std::string Date(const std::string&);

bool Near_Saratov(const std::string&, const std::vector<std::string>&);

// void Delete_File(const std::string&, int);

void DeleteFileWithCmd(const std::string&, int);