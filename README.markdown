RandomForest
======

A C++ Implementation of Randomforest  
For Machine Learning course  



[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/laosiaudi/chat-js/trend.png)](https://bitdeli.com/free "Bitdeli Badge")


 
##Dependencies
 1.`Boost`  
 2.`threadpool`  

##Compile and run  
 1. For `Linux`,   
    g++ main.cpp dTree.cpp RF.cpp -lboost_system -lboost_thread -lpthread -o main
 2. For 'Mac',  
    g++ main.cpp dTree.cpp RF.cpp -lboost_system -lboost_thread-mt -lpthread -o main
    
        
   
##NOTE  
   1. Build decision tree in multi-thread 
   2. Random select samples and features to build trees. 


##To Be Continued  
1. Use `MPI` to implement distributed building.
  
##Copyright and License  
  Copyright 2014 laosiaudi, under the [the MIT license](https://github.com/laosiaudi/Chat-JS/blob/master/LICENSE)

