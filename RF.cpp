// C/C++ File
// AUTHOR:   LaoSi
// FILE:     RF.cpp
// 2014 @laosiaudi All rights reserved
// CREATED:  2014-06-15 16:39:39
// MODIFIED: 2014-06-22 18:17:20
#include "RF.h"
#include <iostream>
#include <boost/bind.hpp>
#include "threadpool.hpp"
using namespace std;
using namespace boost::threadpool;
RF::RF(int s) {
    number = s;
    tree =  new dTree*[number];
    dTree::readData();
    for (int i = 0;i < number;i ++)
        tree[i] = new dTree(10000);
}

RF::~RF() {
   for (int i = 0;i < number; i ++)
       delete tree[i];
}

void RF::thread_cal(void *arg) {
   int s1 = ((struct parameter *)arg)->sizeofSamples;
   int s2 = ((struct parameter *)arg)->sizeofFeatures;
   int treeN = ((struct parameter *)arg)->treenumber;
   dTree **t = ((struct parameter *)arg)->tree;
   (*t)->buildTree(s1,s2,treeN);
}

void RF::buildForest() {
    pool tp(5);//threadpool instantiated
    struct parameter p[number];
    for (int i = 0;i < number;i ++) {
    //    cout << "Building tree " << i << endl;
        /*p[i].sizeofSamples = 1000;
        p[i].sizeofFeatures = 32;
        p[i].treenumber = i;
        p[i].tree = &tree[i];
        tp.schedule(boost::bind(RF::thread_cal,&p[i]));
        */tree[i]->buildTree(1000, 32, i); //every time 1000 samples, 100 features
        //cout << tree[i]->nodeNum << endl;
    }
    
    tp.wait(); //wait until all the threads finish
    cout << "Building finished!\n";
}

int RF::predict(vaNode* node) {
    int num[10];
    for (int i = 0;i < 10;i ++)
        num[i] = 0;
    for (int i = 0;i < number;i ++) {
    //    cout << "Predict in tree " << i << endl;
        int temp = tree[i]->predict(node);
        num[temp] ++;
        //cout << "The result is  " << temp << endl;
    }
    int maxx = 0;
    int spec = 0;
    for (int i = 0;i < 10;i ++) {
        if (num[i] > maxx) {
            maxx = num[i];
            spec = i;
        }
    }
    return spec;
}
