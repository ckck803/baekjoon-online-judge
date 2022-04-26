#include <iostream>
#include <string>
using namespace std;

string confirm(string str)
{
    int size = str.length();
    int sum = 0;

    for(int i=0; i<size; i++)
    {
        if(sum >= 0)
        {
            if(str[i] == '(')
            {
                sum++;
            }
            else if(str[i] == ')')
            {
                sum--;
            }
        }
        else
            return "NO";
    }

    if(sum == 0)
    {
        return "YES";
    }
    else
    {
        return "NO";
    }
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    int n;
    cin>>n;
    cin.ignore();
    while(n--)
    {
        string str;
        getline(cin, str, '\n');
        cout<<confirm(str)<<'\n';
    }

    return 0;
}