//
//  Read_Record.h
//  BDIF_Assingment_A
//
//  Created by Wei Liu on 2/4/15.
//  Copyright (c) 2015 Wei Liu. All rights reserved.
//

#ifndef __BDIF_Assingment_A__Read_Record__
#define __BDIF_Assingment_A__Read_Record__

#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/token_iterator.hpp>
#include <fstream>
#include <map>

struct record_time
{
    long day;
    int hour;
    int minute;
    float second;
    
    record_time(std::string);
    
    friend bool operator < (const record_time & lhs_record_time,
                            const record_time & rhs_record_time);
    
    friend std::ostream & operator << (std::ostream & os,
                                       const record_time & target);
};


struct record_value
{
    float the_price;
    float the_return;
    int the_volume;
    
    record_value(std::string);
    
    friend std::ostream & operator << (std::ostream & os,
                                       const record_value & target);
};



void get_return(std::map<record_time, record_value> & );


std::map<record_time, record_value> get_records(std::string);







#endif /* defined(__BDIF_Assingment_A__Read_Record__) */







