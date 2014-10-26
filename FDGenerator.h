//
//  FDGenerator.h
//  PossibilisticArmstrong
//
//  Created by Cinnamon Scudworth on 16/10/14.
//  Copyright (c) 2014 Cinnamon Scudworth. All rights reserved.
//

#ifndef __PossibilisticArmstrong__FDGenerator__
#define __PossibilisticArmstrong__FDGenerator__

#include <iostream>
#include <set>
#include <cstdlib>
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

stringstream FDgenerator(int n, int numFD, int certainty);
#endif /* defined(__PossibilisticArmstrong__FDGenerator__) */