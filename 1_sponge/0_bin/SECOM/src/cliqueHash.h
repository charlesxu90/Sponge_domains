#pragma once
#include <cstdlib>
#include "clique.h"

using namespace std;

/*************************************************
  Copyright (C), 2011, King Abdullah University of Science and Technology.
  File name:      // clique.h
  Author:  Ming Fan     Version:       Date: // Dec.12, 2011
  Description:    // This file are mainly about k-clique generation and  percolation
                  
  Others:         //
  Function List:  // 

               1. bool filterMap(map<long,map<unsigned,unsigned> >& );
			   do statistical analysis of communities

               2. bool comparesize(const map<long,map<unsigned,unsigned> >& ,
			   const map<long,map<unsigned,unsigned> >& );
			   sort the clusters by their size  

               3. void cliqueCommunityCompare(multimap<unsigned,pair<unsigned,set<pSeed> > > &,
                   list<map<long,map<unsigned,unsigned> > >& ,double, double, unsigned);
				perform clique percolation and community merging process


               4. void compareCommunity(list<map<long,map<unsigned,unsigned> > >&,
                  map<unsigned,map<long,map<unsigned,unsigned> > >&, double, double);
				identify how many nodes are common for two communities

               5. bool mergeit(map<long,map<unsigned,unsigned> >&, map<long,map<unsigned,unsigned> >&,
                  double, double);
				merge two communities if they share nodes more than a threshold

               6. void mergMap(map<long,map<unsigned,unsigned> >&, map<long,map<unsigned,unsigned> >& );
			     added nodes in one community to another  

               7. void cliqueAndHash(multimap<unsigned,pair<unsigned,set<pSeed> > > &,
                 double, double, map<unsigned, map<long,map<unsigned,unsigned> > >&, unsigned & );
				 generate cliques from hash seeds

               8. bool findCommenSubClique(list<pair<componetCique,unsigned> >&,
                map<componetCique,unsigned>&, map<unsigned,map<long,map<unsigned,unsigned> > >&, unsigned);
				detect sub cliques 


              10. void getSubClique(set<pSeed> &, list<pair<componetCique,unsigned> > &,unsigned,unsigned );
			  get sub cliques for size larger than 2


              11. void getSubClique2(set<pSeed> &, list<pair<componetCique,unsigned> > &,unsigned );
			  get sub cliques for size equal to 2

              12. bool filterResult(map<long,map<unsigned,unsigned> >& );

    
              13. void compareself(list<map<long,map<unsigned,unsigned> > >& , double, double);
			  merge clusters

              14. void testvalue(unsigned *, unsigned, map<long,map<unsigned,unsigned> >& );


              15. void addCommunity(list<map<long,map<unsigned,unsigned> > >&,
                map<unsigned,map<long,map<unsigned,unsigned> > >&);
				append communities

*************************************************/


// one hash seed 
class pSeed
{
public:
	long index; //index of the hash seed
	unsigned pos; //position of the hash seed

	bool operator < (const pSeed& tpSeed) const
	{
		return index > tpSeed.index;
	}
};

 bool filterMap(map<long,map<unsigned,unsigned> >& );

 bool islarge(const  map<long,map<unsigned,unsigned> > & mapit,unsigned threshold);

 bool comparesize(const map<long,map<unsigned,unsigned> >& , const map<long,map<unsigned,unsigned> >& );

 void cliqueCommunityCompare(multimap<unsigned,pair<unsigned,set<pSeed> > > &sortClusIndex,
	 list<map<long,map<unsigned,unsigned> > >& listMap,
	 double threshold,  double times,  unsigned statpos);

 void compareSelf(map<unsigned,map<long,map<unsigned,unsigned> > > &mapit, 
	 double threshold, double times);

 void compareCommunity( list<map<long,map<unsigned,unsigned> > >&,
	map<unsigned,map<long,map<unsigned,unsigned> > >&, double, double);

 void compareCommunity(list<map<long,map<unsigned,unsigned> > >& listMap, 
	 list<map<long,map<unsigned,unsigned> > >& listMap2,
	 map<unsigned,map<long,map<unsigned,unsigned> > >& mapit,double threshold,double times);

 bool mergeit(map<long,map<unsigned,unsigned> >&, map<long,map<unsigned,unsigned> >&,
	double, double);

 void mergeMap(map<long,map<unsigned,unsigned> >&, map<long,map<unsigned,unsigned> >& );

 void cliqueAndHash(multimap<unsigned,pair<unsigned,set<pSeed> > > &,
	double, map<unsigned, map<long,map<unsigned,unsigned> > >&, unsigned & );

 bool findCommenSubClique(list<pair<componetCique,unsigned> >&,
	map<componetCique,unsigned>&, map<unsigned,map<long,map<unsigned,unsigned> > >&, unsigned);

// void mergeClique( unsigned, map<unsigned,map<long,map<unsigned,unsigned> > >& );

 void getSubClique(set<pSeed> &, list<pair<componetCique,unsigned> > &,unsigned,unsigned );

 void getSubClique2(set<pSeed> &, list<pair<componetCique,unsigned> > &,unsigned );

 bool filterResult(map<long,map<unsigned,unsigned> >& );


 void compareself(list<map<long,map<unsigned,unsigned> > >& , double, double);

 void testvalue(unsigned *, unsigned, map<long,map<unsigned,unsigned> >& );


 void addCommunity(list<map<long,map<unsigned,unsigned> > >&,
	 map<unsigned,map<long,map<unsigned,unsigned> > >&);
