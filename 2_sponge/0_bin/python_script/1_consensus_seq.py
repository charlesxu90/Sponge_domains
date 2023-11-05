from Bio import AlignIO
from Bio.Align import AlignInfo
import getopt
import sys
#===============================================#
#   Author: Xiaopeng XU
#   Email:  charlesxu90@gmail.com
#===============================================#
#   Description:
#   This file find the consensus sequence from
#   Clustalw MSA file.
#===============================================#

version = '1.0'
verbose = False
opts, remainder = getopt.getopt(sys.argv[1:], 'i:o:v:h',
                                   ['input', 'output=',
                                    'verbose', 'version',
                                    'help',])
for opt, arg in opts:
    if  opt in ('-i', '--input'):
        infile = arg
    elif opt in ('-o', '--output'):
        outfile = arg
    elif opt in ('-v', '--verbose'):
        verbose = True
    elif opt == '--version':
        print version
        exit()
    else:
        print("Usage: %s -i infile -o outfile" % sys.argv[0])
        exit()
#===============================================#
#filename = "/home/xux/Projects/Sponge/1_sponge/3_motif2Domain/0_msa_probcons/SC/cluster10size15.txt.aln"
align = AlignIO.read(infile, "clustal")
summary_align = AlignInfo.SummaryInfo(align)
consensus = summary_align.dumb_consensus(threshold=0.0)
outhd = open(outfile, 'w')
outhd.write(">" + infile + "\n")
outhd.write(str(consensus) + "\n")
#print consensus
