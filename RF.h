// C/C++ File
// AUTHOR:   LaoSi
// FILE:     RF.h
// 2014 @laosiaudi All rights reserved
// CREATED:  2014-06-13 19:17:49
// MODIFIED: 2014-06-19 02:13:25
#ifndef __RF__
#define __RF__

#include "dTree.h"
#include <pthread.h>
struct parameter {
    int sizeofSamples;
    int sizeofFeatures;
    int treenumber;
    dTree **tree;
};
class RF {
    private:
        dTree **tree;
        int number;
        static void thread_cal(void *arg);

    public:
        explicit RF(int s);
        ~RF();
        void buildForest();
        int predict(vaNode* node);
};

#endif

