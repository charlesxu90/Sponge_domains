for k in *_CLUSTER*SIZE*/; do for j in `awk 'FNR <= 10 {print $1}' $k/StructAlign/*.pdb-spalign.out.tab`; do echo -e "spalign\t$j"; done >$k/annotation.tab;done
for k in *_CLUSTER*SIZE*/; do for j in `awk 'FNR <= 10 {print $1}' $k/StructAlign/*.pdb-tmalign.out.tab`; do echo -e "tmalign\t$j"; done >>$k/annotation.tab;done
for j in *_CLUSTER*SIZE*/RaptorX/dom*/ModelRank.rtf; do for i in `egrep  '\<[0-9][^I][0-9]' $j|awk 'FNR>=1&&$1>0{print $7}' `; do d=${j%/*}; echo -e ""${d##*/}"\t$i"; done >>${j%/*/*/*}/annotation.tab; done
