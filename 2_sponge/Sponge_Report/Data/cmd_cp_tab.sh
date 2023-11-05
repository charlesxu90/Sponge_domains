for i in `cat /home/xux/Projects/Sponge/2_sponge/3_raptorx/domain_ori.tab`; do mkdir -p $i/Seq $i/Hmmer $i/RaptorX $i/StructAlign; done
for i in `cat /home/xux/Projects/Sponge/2_sponge/3_raptorx/domain_ori.tab`; do species=${i%_*}; cluster=${i#*_}; cp ~/Projects/Sponge/2_sponge/2_secom/$species/${cluster,,}.txt* $i/Seq; done
for i in `cat /home/xux/Projects/Sponge/2_sponge/3_raptorx/domain_ori.tab`; do species=${i%_*}; cluster=${i#*_}; cp ~/Projects/Sponge/2_sponge/2-1_blast/$species/${cluster,,}/${cluster,,}.txt* $i; done
for i in `cat /home/xux/Projects/Sponge/2_sponge/3_raptorx/domain_ori.tab`; do species=${i%_*}; cluster=${i#*_}; cp ~/Projects/Sponge/2_sponge/2-2_hmmer/$species/${cluster,,}/* $i/Hmmer; done
for i in `cat /home/xux/Projects/Sponge/2_sponge/3_raptorx/domain_ori.tab`; do species=${i%_*}; cluster=${i#*_}; cp -r ~/Projects/Sponge/2_sponge/3_raptorx/$species/$i/* $i/RaptorX/; done
for i in `cat /home/xux/Projects/Sponge/2_sponge/3_raptorx/domain_ori.tab`; do species=${i%_*}; cluster=${i#*_}; cp -r ~/Projects/Sponge/2_sponge/3_raptorx/$species/$i/*align.out.tab $i/StructAlign; done
