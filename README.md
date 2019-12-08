# Theta Tau Happiness Maximization

This is a program to quickly and accurately match Bigs and Littles according to their stated preferences and general personalities. Read below for general setup, usage, assumptions about input, and the algorithms behind it. Made for Fall '19 Pledge Project.     

## Assumptions

We assume our input to be 3 CSV files: `weights.csv`, `big-rankings.csv`, and `little-rankings.csv`.     
The `*-rankings` files include a given person's top 3 rankings for a potential Big/Little.     
Here are the contents we require in each (all cells are 0 indexed):     
     
`weights.csv`: Weights of each possible connection. Rows represent the choices of the Bigs, Columns represent those of the Littles. 0 means a person was not on the list, 3 means they were third on the list, 2 means second, and 1 meants first. For example, the value of the cell at (2, 1) represents the weight for a Big ranking a Little as 2nd and a Little ranking that Big as 1st. In this case, that value would be 47:     

![weights picture](/misc/weights.png)

`big-rankings.csv`: Big's preferences of Littles. 1st entry contains the name of the Big, 2nd entry is that Little's 1st choice of Little, 3rd entry is the 2nd choice of Little, 4th entry is the 3rd choice of Little. Below is an example file     

```
rachel, zach, jorge, evan
ryan, zach, evan, ashley
erin, jorge, evan, ashley
frank, jorge, evan, zach
matt f, zach, sydney, jorge
suhaas, evan, ashley, sydney
```

`little-rankings.csv`: Little's preferences of Bigs. 1st entry contains the name of the Little, 2nd entry is that Little's 1st choice of big, 3rd entry is the 2nd choice of big, 4th entry is the 3rd choice of big. Below is an example file     

```
zach, ryan, rachel, frank
evan, ryan, frank, erin
jorge, frank, erin, rachel
ashley, rachel, erin, frank
sydney, erin, frank, rachel
vince, matt f, frank, rachel
```

Most importantly, all values in `csv` files must be separated by a space and comma with the exception of the first entry in a row. See the `test/` directory for examples of correctly formatted input. Additionally, the number of littles must be greater than or equal to the number of bigs.     

## How it Works

This problem can be well represented by a graph - specifically a bipartite graph (two distinct sets of nodes). These distinct sets represent brothers and pledges (note - there will never be connections within the same set). A node refers to a person in one of these sets, and an edge represents the compatibility between them. We first fill an adjacency matrix using the weights given. From here, we add all edges to a max-heap and repeatedly 'take' the maximum edge, ignoring edges to people who are already matched so that one big does not get multiple littles. This algorithm ensures the matching of any one-to-one pairs because that is the highest possible connection value.     

![bipartite graph](/misc/bipartite_graph.png)

## Setup

1. Have terminal with `git` and `c++11` installed on your computer.

2. Have your input files prepared.

3. `git clone` this repo. Open a terminal, navigate to the file location of your choosing, and type     
   `$ git clone https://github.com/eparres00/happiness-maximization.git`  

## Usage    

1. Make sure you have `clone`d this repo and are in that directory. Do this by running `$ pwd`. You should see something like this     
   `$ /mnt/c/Users/zaboy/MyFiles/freetime_programming/tht/happiness-maximization`     

2. `make` the executable. Do this by typing `$ make happy`. You should receive no errors.    

3. run the executable using `./happy`. Be sure to specify flags and input files in the format:     
   
   `$ ./happy weights.csv big-rankings.csv little-rankings.csv <FLAGS>`     

   Here are the available flags and possible inputs to them:    
   
   | Long Name | Short Name | Description | Options |
   |:---------:|:----------:|:-----------|:------|
   |--algorithm|     -a     | specifiy algorithm to use | 0 : prioritize high connections (locally optimal) |
   |		   |            |             | 1 : prioritize maximum group satisfaction (globally optimal) |
   |--show-weights|  -w     | pretty print the weights file |
   |--show-graph|    -g     | pretty print the graph from the input file |
   |--help     |     -h     | print help output|
