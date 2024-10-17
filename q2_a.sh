#!/bin/bash

trace_files=("gcc_trace.txt" "jpeg_trace.txt")

for trace_file in "${trace_files[@]}"; do
  for m in {7..12}; do
     for ((n = 2; n <= m; n += 2)); do 
     	./bpsim "gshare" "$m" "$n" "$trace_file" 
     done
  done
done
