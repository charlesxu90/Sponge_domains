#pragma once
#include "fileConfig.h"
#include "cliqueHash.h"
#include <cmath>
#include <list>
#include <set>
using namespace std;

/*************************************************
  Copyright (C), 2011, King Abdullah University of Science and Technology.
  File name:      // hash.h
  Author:  Ming Fan     Version:       Date: // Dec.12, 2011
  Description:    //  
  Others:         //
  Function List:  // 
  
              1. void printMapList(const list<map<long,map<unsigned,unsigned> > >& );


              2. void findCommonMaxSet(sequences&   );

              3. void findItem(record*  ,const unsigned,multimap<unsigned,pair<unsigned,set<pSeed> > >& , 
              map<long,record*>&  );


              4. void printProteinFamilies( list<map<long,map<unsigned,unsigned> > >&, pieces&, map<long,record*>&);

              5. void copynum(unsigned*  , unsigned*  ,unsigned  );

              6. void copystring(long&  , map<unsigned,record*>&  ,sequences& , 
                 unsigned  , unsigned  ,unsigned*  ,char*  ,record*  );

              7. void printSegments( map<long,map<unsigned,unsigned> >&  ,unsigned  ,
                   unsigned  ,map<long,record*>&  , ofstream&  ,ofstream& );


              8. double square_error(unsigned*  ,double  , unsigned  );

              9. double mean(unsigned*  , unsigned  );

             10. void caldense(map<long,map<unsigned,unsigned> >&  ,double  ,unsigned  );

             11. void mergit(list<map<long,map<unsigned,unsigned> > >&  , set<unsigned>&  ,
                const pair<long,map<unsigned,unsigned> >&  );

             12. void printsize(const map<unsigned,unsigned>& ,ofstream& );

*************************************************/

class seedClus
{
public:

	bool operator< (const seedClus &a) const
	{
		unsigned ct = 0;
       for (set<unsigned>::iterator it = a.setit.begin(); it != a.setit.end(); ++it)
       {
		   if ( setit.find(*it) != setit.end())
		   {
			   ++ct;
			   if (ct == k)
			   {
				   return false;
			   }
		   }
		   else
		   {
			   return *setit.begin() < *it;
		   }
       }

	} 
	//seedClus(unsigned tmp):k(tmp){}
	set<unsigned> setit;
	unsigned k;
};




class hashPari
{
public:
	unsigned a,b;
	unsigned posa,posb;
	unsigned distant;
	bool operator < (const hashPari& t) const
	{
		if (a != t.a)
		{
			return a < t.a;
		}
		else
		{
			return b < t.b;
		}

	}
	hashPari():a(0),b(0),distant(0){}
};


class hashComp
{
public:
	unsigned a,b;
	unsigned posa,posb;
	unsigned distant;
	unsigned threshold;
	record* rec;
	bool operator < (const hashComp& hc) const
	{
		if ( a != hc.a )
		{
			return a < hc.a;
		}
		else
		{
			return b < hc.b;
		}
	}
};



void printMapList(const list<map<long,map<unsigned,unsigned> > >& );


void findCommonMaxSet(sequences&   );

void findItem(record*  ,const unsigned,multimap<unsigned,pair<unsigned,set<pSeed> > >& , 
 map<long,record*>&  );


void printProteinFamilies( list<map<long,map<unsigned,unsigned> > >&, sequences&, map<long,record*>&);

void copynum(unsigned*  , unsigned*  ,unsigned  );

void copystring(long&  , map<unsigned,record*>&  ,sequences& , 
	unsigned  , unsigned  ,unsigned*  ,char*  ,record*  );

void printSegments( map<long,map<unsigned,unsigned> >&  ,unsigned  ,
	unsigned  ,map<long,record*>&  , ofstream&  ,ofstream& );





double square_error(unsigned*  ,double  , unsigned  );

double mean(unsigned*  , unsigned  );

void caldense(map<long,map<unsigned,unsigned> >&  ,double  ,unsigned  );

void mergit(list<map<long,map<unsigned,unsigned> > >&  , set<unsigned>&  ,
	const pair<long,map<unsigned,unsigned> >&  );

void printsize(const map<unsigned,unsigned>& ,ofstream& );
