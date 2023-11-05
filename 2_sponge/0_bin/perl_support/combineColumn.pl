#!/usr/bin/perl
#==============================================================================#
#-------------------------------help-info-start--------------------------------#

=head1 Name

    combineColoum.pl --> This perl script is used to combine the designed coloums in two files.

=head1 Usage

    perl  combineColoum.pl [options] [input file]

    -help       print this help to screen
    -f1         The first file to input.
    -f2         The second file to input.
    -c1         The coloums to be used in the first input file.separated by comma.(such as 1,2,3)
    -c2         The coloums to be used in the second input file.(such as 4,5,6)
    -k          The key coloum to be used to select.It must come from file1.
    -o          The write file Name .
    

=head1 Example

    perl  combineColoum.pl -h
    perl  combineColoum.pl -f1 [firt_inputfile] -f2 [second_inputfile] -c1 [coloums] -c2 [coloums] -r [refCol] -o [outputfile]
=head1 Contact

    Author      :  Xu Xiaopeng (CharlesXu)
    E-mail      :  872930039@qq.com,xuxiaopeng@genomics.cn
    Company     :  BGI

=cut
#-------------------------------help-info-end--------------------------------#
#============================================================================#
use strict;
use warnings;
use Getopt::Long;

my ($Need_help, $Input_file1, $Input_file2, $Coloums1, $Coloums2, $Key, $Out_file );
GetOptions(
    "help"      => \$Need_help,
    "f1=s"      =>\$Input_file1,
    "f2=s"      =>\$Input_file2,
    "c1=s"      =>\$Coloums1,
    "c2=s"      =>\$Coloums2,
    "key"       =>\$Key,
    "out=s"       => \$Out_file,
);

die `pod2text $0` if ($Need_help);

#============================================================================#
#                              Global Variable                               #
#============================================================================#
if (!defined $Out_file)
{$Out_file ||= 'output.txt';}
if (!defined $Input_file1 or !defined $Input_file2)
{ die "Two input files are needed! $!"}
if (!defined $Key){$Key=1;}
#============================================================================#
#                               Main process                                 #
#============================================================================#

open(STDOUT, '>', $Out_file) or die "Can't write $Out_file : $!"; 

print STDERR "---Program\t$0\tstarts --> ".localtime()."\n";
my @coloum1;
my @coloum2;
my @SelectColoum1;
my @SelectColoum2;

open(IN1, '<', $Input_file1) or die "Can't read $Input_file1 : $!";
while(<IN1>){
    chomp;
    @coloum1=split /\s+/;
    
    #print out the coloums in file1.
    if(defined $Coloums1){ 
        @SelectColoum1=split /\,/,$Coloums1;
        for (@SelectColoum1){print STDOUT "$coloum1[$_-1]\t";}
    }else{
        for (@coloum1){ print STDOUT "$_\t";}
    }

    open(IN2, '<', $Input_file2) or die "Can't read $Input_file2 : $!";
    while(<IN2>){
        chomp;
        @coloum2=split /\t/;
        next unless ($coloum1[$Key-1] eq $coloum2[0]);
        #print out the selected coloums in file2.
        if(defined $Coloums2){
            @SelectColoum2=split /\,/,$Coloums2;
            for(@SelectColoum2){print STDOUT "$coloum2[$_-1]\t";}
        }else{
            for(@coloum2){print STDOUT "$_\t";}
        }        
    }
    close IN2;

    print STDOUT "\n";
}
close IN1;
close STDOUT;
print STDERR "---Program\t$0\tends  --> ".localtime()."\n";

#============================================================================#
#                               Subroutines                                  #
#============================================================================#


