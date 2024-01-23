# Compiler Generator
<p align="center">
    <img src="https://raw.githubusercontent.com/Ghost8345/Compiler-Generator/docs/docs/Images/CompilerGenerator.png" alt="Logo" width="35%" height="35%">
</p>

## Overview
> This is a plug and play compiler which can accommodate with any language once you provide it with its lexical rules and grammar.

## Authors
+ [Ahmed Adel Abudef](https://github.com/Deffo0)
+ [Abdelmeniem Hany](https://github.com/Ghost8345)
+ [Youssef Saeed](https://github.com/usefSaeed)
+ [Zyad Samy](https://github.com/ZyadSamy)

## Setup
1. Clone the repo.
```
git clone https://github.com/Ghost8345/Compiler-Generator.git
```
1. Change the directory to the cloned repo.
```
cd Compiler-Generator
```
1. Load CMakeLists.txt to your project.
1. Add the `Lexical Rules` and `Grammar` paths as program arguments for `Driver.cpp`.
1. Compile `Driver.cpp`.
1. Run the compiled version.

## System Flow Chart
<p align="center">
    <img src="https://raw.githubusercontent.com/Ghost8345/Compiler-Generator/docs/docs/Images/GeneralizedCompilerFlowchart.jpg" alt="Logo" width="70%" height="100%">
</p>

## Inputs 
+ Lexical Rules
+ Grammar
+ Language Code (Program)

## Outputs
+ Stored Data in Files
  + Parsing Table
+ Console Output
  + Symbol Table
  + Parsing Tree
  + Parsing Stack Trace
  + Production Output
  + Errors Reporting

## What Next 🤔
+ Implement the Syntax Directed Translation Scheme and Type checkers.
+ Implement the Intermediate Code Generation Phase.
