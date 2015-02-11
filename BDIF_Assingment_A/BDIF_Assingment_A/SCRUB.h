//
//  SCRUB.h
//  
//
//  Created by Wei Liu on 2/6/15.
//
//

#ifndef ____SCRUB__
#define ____SCRUB__


#include <iostream>
#include <string>
#include <vector>


typedef unsigned int SerialDate;
typedef float SerialTime;


//change in put date format to SerialDate
SerialDate YYYYMMDDToSerialDate(const std::string);


struct record
{
    //store the one line of record
    std::string one_record;
    
    //store date and time in serial form
    SerialDate date;
    SerialTime time;
    
    //store the price and the volume
    float price;
    int volume;
    
    //mark the data point as signal or noise. '0' is signal, '1' outlier, '2' duplicate
    int flag;
    
    //constructor
    record(const std::string &);
    
    //overload of "<<"
    friend std::ostream & operator << (std::ostream & os,
                                       const record & target);
};





class scrub
{
private:
    std::vector<record> records;
    
    
public:
    std::vector<record> get_records(std::string filename);
   
    
    //compare function for sort
    friend bool compare_time (const record & lhs, const record & rhs);
    friend bool compare_price (const record & lhs, const record & rhs);
    friend bool compare_volume (const record & lhs, const record & rhs);
  
    //sort records
    void time_sort();
    void price_sort();
    void volume_sort();
    
    
    //find the outliers, whose_flyer = 0 for price, whose_flyer = 1 for volume
    void find_outlier(int whose_flyer);
    
    
    //output the records
    friend std::ostream & operator << (std::ostream & os, const scrub & target);
    
    
    //write records
    void write_records(std::string signal_filename, std::string noise_filename);
};








#endif /* defined(____SCRUB__) */













