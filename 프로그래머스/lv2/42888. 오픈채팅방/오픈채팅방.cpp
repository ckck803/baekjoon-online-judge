#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

map<string, string> id_nickName;
map<string, string> id_nickName_temp;
map<string, string> last_status;
map<string, vector<string>> nickNameHist;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    vector<pair<string, string>> id_status;

    for (string line : record) {
        stringstream ss;
        ss.str(line);
        string cmd, id, nickName;
        ss >> cmd >> id;

        id_status.push_back({cmd, id});

        if (cmd == "Enter") {
            ss >> nickName;
            last_status[id] = cmd;

            if (id_nickName_temp.find(id) != id_nickName_temp.end() && id_nickName_temp[id] != "") {
                id_nickName[id] = id_nickName_temp[id];
                id_nickName_temp[id] = "";
            } else {
                id_nickName[id] = nickName;
            }
        }

        if (cmd == "Leave") {
            last_status[id] = cmd;
        }

        if (cmd == "Change") {
            ss >> nickName;

            if (last_status[id] == "Enter") {
                id_nickName[id] = nickName;
            } else {
                id_nickName_temp[id] = nickName;
            }
        }
    }

    for (pair<string, string> cmd_id : id_status) {
        string cmd = cmd_id.first;
        string id = cmd_id.second;
        string line;

        if (cmd == "Enter") {
            line = id_nickName[id] + "님이 들어왔습니다.";
            answer.push_back(line);
        }
        if (cmd == "Leave") {
            line = id_nickName[id] + "님이 나갔습니다.";
            answer.push_back(line);
        }
    }

    return answer;
}