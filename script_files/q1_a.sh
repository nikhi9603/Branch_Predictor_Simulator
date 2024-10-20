#!/bin/bash

trace_files=("gcc_trace.txt" "jpeg_trace.txt")

for trace_file in "${trace_files[@]}"; do
  for m in {7..12}; do
  ./bpsim "bimodal" "$m" "$trace_file" 
  done
done
