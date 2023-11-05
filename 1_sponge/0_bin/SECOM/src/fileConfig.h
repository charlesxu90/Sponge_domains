#pragma once
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string.h>
#define eps 0.0000001
using namespace std;



/*************************************************
  Copyright (C), 2011, King Abdullah University of Science and Technology.
  File name:      // clique.h
  Author:  Ming Fan     Version:       Date: // Dec.12, 2011
  Description:    // This file read the parameter from configuration file, and get
                  // parameters of SECOM. If users do not give a parameter, the default
				  // value are given. The whole protein sequences are then read
                  // from original fasta file. The special character such as 'X' or 'B' '*'
				  // are excluded.
				  // 
				  // 
  Others:         // 
  Function List:  //  void SetDefault(config& );
                      if users did not give their own parameter value, then a default value 
					  is set.
                  //  void copystr(char*, const char* ,  unsigned & );
				      copy one protein sequence
                  //  void printpos(unsigned* ,unsigned ,ofstream& );
				      print the hash seed into a file
                  //  void map_rec(record* , map<unsigned,record*>& );
				      build a map for sequence index
*************************************************/


// class information for input file name, length of hash seed, c1 or c2 type of hash seed
class config
{
public:
	string filename; //the name of input .fa file
	unsigned filelength; 
	unsigned window_len; // hash seed length
	string clust_type; // hash seed type
	double threshold;
	config();
};



// class of one protein 
class record
{
public:
	long index; //the index inside 
	char* str; // amino acids
	char* sourcestr; // 
	string headstr; //
	unsigned *position; // hash seed value
	class record *next;
	unsigned num_clu; 
};


// class for storage the sequences, mainly read, create and print 
class sequences
{
public:
	long index;
	config info; 
    sequences();
	void load();
	void read_configfile();
	unsigned count; // number of sequences that to be precessed
	record* head_ptr;
	void show(); // 
	void print();
	void insert_record(record*,record);	
	void delete_record(record* );
private:
	void create(record );
	void pushback(record );
	record* temporal_ptr;
};

//functions

void SetDefault(config& );

void copystr(char*, const char* ,  unsigned & );

void printpos(unsigned* ,unsigned ,ofstream& );

void map_rec(record* , map<unsigned,record*>& );