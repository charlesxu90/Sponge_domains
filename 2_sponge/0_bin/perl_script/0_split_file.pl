#!/usr/bin/perl
#==============================================================================#
#-------------------------------help-info-start--------------------------------#

=head1 Name

    0_split_file.pl --> 

=head1 Usage

    perl  0_split_file.pl [options] [input file]

    -help       print this help to screen
    -o          write result to a file, default print to STDOUT .

=head1 Example

    perl  0_split_file.pl -h
    perl  0_split_file.pl -dir dir -in Input_file -t Threshold
=head1 Contact

    Author      :  Xu Xiaopeng (CharlesXu)
    E-mail      :  xiaopeng.xu@kaust.edu.sa

=cut
#-------------------------------help-info-end--------------------------------#
#============================================================================#
use strict;
use warnings;
use Getopt::Long;

my ($Need_help, $Dir, $Input_file, $Threshold );
GetOptions(
    "help"      => \$Need_help,
    "dir=s"     => \$Dir,
    "in=s"      => \$Input_file,
    "thre=s"    => \$Threshold,
);

die `pod2text $0` if ($Need_help);

#============================================================================#
#                              Global Variable                               #
#============================================================================#
$Threshold ||= 5;
if (!defined $Input_file)
{$Input_file||='input.txt';}
#============================================================================#
#                               Main process                                 #
#============================================================================#

#opendir(DIR, $Dir) or die "Can't open dir $Dir: $!";

open(IN, '<', $Input_file) or die "Can't read $Input_file : $!"; 

print STDERR "---Program\t$0\tstarts --> ".localtime()."\n";

my $if_print = 0;
while(<IN>){
    chomp;
    next if $_=~/^\d+/; #next if the first character is a number
    if ($_ =~/cluster num: (\d+) size: (\d+)/){
        if($2 < $Threshold) { $if_print=0; next;};
        
        $if_print=1;
        #make a file for cluster if cluster size bigger than Threshold
        close OUT;
        my $Out_file=$Dir."cluster".$1."size".$2.".txt";
        open(OUT, '>', $Out_file) or die "Can't write $Out_file : $!"; 
        next;
    }
    next if $if_print==0;
    if($_=~/^>/){
        #print line if starts with '>'
        $_=~s/\r//g;
        print OUT $_."\n";
    }elsif($_=~/^[A-Z]+/){
        #print line if this is content of a sequence
        print OUT $_."\n";
    }
}
close OUT;
close IN;
#closedir(DIR);

print STDERR "---Program\t$0\tends  --> ".localtime()."\n";

#============================================================================#
#                               Subroutines                                  #
#============================================================================#


