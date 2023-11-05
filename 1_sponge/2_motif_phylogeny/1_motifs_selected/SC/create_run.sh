for i in SC_clu*; do echo "cd ../$i">>run.sh;echo "nohup sh hmmsearch.sh &">>run.sh;done
