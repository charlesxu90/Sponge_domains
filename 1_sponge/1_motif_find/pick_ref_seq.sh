#perl SECOM/perl_support/del_domain_seq.pl -d Sc_ltAED075_E_superfamily.gff3 -f SC_proteins_ltAED075_E.fa -o Sc_ltAED075_E_superfamily_protein.fasta

#perl SECOM/perl_support/del_domain_seq.pl -d Xt_ltAED075_E_superfamily.gff3 -f XT_proteins_ltAED075_E.fa -o XT_proteins_ltAED075_E_protein.fasta
# Run SECOM
#cd /home/xux/Projects/SECOM/SECOM/Sponge/Sc_ltAED075_E/seed6/ && \
#    ../../../bin/SECOM && \
#cd ../seed7/ && \
#    ../../../bin/SECOM && \
#cd ../seed8/ && \
#    ../../../bin/SECOM && \
#cd ../seed9/ && \
#    ../../../bin/SECOM && \
#cd ../seed10/ && \
#    ../../../bin/SECOM && \
#cd ../seed11/ && \
#    ../../../bin/SECOM && \ 
#
#cd /home/xux/Projects/SECOM/SECOM/Sponge/XT_proteins_ltAED075_E/seed6/ && \
#    ../../../bin/SECOM && \
#cd ../seed7/ && \
#    ../../../bin/SECOM && \
#cd ../seed8/ && \
#    ../../../bin/SECOM && \
#cd ../seed9/ && \
#    ../../../bin/SECOM && \
#cd ../seed10/ && \
#    ../../../bin/SECOM && \
#cd ../seed11/ && \
#    ../../../bin/SECOM && \

# Clustalw preparation
#cd /home/xux/Projects/SECOM/SECOM/Sponge/Sc_ltAED075_E/seed6/ && \
#perl /home/xux/Projects/SECOM/SECOM/perl_support/0_split_file.pl -t 5 -d ./ -i *.out
#cd ../seed7 && \
#    perl /home/xux/Projects/SECOM/SECOM/perl_support/0_split_file.pl -t 5 -d ./ -i *.out
#cd ../seed8 && \
#    perl /home/xux/Projects/SECOM/SECOM/perl_support/0_split_file.pl -t 5 -d ./ -i *.out
#cd ../seed9 && \ 
#perl /home/xux/Projects/SECOM/SECOM/perl_support/0_split_file.pl -t 5 -d ./ -i *.out
#cd ../seed10 && \
#    perl /home/xux/Projects/SECOM/SECOM/perl_support/0_split_file.pl -t 5 -d ./ -i *.out
#cd ../seed11 && \
#   perl /home/xux/Projects/SECOM/SECOM/perl_support/0_split_file.pl -t 5 -d ./ -i *.out

#cd /home/xux/Projects/SECOM/SECOM/Sponge/XT_proteins_ltAED075_E/seed6/ && \
#    perl /home/xux/Projects/SECOM/SECOM/perl_support/0_split_file.pl -t 5 -d ./ -i *.out
#cd ../seed7 && \
#    perl /home/xux/Projects/SECOM/SECOM/perl_support/0_split_file.pl -t 5 -d ./ -i *.out
#cd ../seed8 && \
#    perl /home/xux/Projects/SECOM/SECOM/perl_support/0_split_file.pl -t 5 -d ./ -i *.out
#cd ../seed9 && \ 
#    perl /home/xux/Projects/SECOM/SECOM/perl_support/0_split_file.pl -t 5 -d ./ -i *.out
#cd ../seed10 && \
#    perl /home/xux/Projects/SECOM/SECOM/perl_support/0_split_file.pl -t 5 -d ./ -i *.out
#cd ../seed11 && \
#    perl /home/xux/Projects/SECOM/SECOM/perl_support/0_split_file.pl -t 5 -d ./ -i *.out

# Run Clustalw
#cd /home/xux/Projects/SECOM/SECOM/Sponge/Sc_ltAED075_E/seed6/ && \
#perl ../../../perl_support/1_run_clustalw_folder.pl -d ./ && \
#nohup sh run_clustalw.sh &
#cd ../seed7/ && \
#    perl ../../../perl_support/1_run_clustalw_folder.pl -d ./ && \
#    nohup sh run_clustalw.sh &
#cd ../seed8/ && \
#    perl ../../../perl_support/1_run_clustalw_folder.pl -d ./ && \
#    nohup sh run_clustalw.sh &
#cd ../seed10/ && \
#    perl ../../../perl_support/1_run_clustalw_folder.pl -d ./ && \
#    nohup sh run_clustalw.sh &
#cd ../seed11/ && \
#    perl ../../../perl_support/1_run_clustalw_folder.pl -d ./ && \
#    nohup sh run_clustalw.sh &
#
#cd /home/xux/Projects/SECOM/SECOM/Sponge/XT_proteins_ltAED075_E/seed6/ && \
#    perl ../../../perl_support/1_run_clustalw_folder.pl -d ./ && \
#    nohup sh run_clustalw.sh &
#cd ../seed7/ && \
#    perl ../../../perl_support/1_run_clustalw_folder.pl -d ./ && \
#    nohup sh run_clustalw.sh &
#cd ../seed8/ && \
#    perl ../../../perl_support/1_run_clustalw_folder.pl -d ./ && \
#    nohup sh run_clustalw.sh &
#cd ../seed10/ && \
#    perl ../../../perl_support/1_run_clustalw_folder.pl -d ./ && \
#    nohup sh run_clustalw.sh &
#cd ../seed11/ && \
#    perl ../../../perl_support/1_run_clustalw_folder.pl -d ./ && \
#    nohup sh run_clustalw.sh &
#

## Pick representative sequence
cd /home/xux/Projects/SECOM/SECOM/Sponge/Sc_ltAED075_E/seed6/ && \
       perl ../../../perl_support/2_run_sel_rep.pl -d ./ && \
sh run_sel_rep.sh && \ 

cd /home/xux/Projects/SECOM/SECOM/Sponge/Sc_ltAED075_E/seed7/ && \
       perl ../../../perl_support/2_run_sel_rep.pl -d ./ && \
sh run_sel_rep.sh && \

cd /home/xux/Projects/SECOM/SECOM/Sponge/Sc_ltAED075_E/seed8/ && \
       perl ../../../perl_support/2_run_sel_rep.pl -d ./ && \
sh run_sel_rep.sh && \

cd /home/xux/Projects/SECOM/SECOM/Sponge/Sc_ltAED075_E/seed9/ && \
       perl ../../../perl_support/2_run_sel_rep.pl -d ./ && \
sh run_sel_rep.sh && \

cd /home/xux/Projects/SECOM/SECOM/Sponge/Sc_ltAED075_E/seed10/ && \
       perl ../../../perl_support/2_run_sel_rep.pl -d ./ && \
sh run_sel_rep.sh && \

cd /home/xux/Projects/SECOM/SECOM/Sponge/Sc_ltAED075_E/seed11/ && \
       perl ../../../perl_support/2_run_sel_rep.pl -d ./ && \
sh run_sel_rep.sh && \

cd /home/xux/Projects/SECOM/SECOM/Sponge/XT_proteins_ltAED075_E/seed6/ && \
       perl ../../../perl_support/2_run_sel_rep.pl -d ./ && \
sh run_sel_rep.sh && \

cd /home/xux/Projects/SECOM/SECOM/Sponge/XT_proteins_ltAED075_E/seed7/ && \
       perl ../../../perl_support/2_run_sel_rep.pl -d ./ && \
sh run_sel_rep.sh && \

cd /home/xux/Projects/SECOM/SECOM/Sponge/XT_proteins_ltAED075_E/seed8/ && \
       perl ../../../perl_support/2_run_sel_rep.pl -d ./ && \
sh run_sel_rep.sh && \

cd /home/xux/Projects/SECOM/SECOM/Sponge/XT_proteins_ltAED075_E/seed9/ && \
       perl ../../../perl_support/2_run_sel_rep.pl -d ./ && \
sh run_sel_rep.sh && \

cd /home/xux/Projects/SECOM/SECOM/Sponge/XT_proteins_ltAED075_E/seed10/ && \
       perl ../../../perl_support/2_run_sel_rep.pl -d ./ && \
sh run_sel_rep.sh && \

cd /home/xux/Projects/SECOM/SECOM/Sponge/XT_proteins_ltAED075_E/seed11/ && \
       perl ../../../perl_support/2_run_sel_rep.pl -d ./ && \
sh run_sel_rep.sh 
