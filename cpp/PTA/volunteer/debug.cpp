#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> scores(n);
    for (int i = 0; i < n; i++) {
        cin >> scores[i];
        cout << "Read score[" << i << "] = " << scores[i] << endl;
    }

    return 0;
}

