//
//  SchemaReader.h
//  PossibilisticArmstrong
//
//  Created by Cinnamon Scudworth on 9/09/14.
//  Copyright (c) 2014 Cinnamon Scudworth. All rights reserved.
//

#ifndef __PossibilisticArmstrong__SchemaReader__
#define __PossibilisticArmstrong__SchemaReader__

#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <sstream>
#include <utility>
#include <string>
#include <fstream>
#include <cstdio>
#include <map>
#include "FuncDependency.h"
#include "Attributes.h"

using namespace std;

class SchemaReader{
    
private:
    Attributes attr;
    set<FuncDependency> funcDep;
    vector<Attributes> maximalSets;
    string filename;
    Attributes closure(Attributes &attributes,Attributes const& start, set<FuncDependency> &fds, int certainty);
    int degOfCert;
public:
    SchemaReader(stringstream &input);
    Attributes getAttr();
    set<FuncDependency> getFDs();
    void removeFD();
    string tupleToString(int* currentSubValue);
    int calcArmstrong(ofstream &armstrongFile);
    void addRandomFD();
    void calcFDCover();
    void compMaximalSets();
    int constrainedSize();
    long getFDSize();
    int getDegOfCert();
};
set<Attributes>& ridOfSubsets(set<Attributes> &temp);
void printSets(vector<set<Attributes> > &maximalTable);
ostream& operator<<(ostream& out, const set<string> &ss);
bool sortFunction(const Attributes &a1, const Attributes &a2);


#endif /* defined(__PossibilisticArmstrong__SchemaReader__) */
