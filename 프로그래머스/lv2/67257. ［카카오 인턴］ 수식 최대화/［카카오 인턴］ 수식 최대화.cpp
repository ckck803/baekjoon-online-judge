#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>


using namespace std;
bool check[3];
vector<char> oneCase = vector<char>(3);
vector<vector<char>> allCases;

void makeAllCase(int choice, int depth, vector<char> &v){
    if(choice == depth){
        allCases.push_back(oneCase);
        return;
    }
    
    for(int i=0; i<3; i++){
        if(check[i] == true){
            continue;
        }
        check[i] = true;
        oneCase[choice] = v[i];
        makeAllCase(choice + 1, depth, v);
        check[i] = false;
    }
}

long long calUsingOp(char op, long long first, long long second){
    if(op == '*'){
        return first * second;
    }else
    if(op == '-'){
        return first - second;
    }
    else{
        return first + second;
    }
}

long long calValue(int index, string line){    
    vector<char> priority = allCases[index];
    
    for(char op : allCases[index]){
        stringstream ss;
        ss.str(line);
        
        stack<long long> value_stack;
        stack<char> op_stack;
        
        long long cnt_value = 0;
        char cnt_op;
        ss>>cnt_value;
        value_stack.push(cnt_value);
        
        while(ss>>cnt_op){
            ss>>cnt_value;
            
            if(cnt_op == op){
                long long calResult = 0;
                long long pre_value = value_stack.top();
                value_stack.pop();
                
                calResult = calUsingOp(op, pre_value, cnt_value);
                value_stack.push(calResult);
            }else{
                value_stack.push(cnt_value);
                op_stack.push(cnt_op);
            }
        }
        
        stack<long long> temp_value_stack;
        stack<char> temp_op_stack;
        
        while(!value_stack.empty()){
            temp_value_stack.push(value_stack.top());
            value_stack.pop();
        }
        while(!op_stack.empty()){
            temp_op_stack.push(op_stack.top());
            op_stack.pop();
        }
        string tempLine = to_string(temp_value_stack.top());
        temp_value_stack.pop();
        
        while(!temp_value_stack.empty()){
            tempLine += temp_op_stack.top();
            temp_op_stack.pop();
            
            tempLine += to_string(temp_value_stack.top());
            temp_value_stack.pop();
        }
        
        line = tempLine;
    }
    
    
    return stol(line);
}


long long solution(string expression) {
    long long answer = 0;
    vector<char> v;
    v.push_back('*');
    v.push_back('+');
    v.push_back('-');
    makeAllCase(0,3,v);
    for(int i=0; i<allCases.size(); i++){
        long long value = calValue(i, expression);

        if(answer < abs(value)){
            answer = abs(value);
        }
    }
    
    return answer;
}

