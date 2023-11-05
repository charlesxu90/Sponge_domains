//#include "stdafx.h"
#include "fileConfig.h"


config::config()
{
    filename = ""; //the name of input .fa file
	filelength = 0; 
	window_len = 0; // hash seed length
	clust_type = ""; // hash seed type
	threshold = 0.0;
}

sequences::sequences()
{
	head_ptr = NULL;
	count = 0;
}
void sequences::create(record newrecord)
{
	if (head_ptr == NULL)
	{
		head_ptr = new record(newrecord);
		if(head_ptr == NULL)
		{
				cout << "malloc error!" <<endl;
				exit(0);
		}
	}
	else
	{
		record* p = head_ptr;
	}
}


void sequences::insert_record(record* rec,record newrecord)
{
	if (head_ptr == NULL)
	{
		head_ptr = new record(newrecord);
	    
		if(head_ptr == NULL)
		{
				cout << "malloc error!" <<endl;
				exit(0);
		}
	}
	else
	{
		record* tmp = new record(newrecord);
		
		if(tmp == NULL)
			{
				cout << "malloc error "<<endl;
				exit(0);
			}
		tmp->next = rec->next;
		rec->next = tmp;
	}
}

void sequences::pushback(record newrecord)
{
	if (head_ptr == NULL)
	{
		head_ptr = new record(newrecord);
			if(head_ptr == NULL)
			{
				cout << "malloc error "<<endl;
				exit(0);
			}
		temporal_ptr = head_ptr;
	}
	else
	{
        temporal_ptr->next = new record(newrecord);
      
		if(temporal_ptr == NULL)
		{
			cout << "malloc error "<<endl;
			exit(0);
		}
		temporal_ptr = temporal_ptr->next;
	}
	temporal_ptr->next = NULL;
	
}
//show amino acid on the screen
void sequences::show()
{
	record* rec;
	rec = head_ptr;

	for (;rec != NULL; rec = rec->next)
	{
		cout<<rec->index<<":"<<endl;
		cout<<rec->str<<endl;
		
		for (unsigned i = 0; i != strlen(rec->str); ++i)
		{
			
			if (rec->position[i] == 0)
			{
				cout<<" ";
			}
			else
			{
				cout<<rec->position[i]<<" ";
			}
		}
		cout<<endl;
	}
}

//print the sequences with their seeds
void sequences::print()
{
	record* rec;
	rec = head_ptr;
	string outfilename = info.filename + ".out";
	ofstream outfile(outfilename.c_str());

	for (;rec != NULL; rec = rec->next)
	{
		outfile<<rec->headstr<<" "<<rec->index << endl;
		outfile<<rec->str<<endl;
		unsigned tp = 1;

		for (unsigned i = 0; i != strlen(rec->str); ++i)
		{

			if (rec->position[i] == 0  )
			{
				if (tp > 1)
				{
					--tp;
					continue;
				}
				outfile<<" ";
			}
			else
			{
				long pos = rec->position[i];
				outfile << pos;

				int sum = 0; 
				while(pos) 
				{ 
					pos /= 10; 
					sum ++; 
				} 
				tp = sum;

			}
		}
		outfile<<endl;
	}
	outfile.close();
}

// load fasta format (.fa) file
void sequences::load()
{
	 
	ifstream infile(info.filename.c_str());
	 
	if (!infile)
	{
		cout<<"can not open " << info.filename << endl;
		exit(0);
	}
	else
	{
		cout <<" begin reading "<< info.filename << " file !"<<endl;
	}
	// some of the sequence is much too short,  we exclude sequences that have length
	// less than maxlen
	const unsigned maxlen = 20; 
	 
	bool firstrun = true;


	long index = 0; 
	long nextIndex = 0;
	string nextHeadPtr;	
	string headstr;
	// number of sequences that have length more than maxlen
	long seq_Len = 0;

	while (!infile.eof())
	{
		//read the index of the file
		//read the second number of a line
		++seq_Len;

		unsigned ct = 0; 
		string sentences;
		if (firstrun == true)
		{
		    string line;	 
			getline(infile,line);
			if (line[0] != '>' && !(line[0] >= '0' && line[0] <= '9') )
			{
				cout << "error ! wrong file format ! input should at least be fasta file "<<endl;
				exit(0);
			}
		//	index = atol(line.c_str());
			++index;
			headstr = line;
			firstrun = false;
		}

		//read the index and amino acids in the sequence file
		while(true)
		{
			string line;
			getline(infile,line);

			if (line.size() == 0)
			{   ++ct;
			    if (ct < 5)
			    {
					continue;
			    }
				else
				{
					break;
				}
			}
	 
			if (line[0] == '>' || (line[0] >= '0' && line[0] <= '9'))
			{
		        nextIndex = nextIndex + 10;
			//	nextIndex = atol(line.c_str());
				nextHeadPtr = line;
				break;
			}
 			sentences = sentences.append(line);			
		}
 
		unsigned lenchar = sentences.size();
		unsigned lenheanstr = headstr.size();

		if (lenchar < maxlen)
		{
			index = nextIndex;
			headstr = nextHeadPtr;
			continue;
		}
		record one_rec;
		one_rec.index = index;
		one_rec.headstr = headstr;
	
		one_rec.str = new char[lenchar+1]();
			
		if(one_rec.str == NULL)
		{
			cout << "malloc error "<<endl;
			exit(0);
		}
		one_rec.position = new unsigned [lenchar]();
			
		if(one_rec.position == NULL)
		{
			cout << "malloc error "<<endl;
			exit(0);
		}
    
		copystr(one_rec.str, sentences.c_str(), lenchar);
      
		one_rec.num_clu = 0;
		one_rec.str[lenchar] = '\0';

		if (lenchar < maxlen)
		{
			index = nextIndex;
			headstr = nextHeadPtr;
			continue;
		}
	 
		
		pushback(one_rec);
		count++;
		 
		index = nextIndex;
		headstr = nextHeadPtr;
	
	}
 
	 
	 cout << " the size of the " << info.filename << " is "<< seq_Len <<endl;
	 cout << endl <<" totally " << count << " sequences that have length more than "
		 <<maxlen<<" are to be precessed "<<endl;
	 infile.clear();
	 infile.close();
	 
}

 




//read the configuration file, which contain the parameters and input file name
void sequences::read_configfile()
{
	ifstream infile("SECOM_config.txt");

	if (!infile)
	{
		cout<< "can not read configuration file ! ";
		exit(0);
	} 	

	//	config mak;
	while(!infile.eof())
	{
		//read the file name
		string line;
		getline(infile,line);
                cout<<line<<endl;

		if(line[0]=='#'||line[0]==NULL)
		{
			continue;
		}
		istringstream strs(line);
		string clown1, clown2;
		strs >> clown1 >> clown2;

		if(clown1 == "InputFileName")
		{
			info.filename = clown2; 
		}
		else if(clown1 == "Threshold")
		{
			info.threshold = atof(clown2.c_str());
		}
		else if(clown1 == "HashSeedLength")
		{
			info.window_len = atoi(clown2.c_str());
		}
		else if(clown1 == "HashSeedType")
		{
			info.clust_type = clown2;  
		}		
		else
		{
			cout<<"error! cannot load config information "<<
				line <<" please check your input "<< endl;
			exit(0);
		}
	}
	infile.clear();
	infile.close();

	SetDefault(info); 
}

 /*************************************************
  Function:      // setDefault
  Description:   // set default value of threshold
  Calls:         // none
  Called By:     // void sequences::read_configfile
  Input:         // config & info
                 //  
  Output:        // 
  Return:        // none
  Others:      
*************************************************/

void SetDefault(config& info)
{
	if (info.filename == "")
	{
		cout << "error! you have not type input fa format file "<<endl;
		exit(0);
	}

	cout << " input file name "<<info.filename << endl;

	if (info.threshold < eps && info.threshold > -eps)
	{
		cout << "you have not set threshold, default is 0.7 "<<endl;
		info.threshold = 0.7;
	}
	else if (info.threshold > 1 || info.threshold < 0)
	{
		cout << " check your parameter for threshold "<<info.threshold<<endl;
		exit(0);
	}
	else
	{
        cout << " threshold for merging communities is : "<< info.threshold <<endl;
	}
 

	if ( info.window_len == 0)
	{
		cout <<" you have not set hash seed length, default is 9 "<<endl;
		info.window_len = 9;
	}
	else if ( info.window_len > 50 )
	{
		cout <<"check your parameter for hash seeds length ! "<< endl;
		exit(0);
	}
	else
	{
        cout << " hash seed length is : "<<info.window_len <<endl;
	}
	
	
	if ( info.clust_type == "")
	{
		cout << " you have not set hash seed type, default is c2 "<<endl;
		info.clust_type = "c2";
	}
	else if ( info.clust_type != "c1" && info.clust_type != "c2")
	{
		cout << "wrong parameter ! please set c1 or c2 for input "<<endl;
		exit(0);
	}
	else
	{
        cout << " hash seed type: "<< info.clust_type <<endl;
	}
	
}


/*************************************************
  Function:      // printpos
  Description:   // print the domain position   
  Calls:         // none
  Called By:     // printSegments
  Input:         // unsigned* pos
                    unsigned s_len
					ofstream& outfile
                 //  
  Output:        // 
  Return:        // none
  Others:      
*************************************************/

void printpos(unsigned* pos,unsigned s_len,ofstream& outfile)
{
	unsigned tp = 1;
	for (unsigned ix = 0; ix != s_len; ++ix)
	{
		if (pos[ix] == 0  )
		{
			if (tp > 1)
			{
				--tp;
				continue;
			}
			outfile<<" ";
		}
		else
		{
			long posi = pos[ix];
			outfile << posi;
			int sum = 0; 
			while(posi) 
			{ 
				posi /= 10; 
				sum ++; 
			} 
			tp = sum;

		}
	}
}



 /*************************************************
  Function:      // copystr
  Description:   // copy the string , and exclude charterers such as 'x' and '*'  
  Calls:         // none
  Called By:     // void sequences::load()
  Input:         // char* dest
                    const char* source
				    unsigned &len
                 //  
  Output:        // 
  Return:        // none
  Others:      
*************************************************/

void copystr(char* dest, const char* source,  unsigned &len)
{
	unsigned ix;
	unsigned iy = 0;
	for ( ix = 0; ix != len; ++ ix )
	{
		if (source[ix] != 'X' && source[ix] != '*' && source[ix] != 'x' && source[ix] != 'B'
			&& source[ix] != 'O' && source[ix] != 'U' && source[ix] != 'J')
		{
			dest[iy] = source[ix];
			++ iy;
		}
	}
	len = iy;
}
