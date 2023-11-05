#!/usr/bin/perl
#==============================================================================#
#-------------------------------help-info-start--------------------------------#

=head1 Name

    4_combine_pfam_blast_seq.pl --> This script is to combine SECOM seq, Pfam and blast result

=head1 Usage

    perl  4_combine_pfam_blast_seq.pl [options] [input file]

    -help       print this help to screen
    -seq        SECOM consensus sequence
    -pfam       pfam result file
    -blast      this is sorted blastp result       
    -out        write result to a file, default print to output.tsv.

=head1 Example

    perl  4_combine_pfam_blast_seq.pl -h
    perl  4_combine_pfam_blast_seq.pl  -seq seq.fa -pfam pfam.out -out out.tsv

=head1 Contact

    Author          :  Xu Xiaopeng (Charles Xu)
    E-mail          :  xiaopeng.xu@kaust.edu.sa,charlesxu90@gmail.com
    Institution   :  KAUST

=cut
#-------------------------------help-info-end--------------------------------#
#============================================================================#
use strict;
use warnings;
use Getopt::Long;

my ($Need_help, $Seq_file, $Pfam_file, $Out_file );
GetOptions(
    "help"      => \$Need_help,
    "seq=s"     => \$Seq_file,
    "pfam=s"    => \$Pfam_file,
    "out=s"       => \$Out_file,
);

die `pod2text $0` if ($Need_help);

#============================================================================#
#                              Global Variable                               #
#============================================================================#

die "No input seq file: $!" if (!defined $Seq_file);
die "No Pfam result file" if (!defined $Pfam_file);
$Out_file ||= 'output.tsv';

#============================================================================#
#                               Main process                                 #
#============================================================================#

print STDERR "---Program\t$0\tstarts --> ".localtime()."\n";
my %ClusterInfo;
my $header = "ClusterId\tNo.OfSeq\tConsensusSeq\tPfamDomain";
my ($clusterId, $noOfSeq, $consensusSeq, $pfamDomain);

open(SEQ, '<', $Seq_file) or die "Can't read $Seq_file : $!";
while(<SEQ>){
    chomp;
    if(/^>cluster(\d+)size(\d+)/){
        # handle annotation line
        $clusterId = $1;
        $ClusterInfo{$1}{'No.OfSeq'} = $2;

        next;
    }
    # Store sequence line
    $ClusterInfo{$clusterId}{'ConsensusSeq'} = $_;
}
close SEQ;

open(PFAM, '<', $Pfam_file) or die "Can't read $Pfam_file: $!";
my @pfamInfo;
while(<PFAM>){
    next if $_ !~ m/^cluster/;
    if(/^cluster(\d+)size\d+/){
        chomp;
        @pfamInfo = split /\s+/,$_;
        if(!defined $ClusterInfo{$1}{'PfamDomain'}){
            $ClusterInfo{$1}{'PfamDomain'} = "$pfamInfo[6]";
            #print "$pfamInfo[6]\n";
        }else{
            $ClusterInfo{$1}{'PfamDomain'} = "$ClusterInfo{$1}{'PfamDomain'}\,$pfamInfo[6]";
        }
        #print $ClusterInfo{$1}{'PfamDomain'}."\n"; 
    }
}
close PFAM;


open(OUT, '>', $Out_file) or die "Can't write $Out_file : $!";
print OUT "$header\n";
foreach my $cluster (sort {$a<=>$b} keys %ClusterInfo){
    if (defined $ClusterInfo{$cluster}{'PfamDomain'}){
        print OUT "$cluster\t$ClusterInfo{$cluster}{'No.OfSeq'}\t$ClusterInfo{$cluster}{'ConsensusSeq'}\t$ClusterInfo{$cluster}{'PfamDomain'}\n";
    }else{
        print OUT "$cluster\t$ClusterInfo{$cluster}{'No.OfSeq'}\t$ClusterInfo{$cluster}{'ConsensusSeq'}\t \n";
    }
}
close OUT;

print STDERR "---Program\t$0\tends  --> ".localtime()."\n";

#============================================================================#
#                               Subroutines                                  #
#============================================================================#


