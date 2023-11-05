#pragma once
#include <set>
#include <list>
#include <map>
#include <iostream>
using namespace std;
/*************************************************
  Copyright (C), 2011, King Abdullah University of Science and Technology.
  File name:      // hash.h
  Author:  Ming Fan     Version:       Date: // Dec.12, 2011
  Description:    // This file defined class for clique 
  Others:         //
  Function List:  // 
   

*************************************************/


// a class for presenting cliques of size k. Realizations of this class just 
  //hold a sorted list of nodes in the clique
class kclique
{	
    public:
	kclique(const set<unsigned>&); //a clique 
	kclique(unsigned); // a clique with one node
	kclique(unsigned,unsigned); // a clique with two node
	
	list<set<unsigned> > getSubcliques();
	
	void add_clique(unsigned,unsigned);

	kclique operator + (const kclique&);
	kclique& operator+= (const kclique& clique);
	
	unsigned k; //size of the clique 
//	double intensity;
	set<unsigned> setit;
};




//clique size k-1 that form k cliques
class componetCique
{
public:
	unsigned* componet; //
	unsigned cliqueSize; //

	bool operator < (const componetCique& cC) const
	{
		for (unsigned  ix = 0; ix != cliqueSize; ++ix)
		{
			if (componet[ix] != cC.componet[ix])
			{
			   return componet[ix] < cC.componet[ix];
			}
		}
		return false;
	}
};


