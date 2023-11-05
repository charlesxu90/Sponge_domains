#!/usr/bin/perl
#==============================================================================#
#-------------------------------help-info-start--------------------------------#

=head1 Name

    4_sel_blast_info.pl --> This script is to select information from blastp results

=head1 Usage

    perl  4_combine_pfam_blast_seq.pl [options] [input file]

    -help       print this help to screen
    -dir        the directory contains blastp result
    -tag        the suffix of the file which is to select info from
    -out        write result to a file, default print to STDOUT .

=head1 Example

    perl  4_combine_pfam_blast_seq.pl -h
    perl  4_combine_pfam_blast_seq.pl  -dir ./ -tag nr.out  -out blast.tsv

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
use File::Spec;

my ($Need_help, $Dir, $Tag, $Out_file );
GetOptions(
    "help"      => \$Need_help,
    "dir=s"     => \$Dir,
    "tag=s"     => \$Tag,
    "out=s"       => \$Out_file,
);

die `pod2text $0` if ($Need_help);

#============================================================================#
#                              Global Variable                               #
#============================================================================#

die "No directory specified: $!" if (!defined $Dir);
die "No Tag specified:$!" if (!defined $Tag);
$Out_file ||= 'blast.tsv';

#============================================================================#
#                               Main process                                 #
#============================================================================#

print STDERR "---Program\t$0\tstarts --> ".localtime()."\n";
my $header = "ClusterId\t$Tag";

my %ClusterInfo;
my $clusterId;
opendir(DIR, $Dir);
my $dir_path = File::Spec->rel2abs($Dir);
my @files = readdir DIR;
foreach my $file (@files){
    next if $file !~ m/$Tag$/;
    $file =~ m/cluster(\d+)size\d+/;
    $clusterId = $1;
    my $file_path = File::Spec->catfile($dir_path,$file);
    
    my ($species, $count)=('',0);
    open(IN, '<', $file_path) or die "Can't read $file : $!";
    while(<IN>){
        if ($_ =~ /^>/) { $count =1};
        chomp;
        if($_ =~ m/\[(.*)$/ and $count == 1){
            # find a sequence of a species
            $species = $1;
            $species =~ s/\s/\_/g;
            if($species =~ m/\]$/){
                $species =~ s/\]//g;
                if(!defined $ClusterInfo{$clusterId}{$species}){
                    $ClusterInfo{$clusterId}{$species} = 1;
                }else{
                    $ClusterInfo{$clusterId}{$species} = $ClusterInfo{$clusterId}{$species} + 1;
                }
                $count = 0;
                #print "$file\t$clusterId\t$species\t$ClusterInfo{$clusterId}{$species}\n";
            }
        }elsif($_ =~ m/^(.*)\]$/ and $count == 1){
            $species = $species.$1;
            if(!defined $ClusterInfo{$clusterId}{$species}){
                $ClusterInfo{$clusterId}{$species} = 1;
            }else{
                $ClusterInfo{$clusterId}{$species} = $ClusterInfo{$clusterId}{$species} + 1;
            }
            $count = 0;
            #print "$file\t$clusterId\t$species\t$ClusterInfo{$clusterId}{$species}\n";
        }

    }
    close IN;
}
close DIR;

my $blastInfo = '';
open(OUT, '>', $Out_file) or die "Can't write $Out_file : $!";
print OUT "$header\n";
foreach my $cluster (sort {$a<=>$b} keys %ClusterInfo){
    $blastInfo='';
    foreach my $species (sort keys %{$ClusterInfo{$cluster}}){
        if(defined $ClusterInfo{$cluster}{$species}){
            $blastInfo = $blastInfo."$species\/$ClusterInfo{$cluster}{$species}\,";
        }
    }
    #print "$cluster\t$blastInfo\n";
    print OUT "$cluster\t$blastInfo\n";
}
close OUT;

print STDERR "---Program\t$0\tends  --> ".localtime()."\n";

#============================================================================#
#                               Subroutines                                  #
#============================================================================#

