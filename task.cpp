#include "task.h"
#include "FileIO.h"
#include <iostream>

/*---------------------------------------- Constructor ---------------------------------------*/
task::task(string _name, string _course, string _duedate,
    int _weight, int _diff, string _description, bool _valid, bool _complete) {
	name = _name;
	course = _course;
	duedate = _duedate;
	weight = _weight;
	difficulty = _diff;
	description = _description;
	valid = _valid;
    complete = _complete;
}

/*------------------------------------------ Getters -----------------------------------------*/

bool task::get_valid() {
	return valid;
}

bool task::get_complete() {
    return complete;
}

int task::get_weight() {
	return weight;
}

int task::get_diff() {
	return difficulty;
}

string task::get_duedate() {
	return duedate;
}

string task::get_course() {
	return course;
}

string task::get_name() {
	return name;
}

string task::get_description() {
	return description;
}

void task::print() {
    cout << "Name: " << this->name << ", ";
    cout << "Weight: " << this->weight << ", ";
    cout << "Diff: " << this->difficulty << endl;
    cout << "Course: " << this->course << endl;
    cout << "Due date: " << this->duedate << endl;
    cout << "Description: " << this->description << endl;
}

/*------------------------------------------ Setters -----------------------------------------*/
void task::set_valid(bool _valid) {
	valid = _valid;
}

void task::set_complete(bool _complete) {
    complete = _complete;
}

void task::set_weight(int _weight) {
	weight = _weight;
}

void task::set_diff(int _diff) {
	difficulty = _diff;
}

void task::set_duedate(string _duedate) {
	duedate = _duedate;
}

void task::set_course(string _course) {
	course = _course;
}

void task::set_name(string _name) {
	name = _name;
}

void task::set_description(string _description) {
	description = _description;
}

/*------------------------------------------ Colors -----------------------------------------*/

/*---------------------------------------- Constructor ---------------------------------------*/
task::task_colors::task_colors(string _filepath) {
    filepath = _filepath;
    load_file();
}

/*------------------------------------------ Getters -----------------------------------------*/
map<string,int> task::task_colors::get_colors() {
    return colors;
}

/*------------------------------------------ Setters -----------------------------------------*/
void task::task_colors::set_colors(map<string,int>& _colors) {
    colors = _colors;
    out_file();
}

void task::task_colors::update_color(pair<string, int>& color) {
    colors[color.first] = color.second;
    out_file();
}
/*------------------------------------------ Helpers -----------------------------------------*/
void task::task_colors::load_file() {
    map<string,int> temp;
    string len, holder;
    pair<string, int> p;

    ifstream in_file;
    in_file.open(filepath);

    getline(in_file, len);
    for (int i = 0; i < stoi(len); i++) {
        getline(in_file, holder);
        p = get_pair(holder);
        temp[p.first] = p.second;
    }

    in_file.close();
    colors = temp;
}

void task::task_colors::out_file() {
    ofstream file;
    file.open(filepath);

    string holder = "";
    file << colors.size() << '\n';
    for (pair<string, int> p : colors) {
        holder = "\"";
        holder += p.first;
        holder += "\",";
        holder += to_string(p.second);
        file << holder << '\n';
    }

    file.close();
}

pair<string, int> task::task_colors::get_pair(string s) {
    pair<string, char> p;
    string holder;
    for (unsigned int i = 1; i < s.length(); i++) {
        if (s[i] == '\"') {
            p.first = holder;
            break;
        }
        else {
            holder += s[i];
        }
    }
    p.second = stoi(s.substr(s.length()-1,1));
    return p;
}
