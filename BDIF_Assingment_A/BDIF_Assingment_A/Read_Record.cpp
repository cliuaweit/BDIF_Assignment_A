//
//  Read_Record.cpp
//  BDIF_Assingment_A
//
//  Created by Wei Liu on 2/4/15.
//  Copyright (c) 2015 Wei Liu. All rights reserved.
//

#include "Read_Record.h"


record_time::record_time(std::string s)
{
    boost::char_separator<char> sep(":", ",");
    boost::tokenizer<boost::char_separator<char> > tokens(s, sep);
    
    boost::tokenizer<boost::char_separator<char> >::iterator it = tokens.begin();
    
    day = std::stol(*it);
    
    hour = std::stoi(*(++it));
    
    minute = std::stoi(*(++it));
    
    second = std::stof(*(++it));
    
}


bool operator < (const record_time & lhs_record_time, const record_time & rhs_record_time)
{
    if (lhs_record_time.day < rhs_record_time.day)
    {
        return true;
    }
    else if (lhs_record_time.day == rhs_record_time.day)
    {
        if (lhs_record_time.hour < rhs_record_time.hour)
        {
            return true;
        }
        else if (lhs_record_time.hour == rhs_record_time.hour)
        {
            if (lhs_record_time.minute < rhs_record_time.minute)
            {
                return true;
            }
            else if (lhs_record_time.minute == rhs_record_time.minute)
            {
                if (lhs_record_time.second < rhs_record_time.second)
                {
                    return true;
                }
            }
        }
    }
    
    return false;
    
}


std::ostream & operator << (std::ostream & os, const record_time & target)
{
    os << target.day << ":" << target.hour << ":" << target.minute << ":" << target.second << " ";
    
    return os;
}




record_value::record_value(std::string s)
:the_return(0.0)
{
    boost::char_separator<char> sep(",");
    boost::tokenizer<boost::char_separator<char> > tokens(s, sep);
    
    boost::tokenizer<boost::char_separator<char> >::iterator it = tokens.begin();
    
    the_price = std::stof(*(++it));
    
    the_volume = std::stoi(*(++it));
}


std::ostream & operator << (std::ostream & os, const record_value & target)
{
    os << "Price: " << target.the_price << " " << "Volume: " << target.the_volume << " ";
    os << "Return: " << target.the_return << std::endl;
    
    return os;
}



void get_return(std::map<record_time, record_value> & records)
{
    std::map<record_time, record_value>::iterator it = records.begin();
    
    for (; it != records.end(); it++)
    {
        if (it != records.begin())
        {
            record_value rv2 = it->second;
            record_value rv1 = (--it)->second;
            
            (++it)->second.the_return = (rv2.the_price - rv1.the_price)/rv1.the_price;
        }
    }
}


std::map<record_time, record_value> get_records(std::string filename)
{
    std::fstream file(filename);
    std::map<record_time, record_value> records;
    
    
    int i = 0;
    while (i != 9999)
    {
        std::string line;
        getline(file, line);
        
        record_time rt(line);
        record_value rv(line);
        
        records.insert(std::pair<record_time, record_value>(rt, rv));
        
        i++;
    }
    
    file.close();
    
    get_return(records);
    
    return records;
}


















