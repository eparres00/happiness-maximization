# Theta Tau Happiness Maximization

This is a program to quickly and accurately match Bigs and Littles according to their stated preferences and general personalities. Read below for general setup, usage, assumptions about input, and the algorithms behind it. Made for Fall '19 Pledge Project.     

## Assumptions

We assume our input to be 3 CSV files: `weights.csv`, `big-rankings.csv`, and `little-rankings.csv`.     
The `*-rankings` files include a given person's top 3 rankings for a potential Big/Little.     
Here are the contents we require in each (all cells are 0 indexed):     
     
`weights.csv`: Weights of each possible connection. Rows represent the choices of the Bigs, Columns represent those of the Littles. 0 means a person was not on the list, 3 means they were third on the list, 2 means second, and 1 meants first. For example, the value of the cell at (2, 1) represents the weight for a Big ranking a Little as 2nd and a Little ranking that Big as 1st. In this case, that value would be 47:     

![weights picture](/misc/weights.png)

`big-rankings.csv`: Little's preferences of Bigs. 1st column contains the name of the Little, 2nd column is that Little's 1st choice of Big, 3rd column is that Little's 2nd choice of Big, 4th column is that Little's 3rd choice of Big


`big-rankings.csv`: Preferences of bigs. Rows represent

`little-rankings.csv`:

`little-rankings.csv`: Big's preferences of Littles. 1st column contains the name of the Big, 2nd column is that Big's 1st choice of Little, 3rd column is that Big's 2nd choice of Little, 4th column is that Big's 3rd choice of Little

## How it Works

describe the algorithms

## Setup

## Usage

1. `clone` this repo. Open a terminal, navigate to the location of your choosing, and type     
   `$ git clone https://github.com/eparres00/happiness-maximization.git`      

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
