//
//  Write_Record.cpp
//  BDIF_Assingment_A
//
//  Created by Wei Liu on 2/6/15.
//  Copyright (c) 2015 Wei Liu. All rights reserved.
//

#include "Write_Record.h"


void write_records(std::map<record_time, record_value> & records, std::string filename)
{
    std::ofstream results (filename);
    //std::ostream_iterator<double> out_it (results, ",");
    
    std::map<record_time, record_value>::iterator records_it = records.begin();
    
    for (; records_it != records.end(); records_it++) {
        record_time rt = records_it->first;
        record_value rv = records_it->second;
        
        results << std::to_string(rt.day) << ":" << std::to_string(rt.hour) << ":";
        results << std::to_string(rt.minute) << ":" << std::to_string(rt.second);
        results << "," << std::to_string(rv.the_price) << "," << std::to_string(rv.the_volume);
        results << "," << std::to_string(rv.the_return) << std::endl;
    }
    
    results.close();
}















