#!/usr/bin/perl
#==============================================================================#
#-------------------------------help-info-start--------------------------------#

=head1 Name

    2_select_rep_seq.pl --> select representative sequence from multiple sequence alignment

=head1 Usage

    perl  2_select_rep_seq.pl [options] [input file]

    -help       print this help to screen
    -o          write result to a file, default print to STDOUT .

=head1 Example

    perl  2_select_rep_seq.pl -h
    perl  2_select_rep_seq.pl -i input.pir
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

my ($Need_help, $Input_file, $Out_file );
GetOptions(
    "help"      => \$Need_help,
    "in=s"      => \$Input_file,
    "o=s"       => \$Out_file,
);

die `pod2text $0` if ($Need_help);

#============================================================================#
#                              Global Variable                               #
#============================================================================#
$Out_file ||= 'rep_seq.fasta';
die "No input file: $!" if (!defined $Input_file);

#============================================================================#
#                               Main process                                 #
#============================================================================#

open(IN, '<', $Input_file) or die "Can't read $Input_file : $!"; 

print STDERR "---Program\t$0\tstarts --> ".localtime()."\n";

# Read sequence one by one
# First, split sequence into bases
# Then for each base, create a array or hash to store the bases
# Finally, caculate the mode of each base.

$/='>';
my $i=1; # sequence number
my $length=0;# length of sequence
my @seqStat; # statistic of each base
my @oneSeq; # transformed sequence

while(<IN>){
    # read info one by one
    my ($id, $seq)=split "\n\n",$_;
    next if !defined $seq;
    $id = (split "\;",$id)[1];
    $seq = (split "\n.\n",$seq)[0];
    $seq =~ s/\n//g;
#    print "id:".$id."\n";
#    print "seq:".$seq."\n";

    # Split sequence into characters and count
    @oneSeq = split //,$seq;
#    print "Sequence".$i.":\n";
    my $j=0;# id of each base
    foreach my $aminoacid (@oneSeq){
        # When the element is new, create the hash for it
        if(!exists $seqStat[$j]->{$aminoacid}){
#            print $aminoacid." ";
            $seqStat[$j]{$aminoacid}= 1;
        }
        # It the element already exists, increase the count
        if(exists $seqStat[$j]->{$aminoacid}){
#            print $aminoacid." ";
            $seqStat[$j]{$aminoacid} += 1;
        }
        $j++;
    }
    # if($i==3) {last;}
    $i++;
}
close IN;

open(OUT, '>>', $Out_file) or die "Can't write $Out_file : $!";
#print "Representative sequence:\n"; 
my $repSeq="";
for my $base (@seqStat)
{
    my ($mode)=sort{$b cmp $a} keys %{$base};
    if($mode ne "-"){ $repSeq = $repSeq.$mode;}
}
$Input_file=~ s/.{4}$//;
print OUT "\>".$Input_file."\n"; 
print OUT $repSeq."\n";
close OUT;
print STDERR "---Program\t$0\tends  --> ".localtime()."\n";

#============================================================================#
#                               Subroutines                                  #
#============================================================================#


