#!/usr/bin/perl
#==============================================================================#
#-------------------------------help-info-start--------------------------------#

=head1 Name

    4.pick_dom_seq.pl --> This is to pick domain sequences form fasta sequences db using hmm.

=head1 Usage

    perl  4.pick_dom_seq.pl [options] [input file]

    -help       print this help to screen
    -profile    domain hmm file
    -fa         fasta sequences database
    -dir        output directory, Defaykt us tge dir of hmm file
    -tag        tag for output file, output file is 'fa.tag'
    -E          threshold for hmmsearch, default '1e-5'

=head1 Example

    perl  4.pick_dom_seq.pl -h
    perl  4.pick_dom_seq.pl -profile Ndr.hmm -fa Homo_sapiens.all.fa -d ./ -tag _dseq.fa

=head1 Contact

    Author          :  Xu Xiaopeng (Charles Xu)
    E-mail          :  xiaopeng.xu@kaust.edu.sa,charlesxu90@gmail.com
    Institution   :  KAUST

=cut
#-------------------------------help-info-end--------------------------------#
#============================================================================#
use strict;
use warnings;
use File::Basename;
use Getopt::Long;

my ($Need_help, $Hmm, $Fa_DB, $Dir, $Tag, $E);
GetOptions(
    "help"      => \$Need_help,
    "profile=s"     => \$Hmm,
    "fa=s"      => \$Fa_DB,
    "dir=s"     => \$Dir,
    "tag=s"     => \$Tag,
    "E=s"       => \$E,
);

die `pod2text $0` if ($Need_help);

#============================================================================#
#                              Global Variable                               #
#============================================================================#

die "No enough input file: $!" if (!defined $Hmm or !defined $Fa_DB);
$Dir ||= dirname($Fa_DB);
$Tag ||= '_hmm.fa';
$E   ||= '1e-5';
my $Outfile1 = dirname($Dir).'/'.basename($Dir).'/'.basename($Fa_DB)."_id.txt";
my $Outfile2 = dirname($Dir).'/'.basename($Dir).'/'.basename($Fa_DB).$Tag;
#============================================================================#
#                               Main process                                 #
#============================================================================#

#print STDERR "---Program\t$0\tstarts --> ".localtime()."\n";

open(IN1,"hmmsearch -E $E $Hmm $Fa_DB |")or die "Cannot open step 1-1: $!\n";

# Retrieve the SeqID, Score, E-value from Hmmsearch
while (<IN1>) {
    last if (/Scores for complete sequences/);   
}
my $n=0;   
my @Id_no;
my @Score_info;
my @data; my ($id, $score, $evalue);
while (<IN1>) {
    chomp ($_);  
    if ($_=~/ENS/ or $_=~/PAC\:/) {
        @data=split(/\s+/,$_);   

        $id=$data[9]; $score=$data[2];$evalue=$data[1]; 
        #print "$id\t$score\t$evalue\n";
        $Score_info[$n]="$id\t$score\t$evalue";
        $Id_no[$n]="$id";
        $n++;
    }
    last if ( $_=~/Domain annotation for each sequence/ );
}
close IN1;

die "No sequences matched in $Fa_DB!" if ($n == 0);
print "Total no. of selected sequences is $n.\n";

open(OUT1,">",$Outfile1)or die"can't save step 1-1:$!";
foreach (@Score_info){
    print OUT1 "$_\n";
}
close OUT1;

# Pick the domain sequences
open(IN2,'<', $Fa_DB)or die "can't open step 1-2: $!";
open (OUT2,'>',$Outfile2)or die"can't save step 1-2:$!";
my @seq_data; my $seq_data;
$/=">";
print OUT2 ">";
while (<IN2>) {
    for (my $i=0;$i<$n ;$i++) {
        @seq_data=split(/\s+/,$_);
        $seq_data=$seq_data[0];
        if ($seq_data =~ $Id_no[$i]) {
            print OUT2 $_;
        }
    }
}
close IN2;
close OUT2;

#print STDERR "---Program\t$0\tends  --> ".localtime()."\n";

#============================================================================#
#                               Subroutines                                  #
#============================================================================#


