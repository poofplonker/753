//
//  Attributes.cpp
//  PossibilisticArmstrong
//
//  Created by Cinnamon Scudworth on 12/10/14.
//  Copyright (c) 2014 Cinnamon Scudworth. All rights reserved.
//

#include "Attributes.h"

Attributes::Attributes(){
    
}

set<string>::iterator Attributes::begin() const{
    return attrib.begin();
}

set<string>::iterator Attributes::end() const{
    return attrib.end();
}
set<string>::iterator Attributes::find(string s) const{
    return attrib.find(s);
}
void Attributes::insert(string attr){
    attrib.insert(attr);
}

int Attributes::size() const{
    return attrib.size();
    
}
void Attributes::remove(string s){
    attrib.erase(s);
}

void Attributes::unite(Attributes attr){
    set<string> temp;
    set_union(attrib.begin(), attrib.end(), attr.begin(), attr.end(), inserter(temp, temp.begin()));
    attrib.swap(temp);
}

void Attributes::intersect(Attributes attr){
    set<string> temp;
    set_intersection(attrib.begin(), attrib.end(), attr.begin(), attr.end(), inserter(temp, temp.begin()));
    attrib.swap(temp);
}
bool Attributes::isSuperset(Attributes attr) const{
    return includes(attrib.begin(), attrib.end(), attr.begin(), attr.end());
}
bool Attributes::isSubset(Attributes attr) const{
    return includes(attr.begin(), attr.end(),attrib.begin(), attrib.end());
}
bool Attributes::isEqual(Attributes attr) const{
    return isSuperset(attr) && isSubset(attr);
}
void Attributes::setCertainty(int cert){
    certainty = cert;
}

int Attributes::getCertainty() const{
    return certainty;
}
ostream& operator<<(ostream& out,Attributes const& ss){
    for (auto it = ss.begin(); it != ss.end(); it++) {
        out << *it << " ";
    }
    return out;
}

Attributes& Attributes::operator=(const Attributes& attr1){
    if (this == &attr1) {
        return *this;
    }
    attrib = attr1.attrib;
    return *this;
}

set<string> Attributes::getString() const{
    return attrib;
}

bool operator<(Attributes const&attr1,Attributes const&attr2){
    if(attr1.getCertainty() != attr2.getCertainty()){
        return attr1.getCertainty() > attr2.getCertainty();
    }
    if (attr1.size() == attr2.size()) {
        auto it2 = attr2.begin();
        for (auto it1 = attr1.begin(); it1 != attr1.end(); it1++) {
            if(*it1 != *it2){
                return *it1 < *it2;
            }
            it2++;
        }
    }
    return attr1.size() < attr2.size();
}