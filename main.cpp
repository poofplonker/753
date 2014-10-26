//
//  main.cpp
//  PossibilisticArmstrong
//
//  Created by Cinnamon Scudworth on 9/09/14.
//  Copyright (c) 2014 Cinnamon Scudworth. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "SchemaReader.h"
#include "FDGenerator.h"
using namespace std;
int main( int argc, const char * argv[]){
    srand(time(NULL));
    for(int m = 0; m < 2; m++){
        stringstream tempstream;
        tempstream << m;
        string filename = "constrained" + tempstream.str();
        string fileInputName = filename + ".txt";
        string fileOutputName = filename + "output.txt";
        string metaFile = filename + "meta.txt";
        string timeMetaFile = filename + "meta2.txt";
        ofstream meta;
        ofstream timeMeta;
        meta.open(metaFile);
        if(!meta.is_open()){
            cout << "Meta file could not opened." << endl;
            return 0;
        }
        timeMeta.open(timeMetaFile);
        if(!timeMeta.is_open()){
            cout << "Time Meta file could not opened." << endl;
            return 0;
        }
        for(int z = 2; z < 17; z++){
            int test = 500;
            
            int attrCount = z;
            int certainty = 2*m;
            
            double averageRows = 0;
            double averageTime = 0;
            int correctCounter = 0;
            for (int i = 0; i < test; i++) {
                stringstream tempss;
                int k = attrCount;
                tempss << filename << "armstrong" << i <<  ".txt";
                string filenameArmOut = tempss.str();
                ofstream out;
                int rows;
                time_t start;
                out.open(filenameArmOut);
                if(!out.is_open()){
                    cout << "Output file could not opened." << endl;
                    return 0;
                }
                stringstream inputstream = FDgenerator(attrCount,2*k,certainty);
                SchemaReader s = SchemaReader(inputstream);
                s.calcFDCover();
                if(m == 0){
                    while (s.getFDSize() < k) {
                        inputstream = FDgenerator(attrCount,2*k,certainty);
                        s = SchemaReader(inputstream);
                        s.calcFDCover();
                    }
                    while(s.getFDSize() > k){
                        s.removeFD();
                    }
                    
                    if(s.getFDSize() == k){
                        correctCounter++;
                    }
                }else{
                    while (s.constrainedSize() != attrCount || s.getFDSize() != k) {
                        inputstream = FDgenerator(attrCount,2*k,certainty);
                        s = SchemaReader(inputstream);
                        s.calcFDCover();
                        while(s.getFDSize() > k){
                            s.removeFD();
                        }
                    }
                    
                    if(s.getFDSize() == k && s.constrainedSize() == attrCount){
                        correctCounter++;
                    }
                }
                long coverSize = s.getFDSize();
                start = clock();
                s.compMaximalSets();
                rows = s.calcArmstrong(out);
                double time = ((double)(clock()-start))/CLOCKS_PER_SEC;
                averageRows += rows;
                averageTime += time;
                out.close();
            }
            averageRows /= test;
            averageTime /= test;
            cout << "For " << z<< " The Fd count was correct " << correctCounter << " times." << endl;
            meta << z << " " << averageRows << endl;
            timeMeta << z << " " << averageTime << endl;
            
        }
        meta.close();
        timeMeta.close();
    }
    return 0;
}

