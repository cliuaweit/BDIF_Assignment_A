//
//  main.cpp
//  BDIF_Assingment_A
//
//  Created by Wei Liu on 2/3/15.
//  Copyright (c) 2015 Wei Liu. All rights reserved.
//

#include <iostream>
#include <string>
#include "SCRUB.h"

using namespace std;

int main()
{
    
    scrub data_scrub;
    
    //read the data
    data_scrub.get_records("data10k.txt");
    
    //find outlier in price
    data_scrub.find_outlier(0);
    //find outlier in volume
    data_scrub.find_outlier(1);
    
    //write signals and noise to two different files
    data_scrub.write_records("signal", "noise");
    
    
    
    return 0;
}










