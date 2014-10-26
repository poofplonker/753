//
//  FuncDependency.cpp
//  PossibilisticArmstrong
//
//  Created by Cinnamon Scudworth on 9/09/14.
//  Copyright (c) 2014 Cinnamon Scudworth. All rights reserved.
//

#include "FuncDependency.h"

// trim from start
inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

inline std::string &spaceReplace(std::string &s){
    while(s.find(" ") != string::npos){
        s.replace(s.find(" "), 1, "_");
    }
    return s;
}

FuncDependency::FuncDependency(string input){
    stringstream fullline, partial1, partial2, partial3;
    string token, chunk;
    fullline << input;
    getline(fullline, chunk, ':');
    
    //token is now the list of attributes in the antecendent
    partial1 << chunk;
    while (getline(partial1, token, ',')) {
        transform(token.begin(), token.end(), token.begin(), ::toupper);
        trim(token);
        spaceReplace(token);
        ante.insert(token);
    }
    getline(fullline, chunk, ':');
    partial2 << chunk;
    while (getline(partial2, token, ',')) {
        transform(token.begin(), token.end(), token.begin(), ::toupper);
        trim(token);
        spaceReplace(token);
        conseq.insert(token);
    }
    getline(fullline, chunk, ':');
    partial3 << chunk;
    partial3 >> certainty;
}

/* Is valid tests simply whether the attributes in the FD are specified in the list of FDs.*/
bool FuncDependency::isValid(Attributes &attributes){
    for (auto it = ante.begin(); it != ante.end(); it++) {
        if (attributes.find(*it) == attributes.end()) {
            return false;
        }
    }
    for (auto it = conseq.begin(); it != conseq.end(); it++) {
        if (attributes.find(*it) == attributes.end()) {
            return false;
        }
    }
    return true;
}

int FuncDependency::getCertainty() const{
    return certainty;
}

Attributes const& FuncDependency::getAnte() const{
    return ante;
}
Attributes const& FuncDependency::getConseq()const{
    return conseq;
}

bool operator<(FuncDependency const&fd1, FuncDependency const&fd2){
    if(fd1.getCertainty() == fd2.getCertainty()){
        if(fd1.getAnte().size() == fd2.getAnte().size()){
            if (fd1.getConseq().size() == fd2.getConseq().size()) {
                set<string>::iterator it1 = fd1.getAnte().begin();
                set<string>::iterator it2 = fd2.getAnte().begin();
                while (it1 != fd1.getAnte().end()) {
                    if(*it1 != *it2){
                        return *it1 < *it2;
                    }
                    it1++;
                    it2++;
                }
                it1 = fd1.getConseq().begin();
                it2 = fd2.getConseq().begin();
                while (it1 != fd1.getConseq().end()) {
                    if(*it1 != *it2){
                        return *it1 < *it2;
                    }
                    it1++;
                    it2++;
                }
                return false;
            }
            return fd1.getConseq().size() < fd2.getConseq().size();
        }
        return fd1.getAnte().size() < fd2.getAnte().size();
    }
    return fd1.getCertainty() < fd2.getCertainty();
}

ostream& operator<< (ostream &out, set<FuncDependency> fds){
    for (set<FuncDependency>::iterator it = fds.begin(); it != fds.end(); it++) {
        out << *it << endl;
    }
    return out;
    
}
ostream& operator<< (ostream &out, FuncDependency fd1){
    for (set<string>:: iterator it = fd1.ante.begin(); it != fd1.ante.end(); it++) {
        out << *it << " ";
    }
    out << ": ";
    for (set<string>:: iterator it = fd1.conseq.begin(); it != fd1.conseq.end(); it++) {
        out << *it << " ";
    }
    out << ": ";
    out << fd1.certainty;
    return out;
}




