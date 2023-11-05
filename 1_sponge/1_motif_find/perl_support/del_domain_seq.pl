#!/usr/bin/perl
#==============================================================================#
#-------------------------------help-info-start--------------------------------#

=head1 Name

    del_domain_seq.pl --> This script is used to read domain info from .gff3 file, and remove domain sequence for corresponding sequence in .fa file

=head1 Usage

    perl  del_domain_seq.pl [options] [input file]

    -help       print this help to screen
    -o          write result to a file, default print to STDOUT .

=head1 Example

    perl  del_domain_seq.pl -h
    perl  del_domain_seq.pl -d domain.gff3 -f protein.fa -o rmd_seq.fa

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
use Bio::Seq;
use Bio::SeqIO;

my ($Need_help, $Domain_file, $Protein_file, $Seq_out );
GetOptions(
    "help"      => \$Need_help,
    "domain=s"  => \$Domain_file,
    "fa=s"      => \$Protein_file,
    "out=s"     => \$Seq_out,
);

die `pod2text $0` if ($Need_help);

#============================================================================#
#                              Global Variable                               #
#============================================================================#

die "Input files undefined: $!" if (!defined $Domain_file or !defined $Protein_file);
$Seq_out ||= 'seq_out.fa';
my $min_length = 20; # Minimum lengh

#============================================================================#
#                               Main process                                 #
#============================================================================#

print STDERR "---Program\t$0\tstarts --> ".localtime()."\n";

# Define variables
# %DomainInfo(2 layer hash, seqID and domain_start as keys, store end of Domain)
# After get the domain info, read the protein seque line by line and split it into parts depend on domains it contains.
# For each iteration, I also need to change the name of protein sequence to make it consistent

open(DOMAIN, '<', $Domain_file) or die "Can't read $Domain_file : $!";
my %DomainInfo;
my @domain_info;
while(<DOMAIN>)
{
    chomp;
    @domain_info = split /\s+/, $_;
    if(!defined $DomainInfo{$domain_info[0]}{$domain_info[3]}){
        $DomainInfo{$domain_info[0]}{$domain_info[3]} = $domain_info[4];
    }elsif($DomainInfo{$domain_info[0]}{$domain_info[3]} == $domain_info[4]){
        # The domain info is duplicated
        next;
    }else{
        # Domains which start in the same location, take the longer one
        if ($DomainInfo{$domain_info[0]}{$domain_info[3]} < $domain_info[4]) {
            $DomainInfo{$domain_info[0]}{$domain_info[3]} = $domain_info[4];
        }
    }
}
close DOMAIN;

my $PROTEIN = Bio::SeqIO->new( -file => $Protein_file, -format =>'fasta');
my $OUT = Bio::SeqIO->newFh( -file=>">$Seq_out", -format =>'fasta'); 

# Test stored domain info
#foreach my $seqID (sort keys %DomainInfo){
#    print $seqID."\t";
#    foreach my $dstart (sort {$a <=> $b} keys %{$DomainInfo{$seqID}}){
#        print $dstart."-".$DomainInfo{$seqID}{$dstart}."\,";
#    }
#    print "\n";
#}

# Then, parse the sequences
my @protein;
my $seq;
my $count = 0;# For test
my ($seq_id, $new_seq);
while($seq = $PROTEIN->next_seq()){
    next if $count >= 2; #For test
    $seq_id = $seq->display_id();
    next if(!defined $DomainInfo{$seq_id});
    
    # Find the start and end of each sub-sequence(possible motif/m) after removing domain
    my ($d_start, $m_start, $m_end, $prev_dend, $counter)=(1,1,1,1,1);
    my @split_pos; # Stores the start and end of sub-sequences
    for $d_start ( sort {$a<=>$b} keys %{$DomainInfo{$seq_id}}){
        if ($counter == 1) {
                ### Start domain of a sequence

            if($d_start>= $min_length){
                $m_end = $d_start;
                push @split_pos, "$m_start\-$m_end";
            }
            $prev_dend = $DomainInfo{$seq_id}{$d_start};# assign d_end to $prev_dend
            $counter = $counter + 1;
        }
        else{
            if($prev_dend >= $DomainInfo{$seq_id}{$d_start}){
                ### Situation 1: all overlap
                ###   ---------
                ###    -------
            }elsif($prev_dend < $DomainInfo{$seq_id}{$d_start} and $d_start < $prev_dend+$min_length){
                ### Situation 2: partial overlap
                ###  --------
                ###         -------
                $prev_dend = $DomainInfo{$seq_id}{$d_start};
            }elsif( $prev_dend < $DomainInfo{$seq_id}{$d_start} and $d_start >= $prev_dend+$min_length){
                ### Situation 3: no overlap
                ### -------
                ###          -----
                $m_start = $prev_dend;
                $m_end = $d_start;
                push @split_pos, "$m_start\-$m_end";
                $prev_dend = $DomainInfo{$seq_id}{$d_start};
            }

            if($counter == scalar keys %{$DomainInfo{$seq_id}}){
                ### For last domain
                if($prev_dend+$min_length <= $seq->length()){
                    $m_start = $prev_dend;
                    $m_end = $seq->length();
                    push @split_pos, "$m_start\-$m_end";
                }
            }
            $counter = $counter + 1;
        }
    }

    my ($sub_pos,$id_sufix);
    my $counter2 = 1;
    my @start_end;
    for $sub_pos (@split_pos){
        if(scalar @split_pos > 1){
            $id_sufix="\/$counter2";
            $counter2 = $counter2 + 1;
        }else{
            $id_sufix="";
        }
        @start_end = split(/\-/,$sub_pos);
        $new_seq = $seq->subseq($start_end[0], $start_end[1]); 
        my $seq_obj = Bio::Seq->new(-seq=>$new_seq,-display_id => $seq_id."$id_sufix",
            -alphabet => 'protein');
        print $OUT $seq_obj; 
    }
}
#close $PROTEIN;
#close $OUT;

print STDERR "---Program\t$0\tends  --> ".localtime()."\n";

#============================================================================#
#                               Subroutines                                  #
#============================================================================#

