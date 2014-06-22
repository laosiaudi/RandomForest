#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2014-05-28 22:55:44
# @Author  : Your Name (you@example.org)
# @Link    : http://example.org
# @Version : $Id$

import os
import csv

def rgbToGray(A):
    ret = [(int(R)*0.299 + int(G)*0.587 + int(B)*0.114) for R,G,B in zip(A[ :1024], A[1024:2048], A[2048:])]
    return ret

def processCSV():
    
    ## read test
    csvfile = open('cifar-10-train.csv', 'rb')
    csvfile.readline()
    reader = csv.reader(csvfile)
    outfile = open('new.txt','wb')
    outfile2 = open('valid.txt','wb')

    writer = csv.writer(outfile)
    writer2 = csv.writer(outfile2)
    i = 1
    for row in reader:
        if i > 10000:
            writer2.writerow([int(row[1])] + rgbToGray(row[2:]))
        writer.writerow([int(row[1])] + rgbToGray(row[2:]))
        i += 1


    

    csvfile.close()
    outfile.close()
    outfile2.close()


if __name__ == '__main__':
    processCSV()



