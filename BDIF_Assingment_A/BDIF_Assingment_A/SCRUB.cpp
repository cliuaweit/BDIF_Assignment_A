//
//  SCRUB.cpp
//  
//
//  Created by Wei Liu on 2/6/15.
//
//


#include <iostream>
#include "SCRUB.h"
#include <boost/tokenizer.hpp>
#include <boost/token_iterator.hpp>
#include <fstream>



record::record(const std::string & s)
:one_record(s), flag(0)
{
    date = YYYYMMDDToSerialDate(one_record.substr(0, 8));
    
    time = std::stof(one_record.substr(9,2)) * 3600.0 + std::stof(one_record.substr(12,2)) * 60.0 + std::stof(one_record.substr(15,9));
    
    boost::char_separator<char> sep(",");
    boost::tokenizer<boost::char_separator<char> > tokens(s, sep);
    boost::tokenizer<boost::char_separator<char> >::iterator it = tokens.begin();
    
    price = std::stof(*(++it));
   
    volume = std::stoi(*(++it));
}



SerialDate YYYYMMDDToSerialDate(const std::string date)
{
    char yyyy[5];
    char mm[3];
    char dd[3];
    
    yyyy[0] = date[0]; yyyy[1] = date[1]; yyyy[2] = date[2]; yyyy[3] = date[3]; yyyy[4] = '\n';
    mm[0] = date[4]; mm[1] = date[5]; mm[2] = '\n';
    dd[0] = date[6]; dd[1] = date[7]; dd[2] = '\n';
    
    int y = atoi(yyyy);
    int m = atoi(mm);
    int d = atoi(dd);
    
    int a = (14 - m) / 12;
    int b = m + 12 * a - 3;
    int c = y + 4800 - a;
    
    return d + (153 * b + 2) / 5 + 365 * c + c / 4 - c / 100 + c / 400 - 32045 - 2415019;
}




std::ostream & operator << (std::ostream & os, const record & target)
{
    os << target.one_record;
    return os;
}



std::vector<record> scrub::get_records(std::string filename)
{
    std::fstream file(filename);
    
    int i = 0;
    while (i != 999)
    {
        std::string line;
        getline(file, line);
        
        record one_record(line);
        
        records.push_back(one_record);
        
        i++;
    }
    
    file.close();
    
    //std::sort(records.begin(), records.end(), compare);
    
    return records;
}



bool compare_time (const record & lhs, const record & rhs)
{
    if (lhs.date < rhs.date)
    {
        return true;
    }
    else if (lhs.date > rhs.date)
    {
        return false;
    }
    else
    {
        if (lhs.time < rhs.time) {
            return true;
        }
        else
        {
            return false;
        }
    }
}

    
bool compare_price (const record & lhs, const record & rhs)
{
    return lhs.price < rhs.price;
}



bool compare_volume (const record & lhs, const record & rhs)
{
    return lhs.volume < rhs.volume;
}


void scrub::time_sort()
{
    std::sort(records.begin(), records.end(), compare_time);
}


void scrub::price_sort()
{
    std::sort(records.begin(), records.end(), compare_price);
}


void scrub::volume_sort()
{
    std::sort(records.begin(), records.end(), compare_volume);
}



void scrub::find_outlier(int whose_flyer)
{
    unsigned long center = records.size()/2;
    unsigned long first_quantile = records.size()/4;
    unsigned long second_quantile = records.size()/4*3;
    
    if (whose_flyer == 0)
    {
        price_sort();
        
        float median = records[center].price;
        float Q1 = records[first_quantile].price;
        float Q3 = records[second_quantile].price;
        float IQR = Q3 - Q1;
        
        
        float lower_bound = median - 1.5 * IQR;
        float upper_bound = median + 1.5 * IQR;
        
        for (int i = 0; i < records.size(); i++)
        {
            if (records[i].price < lower_bound || records[i].price > upper_bound)
            {
                records[i].flag = 1;
            }
        }
    }
    else if (whose_flyer == 1)
    {
        {
            volume_sort();
            
            float median = records[center].volume;
            float Q1 = records[first_quantile].volume;
            float Q3 = records[second_quantile].volume;
            float IQR = Q3 - Q1;
            
            float lower_bound = median - 1.5 * IQR;
            float upper_bound = median + 1.5 * IQR;
            
            for (int i = 0; i < records.size(); i++)
            {
                if (records[i].volume < lower_bound || records[i].volume > upper_bound)
                {
                    records[i].flag = 1;
                }
            }
        }
    }
}




std::ostream & operator << (std::ostream & os, const scrub & target)
{
    for (int i = 0; i < target.records.size(); i++)
    {
        os << target.records[i] << " " << target.records[i].flag << std::endl;
    }
    
    return os;
}




    
void scrub::write_records(std::string signal_filename, std::string noise_filename)
{
    std::ofstream signal(signal_filename);
    std::ofstream noise(noise_filename);
    
    for (int i = 0; i < records.size(); i++) {
        if (records[i].flag == 0)
        {
            signal << records[i].one_record << std::endl;
        }
        else
        {
            noise << records[i].one_record << std::endl;
        }
    }
    
    signal.close();
    noise.close();
}




































