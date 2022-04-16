#include <fstream>
#include <vector>
#include <iostream>
#include "task.h"
#include <string>
#include "FileIO.h"
#include <ctime>

using namespace std;


/*--------------------------------------- File I/O ----------------------------------------*/
vector<task> Open_File() {
	ifstream tasks("Resources/tasks.tsk");
	vector<task> returner;
	if (!tasks.is_open()) {
		cout << "Cannot open the tasks file!" << endl;
	}
	else {
		string looper;
		getline(tasks, looper);
		while (looper == "START") {
			// Task data
            string name, course, duedate, desc = "";
            int weight, difficulty;
            bool complete;

            string tempWeight, tempDiff, tempCom, holder;

			getline(tasks, name);
			getline(tasks, course);
			getline(tasks, duedate);
			getline(tasks, tempWeight);
			weight = stoi(tempWeight);
			getline(tasks, tempDiff);
			difficulty = stoi(tempDiff);
            getline(tasks, tempCom);
            complete = (bool)stoi(tempCom);

            getline(tasks, holder);
            desc += holder;
            getline(tasks, holder);
            while(holder != "END"){
             desc += '\n';
             desc += holder;
             getline(tasks, holder);
            }

            task temp(name, course, duedate, weight, difficulty, desc, 1, complete);

            returner.push_back(temp);

			//either next start or end of file.
			getline(tasks, looper);

		}
	}
	tasks.close();
	return returner;
}

void Write_File(vector<task> tasks){
	std::ofstream save_file;
	save_file.open("Resources/tasks.tsk", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < tasks.size(); i++) {
		if (tasks.at(i).get_valid()) {
			save_file << "START\n";
			save_file << tasks.at(i).get_name() << "\n";
			save_file << tasks.at(i).get_course() << "\n";
			save_file << tasks.at(i).get_duedate() << "\n";
			save_file << tasks.at(i).get_weight() << "\n";
			save_file << tasks.at(i).get_diff() << "\n";
            save_file << (int)tasks.at(i).get_complete() << "\n";
			save_file << tasks.at(i).get_description() << "\n";
			save_file << "END\n";
		}
	}
}


/*--------------------------------------- Load ICS ----------------------------------------*/
vector<task> load_ics(string file_path) {

    string holder, name, course;
    vector<task> added;

    ifstream in_file;
    in_file.open(file_path);

    while (1) {
        getline(in_file, holder);
        if (holder.substr(0,13) == "X-WR-CALDESC:") break;
    }

    bool leave = false;
    while (getline(in_file, holder)) {
        if (holder == "BEGIN:VEVENT"){
            leave = false;
            task hodl;

            while (getline(in_file, holder)) {
                if (holder.substr(0, 5) == "DTEND") {
                    hodl.set_duedate(decode_date(only_numbers(holder)));
                    time_t t = time(NULL);
                    tm* timePtr = localtime(&t);
                      if(stoi(hodl.get_duedate().substr(0,2)) < timePtr->tm_mon + 1)
                          leave = true;

                      else if(stoi(hodl.get_duedate().substr(0,2)) == timePtr->tm_mon + 1 && stoi(hodl.get_duedate().substr(3,2)) < timePtr->tm_mday)
                          leave = true;
                }


                if (holder.substr(0, 12) == "DESCRIPTION:") {
                    if (holder.find("Zoom") != string::npos) {
                        leave = true;
                        break;
                    }
                    else {
                        string temp = holder.substr(12);

                        string s = "";
                        getline(in_file, s);
                        while (s.substr(0, 9) != "SEQUENCE:" && s.substr(0, 9) != "LOCATION:") {
                            temp += s;
                            getline(in_file, s);
                        }
                        hodl.set_description(temp);
                    }
                }

                if (holder.substr(0, 8) == "SUMMARY:") {
                    string next;
                    getline(in_file, next);
                    if(next.substr(0,4) != "URL:"){
                        holder+=next.substr(1);
                    }
                    decode_summary(holder.substr(8), name, course);
                    hodl.set_course(course);
                    hodl.set_name(name);
                    break;
                }
            }
            if (leave == false) {
                added.push_back(hodl);
            }
        }
    }

    in_file.close();

    return added;
}

/*--------------------------------------- Helpers ----------------------------------------*/

string decode_date(string in) {
    string hold = in, m, d, y;
    y = hold.substr(0, 4);
    m = hold.substr(4, 2);
    d = hold.substr(6, 2);
    return m + "/" + d + "/" + y;
}

void decode_summary(string sum, string& name, string& course) {
    string n, c;
    bool add = true, cl = false;
    for (unsigned int i = 0; i < sum.length(); i++) {
        if (sum[i] == '(')
            add = false;
        else if (sum[i] == ')')
            add = true;
        else if (sum[i] == '[') {
            cl = true;
            add = false;
        }
        else if (sum[i] == ']') {
            cl = false;
            add = false;
        }

        if (add == true && sum[i] != ')') {
            n += sum[i];
        }
        else if (cl == true && sum[i] != '[') {
            c += sum[i];
        }
    }
    n = trim(n);
    name = n;
    course = c;
}

string only_numbers(string s) {
    string t = "";
    for (char x : s) {
        if (isdigit(x)) {
            t += x;
        }
    }
    return t;
}

string trim(string s) {
    while(true) {
        if (s[s.length() - 1] == ' ') {
            s = s.substr(0, s.length() - 1);
        }
        else
            break;
    }
    return s;
}
bool all_ints(string s){
    for(unsigned int i=0 ; i<s.length() ; i++){
        if(!isdigit(s[i])){
            return false;
        }
    }
    return true;
}


bool validDate(string date){
    string dT = date;
    if(dT.length()==10){
        string dN = (date.substr(0,2) + date.substr(3,2) + date.substr(6,4)); // dateNums
        if(all_ints(dN) && dT[2] == '/' && dT[5] == '/'){
            return true;
        }else{
            return false;
        }
    }
    else{
        return false;
    }
}

