
# inotifywait ./tests |
# while read -r directory events filename; do
#     # Rscript run_tests.R
#     echo 'yo'
#
# done

watch_dirs=(./tests ./R ./src)

monitor() {
  inotifywait -m ${1} -e create,modify |
    while read path action file; do
        # echo "The file '$file' appeared in directory '$path' via '$action'"
        tput -T linux reset
        Rscript ./tests/_runner.R
    done
}
for dir in "${watch_dirs[@]}"
  do
    monitor ${dir} &
  done


#while ./watch.sh ./tests ; do Rscript run_tests.R ; done
