# Theta Tau Happiness Maximization

This is a program to quickly and accurately match Bigs and Littles according to their stated preferences and general personalities. Read below for general setup, usage, assumptions about input, and the algorithms behind it. Made for Fall '19 Pledge Project.     

## Assumptions

We assume our input to be 3 CSV files: `weights.csv`, `big-rankings.csv`, and `little-rankings.csv`.     
The `*-rankings` files include a given person's top 3 rankings for a potential Big/Little
Here are the contents we require in each (all cells are 0 indexed):     
     
`weights.csv`: Weights of each possible connection. Rows represent the choices of the Bigs, Columns represent those of the Littles. For example, the value of the cell at (2, 1) represents the weight for a Big ranking a Little as 3rd and a Little ranking that Big as 2nd.     
`big-rankings.csv`: Little's preferences of Bigs. 1st column contains the name of the Little, 2nd column is that Little's 1st choice of Big, 3rd column is that Little's 2nd choice of Big, 4th column is that Little's 3rd choice of Big

here is an example:     ![weights picture](/misc/weights.png)

`big-rankings.csv`: Preferences of bigs. Rows represent

`little-rankings.csv`:

`little-rankings.csv`: Big's preferences of Littles. 1st column contains the name of the Big, 2nd column is that Big's 1st choice of Little, 3rd column is that Big's 2nd choice of Little, 4th column is that Big's 3rd choice of Little

## How it Works

describe the algorithms

## Setup

## Usage
