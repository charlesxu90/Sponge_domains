#!/usr/bin/perl
#==============================================================================#
#-------------------------------help-info-start--------------------------------#

=head1 Name

    2_run_sel_rep.pl --> Run select representative sequence in folder

=head1 Usage

    perl  2_run_sel_rep.pl [options] [input file]

    -help       print this help to screen
    -o          write result to a file, default print to STDOUT .

=head1 Example

    perl  2_run_sel_rep.pl -h
    perl  2_run_sel_rep.pl -d dir
=head1 Contact

    Author          :  Xu Xiaopeng (Charles Xu)
    E-mail          :  xiaopeng.xu@kaust.edu.sa,charlesxu90@gmail.com
    Instatitution   :  KAUST

=cut
#-------------------------------help-info-end--------------------------------#
#============================================================================#
use strict;
use warnings;
use File::Spec;
use Getopt::Long;

my ($Need_help, $Dir, $Out_file );
GetOptions(
    "help"      => \$Need_help,
    "dir=s"      => \$Dir,
    "o=s"       => \$Out_file,
);

die `pod2text $0` if ($Need_help);

#============================================================================#
#                              Global Variable                               #
#============================================================================#

$Dir ||= "./";
$Out_file ||= File::Spec->rel2abs($Dir).'/run_sel_rep.sh'; 
#============================================================================#
#                               Main process                                 #
#============================================================================#

print STDERR "---Program\t$0\tstarts --> ".localtime()."\n";

opendir(DIR, $Dir) or die $!;
open(OUT, '>', $Out_file) or die "Can't write $Out_file :$!";

print OUT "#!/usr/bin/bash\n";
while(my $file=readdir(DIR)){
    next if !($file=~/\.pir$/);
#    print "$file\n";
    print OUT " perl /home/xux/Projects/Motif_search/1_multi_seq_align/2_select_rep_seq.pl -i $file\n";
}

close OUT;
closedir(DIR);


print STDERR "---Program\t$0\tends  --> ".localtime()."\n";

#============================================================================#
#                               Subroutines                                  #
#============================================================================#


