//#include "stdafx.h"
#include "hashMethod.h"

/************************************************************
  Copyright (C), 2011, King Abdullah University of Science and Technology..
  FileName: hash_method.cpp
  Author:        Version :          Date:
  Description:     //    
  Version:         //  
  Function List:   //  
    1. -------
***********************************************************/


/*************************************************
  Function:       // str_num
  Description:    // map the 20 amino acids into 11 or 15 classes
  Calls:          //  none
  Called By:      //  main
  Input:          //  const string& clust_type. Only two types of string "C1" or "C2" are
                  //  preferred 
                  //  
  Output:         // 
  Return:         // A amino acid to its class (used as integer) map
  Others:        // The two types of map:
                //c1: C-1,G-2,A-3,T-4,S-4,N-5,D-6,E-6,Q-7,K-7,R-7,V-8,I-8,L-8,M-8,W-9,F-9,Y-9,H-10,P-0
                //c2:  C-1,G-2,A-3,T-4,S-5,N-6,D-7,E-7,Q-8,K-9,R-9,V-10,I-10,L-11,M-11,W-12,F-13,Y-13,H-14,P-0
*************************************************/


map<char,unsigned> str_num(const string& clust_type)
{
	map<char,unsigned> mapit;

	string amino = "CGATSNDEQKRVILMWFYHP";
	int clus1[20] = {1,2,3,4,4,5,6,6,7,7,7,8,8,8,8,9,9,9,10,0};
	int clus2[20] = {1,2,3,4,5,6,7,7,8,9,9,10,10,11,11,12,13,13,14,0};
	if (clust_type == "c1")
	{
		for (unsigned ix = 0; ix != 20; ++ix)
		{
			mapit.insert(make_pair(amino[ix],clus1[ix]));
		}
	}
	else if (clust_type == "c2")
	{
		for (unsigned ix = 0; ix != 20; ++ix)
		{
			mapit.insert(make_pair(amino[ix],clus2[ix]));
		}
	}
	else
	{
		cout << "the input hash seed type "<<clust_type<<" is incorrect ! "<<endl;
		exit(0);
	}
	return mapit;
}

/*************************************************
  Function:       // str_str
  Description:    // map the 20 amino acids into 11 or 15 classes, represented by strings
  Calls:          //  void compare_strhash(sequences& segments)
  Called By:      //  main
  Input:          //  const string& clust_type. Only two types of string "c1" or "c2" are
                  //  preferred 
                  //  
  Output:         // 
  Return:         // A amino acid to its class (used as string) map
  Others:        // The two types of map:
               //c1: C-C,G-G,A-A,T-T,S-T,N-N,D-D,E-D,Q-Q,k-Q,R-Q,V-V,I-V,L-V,M-V,W-W,F-W,Y-M,H-H,P-P
               //c2: C-C,G-G,A-A,T-T,S-S,N-N,D-D,E-D,Q-Q,k-K,R-K,V-V,I-V,L-L,M-L,W-W,F-F,Y-F,H-H,P-P 
*************************************************/
map<char,char> str_str(const string& clust_type)
{
	map<char,char> mapit;
	string amino = "CGATSNDEQKRVILMWFYHP";
	string clus1 = "CGATTNDDQQQVVVVWWWHP";
	string clus2 = "CGATSNDDQKKVVLLWFFHP";
	if ( clust_type == "c1")
	{
	    for (string::size_type ix = 0; ix != amino.size(); ++ ix)
	    {
			mapit.insert(make_pair(amino[ix],clus1[ix]));
	    }
	}
	else if( clust_type == "c2" )
	{
		for (string::size_type ix = 0; ix != amino.size(); ++ ix)
		{
			mapit.insert(make_pair(amino[ix],clus2[ix]));
		}
	}
	else
	{
		cout << "the input hash seed type "<<clust_type<<" is incorrect ! "<<endl;
		exit(0);
	}
	return mapit;
}


/*************************************************
  Function:       // rerange
  Description:   //  check whether a hit between others have a win_len distance, 
                   in order to avoid the sliding window effect
  Calls:          //  none
  Called By:      //  void compare_strhash(sequences& segments)
  Input:          //  unsigned* position, the matrix of index of hash seed 
                      unsigned* k, the postion of a certain hash seed
					  unsigned win_len, length of hash seed
                  //  
  Output:         // 
  Return:         //  0; if the hit are not overrlapped with exsited hash seed
                  //  1; if the hit are overlapped with one hash seed
				  //  2; if the hit are overlapped with two hash seed
  Others:      
*************************************************/

int rerange(unsigned* postion, unsigned* k,unsigned win_len)
{
	if (postion[*k] != 0)
	{
		return 0;
	}

	unsigned t_sta,t_end;
	
	if (*k < win_len )
	{
		t_sta = 0;
	}
	else
	{
		t_sta =  (*k) - win_len;	

	}

	t_end = (*k) + win_len + 1;
	
	unsigned ct = 0;
	unsigned tp,tp2;
	
	for (unsigned i = t_sta; i!= t_end;++i)
	{
		if (postion[i] != 0)
		{
			ct++;
			if (ct == 1)
			{
				tp = i;
			}
			else if(ct == 2)
			{
				tp2 = i;		

				if (tp2 - *k > *k - tp)
				{
					*k = tp;
				}
				else
				{
					*k = tp2;
				}
				return -1;		
			}
			else
			{
				cout<<"error ! please check the input file ";
				exit(0);
			}
		}
	}
	if (ct == 1)
	{
		if (*k <= tp)
		{
			if ( tp > win_len)
			{
				*k = tp - win_len;
			}
			else
			{
				*k = 0;
			}
		}
		else
		{
			*k = tp + win_len;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

/*************************************************
  Function:       // compare_numhash
  Description:   //    Perform protein sequence index by hash seed method in whole sequence, 
                       use integers as hash value
  Calls:     //  map<char,unsigned> str_num(const string& );
                 int rerange(unsigned* , unsigned* ,unsigned );

  Called By:      //  main()
  Input:          // sequences&  : class of protein sequence information
                  //  
  Output:         // 
  Return:         // none
  Others:      
*************************************************/

// calculated the hash value of whole protein sequence  
void compare_numhash(sequences& segments)
{

	record* rec = segments.head_ptr;
	unsigned clus_num = 0;
	unsigned wind_len = segments.info.window_len;
	map<char,unsigned> mapit = str_num(segments.info.clust_type);

	map<unsigned long,hash_clus> hashseed_table;
	unsigned shiftnum = 4 * (wind_len - 1);
	for ( ; rec != NULL;  rec = rec->next )
	{
	
		 char *strs = rec->str;
		 unsigned long seed = 0;
         unsigned start_seed = 0;
	     unsigned long tp = 0;
		 unsigned t_start_seed = 0;
		 unsigned jump = 0; 
		 unsigned resta = 0;
		//slide window
		for (unsigned ix = wind_len-1; ix != strlen(strs); ++ix, ++start_seed)
		{
			if (jump != 0)
			{
				--jump;
				continue;
			}
			if ( ix == wind_len - 1 + resta)
			{
				for(unsigned ix = resta; ix != wind_len + resta; ++ix)
				{
					map<char,unsigned>::const_iterator it = mapit.find(strs[ix]);

					if ( it != mapit.end())
					{
						seed = (seed<<4 ) + it->second;
					}
				}
				
				map<char,unsigned>::const_iterator it = mapit.find(strs[start_seed]);
				tp = it->second;
			}
			else
			{
		       tp = tp<< shiftnum; 
               map<char,unsigned>::const_iterator it = mapit.find(strs[ix]);
			   seed = ((seed - tp) << 4) + it->second; 
			   it = mapit.find(strs[start_seed]);
			   tp = it->second;	
			   ////////////////////////		   
			}

			t_start_seed = start_seed; 
			hash_clus tmp_clus;
			tmp_clus.clus = 0; tmp_clus.pos = start_seed; tmp_clus.rec = rec;
			pair<map<unsigned long,hash_clus>::iterator,bool> ret = 
				hashseed_table.insert(make_pair(seed,tmp_clus));
			unsigned t_pos = ret.first->second.pos;
			if ( ret.second == false) // not been inserted 
			{ 
				if (rec->index == ret.first->second.rec->index && start_seed - t_pos < wind_len)
				{
					continue;
				}

				int rera = rerange(rec->position,&t_start_seed,wind_len-1);
				int rera2 = rerange(ret.first->second.rec->position,&t_pos,wind_len-1);
		 
				if (rera == 0 && rera2 == 0) // no need to revise the boundary
				{
		           if ( ret.first->second.clus == 0 )
					{	
						clus_num++;		
					    ret.first->second.clus = clus_num;
						record* tmp_rec = ret.first->second.rec;
						unsigned tmp_pos = ret.first->second.pos;
					    tmp_rec->position[tmp_pos] = clus_num;	  
					}
				   	rec->position[t_start_seed] = ret.first->second.clus;
					jump = wind_len - 1; resta = ix; resta++;	
	            }
		}
		
	}
  }
 
}

/*************************************************
  Function:       // compare_strhash
  Description:   //    Perform protein sequence index by hash seed method in whole sequence, 
                       use strings as hash value
  Calls:     //  map<char,unsigned> str_num(const string& );
                 int rerange(unsigned* , unsigned* ,unsigned );

  Called By:      //  main()
  Input:          // sequences&  : class of protein sequence information
                  //  
  Output:         // 
  Return:         // none
  Others:      
*************************************************/

void compare_strhash(sequences& segments)
{
	record* rec = segments.head_ptr;
	unsigned clus_num = 0;
	unsigned wind_len = segments.info.window_len;

	map<string,hash_clus> hashseed_table;
	map<char,char> mapit = str_str(segments.info.clust_type);



	for ( ; rec != NULL;  rec = rec->next )
	{

		char *strs = rec->str;
		string seed; 
		unsigned start_seed = 0;
		unsigned t_start_seed = 0; // temporal start seed
		unsigned jump = 0; // if one hash seed already exist, then jump the other win_len - 1 positions
		unsigned resta = 0;
		//slide window
		unsigned slen = strlen(strs)-1;
		for (unsigned ix = wind_len-1; ix != slen; ++ix, ++start_seed)
		{
			if (jump != 0)
			{
				--jump;
				continue;
			}
		
			if ( ix == wind_len - 1 + resta)
			{
				seed.clear();
				for(unsigned ix = resta; ix != wind_len + resta; ++ix)
				{
					map<char,char>::const_iterator it = mapit.find(strs[ix]);

					if ( it != mapit.end())
					{
						seed.push_back(it->second);
					}
				}
			//	map<char,char>::const_iterator it = mapit.find(strs[start_seed]);
			//	tp = it->second;
			}
			else
			{

				map<char,char>::const_iterator it = mapit.find(strs[ix]);
				seed = seed.substr(1,wind_len-1);
			  seed.push_back(it->second);	
				////////////////////////		   
			}


			if (seed.size() != wind_len)
			{
 				cout << "error ! un-recognized character "<<endl;
				cout << "Please check the protein sequence" <<endl;
				cout << rec->headstr <<endl;
				cout << rec->str <<endl;
				cout << "size of the seed " <<seed.size()<<" size of hash seed "<<wind_len<<endl;
				cout << seed <<endl;
				cout << slen <<endl;
				cout << strs <<endl;
				cout << strs[52]<<endl;
				exit(0);
			}
			t_start_seed = start_seed; 
			hash_clus tmp_clus;
			tmp_clus.clus = 0; tmp_clus.pos = start_seed; tmp_clus.rec = rec;
			
			pair<map<string,hash_clus>::iterator,bool> ret = 
				hashseed_table.insert(make_pair(seed,tmp_clus));
			
			unsigned t_pos = ret.first->second.pos;
					
			if ( ret.second == false) // not been inserted 
			{ 
				if (rec->index == ret.first->second.rec->index && start_seed - t_pos < wind_len)
				{
					continue;
				}

				int rera = rerange(rec->position,&t_start_seed,wind_len-1);
				int rera2 = rerange(ret.first->second.rec->position,&t_pos,wind_len-1);

				if (rera == 0 && rera2 == 0) // no need to revise the boundary
				{
					if ( ret.first->second.clus == 0 )
					{	
						++clus_num;		
						ret.first->second.clus = clus_num;
						record* tmp_rec = ret.first->second.rec;
						unsigned tmp_pos = ret.first->second.pos;
						tmp_rec->position[tmp_pos] = clus_num;	
						++tmp_rec->num_clu;
					}
					
					rec->position[t_start_seed] = ret.first->second.clus;
					
					++rec->num_clu;
					jump = wind_len - 1; 
					resta = ix; 
					++resta;	
				}
			}

		}
	}
	cout<<"totally "<<hashseed_table.size()<<" seeds have been found "<<endl;
}

/*************************************************
  Function:      // compare_numhash
  Description:   //  calculated the average hash seed density of the whole sequence
  Calls:         // none
  Called By:      //  main()
  Input:          // sequences&  : class of protein sequence information
                  //  
  Output:         // 
  Return:         // none
  Others:      
*************************************************/
void ShowHashSeedDesnsity(sequences& segments)
{
	record* rec = segments.head_ptr;
	unsigned wind_len = segments.info.window_len;
	double meanv =0;
	unsigned ct = 0;
	for ( ; rec != NULL; rec=rec->next)
	{
	unsigned num = 0;
	for (unsigned ix = 0; ix != strlen(rec->str); ++ix)
	{
		if (rec->position[ix] != 0)
		{
			++num;
		}
	}
	++ct;
	meanv = meanv + double(num) * wind_len/strlen(rec->str);
	}
	cout << "mean density is "<<meanv/ct <<endl;
}
