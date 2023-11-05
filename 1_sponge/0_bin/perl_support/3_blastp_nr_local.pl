#!/usr/bin/perl
#==============================================================================#
#-------------------------------help-info-start--------------------------------#

=head1 Name

    3_blastp_nr.pl --> This script picks up sequences and run blastp against ncbi non-redundant database locally.

=head1 Usage

    perl  3_blastp_nr.pl [options] [input file]

    -help       print this help to screen
    -in         input sequence file
    -dir        out put folder
    -tag        tag
    -db         database to search
    #-o          write result to a file, default print to STDOUT .

=head1 Example

    perl  3_blastp_nr.pl -h
    perl  3_blastp_nr.pl -i sequences.fa -d output_folder

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
use Bio::SeqIO;
use Bio::Seq;
use Bio::Tools::Run::RemoteBlast;

my ($Need_help, $Input_file, $Out_folder, $db, $tag);
GetOptions(
    "help"      => \$Need_help,
    "in=s"      => \$Input_file,
    "dir=s"     => \$Out_folder,
    "db=s"        => \$db,
    "tag=s"       => \$tag,
);

die `pod2text $0` if ($Need_help);

#============================================================================#
#                              Global Variable                               #
#============================================================================#

die "No input file: $!" if (!defined $Input_file);
$Out_folder ||='./';
$db ||="/home/xux/db/ncbi_nr/nr";
$tag ||="out";
#============================================================================#
#                               Main process                                 #
#============================================================================#

print STDERR "---Program\t$0\tstarts --> ".localtime()."\n";

my $in = Bio::SeqIO->new(-file=>$Input_file , -format => 'fasta' );

opendir(DIR,$Out_folder);
open(SH, ">$Input_file\_blastp_$tag\.sh");
while(my $seq = $in->next_seq()){
    # save the output
    my $filename = $seq->display_id()."\.seq";
    open(SEQFILE, ">$filename") or die "cannot write to seq";
    print SEQFILE ">".$seq->display_id."\n";
    print SEQFILE $seq->seq."\n";
    close SEQFILE;
    print SH "blastp -db $db -query $filename -out $filename\_$tag.out\n";
}
close SH;
# This example shows how to change a CGI parameter:
# $Bio::Tools::Run::RemoteBlast::HEADER{'MATRIX_NAME'} = 'BLOSUM45';
# $Bio::Tools::Run::RemoteBlast::HEADER{'GAPCOSTS'} = '15 2';

# And this is how to delete a CGI parameter:
# delete $Bio::Tools::Run::RemoteBlast::HEADER{'FILTER'};
closedir(DIR);
print STDERR "---Program\t$0\tends  --> ".localtime()."\n";

#============================================================================#
#                               Subroutines                                  #
#============================================================================#


