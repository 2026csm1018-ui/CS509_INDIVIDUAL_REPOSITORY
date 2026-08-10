# CS509 Individual Repository

This repository contains the implementations of the CS509 lab assignments.

Each lab assignment is maintained in a separate directory with its own source code, test cases, executable, and README.md containing the details specific to that assignment.

## Repository Structure

```text
CS509_INDIVIDUAL_REPOSITORY/
│
├── run.sh
├── README.md
│
├── Lab_Assignment_01/
│   ├── README.md
│   └── ...
│
├── Lab_Assignment_02/
│   ├── README.md
│   └── ...
│
└── ...

## Running the Assignments

A common run.sh script is provided in the root directory to launch the required lab assignment.

First, give the script execute permission:

chmod +x run.sh

Then run the launcher from the root directory:

./run.sh

The script displays a menu containing the available lab assignments. Select the required assignment by entering its corresponding option.

The launcher automatically enters the selected assignment's directory before executing it. This allows each assignment to maintain its own relative paths for input files, output files, test cases, and other resources.

## Assignment Documentation

Each lab assignment contains its own README.md with assignment-specific information, including:

- Objective and problem statement
- Implementation details
- Algorithms used
- Input and output formats
- Compilation and execution instructions
- Test case information

The root README.md provides only the general repository structure and instructions for using the common launcher.

## Requirements

The assignments are primarily implemented using C/C++ and can be compiled using g++.

For compilation requirements and instructions specific to an assignment, refer to the README.md inside that assignment's directory.

## Author

**Shahid Alam**

***Indian Institute of Technology, Ropar***
