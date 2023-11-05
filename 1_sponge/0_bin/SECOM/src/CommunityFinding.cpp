//#include "stdafx.h"
#include "CommunityFinding.h"

/************************************************************
  Copyright (C), 2011, King Abdullah University of Science and Technology..
  FileName: hash_method.cpp
  Author:        Version :          Date:
  Description:     //    
  Version:         //  
 
***********************************************************/

 


 

  /*************************************************
  Function:       // findrepeat
  Description:    // if hash seeds in one sequences are repeated more 
                     than given times, than this sequence should be break 
  Calls:          // none
  
  Called By:      // cliqueCommunityCompare
  Input:          // unsigned* pos 
                     unsigned seed
					 unsigned sequenceLens
					 unsigned times
                  //  
                  //  
  Output:         // 
  Return:         // 
  Others:     
*************************************************/
bool findrepeat(unsigned* pos, unsigned seed,unsigned sequenceLens, unsigned times)
{
	unsigned ct = 0;
	for (unsigned ix = 0; ix != sequenceLens; ++ix )
	{
		if (pos[ix] == seed)
		{
			++ct;
			if (ct > times)
			{
				return true;
			}
		}
	}
	return false;
}

 /*************************************************
  Function:       // findItem
  Description:    // 
  Calls:          // copynum
                     findrepeat

  Called By:      // findCommonMaxSet
  Input:          // record* recHead
                     const unsigned win_len
                     multimap<unsigned,pair<unsigned,set<pSeed> > >& sortclusIndex
					 map<long,record*>& mapit 
 
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void findItem(record* recHead,const unsigned win_len,
	multimap<unsigned,pair<unsigned,set<pSeed> > >& sortclusIndex,  map<long,record*>& mapit)
{

	record* rec;

	map<hashPari,unsigned> hashPairMap;
	map<unsigned,map<unsigned,unsigned> > netit;

	multiset<hashComp> disHashSet;
	map<unsigned,set<pSeed> > mapclus;

	long oldindex ;
	unsigned ct = 0;

 	
	set<long> setit;
	
	for ( rec = recHead ; rec != NULL; rec = rec->next)
	{
		setit.insert(rec->index);
	
		mapit.insert(make_pair(rec->index,rec));
	}

	

	bool findit = false;
	
	for (rec = recHead; rec != NULL; rec = rec->next)
	{
		unsigned rec_len = strlen(rec->str);
	
		unsigned tmppos = 0;
		unsigned oldpos = 0;
	    
 
		if (findit == false)
		{
			oldindex = rec->index;
		}
		else
		{
			findit = false;
		}
		unsigned lens = strlen(rec->str);
		for (unsigned k = 0; k != lens; ++k)
		{
			if (rec->position[k] == 0)
			{
				continue;
			}  
			tmppos = k;

			oldpos = tmppos;

			pSeed tmppSeed;
			//tmppSeed.clus = rec->position[k];
			tmppSeed.index = rec->index;
			tmppSeed.pos = k;
	
			set<pSeed> tmpsetpSeed;
			tmpsetpSeed.insert(tmppSeed);
			
			pair<map<unsigned,set<pSeed> >::iterator,bool> retit = 
				mapclus.insert(make_pair(rec->position[k],tmpsetpSeed));
			
			if (retit.second == false)
			{
				pair<set<pSeed>::iterator,bool> retretit = 
				retit.first->second.insert(tmppSeed);
				
				if (retretit.second == false)
				{
					 if ( findrepeat(rec->position,rec->position[k],lens,100) == false)
				     {
						continue;
			 	     }
					 record r1;
					 long index = rec->index;
					 ++index;
					 while(setit.find(index) != setit.end() )
					 {
						 ++index;
					 }
					 r1.index = index;
					 r1.headstr = rec->headstr;
					 setit.insert(index);
					 //mapit.insert(make_pair(index,oldindex));

					 //unsigned endpos = strlen(rec->str);
					 unsigned endpos = rec_len;

					 //r1.position = new unsigned[endpos - k]();
					 r1.position = new unsigned[endpos]();
					 if(r1.position == NULL)
					 {
						 cout << "malloc error!" <<endl;
						 exit(0);
					 }
					 //copynum(r1.position, rec->position + k, endpos - k);
					 copynum(r1.position + k, rec->position + k , endpos - k);
					 //r1.str = new char[endpos - k + 1]();
					 r1.str = new char[endpos+1]();
					 if(r1.str == NULL)
					 {
						 cout << "malloc error!" <<endl;
						 exit(0);
					 }
					 //strncpy(r1.str, rec->str + k, endpos - k);
					 strncpy(r1.str,rec->str,endpos);
					 //r1.str[endpos - k] = '\0';
					 r1.str[endpos] = '\0';


					 record *tmp = new record(r1);

					 if(tmp == NULL)
					 {
						 cout << "malloc error!" <<endl;
						 exit(0);
					 }
					 tmp->next = rec->next;
					 rec->next = tmp;


					 mapit.insert(make_pair(index,tmp));

					 rec->str[k] = '\0';
					 for (unsigned ix = k; ix != endpos; ++ix)
					 {
						 rec->position[ix] = 0;
					 }
					 findit = true;
					 break;
				}
			}
		}//end rec index

	}

	//cout<<" mapclus: "<<mapclus.size()<<endl;


	for (map<unsigned,set<pSeed> >::iterator it = mapclus.begin(); it != mapclus.end(); ++it)
	{
		sortclusIndex.insert(make_pair(it->second.size(),make_pair(it->first,it->second)));
	}
}


  
 


 /*************************************************
  Function:       // compareit
  Description:    //  
  Calls:          // none
  
  Called By:      // splitMap
  Input:          // set<unsigned> &set1
                     set<unsigned>& set2
                    
  Output:         // 
  Return:         // none 
  Others:     
*************************************************/
bool compareit(set<unsigned> &set1, set<unsigned>& set2)
{
	unsigned ct = 0;
	for (set<unsigned>::iterator it = set1.begin();it != set1.end(); ++it)
	{
		if ( set2.find(*it) != set2.end())
		{
			++ct;
			if (ct == 3)
			{
				for (set<unsigned>::iterator ik = set2.begin(); ik != set2.end(); ++ik)
				{
					set1.insert(*ik);
				}
				return true;
			}
		}
	}
	return false;
}


 /*************************************************
  Function:       // splitMap
  Description:    //  
  Calls:          // compareit
  
  Called By:      // findCommonMaxSet
  Input:          // list<map<long,map<unsigned,unsigned> > >& listMap
       
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void splitMap(list<map<long,map<unsigned,unsigned> > >& listMap)
{
	
	for (list<map<long,map<unsigned,unsigned> > >::iterator it = listMap.begin();
		it != listMap.end(); /*++it*/)
	{
		if (it->size() == 2)
		{
			++it;
			continue;
		}
		
		list<map<long,map<unsigned,unsigned> > > tmplistMap;
		list<set<unsigned> > listSet;
		
		for (map<long,map<unsigned,unsigned> >::iterator is = it->begin();
			is != it->end(); ++is)
		{
			set<unsigned> tmpSet;
			for (map<unsigned,unsigned>::iterator ik = is->second.begin();
				ik != is->second.end(); ++ik)
			{
				tmpSet.insert(ik->second);
			}
		   map<long,map<unsigned,unsigned> > tmpMap;
		   tmpMap.insert(make_pair(is->first,is->second));
		   tmplistMap.push_back(tmpMap);
		   listSet.push_back(tmpSet);
		}


		//clustering
		list<map<long,map<unsigned,unsigned> > >::iterator ii,jj;
		list<set<unsigned> >::iterator kk, ll;
		int t=0;	
		
		while(tmplistMap.size() != 1)
		{
			 
		    unsigned oldsize = tmplistMap.size();
			ii = tmplistMap.begin();
			kk = listSet.begin();
			for ( ;ii != tmplistMap.end(); ++ii,++kk )
			{

				jj = ii; ++jj;
				ll = kk; ++ll;
				for ( ; jj != tmplistMap.end();  )
				{
					if (compareit(*kk,*ll) == true)
					{
						mergeMap(*ii,*jj);
						jj = tmplistMap.erase(jj);
						ll = listSet.erase(ll);
					}
					else
					{
						++jj; ++ll;
					}
				}
			}
			if ( tmplistMap.size() == oldsize )
			{
				break;
			}
			 
		}
	
		if (  tmplistMap.size() > 1)
		{
			it = listMap.erase(it);
			listMap.splice(it,tmplistMap);
		}
		else
		{
			++it;
		}
	 
	}

}


 


/*************************************************
  Function:       // caldense
  Description:    //  
  Calls:          // none
  
  Called By:      // findCommonMaxSet
  Input:          // map<long,map<unsigned,unsigned> >& mapit
                     double threshold
					 unsigned win_len  
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void caldense(map<long,map<unsigned,unsigned> >& mapit,double threshold,unsigned win_len)
{
	for (map<long,map<unsigned,unsigned> >::iterator it = mapit.begin();
		it != mapit.end();  )
	{
		map<unsigned,unsigned>::iterator is = it->second.begin();
		unsigned sta = is->first; unsigned t1 = is->second;
		is = it->second.end();
		--is; unsigned ed = is->first;unsigned t2 = is->second;

		if (ed < sta)
		{
			++it;//
			continue;
		}

		if ( it->second.size()* double(win_len) < (ed - sta)*threshold )
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
  Function:       // printsize
  Description:    //  
  Calls:          // none
  
  Called By:      // printProteinFamilies
  Input:          // const map<unsigned,unsigned>& mapit
                     ofstream& outsize 
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void printsize(const map<unsigned,unsigned>& mapit,ofstream& outsize)
{
	outsize << "Cluster size    No. of clusters"<<endl;
	for (map<unsigned,unsigned>::const_iterator it = mapit.begin();
		it != mapit.end(); ++it)
	{
		outsize <<it->first<<"\t"<<it->second<<endl;
	}
}

  /*************************************************
  Function:       // printProteinFamilies
  Description:    //  
  Calls:          // printSegments
                     printsize
  
  Called By:      // findCommonMaxSet
  Input:          // list<map<long,map<unsigned,unsigned> > >& listMap
                     sequences& segments, map<long,record*>& mapRec 
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void printProteinFamilies( list<map<long,map<unsigned,unsigned> > >& listMap,
	sequences& segments, map<long,record*>& mapRec)
{
//	unsigned ct = 0;
	unsigned cluster = 0;
	unsigned win_len = segments.info.window_len;
	cout<<"the size of the MapList: "<<listMap.size()<<endl;	
	
	const string filename = segments.info.filename;
	
	string outfilename = filename + ".Result.out";
	ofstream outfile(outfilename.c_str());

//	outfilename = filename + ".statResut.out";
//	ofstream outfileStat(outfilename.c_str());

        outfilename = filename + ".clus";
	ofstream outinf(outfilename.c_str());

	outfilename = filename + ".size";
	ofstream outsize(outfilename.c_str());

	map<unsigned,unsigned> mapit;

 
	double bsum = 0.0; 
	unsigned bsize = 0;
	unsigned ct = 0;
	
	for (list<map<long,map<unsigned,unsigned> > >::iterator it = listMap.begin();
		it != listMap.end(); ++it)
	{
		++ct;
		outinf << "cluster "<<ct <<endl;
		outinf << "size "<<it->size();

		++mapit[it->size()];
	    
		++cluster;
		printSegments(*it,cluster,win_len,mapRec, outfile,outinf);
		outfile<<"------------------------------------------------------------------------------------"<<endl;
		outfile<<"------------------------------------------------------------------------------------"<<endl;
		
		double asum = 0.0;
		for (map<long,map<unsigned,unsigned> >::iterator ik = it->begin();
			ik != it->end(); ++ik )
		{
			map<unsigned,unsigned>::iterator ij = ik->second.begin(); 
			map<unsigned,unsigned> ::reverse_iterator ii = ik->second.rbegin();
		
			double tmp = ik->second.size()*win_len/double(ii->first - ij->first);
			asum = asum + tmp;
		//	bsum = bsum + tmp;
		}
		asum = asum/double(it->size());
	//	bsize = bsize + it->size();
		outinf <<" confidence "<< asum <<endl;

	// 	outfileStat<<it->size()<<" "<<asum<< endl;
	}		
//	cout << "mean density is "<<bsum/double(bsize)<<endl;
	
	printsize(mapit,outsize);
	
//	outfileStat.clear(); 
//	outfileStat.close();
	
	outinf.clear(); 
	outinf.close();
	
	outfile.clear(); 
	outfile.close();

	outsize.clear();
	outsize.close();
}

 

  /*************************************************
  Function:       // printSegments
  Description:    //  
  Calls:          // printpos
  
  Called By:      // printProteinFamilies
  Input:          // map<long,map<unsigned,unsigned> >& mapit
                     unsigned cluster
                     unsigned win_len,map<long,record*>& map_str
					 ofstream& outfile
					 ofstream& outinf
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void printSegments( map<long,map<unsigned,unsigned> >& mapit,unsigned cluster,
	unsigned win_len,map<long,record*>& map_str, ofstream& outfile, ofstream& outinf)
{

	
	map<long,record*>::iterator map_it;

	map<long,map<unsigned,unsigned> >::iterator it;
	outfile<<"cluster num: "<<cluster<<" size: "<<mapit.size()<<endl;
	long ct = 0;
	
	unsigned tt = 0;
	double asum = 0.0;
	for (it = mapit.begin(); it != mapit.end(); ++it)
	{
		map<unsigned,unsigned>::iterator is = it->second.begin();
		unsigned stapos = is->first;
		//if (stapos < 2 * win_len)
		//{
		//	stapos = 0;
		//}
		is = it->second.end();
		--is;
		unsigned endpos = is->first; 
        
		
		map_it = map_str.find(it->first);

		if (map_it != map_str.end())
		{
			record* rec = map_it->second;
			unsigned str_len = strlen(rec->str);
	
			if (endpos > str_len)
			{
			    cout<<"error "<<rec->headstr<< ":"<<stapos<<"-"<<endpos<<"-"<<str_len<<" "<<endl;
				cout<<rec->str<<'\t';
			}

			if (endpos + win_len > str_len)
			{
				endpos = str_len;
			}
			else
			{
				endpos = endpos + win_len;
			}		
	
			unsigned s_len;
			if (endpos < stapos )
			{
				//cout<<endl<<"error "<<rec->index<< ":"<<stapos<<"-"<<endpos<<'\t';
				
				continue;
			}
			else
			{
                s_len = endpos - stapos;
			}
		

			outinf << rec->headstr <<" "<<stapos<<"-"<<endpos <<" length "
				<<endpos - stapos + 1 << endl;

			outfile<<rec->headstr<<" "<<stapos<<" "<< endpos <<endl;

			for (unsigned ix = stapos; ix != stapos + s_len; ++ix)
			{
				outfile << rec->str[ix];
			}
			outfile <<endl;


			unsigned* tmp = new unsigned[str_len]();
			if(tmp == NULL)
			{
				cout << "malloc error!" <<endl;
				exit(0);				
			}

			for (map<unsigned,unsigned>::iterator ix = it->second.begin();
				ix != it->second.end(); ++ix)
			{
				tmp[ix->first] = ix->second;
			}

			//copynum(tmp,rec->position+stapos,s_len);

			printpos(tmp + stapos, s_len, outfile);
			 
			delete[] tmp;
			tmp = NULL;
			outfile<<endl;
		}
		else
		{
			cout<<"error can not find the index "<<endl;
			exit(0);
		}
		
		//cout<<endl;
		outfile<<endl;
	}
	//cout<<ct<<endl;
	
}

  /*************************************************
  Function:       // copynum
  Description:    //  
  Calls:          // none
  
  Called By:      // findItem
                     printSegments
  Input:          // unsigned* a1
                     unsigned* a2
					 unsigned num  
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
inline void copynum(unsigned* a1, unsigned* a2,unsigned num)
{
	for (unsigned ix = 0; ix != num; ++ix)
	{
		*a1++ = *a2++;
	}
}


void precessCommunity(list<map<long,map<unsigned,unsigned> > >& listMap)
{
	for(list<map<long,map<unsigned,unsigned> > >::iterator it = listMap.begin();
		it != listMap.end(); )
	{
		if (filterMap(*it) == true)
		{
			it = listMap.erase(it);
		}
		else
		{
			++it;
		}
	}
}


 /*************************************************
  Function:       // filterCommunitybyDensity
  Description:    //  
  Calls:          // caldense
  
  Called By:      // findCommonMaxSet
                     
  Input:          // list<map<long,map<unsigned,unsigned> > >& listMap 
					 unsigned win_len
                  //  
                  //  
  Output:         // 
  Return:         // none
  Others:     
*************************************************/
void filterCommunitybyDensity(list<map<long,map<unsigned,unsigned> > >& listMap,
	unsigned win_len)
{
	
	for (list<map<long,map<unsigned,unsigned> > > ::iterator it = listMap.begin();
		it != listMap.end(); )
	{
		if (it->size() < 10)
		{
			caldense(*it, 0.15, win_len);
		}


		if (it->size() == 1 || it->size() == 0)
		{
			it = listMap.erase(it);
		}
		else
		{
			++it;
		}
	}
}

/*************************************************
  Function:       // findCommonMaxSet
  Description:    // detect protein families using hash seeds information 
  Calls:          // findItem
                     cliqueCommunityCompare
					 splitMap
					 compareself
					 precessCommunity
					 filterCommunitybyDensity
					 printProteinFamilies
  Called By:      // main()
  Input:          //  sequences& segments 
                  //  
                  //  
  Output:         // 
  Return:         // 
  Others:     
*************************************************/
 
void findCommonMaxSet(sequences& segments)
{
	double times = 5;
	
	multimap<unsigned,pair<unsigned,set<pSeed> > > sortClusIndex;
	map<long,record*> mapRec;

	double threshold = segments.info.threshold;
	unsigned win_len = segments.info.window_len;


	findItem(segments.head_ptr,win_len, sortClusIndex, mapRec);
	cout<<"totally "<<sortClusIndex.size()<<"number of hash seed are detected"<<endl;
//ofstream outfile("sortClusIndex.txt");
	//for ( multimap<unsigned,pair<unsigned,set<pSeed> > >::reverse_iterator it = sortClusIndex.rbegin(); 
	//	it != sortClusIndex.rend(); ++it)
	//{
	//	outfile<<"count: "<<it->first<<endl;
	//	outfile<<"Seed: "<<it->second.first<<endl;
	//	for (set<pSeed>::iterator is = it->second.second.begin(); 
	//		is != it->second.second.end(); ++is)
	//	{
	//		outfile<<is->index<<" ";
	//	}
	//	outfile<<endl<<endl;
	//}
	//outfile.clear();
	//outfile.close();
	list<map<long,map<unsigned,unsigned> > > listMap;
	//backbone(sortClusIndex,threshold,listMap);
	//cout<<"size of list Map is : "<<listMap.size()<<endl;
//	cout<<"printMapList"<<endl;
//	printMapList(listMap);

	cout<<"begin clique community compare"<<endl;

	unsigned stapos;
	multimap<unsigned,pair<unsigned,set<pSeed> > >::iterator it = sortClusIndex.begin();

	//long sums=0;
	//for ( ; it != sortClusIndex.end(); ++it)
	//{
	//	sums = sums + it->second.second.size() ;
	//}
	//cout << sums <<endl;

	stapos = it->first;
	stapos = sortClusIndex.rbegin()->first;
	 
	cliqueCommunityCompare(sortClusIndex,listMap,threshold,times, stapos);
 

	splitMap(listMap);
	
	//for (list<map<long,map<unsigned,unsigned> > > ::iterator it = listMap.begin();
	//	it != listMap.end(); ++it)
	//{
	//	for (map<long,map<unsigned,unsigned> >::iterator is = (*it).begin(); 
	//		is != (*it).end(); ++is)
	//	{
	//		if (is->first == 49820)
	//		{
	//			for (map<long,map<unsigned,unsigned> >::iterator ik = (*it).begin();
	//				ik != (*it).end(); ++ik )
	//			{
	//				cout<<ik->first <<":"<<ik->second.size()<<endl;
	//				for (map<unsigned,unsigned>::iterator ip = ik->second.begin();
	//					ip != ik->second.end(); ++ip)
	//				{
	//					cout<<ip->second<<" ";
	//				}
	//				cout <<endl;
	//			}
	//			cout << "that is it" <<endl;
	//		}
	//	}
	//}

	compareself(listMap,threshold,times);
	//  anaomap(listMap);

	/*for (list<map<long,map<unsigned,unsigned> > > ::iterator it = listMap.begin();
		it != listMap.end(); ++it)
	{
		for (map<long,map<unsigned,unsigned> >::iterator is = (*it).begin(); 
			is != (*it).end(); ++is)
		{
			if (is->first == 49820)
			{
				for (map<long,map<unsigned,unsigned> >::iterator ik = (*it).begin();
					ik != (*it).end(); ++ik )
				{
					cout<<ik->first <<":"<<ik->second.size()<<endl;
					for (map<unsigned,unsigned>::iterator ip = ik->second.begin();
						ip != ik->second.end(); ++ip)
					{
						cout<<ip->second<<" ";
					}
					cout <<endl;
				}
				cout << "that is it" <<endl;
			}
		}
	}*/

	precessCommunity(listMap);

	 //cout << "after split "<<endl;
	 //for (list<map<long,map<unsigned,unsigned> > > ::iterator it = listMap.begin();
		// it != listMap.end(); ++it)
	 //{
		// for (map<long,map<unsigned,unsigned> >::iterator is = (*it).begin(); 
		//	 is != (*it).end(); ++is)
		// {
		//	 if (is->first == 15706211)
		//	 {
		//		 for (map<long,map<unsigned,unsigned> >::iterator ik = (*it).begin();
		//			 ik != (*it).end(); ++ik )
		//		 {
		//			 cout<<ik->first <<":"<<ik->second.size()<<endl;
		//			 for (map<unsigned,unsigned>::iterator ip = ik->second.begin();
		//				 ip != ik->second.end(); ++ip)
		//			 {
		//				 cout<<ip->second<<" ";
		//			 }
		//			 cout <<endl;
		//		 }
		//		 exit(0);break;
		//	 }
		// }
	 //}


	filterCommunitybyDensity(listMap,win_len);


	listMap.sort(comparesize);


    cout<<"the size of final protein families are : "<<listMap.size()<<endl;

	printProteinFamilies(listMap,segments,mapRec);
 
}
