#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;
// int timeTable[(24*60*60)+10];
// int timeTable[(24*60*60*1000)+10];

int timeToMMMSecond(string& time){
    string hh, mm, sssss;
    stringstream ss;
    ss.str(time);
    
    int MMMSecond = 0;
    getline(ss, hh, ':');
    getline(ss, mm, ':');
    getline(ss, sssss, '\n');
    
    // cout<<hh<<" "<<mm<<" "<<sssss<<" "<<endl;
    
    MMMSecond += 60*60*1000*stoi(hh);
    MMMSecond += 60*1000*stoi(mm);
    MMMSecond += 1000*stoi(sssss.substr(0,2)) + stoi(sssss.substr(3,3));
    
    return MMMSecond;
}

int gapToMMMSecond(string gap){
    string s;
    for(int i = 0; i<gap.length(); i++){
        if(gap[i] == 's'){
            break;
        }
        s += gap[i];
    }
    return stof(s) * 1000;
}


int solution(vector<string> lines) {
    int answer = 0;
    int initialStart = 24*60*60*1000 + 100;
    vector<pair<int, int>> timestamps;
    
    for(string log : lines){
        stringstream ss;
        ss.str(log);
        string day, times, gap;
        ss>>day>>times>>gap;
        
        int gapTime = gapToMMMSecond(gap);
        int endTime = timeToMMMSecond(times);
        int startTime = (endTime - gapTime + 1);
        
        initialStart = min(initialStart, endTime);
        
        if(startTime <= 0){
            startTime = 0;
        }
        
        timestamps.push_back({startTime, endTime});
    }
    
    int maxValue = 0;
//     for(int i=initialStart; i<=24*60*60*1000 + 2000; i+=999){
//         int value = 0;
//         for(pair<int, int> timestamp : timestamps){
//             int start = timestamp.first;
//             int end = timestamp.second;
            
//             if(start <= initialStart+999){
//                 value++;
//             }
//         }
//         maxValue = max(maxValue, value);
//     }
    
    for(int i=0; i<timestamps.size(); i++){
        int value = 0;
        int cnt_start = timestamps[i].first;
        int cnt_end = timestamps[i].second;
        
        for(int j=i; j<timestamps.size(); j++){
            int start = timestamps[j].first;
            int end = timestamps[j].second;
            
            if(cnt_end + 999 >= start){
                value += 1;
            }
        }
        maxValue = max(maxValue, value);
    }
    
    
    answer = maxValue;
    
    return answer;
} 