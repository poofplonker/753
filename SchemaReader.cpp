//
//  SchemaReader.cpp
//  PossibilisticArmstrong
//
//  Created by Cinnamon Scudworth on 9/09/14.
//  Copyright (c) 2014 Cinnamon Scudworth. All rights reserved.
//

#include "SchemaReader.h"


Attributes SchemaReader::closure(Attributes &attributes, Attributes const&start, set<FuncDependency> &fds, int certainty){
    Attributes closure = start;
    Attributes oldClosure;
    set<FuncDependency> workingFDs = fds;
    bool remainingFDs = true;
    
    //while closure is changing and there are more FDs
    while (remainingFDs && !(closure.isEqual(oldClosure))) {
        
        oldClosure = closure;
        remainingFDs = false;
        
        //for every FD
        for (auto it = workingFDs.begin(); it != workingFDs.end(); it++) {
            
            //if it has a greater certainty than we are interested in, break
            if((*it).getCertainty() > certainty){
                break;
            }
            //
            remainingFDs = true;
            Attributes const &ante = (*it).getAnte();
            Attributes const&conseq = (*it).getConseq();
        
            //if the antecedent is a subset of the closure, add the consequent to the closure
            if (ante.isSubset(closure)) {
                closure.unite(conseq);
            }
        }
    }
    return closure;
}

void SchemaReader::calcFDCover(){
    set<FuncDependency> eraseList;
    for (set<FuncDependency>::iterator it = funcDep.begin(); it != funcDep.end(); it++) {
        set<FuncDependency> temp = funcDep;
        temp.erase(*it);
        Attributes clos = closure(attr, (*it).getAnte(), temp, (*it).getCertainty());
        Attributes conseq = (*it).getConseq();
        if(includes(clos.begin(), clos.end(), conseq.begin(), conseq.end())){
            eraseList.insert(*it);
        }
    }
    for (set<FuncDependency>::iterator it = eraseList.begin(); it != eraseList.end(); it++) {
        funcDep.erase(*it);
    }
}

SchemaReader::SchemaReader(stringstream &input){

        //read in attributes
        string line;
        getline(input, line);
        int lineCounter = 0;
        lineCounter++;
        while (line != "") {
            transform(line.begin(), line.end(), line.begin(), ::toupper);
            trim(line);
            spaceReplace(line);
            attr.insert(line);
            getline(input, line);
            lineCounter++;
        }
        input >> degOfCert;
        getline(input, line);
        lineCounter++;
        while (getline(input, line)) {
            lineCounter++;
            FuncDependency fd = FuncDependency(line);
            if (fd.isValid(attr)) {
                funcDep.insert(fd);
            }else{
                cout << "There is an FD on line " << lineCounter << " which contains an attribute not specified in the input attributes." << endl;
            }
            
        }
    
}

void recordMaximalForCertainty(vector<set<Attributes> > &maximalTable, vector<set<Attributes> > &attributeSetsByCert, int certainty){
    set<Attributes> setsForCert;
    for (auto it2 = maximalTable.begin(); it2 != maximalTable.end(); it2++) {
        for (auto it3 = it2->begin(); it3 != it2->end(); it3++) {
            Attributes temp = *it3;
            temp.setCertainty(certainty);
            setsForCert.insert(temp);
            
        }
    }
    attributeSetsByCert.push_back(setsForCert);
    
}

void SchemaReader::compMaximalSets(){
    //For every attribute, the sole attribute set is the whole attribute set
    vector<set<Attributes> > maximalTable;
    vector<Attributes> attribVect;
    vector<set<Attributes> > attributeSetsByCert;
    map<string,int> attrIntMap;
    int currentFDCert = funcDep.begin()->getCertainty();
    int counter = 0;
    for (auto it = attr.begin(); it != attr.end(); it++) {
        set<Attributes> temp;
        Attributes temp2 = attr;
        temp2.remove(*it);
        temp2.setCertainty(currentFDCert);
        temp.insert(temp2);
        Attributes temp3;
        temp3.insert(*it);
        temp3.setCertainty(currentFDCert);
        maximalTable.push_back(temp);
        attribVect.push_back(temp3);
        attrIntMap[*it] = counter;
        counter++;
        
    }
    set<FuncDependency> currentFDs;
    for (auto it = funcDep.begin(); it != funcDep.end(); it++) {
        
        if(currentFDCert < it->getCertainty()){
            recordMaximalForCertainty(maximalTable, attributeSetsByCert, currentFDCert);
            currentFDCert = it->getCertainty();
        }
        
        currentFDs.insert(*it);
        
        for (int i = 0; i < maximalTable.size(); i++) {
            set<Attributes> newMaximal = maximalTable[i];
            set<Attributes> tempMaximal = newMaximal;
            Attributes currentAttr = attribVect[i];
            
            for (auto it2 = newMaximal.begin(); it2 != newMaximal.end(); it2++) {
                
                //check to see if Fds in combination with newMaximal can find the current attribute
                Attributes clos = closure(attr,*it2,currentFDs,it->getCertainty());
                clos.setCertainty(currentFDCert);
                
                if(currentAttr.isSubset(clos)){
                    
                    //modify the new maximal
                    tempMaximal.erase(*it2);

                    //for every attribute in the antecedent FD added
                    for (auto it3 = it->getAnte().begin(); it3 != it->getAnte().end(); it3++) {

                        set<Attributes> possMod = maximalTable[attrIntMap[*it3]];
                        for (auto it4 = possMod.begin(); it4 != possMod.end(); it4++) {

                            //test to see whether the union implies the target attribute.
                            Attributes tempAttr = *it2;
                            tempAttr.intersect(*it4);
                            Attributes clos2 = closure(attr,tempAttr, currentFDs,it->getCertainty());
                            clos2.setCertainty(currentFDCert);
                            if(!currentAttr.isSubset(clos2)){
                                tempMaximal.insert(clos2);
                            }
                            
                        }
                    }
                    
                }
                
            }
            tempMaximal = ridOfSubsets(tempMaximal);
            set<Attributes> temptempMaximal;
            for (auto it9 = tempMaximal.begin(); it9 != tempMaximal.end(); it9++){
                Attributes tem = *it9;
                tem.setCertainty(currentFDCert);
                temptempMaximal.insert(tem);
            }
            maximalTable[i] = temptempMaximal;

        }
    }
    map<set<string>,int> seenBefore;
    set<Attributes> maxSets;
    for (auto it = maximalTable.begin(); it != maximalTable.end(); it++) {
        for(auto it2 = it->begin(); it2 != it->end(); it2++){
            if(seenBefore[it2->getString()] != 1){
                Attributes temp = *it2;
                temp.setCertainty(currentFDCert);
                maxSets.insert(temp);
            }
            seenBefore[it2->getString()] = 1;
        }
    }
    if(attributeSetsByCert.size()> 0){
        for (auto it = attributeSetsByCert.end()-1; it >= attributeSetsByCert.begin(); it--) {
            for (auto it2 = it->begin(); it2 != it->end(); it2++) {
                if(seenBefore[it2->getString()] != 1){
                    maxSets.insert(*it2);
                }
                seenBefore[it2->getString()] = 1;
            }
        }
    }
    vector<Attributes> maxVector;
    for (auto it = maxSets.begin(); it != maxSets.end(); it++) {
        maxVector.push_back(*it);
    }
    maximalSets = maxVector;
}




set<Attributes>& ridOfSubsets(set<Attributes> &temp){
    set<Attributes> tempCopy;
    for(auto it = temp.begin(); it != temp.end(); it++){
        tempCopy.insert(*it);
        for (auto it2 = it; it2 != temp.end(); it2++) {
            if(it->isSubset(*it2) && !(it->isEqual(*it2))){
                tempCopy.erase(*it);
            }
            
        }
    }
    temp = tempCopy;
    return temp;
}

void printSets(vector<set<Attributes> > &maximalTable){
    for (auto it = maximalTable.begin(); it != maximalTable.end(); it++) {
        //need to compare Attributes
        for(auto it2 = (*it).begin(); it2 != (*it).end(); it2++){
            cout << *it2 << endl;
        }
    }
}
string SchemaReader::tupleToString(int* currentSubValue){
    stringstream temp;
    int i = 0;
    for(auto it = attr.begin(); it != attr.end(); it++){
        temp << *it << "_" << currentSubValue[i++] << ", ";
    }
    temp << "alpha_" << currentSubValue[i] << endl;
    return temp.str();
}

void SchemaReader::removeFD(){
    int random = rand()%funcDep.size();
    auto it = funcDep.begin();
    advance(it, random);
    funcDep.erase(it);
}
int SchemaReader::calcArmstrong(ofstream &armstrongFile){
    
    //initialise the first tuple, all attr_0
    int armstrongCols = attr.size()+1;
    map<string,int> mapping;
    int counter =0;
    for (auto it = attr.begin(); it != attr.end(); it++) {
        mapping[*it] = counter++;
    }
    int* currentSubValue = new int[armstrongCols];
    int rowCounter = 0;
    for(int i = 0; i < armstrongCols-1; i++){
        currentSubValue[i] = 0;
    }
    currentSubValue[armstrongCols-1] = 1;   //first alpha value
    
    	//output row
    armstrongFile << tupleToString(currentSubValue);
    rowCounter++;
    
    //for every maximal set
    for(auto it = maximalSets.begin(); it != maximalSets.end(); it++){
        
        int possibility = it->getCertainty();
        
        //for every attribute in the table
        for (auto it2 = attr.begin(); it2 != attr.end(); it2++){
            
            //if it is not in the maximal set, change the value
            if(it->find(*it2) == it->end()){
                currentSubValue[mapping[*it2]]++;
            }
        }
        currentSubValue[armstrongCols-1] = degOfCert-possibility;
        armstrongFile << tupleToString(currentSubValue);
        rowCounter++;
    }
    delete[] currentSubValue;
    
    return rowCounter;
}

long SchemaReader::getFDSize(){
    return funcDep.size();
}

int SchemaReader::constrainedSize(){
    Attributes temp;
    for (auto fdit = funcDep.begin(); fdit != funcDep.end(); fdit++) {
        for (auto anteit = fdit->getAnte().begin(); anteit != fdit->getAnte().end(); anteit++) {
            temp.insert(*anteit);
        }
        for (auto cit = fdit->getConseq().begin(); cit != fdit->getConseq().end(); cit++) {
            temp.insert(*cit);
        }
    }
    return temp.size();
}