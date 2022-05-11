#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int multiValue(float value) {
    return value * 65536;
}

string toLower(string str) {
    string newStr = "";
    for (int i = 0; i < str.size(); i++) {
        if (isupper(str[i])) {
            str[i] += ('a' - 'A');
        }
        newStr += str[i];
    }

    return newStr;
}

bool isValid(string& str) {
    for (int i = 0; i < str.size(); i++) {
        if (!islower(str[i])) {
            return false;
        }
    }

    return true;
}

int solution(string str1, string str2) {
    int answer = 0;
    str1 = toLower(str1);
    str2 = toLower(str2);

    map<string, int> m;
    map<string, int> m2;

    for (int i = 0; i < str1.size() - 1; i++) {
        string sub = toLower(str1.substr(i, 2));
        if (isValid(sub)) {
            if (m.find(sub) == m.end()) {
                m.insert({sub, 1});
            } else {
                m[sub]++;
            }
        }
    }

    for (int i = 0; i < str2.size() - 1; i++) {
        string sub = toLower(str2.substr(i, 2));
        if (isValid(sub)) {
            if (m2.find(sub) == m2.end()) {
                m2.insert({sub, 1});
            } else {
                m2[sub]++;
            }
        }
    }

    int intersact = 0;
    int unionValue = 0;
    for (auto iter = m.begin(); iter != m.end(); iter++) {
        if (m2.find(iter->first) == m2.end()) {
            unionValue += iter->second;
        } else {
            unionValue += max(iter->second, m2[iter->first]);
            intersact += min(iter->second, m2[iter->first]);
        }
    }

    for (auto iter = m2.begin(); iter != m2.end(); iter++) {
        if (m.find(iter->first) == m.end()) {
            unionValue += iter->second;
        }
    }

    if (unionValue == 0) {
        return 65536;
    }
    answer = multiValue((float)intersact / unionValue);
    return answer;
}