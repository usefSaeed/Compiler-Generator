
# Syntax Phase Documentation

## Table of Contents
+ [Grammar Reader and Converter](#Grammar-Reader-and-Converter)
+ [First and Follow Generator](#First-and-Follow-Generator)
+ [Predictive Parser: Parsing Table](#Parsing-Table)
+ [Predictive Parser: Parsing](#Parsing)

## Grammar Reader and Converter
#### Description
The first part handles parsing the Grammar rules file and turning it into a standardized list of Non-Terminals and Start Symbol.

#### Steps
1. (1st Pass) Read the Grammar rules file line by line, validate correctness, and detect undefined or doubly defined Non-Terminals.
2. (2nd Pass) Read the Grammar rules file line by line, find Terminals in Productions, handle escaped reserved characters, populate Non-Terminal productions.
3. Apply Left Factoring (bonus) and Eliminate Left Recursion (bonus).
4. Return a list of standardized Non-Terminals and the Non-Terminal Start Symbol.

#### Data Structures
- `std::unordered_set<std::string> terminals`: Holds all Terminal names in the grammar.
- `std::unordered_set<std::string> nonTerminalNames`: Holds all Non-Terminal names in the grammar.
- `std::vector<NonTerminal> nonTerminals`: Holds all Non-Terminals with their productions.

#### Assumptions
- Reserved characters need to be escaped to be used as a Terminal.
- The Start Symbol is the first Non-Terminal in the grammar file.
- No escaped characters are present in the Non-Terminal Name.

## First and Follow Generator
#### Description
This part generates the First and Follow sets for each nonterminal.

#### Steps
1. Compute First sets for nonterminals.
2. Compute Follow sets for nonterminals.
3. Handle epsilon and locked nonterminals to avoid infinite recursion.

#### Data Structures
- `std::vector<std::shared_ptr<NonTerminal>> NTs`: Holds all non-terminals of the grammar.
- `std::unordered_set<Terminal*> firstSet`: First set attribute in each non-terminal.
- `std::unordered_set<Terminal*> followSet`: Follow set attribute in each non-terminal.
- `std::unordered_set<NonTerminal*> lockedNTs`: Contains non-terminals being computed to eliminate infinite recursion.

#### Assumptions
- Input grammar should be properly formatted with all productions.
- Input grammar should be left-refactored and free of any left recursion.
- Nonterminal vector size equals the number of nonterminals in the grammar.

## Parsing Table
#### Description
This part constructs the parsing table for predictive parsing.

#### Steps
1. Compute NTs with First Set and Follow Set.
2. Search for matched production in the First set.
3. Construct the parsing table based on First and Follow sets.
4. Print and export the parsing table.

#### Data Structures
- `std::vector<std::shared_ptr<NonTerminal>> NTs`: Holds all non-terminals of the grammar.
- `std::unordered_map<std::pair<NonTerminal*, std::string>, ParsingTableEntry> parsingTable`: Holds the parsing table.

#### Assumptions
- Sync and Epsilon represented by boolean vars inside the ParsingTableEntry.

## Parsing 
#### Description
This part handles the actual parsing, generating the parsing tree, and error recovery.

#### Steps
1. Seed the stack with the Start Symbol and repeat until the stack is empty.
2. Match or handle errors based on the parsing table entry and input token.
3. Implement panic-mode error recovery.

#### Data Structures
- `std::stack<Symbol*> stack`: Stack for parsing.
- `std::stack<ParsingTreeNode*> nodes`: Stack for parsing tree nodes.
- `std::vector<ParsingTrace> traces`: Keeps track of traces while parsing.
- `ParsingTreeNode`: Used for creating the parsing tree.
- `ParsingTree`: Wrapper for the root node.
- `ParsingTrace`: Used for keeping track of parsing traces.
- `ParsingResult`: Wrapper that contains traces and the final parsing tree.
