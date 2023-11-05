//#include "stdafx.h"
#include "cliqueHash.h"



/*************************************************
  Function:       // getSubClique
  Description:    // project  k-clique into  (k-1)-cliques 
  Calls:          // none
  Called By:      // void cliqueAndHash(multimap<unsigned,pair<unsigned,set<pSeed> > > & sortClusIndex,
                     double threshold, map<unsigned, map<long,map<unsigned,unsigned> > >& MapMap,
					 unsigned &statpos)
  Input:          // set<pSeed> &setpSeed
                     list<pair<componetCique,unsigned> > &listPari
					 unsigned mapClusNum
					 unsigned cliqueSize
                    
     
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void getSubClique(set<pSeed> &setpSeed, list<pair<componetCique,unsigned> > &listPari,
	unsigned mapClusNum,unsigned cliqueSize)
{

	for (set<pSeed>::iterator is = setpSeed.begin(); is != setpSeed.end(); ++is)
	{
		componetCique cC;

		unsigned ix = 0;
		cC.componet = new unsigned[cliqueSize]();

		if(cC.componet == NULL)
		{
			cout << " alloc failure " <<endl;
			exit(0);
		}

		for (set<pSeed>::iterator iss = setpSeed.begin(); iss != setpSeed.end(); ++iss)
		{
			if (is->index != iss->index)
			{
				cC.componet[ix] = iss->index;
				++ix;
			}
		}

		cC.cliqueSize = cliqueSize;
		listPari.push_back(make_pair(cC,mapClusNum));	
	}
}

/*************************************************
  Function:       // getSubClique2
  Description:    // project 2-clique into 2-clique 
  Calls:          //  none
  Called By:      //  void cliqueAndHash(multimap<unsigned,pair<unsigned,set<pSeed> > > & sortClusIndex,
                      double threshold, map<unsigned, map<long,map<unsigned,unsigned> > >& MapMap,
					  unsigned &statpos)
  Input:          //  set<pSeed> &setpSeed
                      list<pair<componetCique,unsigned> > &listPari
					  unsigned mapClusNum
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void getSubClique2(set<pSeed> &setpSeed, list<pair<componetCique,unsigned> > &listPari,
	unsigned mapClusNum)
{
	componetCique cC;
	cC.componet = new unsigned[2]();
		
	if(cC.componet == NULL)	
	{
		cout << " new node alloc failure " <<endl;
		exit(0);
	}
	
	unsigned ix = 0;	
	
	for (set<pSeed>::iterator is = setpSeed.begin(); is != setpSeed.end() && ix != 2; ++is,++ix)
	{
		cC.componet[ix] = is->index;
	}
	
	cC.cliqueSize = 2;
	listPari.push_back(make_pair(cC,mapClusNum));	
}







/*************************************************
  Function:       // findCommenSubClique
  Description:    //  
  Calls:          //  mergeMap
  Called By:      //  void cliqueAndHash(multimap<unsigned,pair<unsigned,set<pSeed> > > & sortClusIndex,
                      double threshold, map<unsigned, map<long,map<unsigned,unsigned> > >& MapMap,
					  unsigned &statpos)
					  
 Input:          //  list<pair<componetCique,unsigned> >& tmplist
					  map<componetCique,unsigned>& mapComponetClique
					  map<unsigned,map<long,map<unsigned,unsigned> > >& mapit
					  unsigned mapcluster 
                  //  
                  //  
  Output:         // 
  Return:         //  
  Others:     
*************************************************/
bool findCommenSubClique(list<pair<componetCique,unsigned> >& tmplist,
	map<componetCique,unsigned>& mapComponetClique,
	map<unsigned,map<long,map<unsigned,unsigned> > >& mapit,
	unsigned mapcluster)
{
	bool isfind = false;
	
	map<unsigned,map<long,map<unsigned,unsigned> > >::iterator kk = mapit.end();
	--kk;
	for (list<pair<componetCique,unsigned> >::iterator it = tmplist.begin();
		it != tmplist.end(); ++it)
	{
		map<componetCique,unsigned>::iterator tpit =
			mapComponetClique.find(it->first);
		if (tpit != mapComponetClique.end())
		{
			//mergclique(tpit->second, mapit);
			//ret.first->second.kcli = 
			mergeMap(mapit.find(tpit->second)->second,kk->second);
			mapit.erase(kk);
			mapcluster = tpit->second;
			isfind = true;
			break;
		}
	}
	for ( list<pair<componetCique,unsigned> >::iterator is = tmplist.begin();
		is != tmplist.end(); ++is)
	{
		mapComponetClique.insert(make_pair(is->first,mapcluster));
	}

    return isfind;
}



/*************************************************
  Function:       // cliqueAndHash
  Description:    //  
  Calls:          //  getSubClique
                      getSubClique2
					  findCommenSubClique
  Called By:      //  void cliqueAndHash(multimap<unsigned,pair<unsigned,set<pSeed> > > & sortClusIndex,
                      double threshold, map<unsigned, map<long,map<unsigned,unsigned> > >& MapMap,
					  unsigned &statpos)
					  cliqueCommunityCompare
					 
  Input:          //  multimap<unsigned,pair<unsigned,set<pSeed> > > & sortClusIndex
					  double threshold
					  map<unsigned, map<long,map<unsigned,unsigned> > >& MapMap
					  unsigned &startPos
                  //  
                  //  
  Output:         // 
  Return:         //  none
  Others:     
*************************************************/
void cliqueAndHash(multimap<unsigned,pair<unsigned,set<pSeed> > > & sortClusIndex,
	double threshold, map<unsigned, map<long,map<unsigned,unsigned> > >& MapMap,unsigned &startPos)
{                   //    cluster number, index number, position, seed   
	unsigned mapcluster = 0;
	map<componetCique,unsigned> mapComponetClique;

	pair<multimap<unsigned,pair<unsigned,set<pSeed> > >::iterator, multimap<unsigned,pair<unsigned,set<pSeed> > >::iterator>
		ret = sortClusIndex.equal_range(startPos);
	while (ret.first == ret.second)
	{
		--startPos;
		ret = sortClusIndex.equal_range(startPos);
	}


	unsigned tstatPos = startPos;
	if ( tstatPos != 2)
	{
		--tstatPos;
	}
	
	unsigned tp = sortClusIndex.count(startPos);
	//cout<<"the size of the original k clique "<<tp<<endl;

	for (; ret.first != ret.second; ++ret.first)
	{
	//every round process one seed.
	  
		list<pair<componetCique,unsigned> > listPair;
	 
 
		

		if ( tstatPos != 2)
		{
              getSubClique(ret.first->second.second,listPair,mapcluster, tstatPos);
		}
		else
		{
			  getSubClique2(ret.first->second.second,listPair,mapcluster);
		}
	    

		map<long,map<unsigned,unsigned> > mapit;
		for (set<pSeed>::iterator tp = ret.first->second.second.begin(); 
			tp != ret.first->second.second.end(); ++tp)
		{
			map<unsigned,unsigned> tmp;
			tmp.insert(make_pair(tp->pos, ret.first->second.first));
		 
			pair<map<long,map<unsigned,unsigned> >::iterator,bool> res =
			     mapit.insert(make_pair(tp->index,tmp));
		 
			if (res.second == false)
		    {
			     res.first->second.insert(make_pair(tp->pos,ret.first->second.first));
		    }
		}

		MapMap.insert(make_pair(mapcluster,mapit));

		if ( findCommenSubClique(listPair, mapComponetClique, MapMap, mapcluster) == false)
		{
			++mapcluster;
		}
       
	}      
}


/*************************************************
  Function:       // mergeMap
  Description:    //  
  Calls:          //  none
                      
  Called By:      //  cliqueCommunityCompare
					  mergeit
  Input:          //  map<long,map<unsigned,unsigned> >& mp1
                      map<long,map<unsigned,unsigned> >& mp2
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void mergeMap(map<long,map<unsigned,unsigned> >& mp1, map<long,map<unsigned,unsigned> >& mp2)
{

	for (map<long,map<unsigned,unsigned> >::iterator it = mp2.begin();
		it != mp2.end(); ++it)
	{

		pair<map<long,map<unsigned,unsigned> >::iterator, bool> ret
			= mp1.insert(make_pair(it->first,it->second));

		if (ret.second == false)
		{
			for (map<unsigned,unsigned>::iterator is = it->second.begin(); 
				is != it->second.end(); ++is)
			{
				ret.first->second.insert(make_pair(is->first,is->second));
			}
		}

	}
	// erase the last one;
}

/*************************************************
  Function:       // mergeit
  Description:    //  
  Calls:          //  mergeMap
                      
  Called By:      // compareself
					 compareCommunity
					 filterCommunity
  Input:          // map<long,map<unsigned,unsigned> >& mp1
                     map<long,map<unsigned,unsigned> >& mp2
					 double threshold
					 double times
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
bool mergeit(map<long,map<unsigned,unsigned> >& mp1, map<long,map<unsigned,unsigned> >& mp2,
	double threshold, double times)
{
	if (mp1.size() > times * mp2.size() || mp1.size() * times < mp2.size() || mp1.size() < 2 || mp2.size() < 2)
	{
		return false;
	}
    

	unsigned leastMach = 0;
	unsigned ct = 0;
	unsigned ct2  = 0;
	unsigned maches = 0;
	if (mp1.size() < mp2.size())
	{
		if (mp1.size() == 2)
		{
			leastMach = 0;
			maches = 2;
		}
		else
		{
            leastMach = int(mp1.size() * (1 - threshold) + 0.5);
		    maches = mp1.size() - leastMach;
		}
		
		for (map<long,map<unsigned,unsigned> >::iterator it = mp1.begin();
			it != mp1.end(); ++it)
		{
			if (mp2.find(it->first) == mp2.end())
			{
				++ct;
				if (ct == leastMach + 1)
				{
					return false;
				}
			}
			else
			{
				++ct2;
			
				if (ct2 == maches )
			    {
				    mergeMap(mp1,mp2);
				    return true;
			    }
			}
		}
	}
	else
	{
		if ( mp2.size() == 2)
		{
			leastMach = 0;
			maches = 2;
		}
		else
		{
	 		leastMach = int(mp2.size() * (1 - threshold) + 0.5);
			maches = mp2.size() - leastMach;
		}


		for (map<long,map<unsigned,unsigned> >::iterator it = mp2.begin();
			it != mp2.end(); ++it)
		{
			if (mp1.find(it->first) == mp1.end())
			{
				++ct;
				if (ct == leastMach + 1)
				{
					return false;
				}
			}
			else
			{
				++ct2;
				if (ct2 == maches)
				{
					mergeMap(mp1,mp2);
					return true;
				}

			}
		}
	}
	return false;
	cout << "error !" <<endl;
	exit(0);
	 
}



/*************************************************
  Function:       // compareCommunity
  Description:    //  
  Calls:          //  mergeit
                      
  Called By:      // cliqueCommunityCompare
  Input:          // list<map<long,map<unsigned,unsigned> > >& listMap
                     map<unsigned,map<long,map<unsigned,unsigned> > >& mapit
					 double threshold
					 double times  
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void compareCommunity( list<map<long,map<unsigned,unsigned> > >& listMap,
	map<unsigned,map<long,map<unsigned,unsigned> > >& mapit,double threshold, double times)
{
	for (map<unsigned,map<long,map<unsigned,unsigned> > >::iterator it = mapit.begin();
		it != mapit.end(); )
	{
		bool findit = false;
		for ( list<map<long,map<unsigned,unsigned> > >::iterator is = listMap.begin();
			is != listMap.end(); ++is)
		{
		  if (mergeit( *is, it->second, threshold, times) == true)
		  {
			   mapit.erase(it++); 
			  findit = true;
			  break;
		  }
		   
		}
		if (findit == false)
		{
			++it;
		}
		 
	}
 
}


/*************************************************
  Function:       // compareCommunity
  Description:    //  
  Calls:          //  mergeit
                      
  Called By:      // cliqueCommunityCompare
  Input:          // list<map<long,map<unsigned,unsigned> > >& listMap 
                     list<map<long,map<unsigned,unsigned> > >& listMap2
                     map<unsigned,map<long,map<unsigned,unsigned> > >& mapit
					 double threshold
					 double times  
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void compareCommunity(list<map<long,map<unsigned,unsigned> > >& listMap, 
	list<map<long,map<unsigned,unsigned> > >& listMap2,
	map<unsigned,map<long,map<unsigned,unsigned> > >& mapit,double threshold,double times)
{
 
	for (map<unsigned,map<long,map<unsigned,unsigned> > >::iterator it = mapit.begin();
		it != mapit.end(); )
	{
		bool findit = false;
		
		for ( list<map<long,map<unsigned,unsigned> > >::iterator is = listMap.begin();
			is != listMap.end(); ++is)
		{

			if (mergeit( *is, it->second, threshold, times) == true)
			{
				mapit.erase(it++); 
				findit = true;
				 
				break;
			}
		}
		if (findit == false)
		{
			for ( list<map<long,map<unsigned,unsigned> > >::iterator is2 = listMap2.begin();
				is2 != listMap2.end();++is2)
			{
				if (mergeit( *is2, it->second, threshold, times) == true)
				{
		
				    mapit.erase(it++);
				 	listMap.splice(listMap.end(),listMap2,is2); 
					findit = true;
					break;
				}

			}

			if (findit == false)
			{
				++it;
			}
		
		}

	}

}



/*************************************************
  Function:       // compareCommunity
  Description:    //  
  Calls:          // mergeit
                      
  Called By:      // cliqueCommunityCompare
  Input:          // map<unsigned,map<long,map<unsigned,unsigned> > > &mapit 
                     double threshold
					 double times  
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void compareSelf(map<unsigned,map<long,map<unsigned,unsigned> > > &mapit, 
	double threshold, double times)
{
 
	list<map<long,map<unsigned,unsigned> > > tmplist;

	unsigned clused = 0;
	unsigned oldclused = 0;
	unsigned oldsize = mapit.size();

	while( mapit.size() != 1)
	{
		unsigned oldsize = mapit.size();
		for (map<unsigned,map<long,map<unsigned,unsigned> > >::iterator it = mapit.begin();
			it != mapit.end();++it )
		{
			map<unsigned,map<long,map<unsigned,unsigned> > >::iterator is = it; ++is;
			for (;	is != mapit.end(); )
			{
				if (mergeit( it->second, is->second, threshold, times) == true)
				{
				    mapit.erase(is++); 
				 
				}
				else
				{
					++is;
				}
			}
		}
		if ( mapit.size() == oldsize)
		{
			return;
		}
	}

	
}

/*************************************************
  Function:       // filterResult
  Description:    //  
  Calls:          //  none
                      
  Called By:      // cliqueCommunityCompare
  Input:          // map<long,map<unsigned,unsigned> >& mapit  
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
bool filterResult(map<long,map<unsigned,unsigned> >& mapit)
{

	for (map<long,map<unsigned,unsigned> >::iterator it = mapit.begin();
		it != mapit.end(); )
	{
		if (it->second.size() < 2)
		{
			  mapit.erase(it++);
		}
		else
		{
			++it;
		}
	}
	if (mapit.size() < 2)
	{
		return true;
	}
    return false; 
}


/*************************************************
  Function:       // comparesize
  Description:    //  
  Calls:          // none
                      
  Called By:      // cliqueCommunityCompare
  Input:          //  const map<long,map<unsigned,unsigned> >& mp1
                      const map<long,map<unsigned,unsigned> >& mp2 
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
bool comparesize(const map<long,map<unsigned,unsigned> >& mp1,
	const map<long,map<unsigned,unsigned> >& mp2)
{
	return mp1.size() > mp2.size();
}


bool islarge(const  map<long,map<unsigned,unsigned> > & mapit,unsigned threshold)
{
	for ( map<long,map<unsigned,unsigned> >::const_iterator it = mapit.begin(); 
		it != mapit.end(); ++it)
	{
		if (it->second.size() > threshold)
		{
			return true;
		}
	}
	return false;
}



/*************************************************
  Function:       // cliqueCommunityCompare
  Description:    //  
  Calls:          // cliqueAndHash
                     filterResult
                     compareSelf
					 compareCommunity
					 filterResult
					 addCommunity

  Called By:      // findCommonMaxSet
  Input:          // multimap<unsigned,pair<unsigned,set<pSeed> > > &sortClusIndex
                     list<map<long,map<unsigned,unsigned> > >& listMap,
                     double threshold
					 double times
					 unsigned statpos  
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void cliqueCommunityCompare(multimap<unsigned,pair<unsigned,set<pSeed> > > &sortClusIndex,
	list<map<long,map<unsigned,unsigned> > >& listMap,
	 double threshold,  double times,  unsigned statpos)
{
   
	list<map<long,map<unsigned,unsigned> > > listMap2;


	for( ; statpos > 1; --statpos)
	{
		map<unsigned,map<long,map<unsigned,unsigned> > > mapit;
		cliqueAndHash(sortClusIndex, threshold,mapit,statpos);
		cout<<"start pos "<<statpos; 
	//	cout<<"start pos "<<statpos<<endl;
	//	cout<<"map size before refine "<<mapit.size();

		if (statpos < 5)
		{
			for (map<unsigned,map<long,map<unsigned,unsigned> > >::iterator it = mapit.begin();
				it != mapit.end(); )
			{

				if ( filterResult(it->second) == false)
				{
					++it;
				}
				else
				{
					mapit.erase(it++);
				}

			}
		}
			
    //	cout<<"map size after refine "<<mapit.size()<<endl;
	//	cout<<"the size of the Map "<<mapit.size()<<" and the listMap "<<listMap.size()<<endl;
	 	compareSelf(mapit,threshold,times);

		//if the community are large enough, we can put it directly into the listMap 
		
	
        compareCommunity(listMap,listMap2,mapit,threshold,times);

		//filtCommunity(listMap,threshold);

		unsigned ct = 0;
		//change 5 into 20
		if ( statpos < 5 )
		{
			for (list<map<long,map<unsigned,unsigned> > >::iterator ik = listMap.begin();
				ik != listMap.end(); )
			{

				if ( filterResult(*ik) == false)
				{
					++ik;
				}
				else
				{
					ik = listMap.erase(ik);
				}
			}
		}
	
		//sort list by descending order
		listMap.sort(comparesize);

		cout<<" size  "<<listMap.size() <<endl;

		addCommunity(listMap2,mapit);	
		listMap2.sort(comparesize);


	}
	unsigned ct = 0;
     cout<<"community 2 "<<listMap2.size()<<endl;
	//splitMap();
	for(list<map<long,map<unsigned,unsigned> > >::iterator ik = listMap2.begin();
		ik != listMap2.end(); )
	{
		if (filterMap(*ik) == true || islarge(*ik,5) == false)
		{
			ik = listMap2.erase(ik);
		}
		else
		{
			++ik;
		}
	}
	  cout<<"community 2 "<<listMap2.size()<<endl;
	//
	
	 compareself(listMap2,threshold,times);
	 listMap.splice(listMap.end(),listMap2);
//	cout<<"the last one "<<listMap.size()<<endl;
	 
}
 


/*************************************************
  Function:       // compareself
  Description:    //  
  Calls:          // mergeit
  
  Called By:      // cliqueCommunityCompare
  Input:          // list<map<long,map<unsigned,unsigned> > >& listMap
                     double threshold
					 double times  
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void compareself(list<map<long,map<unsigned,unsigned> > >& listMap,double threshold,double times)
{
	unsigned tmp = 0;
	unsigned oldtmp = 0;
	while( listMap.size() > 1 )
	{
		tmp = oldtmp;
		for ( list<map<long,map<unsigned,unsigned> > >::iterator it = listMap.begin();
			it != listMap.end(); ++it)
		{
			list<map<long,map<unsigned,unsigned> > >::iterator is = it; ++is;
			for ( ; is != listMap.end(); )
			{
				if (mergeit( *it, *is, threshold, times) == true)
				{
					is = listMap.erase(is);
					++tmp;
				}
				else
				{
					++is;
				}
			}
		}
		if ( tmp == oldtmp)
		{
			break;
		}
		 
	}
	
}


 /*************************************************
  Function:       // filterMap
  Description:    //  
  Calls:          // testvalue
  
  Called By:      // cliqueCommunityCompare
  Input:          //  map<long,map<unsigned,unsigned> >& mapit 
                  //  
                  //  
  Output:         // 
  Return:         // 
  Others:     
*************************************************/
 bool filterMap(map<long,map<unsigned,unsigned> >& mapit)
 {
	 unsigned *tmp = new unsigned[mapit.size()]();
	 if(tmp == NULL)
	 {
		 cout << "malloc error!" <<endl;
		 exit(0);
	 }
	 unsigned ix = 0;
	 unsigned times = 5;
	 for (map<long,map<unsigned,unsigned> >::iterator it = mapit.begin();
		 it != mapit.end(); )
	 {

		 if (it->second.size() == 1)
		 {
			 //it = mapit.erase(it);
			 ++it;
			 continue;
		 }
		 else if ( it->second.size() == 2)
		 {
			 map<unsigned,unsigned>::iterator is = it->second.begin();

			 unsigned oldpos = is->first;

			 ++is;

			 if (is->first > oldpos && is->first - oldpos > 80)
			 {
				 mapit.erase(it++);
			 }
			 else
			 {
				 //processDis();
				 tmp[ix] = it->second.size();
				 ++ix;
				 ++it;
			 }	
		 }
		 else
		 {
			 tmp[ix] = it->second.size();
			 ++ix;
			 ++it;
		 }		
	 }
	 if (ix > 1)
	 {
		 if ( mapit.size()== 2)
		 {
			 map<long,map<unsigned,unsigned> >::iterator it = mapit.begin();
			 map<long,map<unsigned,unsigned> >::iterator is = it; ++is;
			 if( it->second.size() > is->second.size() * times || 
				 it->second.size() * times < is->second.size())
			 {
				 return true;
			 }
		 }
		 else
		 {
			 testvalue(tmp,ix,mapit);
		 }

	 }
	 else
	 {
		 return true;
	 }

	 for (map<long,map<unsigned,unsigned> >::iterator it = mapit.begin();
		 it != mapit.end(); )
	 {

		 if (it->second.size() == 1 || it->second.size() == 0)
		 {
			 mapit.erase(it++);
		 }
		 else
		 {
			 ++it;
		 }		
	 }



	 if ( mapit.size() > 1)
	 {
		 return false;
	 }
	 else
	 {
		 return true;
	 }



 }
 
  /*************************************************
  Function:       // mean
  Description:    //  
  Calls:          // none
  
  Called By:      // testvalue
  Input:          // unsigned* values
                     unsigned n  
                  //  
                  //  
  Output:         // 
  Return:         // mean value of vector
  Others:     
*************************************************/
 double mean(unsigned* values, unsigned n)
 {
	 double value = 0;

	 for (unsigned ix = 0; ix != n; ++ix)
	 {
		 value = value + values[ix];
	 }
	 return value/n;

 } 
 double square_error(unsigned* values,double mvalue, unsigned n)
 {
	 double value = 0;
	 for (unsigned ix = 0; ix != n; ++ix)
	 {
		 value = value + (int(values[ix]) - mvalue)*(int(values[ix]) - mvalue);
	 }
	 return value;
 }
 

  /*************************************************
  Function:       // testvalue
  Description:    //  
  Calls:          // mean
  
  Called By:      // filterMap
  Input:          // unsigned *values
                     unsigned n
                     map<long,map<unsigned,unsigned> >& mapit 
                  //  
                  //  
  Output:         // 
  Return:         // 
  Others:     
*************************************************/
 void testvalue(unsigned *values,unsigned n,map<long,map<unsigned,unsigned> >& mapit)
 {
	 double meanv = mean(values,n);
	 //unsigned se = square_error(values,meanv,n);
	 //double std = sqirt(se);
	 //double xishu = n/sqrt(double(se));
	 map<long,map<unsigned,unsigned> >::iterator it = mapit.begin();

	 for (unsigned ix  = 0; ix != n && it != mapit.end(); ++ix)
	 {
		 /*if (2 * values[ix] < meanv || values[ix] > meanv * 2 )*/
		 if( 3 * it->second.size() < meanv || it->second.size() > meanv * 3)
		 {
			 mapit.erase(it++);
		 }
		 else
		 {
			 ++it; 
		 }
	 }

 }

  /*************************************************
  Function:       // addCommunity
  Description:    //  
  Calls:          // none
  
  Called By:      // cliqueCommunityCompare
  Input:          // list<map<long,map<unsigned,unsigned> > >& listMap
                     map<unsigned,map<long,map<unsigned,unsigned> > >& mapit  
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
 void addCommunity(list<map<long,map<unsigned,unsigned> > >& listMap,
	 map<unsigned,map<long,map<unsigned,unsigned> > >& mapit)
 {
	 for (map<unsigned,map<long,map<unsigned,unsigned> > >::iterator it = mapit.begin();
		 it != mapit.end(); ++it)
	 {
		 listMap.push_back(it->second);
	 }
 }
