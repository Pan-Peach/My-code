#include <iostream>
#include <string>
using namespace std;

// 返回X的最长前缀，同时也是Y的后缀


int main() {
    string X, Y;
    cin >> X >> Y;
    cout << longestPrefixSuffix(X, Y) << endl;
    return 0;
}