for i in *_CLUSTER*SIZE*; do echo "cd $i/StructAlign && for j in \`awk 'FNR <= 10 {print \$1}' *.pdb-spalign.out.tab\`;do cp /home/xux/db/pdb/cullpdb_pc40/*/\$j*.pdb spalign/; done" >$i/StructAlign/cp_spalign_pdb.sh; done
for i in *_CLUSTER*SIZE*; do echo "cd $i/StructAlign && for j in \`awk 'FNR <= 10 {print \$1}' *.pdb-tmalign.out.tab\`;do cp /home/xux/db/pdb/cullpdb_pc40/*/\$j*.pdb tmalign/; done" >$i/StructAlign/cp_tmalign_pdb.sh; done
