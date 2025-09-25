#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    static int parseRPNString(const string& input) {
        stack<int> s;

        for (const char c : input) {
            if ('0' <= c && c <= '9') {
                // is number
                s.push(c - '0');
            } else if (c != ' ') {
                if (c == '+') {
                    const int num1 = s.top();
                    s.pop();
                    const int num2 = s.top();
                    s.pop();
                    s.push(num1 + num2);
                } else if (c == '-') {
                    const int num1 = s.top();
                    s.pop();
                    const int num2 = s.top();
                    s.pop();
                    s.push(num2 - num1);
                } else if (c == '*') {
                    const int num1 = s.top();
                    s.pop();
                    const int num2 = s.top();
                    s.pop();
                    s.push(num1 * num2);
                } else if (c == '/') {
                    const int num1 = s.top();
                    s.pop();
                    const int num2 = s.top();
                    s.pop();
                    s.push(num2 / num1);
                }
            }
        }
        return s.top();
    }
};


int main() {
    const string input = "1 2 + 3 * 4 5 + 3 / -";
    cout << Solution::parseRPNString(input) << endl;
}