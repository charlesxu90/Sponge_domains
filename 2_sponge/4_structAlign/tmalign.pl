#!/usr/bin/perl
#===========================================#
#--------------help-info-start--------------#

=head1 Name

    tmalign.pl --> Align a query against all pdb list

=head1 Usage

    perl  tmalign.pl [options] [input file]

    -help       print this help to screen
    -o          write result to a file

=head1 Example

    perl  tmalign.pl -h
    perl  tmalign.pl -in query -lst List -dbdir dbdir -tmalign tmalign -o out_filename

=head1 Contact

    Author          :  Xu Xiaopeng (Charles Xu)
    E-mail          :  charlesxu90@gmail.com
    Institution     :  KAUST

=cut
#---------------help-info-end---------------#
#===========================================#
use strict;
use warnings;
use Getopt::Long;

my ($Need_help, $Query, $List, $Dbdir, $Out_file, $tmalign);
GetOptions(
    "help"      => \$Need_help,
    "in=s"      => \$Query,
    "lst=s"     => \$List,
    "dbdir=s"   => \$Dbdir,
    "tmalign=s" => \$tmalign,
    "o=s"       => \$Out_file,
);

die `pod2text $0` if ($Need_help);
#===============================================#
#                 Global Variable               #
#===============================================#
die "Params not fit: $!" if (!defined $Query or !defined $List or !defined $Dbdir or !defined $tmalign );
$Out_file ||= "$Query-tmalign.out";

#===============================================#
#                  Main Process                 #
#===============================================#

warn "---Program\t$0\tstarts --> ".localtime()."\n";

my @pdbid = ();
open(LIST, '<', $List) or die "Can't read $List: $!";
open(OUT, '>', $Out_file) or die "Can't write $Out_file: $!"; 

foreach (<LIST>) {
    next if /^IDs/;       
    chomp; s/\s+.*//; $_ = lc;
    warn "Align with $_ ...\n";

    my ($id, $chain) = /^(....)(.)$/;
    my $dir = substr($id, 1, 2);
    my $pdbf = "$Dbdir/$dir/$_.pdb";

    my @normlen = (); my @tmscore = ();
    my ($rmsd, $alnlen, $seqid) = (undef, undef, undef);
    open(INPUT, "$tmalign $Query $pdbf -c|") or die "Error in tmalign: $!";
    foreach(<INPUT>){
        chomp;
        push(@normlen, (split(/\s+/))[3]) if /^Length/;
        push(@tmscore, (split(/\s+/))[1]) if /^TM-score/;
        ($alnlen, $rmsd, $seqid) = (split(/[=,]/))[1,3,6] if /^Aligned/;
    }
    close INPUT;

    print OUT join("\t", $id, $tmscore[-1], $normlen[-1], $alnlen, $rmsd, $seqid), "\n";
}

close LIST;
close OUT;

warn "---Program\t$0\tends  --> ".localtime()."\n";

