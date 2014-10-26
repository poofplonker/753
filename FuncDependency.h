//
//  FuncDependency.h
//  PossibilisticArmstrong
//
//  Created by Cinnamon Scudworth on 9/09/14.
//  Copyright (c) 2014 Cinnamon Scudworth. All rights reserved.
//

#ifndef __PossibilisticArmstrong__FuncDependency__
#define __PossibilisticArmstrong__FuncDependency__

#include <iostream>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include "Attributes.h"


using namespace std;
inline std::string &ltrim(std::string &s);
inline std::string &rtrim(std::string &s);
inline std::string &trim(std::string &s);
inline std::string &spaceReplace(std::string &s);



class FuncDependency {
private:
    Attributes ante;
    Attributes conseq;
    int certainty;
public:
    FuncDependency(string inputline);
    Attributes const& getAnte() const;
    Attributes const& getConseq() const;
    bool isValid(Attributes &attributes);
    int getCertainty() const;
    friend ostream& operator<< (ostream &out, FuncDependency fd1);
};

ostream& operator<< (ostream &out, set<FuncDependency> fds);
bool operator<(FuncDependency const&fd1,FuncDependency const&fd2);


#endif /* defined(__PossibilisticArmstrong__FuncDependency__) */
