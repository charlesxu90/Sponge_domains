// domain_finding.cpp : Defines the entry point for the console application.
//#include "stdafx.h"

//#include "testfile.h"
#include "hashMethod.h"
#include "CommunityFinding.h"
#include <ctime>

 

int  main( void )
{
 	// readfile();exit(0);
	// class for input sequence
	sequences segments;

	//read the input information 
	cout << "load configuration file ...."<<endl;
    // read the configuration file, load the length of the hash seeds, input sequence file name
	// type of hash seed, and so on
	segments.read_configfile();

	cout <<endl<< "load protein sequence ...."<<endl;
	//load the protein sequence
	segments.load();


	// define the length of hash seeds
    // unsigned wind_len = mak.window_len;

	// time for hash table
	clock_t clock_beg,clock_end;	
	clock_beg = clock();

	//
	//
	//The alternative way is to use function compare_numhash below. This function use 
	//integer as hash value, and can save more memory. However, I do not suggest you
	//using this function, be cause it can not process hash seed with length more than 8 in 
	// 32-bit computer
	//compare_numhash(segments);
	//

	cout << endl<< "begin hash seed for the whole protein sequence  "<<endl;

	compare_strhash(segments);

	ShowHashSeedDesnsity(segments);
	
	//////////////////////////////////////////////////////////
	// finish build hash table
	///////////////////////////////////////////////////////////
	 
	// segments.print(); 
	//////////////////////////////////////////////////////////
    //rec = segments.head_ptr;
	
    
    //findstrfortest(segments.head_ptr,"PF05729_1.txt","PF05729.out");
    //exit(0);
	 
	/////////////////////////////////////////////////////////
	// begin find the protein families
	/////////////////////////////////////////////////////////
	cout<<"begin the protein family detection method"<<endl;
	
	findCommonMaxSet(segments ); 

	clock_end = clock();

	cout << "Time elapsed for the max community finding is : " 
		<< double(clock_end - clock_beg)/CLOCKS_PER_SEC << " s"<< endl; 
	 
 
	return 0;
}

