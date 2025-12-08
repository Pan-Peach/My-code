#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> scores(n);
    vector<int> freq(1001, 0);

    // Read scores and count frequencies
    for (int i = 0; i < n; i++) {
        cin >> scores[i];
        freq[scores[i]]++;
    }

    // Calculate prefix sums - prefix[i] = number of students with score < i
    vector<int> prefix(1002, 0);
    for (int i = 1; i <= 1001; i++) {
        prefix[i] = prefix[i-1] + freq[i-1];
    }

    // Output results
    for (int i = 0; i < n; i++) {
        cout << prefix[scores[i]] << " ";
    }
    cout << endl;

    return 0;
}
