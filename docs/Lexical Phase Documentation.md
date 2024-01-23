
# Lexical Phase Documentation
## Table of Contents
+ [Rules File to RE](Rules-File-to-RE)
+ [RE to NFA](RE-to-NFA)
+ [NFA to DFA](NFA-to-DFA)
+ [Symbol Table Generator](Symbol-Table-Generator)
    
## Rules File to RE
#### Description
The first part handles parsing the rules file and transforming it into a normalized standardized regular expression that can be easily turned into an NFA.

#### Steps
1. Read the rules file line by line.
2. Detect if it's a keyword, punctuation, regular definition, or regular expression, and handle the cases appropriately. Exit gracefully if there is an error or an unstructured line.
3. Handle keywords and punctuation by assigning each one its own regular expression with the same name and token type.
4. Standardize regular definitions and expressions.
5. Return a list of standardized regular expressions.

#### Data Structures
- `Vector<String> allKeywords`: Holds all keywords while parsing the rules file.
- `Vector<String> allPunctuation`: Holds all punctuation while parsing the rules file.
- `Vector<String> regularDefinitions`: Holds all regular definitions.
- `Vector<String> regularExpressions`: Holds the final regular expressions.

#### Assumptions
- Keywords and punctuation must be separated by a space.
- '=' and ':' are added to the reserved symbols that must be escaped by ''.
- Space doesn't matter in disjunction, closure, or range.
- Keywords and punctuation can come anywhere in the rules file, and they will have the highest priority.
- Other regular expressions' priorities will be based on their precedence in the rules file.
- Regular Definitions must be defined before being used.

## RE to NFA
#### Description
The second part converts the regular expression with its operations to a non-finite automaton (NFA).

#### Steps
1. Construct fine-grain classes for NFA graph.
2. Define NFA arms and brain, considering parentheses.
3. Define Thompson algorithm transformations.
4. Walk through the regExp and convert it to NFA represented by the start state.
5. Combine NFAs into one.
6. Convert the graph to a map for easier reading and conversions (using DFS).

#### Data Structures
- `Vector<Transition> transitions`: Holds all transitions in each state.
- `stack<stack<State*>> nfaStack`: Holds the start and end state of each NFA during conversion.
- `stack<stack<String>> disjunctionStack`: Holds disjunction operations in each parentheses level.
- `unordered_map<pair<State*, char>, vector<State*>> transitionTable`: Represents the adjacency matrix between states.

#### Assumptions
- All disjunction operands must be surrounded by brackets ().

## NFA to DFA
#### Description
The third part turns the NFA into a DFA with minimized states.

#### Steps
1. Use the epsilon closure of the NFA start state as a seed to the unmarked stack.
2. While unmarked states are not empty, repeat for each state T and each symbol a:
   - Find the epsilon closure of states resulting from moving state T using symbol a.
   - If the set of states doesn't have a DFA state mapping, create a new state with the token of the highest priority.

#### Data Structures
- `unordered_map<std::unordered_set<State*>, State*>`: Mapping from a set of NFA states to a DFA state.
- `stack<unordered_set<State*>>`: Holds unmarked states.

#### Assumptions

## Symbol Table Generator
#### Description
  SimplyTakes the DFA as input and the input code file satisfying the grammar rules to generate the symbol table.
Takes the DFA as input and the input code file satisfying the grammar rules to generate the symbol table.
 it takes the DFA as input to initiate the constructor, so it has all the main states and all their transitions. Then it takes the input code file that supposedly satisfies the grammar rules that generated the DFA. The output of this part is the symbol table, where it has all the strings that represent a token and their corresponding token names, the syntax errors representing the indices and the characters that didn’t satisfy the DFA, and the trace which tells us how exactly the symbol table was generated and what happened in each state transition.
  ```
