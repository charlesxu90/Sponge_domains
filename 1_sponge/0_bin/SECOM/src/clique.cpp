
//#include "stdafx.h"
#include "clique.h"

/*************************************************
  Copyright (C), 2011, King Abdullah University of Science and Technology.
  File name:      // hash.h
  Author:  Ming Fan     Version:       Date: // Dec.12, 2011
  Description:    // 
  Others:         //
  Function List:  // 
   

*************************************************/ 



//initialize: copy 
kclique::kclique(const set<unsigned>& tSet)
{
    setit.insert(tSet.begin(),tSet.end());
}

kclique::kclique(unsigned tmp)
{
	setit.insert(tmp);
}

kclique::kclique(unsigned p1,unsigned p2)
{
	setit.insert(p1);
	setit.insert(p2);
}


kclique &kclique::operator+=(const kclique& clique)
{
	setit.insert(clique.setit.begin(),clique.setit.end());
	return* this;
}

kclique kclique::operator+(const kclique& kcli)
{
	kclique ret(setit);
	//ret.setit.insert(kcli.setit.begin(),kcli.setit.end());
	ret += kcli;
	return ret;
}

//project k-cliques into k (k-1) sub-cliques
list<set<unsigned> > kclique::getSubcliques()
{
	set<unsigned>::iterator it,is;
	list<set<unsigned> > listNode;

	for ( it = setit.begin(); it != setit.end();++it  )
	{
		set<unsigned> tmpSet;
		for (is = setit.begin(); it != setit.end(); ++it)
		{
			if ( it != is)
			{
				tmpSet.insert(*is);
			}
		}
		listNode.push_back(tmpSet);
	}
	return listNode;
}

void kclique::add_clique(unsigned p1,unsigned p2)
{
	setit.insert(p1);
	setit.insert(p2);
}

