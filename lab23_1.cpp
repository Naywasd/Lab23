#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstdio>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream file(filename);
    string line;
    
    while(getline(file, line)){
        size_t colon_pos = line.find(':');
        if(colon_pos != string::npos){
            string name = line.substr(0, colon_pos);
            names.push_back(name);
            
            string score_str = line.substr(colon_pos + 1);
            int s1, s2, s3;
            sscanf(score_str.c_str(), "%d %d %d", &s1, &s2, &s3);
            
            int total = s1 + s2 + s3;
            scores.push_back(total);
            grades.push_back(score2grade(total));
        }
    }
    file.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    string line;
    getline(cin, line);
    
    size_t space_pos = line.find_first_of(" ");
    if(space_pos != string::npos){
        command = line.substr(0, space_pos);
        key = line.substr(space_pos + 1);
    } else {
        command = line;
        key = "";
    }
}

void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(size_t i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = true;
            break;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(size_t i = 0; i < names.size(); i++){
        if(key.length() > 0 && grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
