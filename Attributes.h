//
//  Attributes.h
//  PossibilisticArmstrong
//
//  Created by Cinnamon Scudworth on 12/10/14.
//  Copyright (c) 2014 Cinnamon Scudworth. All rights reserved.
//

#ifndef __PossibilisticArmstrong__Attributes__
#define __PossibilisticArmstrong__Attributes__

#include <iostream>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

class Attributes{
private:
    set<string> attrib;
    int certainty;
public:
    Attributes();
    void insert(string attr);
    bool isSubset(Attributes attr) const;
    bool isSuperset(Attributes attr) const;
    bool isEqual(Attributes attr) const;
    set<string> getString() const;
    void unite(Attributes attr);
    void remove(string s);
    set<string>::iterator begin() const;
    int size() const;
    set<string>::iterator end() const;
    void intersect(Attributes attr);
    set<string>::iterator find(string s) const;
    Attributes& operator=(const Attributes &attr1);
    void setCertainty(int cert);
    int getCertainty() const;
};
bool operator<(Attributes const&attr1,Attributes const&attr2);
ostream& operator<<(ostream& out,Attributes const&ss);
#endif /* defined(__PossibilisticArmstrong__Attributes__) */
