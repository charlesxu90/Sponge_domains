#!/usr/bin/perl
#===========================================#
#--------------help-info-start--------------#

=head1 Name

    spalign.pl --> Align a query against all pdb list

=head1 Usage

    perl  spalign.pl [options] [input file]

    -help       print this help to screen
    -o          write result to a file

=head1 Example

    perl  spalign.pl -h
    perl  spalign.pl -in query -lst List -dbdir dbdir -spalign spalign -o out_filename

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

my ($Need_help, $Query, $List, $Dbdir, $Out_file, $SPalign);
GetOptions(
    "help"      => \$Need_help,
    "in=s"      => \$Query,
    "lst=s"     => \$List,
    "dbdir=s"   => \$Dbdir,
    "spalign=s" => \$SPalign,
    "o=s"       => \$Out_file,
);

die `pod2text $0` if ($Need_help);
#===============================================#
#                 Global Variable               #
#===============================================#
die "Params not fit: $!" if (!defined $Query or !defined $List or !defined $Dbdir or !defined $SPalign );
$Out_file ||= "$Query-spalign.out";

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

    my ($SPe, $SPa, $SPb, $normlen, $rmsd, $alnlen, $TMsa, $TMsb, $TMsc) = (undef, undef, undef, undef, undef, undef, undef, undef, undef);
    open(INPUT, "$SPalign $Query $pdbf|") or die "Error in SPalign: $!";
    foreach(<INPUT>){
        chomp;
        ($SPe, $SPa, $SPb, $normlen) = (split(/\s+/))[4,5,6,8] if /^Pfold/;
        ($rmsd, $alnlen, $TMsa, $TMsb, $TMsc) = (split(/\s+/))[1,3,7,8,9] if /^RMSD/;
    }
    close INPUT;

    print OUT join("\t", $id, $SPe, $normlen, $rmsd, $alnlen, $TMsa), "\n";
}

close LIST;
close OUT;
warn "---Program\t$0\tends  --> ".localtime()."\n";

