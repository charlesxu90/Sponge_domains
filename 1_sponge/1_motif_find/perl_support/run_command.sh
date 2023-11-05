perl SECOM/perl_support/del_domain_seq.pl -d Sc_ltAED075_E_superfamily.gff3 -f SC_proteins_ltAED075_E.fa -o Sc_ltAED075_E_superfamily_protein.fasta

perl SECOM/perl_support/del_domain_seq.pl -d Xt_ltAED075_E_superfamily.gff3 -f XT_proteins_ltAED075_E.fa -o XT_proteins_ltAED075_E_protein.fasta

perl ../../perl_support/0_split_file.pl -d ./ -i *.out

cd ../XT_proteins_ltAED075_E/
perl ../../perl_support/0_split_file.pl -d ./ -i *.out
perl ../../perl_support/1_run_clustalw_folder.pl -d ./ 
nohup sh run_clustalw.sh &

cd ../Sc_ltAED075_E/
perl ../../perl_support/1_run_clustalw_folder.pl -d ./ 
nohup sh run_clustalw.sh &
perl ../../perl_support/2_run_sel_rep.pl -d ./ 
nohup sh run_sel_rep.sh &

cd ../XT_proteins_ltAED075_E/
perl ../../perl_support/2_run_sel_rep.pl -d ./ 
nohup sh run_sel_rep.sh &

