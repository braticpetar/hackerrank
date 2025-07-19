#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, q;
    std::cin >> n >> q;
    
    std::vector<std::vector<int>> arr(n);
    
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        arr[i].resize(k);
        
        for (int j = 0; j < k; j++)
        {
            std::cin >> arr[i][j];
        }
    }
    
    for (int i = 0; i < q; i++)
    {
        int q1, q2;
        std::cin >> q1 >> q2;
        
        std::cout << arr[q1][q2] << endl;
        
        
    }
    
}
