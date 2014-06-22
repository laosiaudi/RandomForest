// C/C++ File
// AUTHOR:   LaoSi
// FILE:     dTree.h
// 2014 @laosiaudi All rights reserved
// CREATED:  2014-06-14 10:25:59
// MODIFIED: 2014-06-19 01:44:00
#ifndef __DTREE__
#define __DTREE__
#include <string>
#include <vector>

using namespace std;
struct Node {
    int cateNum;
    double threshold;
    int output;
    Node *left;
    Node *right;
    Node(){left = NULL;right = NULL;}
};

struct vaNode {
    int aclabel;
    double fea[1024];
};
class dTree {
    public:
        explicit dTree(int);
        ~dTree();
        void buildTree(int sizeofSample, int sizeofFeature, int treenumber);
        int predict(vaNode* node);
        int nodeNum;
        static void readData();
        int sindex;
    private:
        void recursiveBuild(Node *root, int* visit, int* classified, int level);
        int recursivePredict(vaNode* node, Node* root);
        double entrophy(int threshold, int* used, int fea);
        double Gini(int threshold, int* used, int fea);
        void releaseMemory(Node* root);
        char filename[100];
        Node* Root;
        int scale;
        static int label[10000];
        static double data[10000][1024];
};

#endif
