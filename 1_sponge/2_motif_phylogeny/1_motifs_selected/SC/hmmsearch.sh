for i in ~/db/species/peptides/*;
do perl ../../../0_perl_script/1.pick_dom_seq.pl -E 0.1 -p ./*.msa.hmm -fa $i;
done
