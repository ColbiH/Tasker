#pragma once
#include <vector>
#include "task.h"

/*------------------------ File I/O ------------------------*/
vector<task> Open_File();
void Write_File(vector<task> tasks);

/*------------------------ Load ICS ------------------------*/
vector<task> load_ics(string file_path);

/*------------------------ Helpers -------------------------*/
string decode_date(string in);
void decode_summary(string sum, string& name, string& course);
string only_numbers(string s);
string trim(string s);
bool all_ints(string s);
bool validDate(string date);
