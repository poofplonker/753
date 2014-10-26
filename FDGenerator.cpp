//
//  FDGenerator.cpp
//  PossibilisticArmstrong
//
//  Created by Cinnamon Scudworth on 16/10/14.
//  Copyright (c) 2014 Cinnamon Scudworth. All rights reserved.
//

#include "FDGenerator.h"


stringstream FDgenerator(int n, int numFD, int certainty){

    stringstream fdStream;
    vector<char> attributes;
    char beginning = 'A';
    for (int i = 0; i < n; i++) {
        fdStream << char(beginning+i) << endl;
        attributes.push_back(beginning+i);
    }
    fdStream << endl << certainty << endl;
    int fdCount = numFD;
    for (int i = 0; i < fdCount; i++) {
        vector<char> tempAttributes = attributes;
        int targetInt =rand()%n;
        char target = tempAttributes[targetInt];
        tempAttributes.erase(tempAttributes.begin()+targetInt);
        int numAntecendent = rand()%(n-1);
        for (int j = 0; j < numAntecendent; j++) {
            int randomValue = rand()%(tempAttributes.size());
            if(j == 0){
                fdStream <<tempAttributes[randomValue];
            }else{
                fdStream << ", "<<tempAttributes[randomValue];
            }
            tempAttributes.erase(tempAttributes.begin()+randomValue);
        }
        fdStream << ": " << target << ": ";
        int randomCert = rand()%(certainty-1)+1;
        fdStream << randomCert << endl;
        
    }
    return fdStream;
    
}