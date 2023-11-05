//#pragma once
#include "fileConfig.h"
#include <queue>
/*************************************************
  Copyright (C), 2011, King Abdullah University of Science and Technology.
  File name:      // hash_method.h
  Author:  Ming Fan     Version:       Date: // Dec.12, 2011
  Description:    // 

  Others:         //
  Function List:  // 
					1. map<char,unsigned> str_num(const string& );
					map the 20 amino acids into 11 or 15 classes

					2. map<char,char> str_str(const string& );
					map the 20 amino acids into 11 or 15 classes, represented by strings

					3. int rerange(unsigned* , unsigned* ,unsigned );
					check whether a hit between others have a win_len distance, 
					in order to avoid the sliding window effect

					4. void compare_numhash(sequences& );
					Perform protein sequence index by hash seed method in whole sequence, 
					use integers as hash value

					5. void compare_strhash(sequences& );
					Perform protein sequence index by hash seed method in whole sequence, 
					use strings as hash value

					6. void ShowHashSeedDesnsity( sequences&  );
					calculated the average hash seed density of the whole sequence
*************************************************/

//this structure record position and index of hash seed

class hash_clus
{
public:
	record* rec; //pointer to one protein sequence
	unsigned clus; // index of hash seed
	unsigned pos; // position of amino acids
};



map<char,unsigned> str_num(const string& );

map<char,char> str_str(const string& );

 

int rerange(unsigned* , unsigned* ,unsigned );

void compare_numhash(sequences& );

void compare_strhash(sequences& );


void ShowHashSeedDesnsity(sequences&  );
