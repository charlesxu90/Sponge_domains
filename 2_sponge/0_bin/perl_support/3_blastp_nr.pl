#!/usr/bin/perl
#==============================================================================#
#-------------------------------help-info-start--------------------------------#

=head1 Name

    3_blastp_nr.pl --> This script picks up sequences and run blastp against ncbi non-redundant database remotely.

=head1 Usage

    perl  3_blastp_nr.pl [options] [input file]

    -help       print this help to screen
    -i          input sequence file
    -d          out put folder
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

my ($Need_help, $Input_file, $Out_folder );
GetOptions(
    "help"      => \$Need_help,
    "in=s"      => \$Input_file,
    "dir=s"       => \$Out_folder,
);

die `pod2text $0` if ($Need_help);

#============================================================================#
#                              Global Variable                               #
#============================================================================#

die "No input file: $!" if (!defined $Input_file);
$Out_folder ||='./';

#============================================================================#
#                               Main process                                 #
#============================================================================#

print STDERR "---Program\t$0\tstarts --> ".localtime()."\n";

my ($prog, $db, $e_val)=('blastp', 'nr', '1e-2');
opendir(DIR,$Out_folder);
# Set params for blast
my @params = ( '-prog' => $prog, '-data' => $db, '-expect' => $e_val, '-readmethod' => 'searchIO');
my $factory = Bio::Tools::Run::RemoteBlast->new(@params);

#change a query parameter
#$Bio::Tools::Run::RemoteBlast::HEADER{'ENTREZ_QUERY'} = 'Homo sapiens [ORGN]';

#change a retrieval parameter
#$Bio::Tools::Run::RemoteBlast::RETRIEVALHEADER{'DESCRIPTIONS'} = 1000;

#remove a parameter
#delete $Bio::Tools::Run::RemoteBlast::HEADER{'FILTER'};

#$v is just to turn on and off the messages
my $v = 0;

my $in = Bio::SeqIO->new(-file=>$Input_file , -format => 'fasta' );
while(my $seq = $in->next_seq()){
    #Blast against a database
    #Alternatively, you could  pass in a file with many 
    #sequences rather than loop through sequence one at a time
    #Remove the loop starting 'while (my $input = $str->next_seq())'
    #and swap the two lines below for an example of that.
    my $r = $factory->submit_blast($seq);
    #my $r = $factory->submit_blast($Input_file);

    print STDERR "Waiting ..." if ($v>0);
    while(my @rids = $factory->each_rid){
        foreach my $rid (@rids){
            my $rc = $factory->retrieve_blast($rid);
            if(!ref($rc)){
                if($rc<0){
                    $factory->remove_rid($rid);
                }
                print STDERR "." if ($v > 0);
                sleep 5;
            }else{
                my $result = $rc->next_result();
                # save the output
                my $filename = $result->query_name()."\.out";
                $factory->save_output($filename);
                $factory->remove_rid($rid);
                print "\nQuery Name: ", $result->query_name(), "\n";
                while(my $hit = $result->next_hit){
                    next unless ($v >0);
                    print "\t hit name is ", $hit->name, "\n";
                }
            }
        }
    }
}

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


