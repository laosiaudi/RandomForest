// C/C++ File
// AUTHOR:   LaoSi
// FILE:     main.cpp
// 2014 @laosiaudi All rights reserved
// CREATED:  2014-06-14 16:48:41
// MODIFIED: 2014-06-22 18:17:26

#include "RF.h"
#include <iostream>
#include <fstream>
using namespace std;

vaNode vn[10000];
int main() {
    ifstream infile("valid.txt",ios::in);
    for (int i = 0;i < 10000;i ++) {
        infile >> vn[i].aclabel;
        char c;
        infile >> c;
        for (int j = 0; j< 1024;j ++) {
            infile >> vn[i].fea[j];
            if (j != 1023)
                infile >> c;
        }
    }
    infile.close();
    cout << "Start building forest!\n";
    RF randomForest(1000);
    randomForest.buildForest();
    cout << "Start predicting\n";
    int sum = 0;
    int count[10] ;
    for (int i = 0;i < 10;i ++)
        count[i] = 0;
    for (int i = 0;i < 10000;i ++) {
        int p = randomForest.predict(&vn[i]);
        if (p  == vn[i].aclabel) {
          //  cout << vn[i].aclabel << endl;
            sum ++;
            count[p] ++;
        }
    }
    cout << "Valid ones-----> " << sum << endl;
    for (int i = 0;i < 10;i ++)
        cout << i << ": " << count[i] << endl;
    return 0;
}
