#!/usr/bin/perl
#===========================================#
#--------------help-info-start--------------#

=head1 Name

    monitor.pl --> 

=head1 Usage

    perl  monitor.pl [options] [input file]

    -help       print this help to screen
    -in         input shell command file.
    -usage      Percent of cpu usage, default half (0.5).

=head1 Example

    perl  monitor.pl -h
    perl  monitor.pl -in test.sh -u 0.7

=head1 Contact

    Author      :  Xu Xiaopeng (CharlesXu)
    E-mail      :  charlesxu90@gmail.com 

=cut
#---------------help-info-end---------------#
#===========================================#

use strict;
use warnings;
use File::Basename;
use autodie qw(open);
use Getopt::Long;

my ($Need_help, $Input_file, $Usage );
GetOptions(
    "help"      => \$Need_help,
    "in=s"      => \$Input_file,
    "usage=f"   => \$Usage,
);

die `pod2text $0` if ($Need_help);

#===============================================#
#                 Global Variable               #
#===============================================#
die "Input shell command file not Specified! \n" if (!defined $Input_file);
$Usage ||= 0.5;
#===============================================#
#                 Global Variable               #
#===============================================#
print STDERR "---Program\t$0\tstarts --> ".localtime()."\n";

my @cmd = (); # list of commands to run
my $numps = sprintf("%.0f", `nproc` * $Usage);

open(IN, '<', $Input_file) or die "Can't read $Input_file : $!"; 
while(<IN>){
    next if /^#/ or /^\s+$/;
    push @cmd, $_;
    print $_;
}
close IN;

my %pid = ();
foreach my $cmd (@cmd) {
    my $pid = fork();
    if ($pid) {
        $pid{$pid} = 1;
    } else {
        warn "#calling <$cmd> ...\n";
        system("$cmd 2>&1");
        exit;
    }
    while (keys %pid >= $numps) {
        $pid = wait();
        warn "#process $pid finished!\n";
        delete $pid{$pid} if defined $pid{$pid};
    }
}
while (scalar keys %pid) {
    my $pid = wait();
    warn "#process $pid finished!\n";
    delete $pid{$pid} if defined $pid{$pid};
}

warn "#done!!!\n";

print STDERR "---Program\t$0\tends  --> ".localtime()."\n";
