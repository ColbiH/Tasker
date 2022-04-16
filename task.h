#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

class task
{
    bool valid, complete;
	int weight, difficulty;
	string duedate, course, name, description;

public:
	/*---------------------------------------- Constructor ---------------------------------------*/
    task(string _name = "Task", string _course = "None", string _duedate = "01/01/1969",
        int _weight = 0, int _diff = 0, string _description = "", bool _valid = 1, bool _complete = 0);


	/*------------------------------------------ Getters -----------------------------------------*/
	bool get_valid();
    bool get_complete();
	int get_weight();
	int get_diff();
	string get_duedate();
	string get_course();
	string get_name();
	string get_description();
    void print();

	/*------------------------------------------ Setters -----------------------------------------*/
	void set_valid(bool _valid);
    void set_complete(bool _complete);
	void set_weight(int _weight);
	void set_diff(int _diff);
	void set_duedate(string _duedate);
	void set_course(string _course);
	void set_name(string _name);
	void set_description(string _description);

    /*------------------------------------------ Colors -----------------------------------------*/

    struct task_colors{

        map<string,int> colors;
        string filepath;


        /*---------------------------------------- Constructor ---------------------------------------*/
        task_colors(string filepath);

        /*------------------------------------------ Getters -----------------------------------------*/
        map<string,int> get_colors();

        /*------------------------------------------ Setters -----------------------------------------*/
        void set_colors(map<string,int>& colors);
        void update_color(pair<string, int>& color);
        /*------------------------------------------ Helpers -----------------------------------------*/
        void load_file();
        void out_file();
        pair<string, int> get_pair(string s);
    };

};
