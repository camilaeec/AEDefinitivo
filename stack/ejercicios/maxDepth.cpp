#include <iostream>

using namespace std;


int maxDepth(string s) {
    int count = 0;
    int depth = 0;
    for(char c:s){
        if (c == '(') count++;
        else if (c == ')') count--;
        depth = max(depth,count);
    }
    return depth;
}


int main() {
    string s1 = "(1+(2*3)+((8)/4))+1";
    string s2 = "(1)+((2))+(((3)))";

    cout << "Profundidad de anidacion de s1: " << maxDepth(s1) << endl;  // Output: 3
    cout << "Profundidad de anidacion de s2: " << maxDepth(s2) << endl;  // Output: 3

    return 0;
}


