//
// Created by Meniem on 28-Nov-23.
//

#include <algorithm>
#include "RegularDefinition.h"
#include "../Util/Util.h"


RegularDefinition::RegularDefinition() = default;

const std::string &RegularDefinition::getName() const {
    return name;
}

const std::string &RegularDefinition::getRegex() const {
    return regex;
}

RegularDefinition::RegularDefinition(std::string name, std::string regex) : name(std::move(name)), regex(std::move(regex)) {}

int RegularDefinition::standardizeRegex(std::vector<RegularDefinition> regularDefinitions) {
    removeConsecutiveSpaces(regex);
    parenthesizeClosures(regex);
    regex = parenthesizeDisjunctions(regex);
    int statusCode = enumerateRanges(regex);
    if (statusCode == -1)
        return -1;
    replaceDefinitions(regex, std::move(regularDefinitions));
    return 0;
}

int RegularDefinition::enumerateRanges(std::string &str) {
    std::string result;
    for(int i = 0; i < str.length(); i++){
        char c = str[i];
        if (c != '-')
            result += c;
        else {
            if (str[i-1] == '\\') //escaped reserved '-' character
                result += c;
            else {
                // Check if there is an alphanumeric before and after the '-' with spaces or not.
                if ( (isalnum(str[i-1]) || isalnum(str[i-2])) && (isalnum(str[i+1]) || isalnum(str[i+2])) ){
                    // erase the last character added to result while handling space.
                    (str[i-1] != ' ') ? result.erase(result.size() - 1) : result.erase(result.size() - 2);
                    char beginning = (str[i-1] != ' ') ? str[i-1] : str[i-2];
                    char end = (str[i+1] != ' ') ? str[i+1] : str[i+2];
                    char ch;
                    // Add the whole range
                    result += '(';
                    for(ch = beginning; ch < end; ch++){
                        result += "(" + std::string(1, ch) + ")|";
                    }
                    result += "(" + std::string(1, ch) + "))";
                    // Skip the character after '-' as it's already included in the range while handling space.
                    (str[i+1] != ' ') ? i++ : i+=2;
                }
                else{
                    return -1;
                }
            }
        }
    }
    str = result;
    return 0;
}

void RegularDefinition::replaceDefinitions(std::string &str, std::vector<RegularDefinition> regularDefinitions) {
    std::string result;
    std::string accumulator;

    for (int i = 0; i < str.length(); ++i) {
        char c = str[i];
        char reservedChars[] = {'=', '+', '*', '|', '(', ')'};

        if (c == ' ') {
            // Checks if the accumulator value the word is defined in the regular definition's array
            auto it = std::find_if(regularDefinitions.begin(), regularDefinitions.end(),
                                   [&accumulator](const RegularDefinition& def) {
                                       return def.name == accumulator;
                                   });
            if (it != regularDefinitions.end()) {
                result += "(" + it->regex + ")"; //If it's found then add the regex of the regular definition to the result ie. (Expand Definition)
            } else {
                result += accumulator; // If not then just add it to the result.
            }
            result += c;
            accumulator.clear();
            // Does the same thing but instead of delimiting by space we delimit by special reserve characters
        } else if (std::find(std::begin(reservedChars), std::end(reservedChars), c) != std::end(reservedChars)) {
            if (i > 0 && str[i - 1] == '\\') { // Check if it has an escape character.
                accumulator += c; // If it does then treat it like any other character
            } else { // If it doesn't then it has a special meaning and should be regarded as delimiter like space, so we do the same thing.
                auto it = std::find_if(regularDefinitions.begin(), regularDefinitions.end(),
                                       [&accumulator](const RegularDefinition& def) {
                                           return def.name == accumulator;
                                       });
                if (it != regularDefinitions.end()) {
                    result += "(" + it->regex + ")";
                } else {
                    result += accumulator;
                }
                result += c;
                accumulator.clear();
            }
        } else {
            accumulator += c;
        }
    }
    result += accumulator;
    str = result;
}

std::string RegularDefinition::parenthesizeDisjunctions(std::string &str) {
    std::string result;
    std::string accumulator;
    bool disjunctionFound = false;
    for (int i = 0; i < str.length(); i++){ // Loop over the whole input string
        char c = str[i];
        if (c != '|' && c != '(') // If the character is not a disjunction or a left curly bracket then it gets treated normally.
            accumulator += c;
        else if (c == '('){ // When a left curly bracket is found then recursion is needed to parenthesize disjunctions inside brackets to maintain precedence of operations.
            // Loop until we find the closing bracket of our opening bracket
            int j = i+1;
            int moreBrackets = 1;
            while (j < str.length()){
                if (str[j] == '(')
                    moreBrackets++;
                if (str[j] == ')'){
                    moreBrackets--;
                    if (moreBrackets == 0)
                        break;
                }
                j++;
            }
            int endingBracket = j;
            // Get the string inside the brackets
            std::string betweenBrackets = str.substr(i+1, endingBracket - (i+1));
            std::string betweenBracketsAfterModification = parenthesizeDisjunctions(betweenBrackets);  //Recursively call the same function and return the modified string
            accumulator +=  "(" + betweenBracketsAfterModification + ")";
            i = endingBracket; // Move the counter to the end of the bracket as we already processed it recursively.
        }
        else {
            // Handle Disjunction's Left and Right parameters with spaces.
            bool spaceBefore = false;
            bool spaceAfter = false;
            if (str[i-1] == ' '){
                accumulator.pop_back();
                spaceBefore = true;
            }

            if (str[i+1] == ' ')
                spaceAfter = true;


            result += "(" + accumulator + ")";
            spaceBefore ? result += " |" : result += "|";
            if (spaceAfter){
                result += " ";
                i++;
            }
            disjunctionFound = true;
            accumulator.clear();
        }
    }

    disjunctionFound ? result += "(" + accumulator + ")" : result += accumulator;
    return result;
}

void RegularDefinition::parenthesizeClosures(std::string &str) {
    std::string result;
    char delimiters[] = {' ', '+', '*', '|',  '('};
    for (int i = 0; i < str.length(); ++i) {
        char c = str[i];
        if (c == '+' || c == '*'){
            if (str[i-1] != '\\'){
                if (str[i-1] == ')') // Ignore already parenthesized closure.
                    continue;
                int j = i-1;
                while (j >= 0){ // Find the beginning of the word that has closure by checking delimiters
                    if (std::find(std::begin(delimiters), std::end(delimiters), str[j]) != std::end(delimiters))
                        break;
                    j--;
                }
                str.insert(j+1, 1, '(');
                str.insert(i+1, 1, ')');
                i+=2; // adjust loop for both inserts.
            }
        }
    }
}
