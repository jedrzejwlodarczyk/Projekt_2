#!/bin/bash

# Function to run the script and measure execution time
benchmark() {
    input_file=$1
    algorithm=$2
    algorithm_name=${algorithm_mapping_reverse[$algorithm]}
    # List of supported languages and their run commands
    runrust=""
    runjava=""
    runpython=""
    runcpp="./main"
    #runexample="python3 example.py"
    runcurrent=$runcpp

    echo "Benchmarking Algorithm $algorithm with input $input_file"
    result=$(/usr/bin/time -f "%e" ${runcurrent} --algorithm $algorithm < $input_file 2>&1 >/dev/null)
    echo "Result $result"
    time=$(echo $result | head -1)  # Extract real time from the time command output
    echo $time
    size=$(head -n 1 $input_file)
    # Append results to CSV file
    echo "$algorithm_name,$size,$time,$input_type" >> benchmark_results.csv
    echo "------------------------"
}

# Map algorithm names to numbers
declare -A algorithm_mapping=(
    ["findminmax"]=1
    ["rebalance"]=2
    ["insert"]=3
    ["printinorder"]=4
)

# Create a reverse mapping from numbers to algorithm names
declare -A algorithm_mapping_reverse
for algorithm_name in "${!algorithm_mapping[@]}"; do
    algorithm_number=${algorithm_mapping[$algorithm_name]}
    algorithm_mapping_reverse[$algorithm_number]=$algorithm_name
done


# List of input file types
input_files=("random_nodes_to_findminmax" "random_nodes_to_rebalance" "random_nodes_to_insert" "random_nodes_to_printinorder")
#input_files=("random_array")

# Create or clear the CSV file
echo "Algorithm,InputSize,Time,input_files" > benchmark_results.csv

# Run the benchmark for each input file, sorting algorithm, and size
for input_type in "${input_files[@]}"; do
    for algorithm_name in "${!algorithm_mapping[@]}"; do
        algorithm_number=${algorithm_mapping[$algorithm_name]}
        for input_file in "benchmark/${input_type}_"*".txt"; do
            benchmark $input_file $algorithm_number
        done
    done
done
