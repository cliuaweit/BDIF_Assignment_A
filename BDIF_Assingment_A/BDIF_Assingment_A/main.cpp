//
//  main.cpp
//  BDIF_Assingment_A
//
//  Created by Wei Liu on 2/3/15.
//  Copyright (c) 2015 Wei Liu. All rights reserved.
//

#include <iostream>
#include <string>
#include "Read_Record.h"
#include <map>
#include "Write_Record.h"
#include "NORMAL.h"

using namespace std;

int main()
{
    map<record_time, record_value> records;
    
    records = get_records("data10k.txt");
    
    
    write_records(records, "signal.csv");
    
    //normal_test("data10k.txt");
    
    return 0;
}










