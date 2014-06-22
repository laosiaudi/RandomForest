// C/C++ File
// AUTHOR:   LaoSi
// FILE:     dTree.cpp
// 2014 @laosiaudi All rights reserved
// CREATED:  2014-06-14 10:50:27
// MODIFIED: 2014-06-22 09:07:58
#include "dTree.h"
#include <fstream>
#include <string>
#include <math.h>
#include <iostream>
#include <ctime>
using namespace std;
int dTree::label[10000];
double dTree::data[10000][1024];
#define data dTree::data
#define label dTree::label

dTree::dTree(int s) {
    Root = new Node();
    strcpy(filename,"new.txt");
    scale = s;
//  label = new int[scale];
//  data = new double*[scale];
//  for (int i = 0;i < scale;i ++)
//      data[i] = new double[1024];
    nodeNum = 1;

}



void dTree::readData() {
    ifstream infile;
    infile.open("new.txt",ios::in);
    for (int i = 0;i < 10000;i ++) {
        infile >> label[i];
        char c;
        infile >> c;
        for (int j = 0;j < 1024;j ++) {
            infile >> data[i][j];
            if (j != 1023)
                infile >> c;
        }
    }
    infile.close();
    
}
dTree::~dTree() {
    releaseMemory(Root);
}

void dTree::releaseMemory(Node* root) {
    if (root->left ==  NULL && root->right == NULL)
        delete root;
    else {
        Node* tempLeft = root->left;
        Node* tempRight = root->right;
        root->left = NULL;
        root->right = NULL;
        delete root;
        releaseMemory(tempLeft);
        releaseMemory(tempRight);
    }
}
void dTree::buildTree(int sizeofSample, int sizeofFeature, int treenumber) {
   int *visit = new int[1024]; //visit is the tree's initial feature set
   int *classified = new int[scale]; // classified is the tree's initial sample set
   for (int i = 0;i < 1024;i ++) 
       visit[i] = 1;
   srand(treenumber);
   for (int i = 0;i < sizeofFeature;) {
       int index = rand() % 1024;
       if (visit[index] == 1){
           visit[index] = 0;
           i ++;
       } 
   }
   for (int i = 0;i < scale;i ++)
       classified[i] = 1;
   for (int i = 0;i < sizeofSample;) {
       int index = rand() % 10000;
       if (classified[index] == 1){
           classified[index] = 0;
           i ++;
       } 
   }
   sindex = treenumber;
   cout << "Building tree " << treenumber << endl;
   recursiveBuild(Root, visit, classified, 0); 
}

double dTree::entrophy(int threshold, int* used, int fea) {
    int p1 = 0;
    int p2 = 0;
    int sum = 0;
    for (int i = 0; i< scale; i ++) {
        if (used[i] == 0) {
            sum ++;
            if (data[i][fea] < threshold)
                p1 ++;
            else
                p2 ++;
        }
    }
    double para1 = (double)p1/sum;
    double para2 = (double)p2/sum;
    if (para2 == 0)
        return 10000;
    else
        return (-para1*log2(para1) - para2*log2(para2)); 
}

double dTree::Gini(int threshold,int *used, int fea) {
    int p1 = 0;
    int count1[10];
    int p2 = 0;
    int count2[10];
    int sum = 0;
    for (int i = 0;i < 10;i ++) {
        count1[i] = 0;
        count2[i] = 0;
    }

    for (int i = 0;i < scale;i ++) {
        if (used[i] == 0) {
            sum ++;
            if (data[i][fea] < threshold) {
                p1 ++;
                count1[label[i]] ++;
            } else {
                p2 ++;
                count2[label[i]] ++;
            }
        }
    }
    double s1 = 0;
    double s2 = 0;
    for (int i = 0;i < 10;i ++) {
        s1 += (double)count1[i]/p1 *(double)count1[i]/p1;
        s2 += (double)count2[i]/p2 *(double)count2[i]/p2;
    }
    return (double)p1/sum*(1 - s1) + (double)p2/sum*(1-s2);
}
void dTree::recursiveBuild(Node* root, int* visit, int* classified, int level) {
    level ++;
    int jj = 0;
    for (jj = 0;jj < 1024;jj ++) {
        if (visit[jj] == 0)
            break;
    } //no feature to choose,then stop
    if (jj == 1024) {
        root->left = NULL;
        root->right = NULL;
        int num[10];
        for (int i = 0;i < 10;i ++)
            num[i] = 0;
        for (int i = 0;i < scale;i ++) {
            if (classified[i] == 0)
                num[label[i]] ++;
        }
        int maxx = 0;
        int spec = 0;
        for (int i = 0;i < 10;i ++) {
            if (num[i] > maxx){
                maxx = num[i];
                spec = i;
            }
        }
        root->output = spec;
        delete []visit;
        delete []classified;
        cout << "no feature!\n";
        return;
    }
    int ii = 0;
    for (int j = 0;j < scale;j ++) {
        if (classified[j] == 0)
            ii ++;
    } // samples less than 50 or nodenum >= 1000, then stop
    if (ii <= 10 || level > 20) {
        root->left =NULL;
        root->right = NULL;
        int num[10];
        for (int i = 0;i < 10;i ++)
            num[i] = 0;
        for (int i = 0;i < scale;i ++) {
            if (classified[i] == 0)
                num[label[i]] ++;
        }
        int maxx = 0;
        int spec = 0;
       for (int i = 0;i < 10;i ++) {
            if (num[i] > maxx){
                maxx = num[i];
                spec = i;
            }
        }
        root->output = spec;
        delete []visit;
        delete []classified;
        //cout << spec << endl;
        //cout << "too many!\n";
        return ;
    }

    // judge if is time to stop building

    int splitValue;
    int splitFeature = -1;
    double minEntro = 10000;
    for (int i = 0;i < 1024;i ++) {
        if (visit[i] == 0) { //visit[i] = 0 means i-th feature has not been used.
            for (int j = 1;j <= 10; j++) {
               int temp = 25*j;
               
               double tempEn = Gini(temp, classified, i);
               if (tempEn < minEntro) {
                  minEntro = tempEn;
                  splitValue = temp;
                  splitFeature = i;
               }
            }
        }
    }
    if (splitFeature == -1) {
        cout << "bad\n";
        root->left =NULL;
        root->right = NULL;
        int num[10];
        for (int i = 0;i < 10;i ++)
            num[i] = 0;
        for (int i = 0;i < scale;i ++) {
            if (classified[i] == 0)
                num[label[i]] ++;
        }
        int maxx = 0;
        int spec = 0;
        for (int i = 0;i < 10;i ++) {
            if (num[i] > maxx) {
                maxx = num[i];
                spec = i;
            }
                
        }
        root->output = spec;
        delete []visit;
        delete []classified;
        return ;
    }

    //find the split point and the split feature
    visit[splitFeature] = 1; // set this feature can not be used
    root->cateNum = splitFeature; // set split feature
    root->threshold = splitValue; // set threshold for spliting
    int* newVisit = new int[1024];
    int* newClassified = new int[scale];
    for (int i = 0;i < 1024;i ++)
        newVisit[i] = visit[i];
    for (int i = 0; i< scale;i ++)
        newClassified[i] = classified[i];
    for (int i = 0; i< scale;i ++) {
        if (classified[i] == 0){
            if (data[i][splitFeature] < splitValue) {
                classified[i] = 0;
                newClassified[i] = 1;
            } else {
                classified[i] = 1;
                newClassified[i] = 0;
            }
        }
    }
    root->left = new Node();
    root->right = new Node();
    nodeNum += 2;
    //cout << nodeNum << endl;
    recursiveBuild(root->left, visit, classified, level);
    recursiveBuild(root->right,newVisit, newClassified,level);
}


int dTree::predict(vaNode * node) {
   return recursivePredict(node, Root);
}

int dTree::recursivePredict(vaNode* node, Node* root) {
   if (root->left == NULL && root-> right == NULL)
       return root->output;
   else {
      int feaa = root->cateNum;
      if (node->fea[feaa] < root-> threshold)
          return recursivePredict(node, root->left);
      else
          return recursivePredict(node, root->right);
   }
}
