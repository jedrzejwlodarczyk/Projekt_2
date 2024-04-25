#!/bin/bash

# Function to run the script and measure execution time
benchmark() {
    input_file=$1
    tree_type=$2

    echo "Benchmarking Tree Type $tree_type with input $input_file"
    result=$(/usr/bin/time -f "%e" ./program.exe --tree $tree_type < $input_file 2>&1 >/dev/null)
    echo "Result $result"
    time=$(echo $result | head -1)  # Extract real time from the time command output
    echo $time
    size=$(head -n 1 $input_file)
    # Append results to CSV file
    echo "$tree_type,$size,$time,$input_type" >> ./data/benchmark_results_for_bst.csv
    echo "------------------------"
}

# List of tree types
tree_types=("BST")

# List of input file types
input_files=("degraded_nodes_to_BST_for_Print" "degraded_nodes_to_BST_for_Exit" "degraded_nodes_to_BST_for_FindMinMax" "degraded_nodes_to_BST_for_Rebalance")

# Create or clear the CSV file
echo "TreeType,InputSize,Time,input_files" > ./data/benchmark_results_for_bst.csv

# Run the benchmark for each input file, tree type, and size
for input_type in "${input_files[@]}"; do
    for tree_type in "${tree_types[@]}"; do
        for input_file in "./data/benchmark/${input_type}_"*".txt"; do
            benchmark $input_file $tree_type
        done
    done
done
