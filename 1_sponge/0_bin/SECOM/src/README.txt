#______________________________________________________________
# Title     : SECOM REAME file
# Usage     :
# Function  : protein domain detection
# Example   :
# Keywords  :
# Options   :
# Author    : ming.fan@kaust.edu.sa
# Category  :
# Returns   :
# Version   : 1.0
#--------------------------------------------------------------

1. Compiling

On linux/unix system with gcc/g++ installed running "make" 
should be sufficient.Executable named "SECOM" will be created 
in the same directory.

2. Running

The command to run the program is of form
  SECOM

  in ./Test  directory.

3. Configuration file

Users should type their own input file name and parameters
descriped in the manuscript. The structure of the configuration
file is represented as follows:

InputFilename		AQ_sponge.fa 	#example: AQ_sponge.fa or any
# fasta format file
Threshold				0.7						#It can be 0.3,0.4....0.9
HashSeedLength	9							#type a value like 6,7,8,9,10,11
HashSeedType	  c2						#only "c1" and "c2" are accepted

In the first row "InputFIleName", users should type fasta format
file. The sencond line "Threshold" could be any value between 0 
and 1. Since not all of the value can generate proper results, 
please refer to supplemeantary meterial and decide which is fine
threshold. In the third row "HashSeedLength", users should type the 
length of hash seeds. In the fourth row "HashSeedType", users should
type "c1" or "c2". If none threshold are provided, SECOM will
run with default parameter (Threshold = 0.7, HashSeedLength = 9, 
HashSeedType = c2).
    
4. Output
If users use file which name "test.fa", then output results are 
generated. The distribution of protein families are generated as
"test.fa.size", and all the clusters with their members (described by 
IDs and start and end positions) are listed in "test.fa.clus";
Finally, the clusters with their sequence information are shown in 
"test.fa.result.out". 