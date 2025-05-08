#include <iostream>
#include <vector>

using namespace std;


void reshapeMatrix(vector<vector<int>>& matrix, int newP, int newQ) {
    int n = matrix.size();
    int m = matrix[0].size();
    if (n * m != newP * newQ) {  
    }

    vector<int> flatList;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            flatList.push_back(matrix[i][j]);
        }
    }


    vector<vector<int>> newMatrix(newP, vector<int>(newQ));
    for (int i = 0; i < newP; ++i) {
        for (int j = 0; j < newQ; ++j) {
            newMatrix[i][j] = flatList[i * newQ + j];
        }
    }

    matrix = newMatrix;  

}


void transposeMatrix(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> transposed(m, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }

    matrix = transposed;  
}


int queryElement(const vector<vector<int>>& matrix, int i, int j) {
    return matrix[i][j];
}

int main() {
    int n, m, t;
    cin >> n >> m >> t;

    
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }

    
    for (int k = 0; k < t; ++k) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1) {  
            reshapeMatrix(matrix, a, b);
        } else if (op == 2) {  
            transposeMatrix(matrix);
        } else if (op == 3) {  
            cout << queryElement(matrix, a, b) << endl;
        }
    }

    return 0;
}