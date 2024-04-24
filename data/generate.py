#Remember to pip3 install numpy
import numpy as np

def generate_nodes(size):
    return np.random.choice(range(0,size),size,replace=False)



# Set the sizes for the arrays
sizes = [2**x for x in range(1, 20)]
what=['Print','Rebalance','FindMinMax','Exit']

for i in range(len(what)):
    for size in sizes:
        # Generate arrays
        unique_nodes = generate_nodes(size)
        
        # Convert the array to a list
        unique_nodes = list(unique_nodes)
        
        # Save arrays to files
        with open(f'./data/benchmark/unique_nodes_to_{what[i]}_{size:08d}.txt', 'w') as f:
            f.write(str(size) + "\n")  # Write the size on the first line
            f.write(' '.join(map(str, unique_nodes)) + "\n")  # Write the nodes on the second line
            f.write(what[i] + "\n")  # Write the command on the third line

print("Arrays with unique numbers have been generated and saved to files.")