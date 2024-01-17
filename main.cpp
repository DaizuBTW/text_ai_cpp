#include <iostream>
#include <cstring>
#include <list>

using namespace std;

const string SEPARATORS = " .,;:!?-\"“”'‘’()[]{}+-*/=«»—–\n";

const string TEXT_TO_COMPARE = "In 15.05.1476, Ezio Auditore witnesses his father's unjust execution, setting him on a quest for revenge. Uncovering a connection to the Assassins, Ezio navigates Renaissance Italy, encountering historical figures and unraveling a Templar plot for power.\n"
                               "\n"
                               "Honing his Assassin skills, Ezio discovers a conspiracy to control artifacts with world-altering potential. The narrative unfolds against the backdrop of political turmoil and artistic brilliance, leading to a climactic confrontation in 20.11.1499.\n"
                               "\n"
                               "The story explores themes of revenge, redemption, and the broader battle for freedom, leaving a lasting impact on the Assassins' legacy.";

const string PRONOUNS[]{"you", "she", "they", "your", "his", "him", "her", "hers", "its", "our", "ours", "their",
                        "theirs",
                        "this", "these", "that", "those", "myself", "yourself", "himself", "herself", "itself", "some",
                        "something", "somebody", "someone", "any", "anything", "anybody", "anyone", "who", "what",
                        "whose",
                        "which", "whoever", "whatever", "whichever", "all", "both", "either", "each", "everybody",
                        "everyone", "everything", "another", "other", "others"};

const string CONJUNCTIONS[]{"also", "and", "because", "but", "both", "neither", "however", "moreover", "nevertheless",
                            "nor", "once", "otherwise", "still", "than", "that", "therefore", "although", "thus",
                            "unless", "whether", "while", "yet", "for", "against", "like", "unlike", "with",
                            "without", "within", "meanwhile", "whereas"};

const string PREPOSITIONS[]{"since", "for", "over", "till", "until", "from", "during", "after", "before", "across",
                            "along", "around", "into", "through", "above", "under", "behind", "between", "among",
                            "inside", "the"};

const int PRONOUNS_SIZE = 47;
const int CONJUNCTIONS_SIZE = 31;
const int PREPOSITIONS_SIZE = 21;

double antiPlagiarism(string text, string fragment);
list<string> cleanTextAndGetStringsList(string text);
bool isSeparator(char currChar);
string toLowerCase(string currString);
bool isPronoun(const string &word);
bool isConjunction(const string &word);
bool isPreposition(const string &word);
bool isCleanWord(const string &word);
bool isDigit(char currChar);
bool isNumberFromDate(const string &word);
list<string> removeDuplicates(list<string> strings);

int main() {
    cout << "Text to compare is following: " << endl << endl;
    cout << TEXT_TO_COMPARE << endl << endl;
    cout << "Text after cleaning is:" << endl << endl;
    list<string> result = cleanTextAndGetStringsList(TEXT_TO_COMPARE);
    for (const auto &str: result) {
        cout << "Word: " << str << endl;
    }
    return 0;
}

bool isPronoun(const string &word) {
    for (int i = 0; i < PRONOUNS_SIZE; ++i) {
        if (strcmp(PRONOUNS[i].c_str(), word.c_str()) == 0) {
            return true;
        }
    }

    return false;
}

bool isConjunction(const string &word) {
    for (int i = 0; i < CONJUNCTIONS_SIZE; ++i) {
        if (strcmp(CONJUNCTIONS[i].c_str(), word.c_str()) == 0) {
            return true;
        }
    }

    return false;
}

bool isPreposition(const string &word) {
    for (int i = 0; i < PREPOSITIONS_SIZE; ++i) {
        if (strcmp(PREPOSITIONS[i].c_str(), word.c_str()) == 0) {
            return true;
        }
    }

    return false;
}

bool isDigit(char currChar) {
    char digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int size = 10;
    for (int i = 0; i < size; ++i) {
        if (currChar == digits[i]) {
            return true;
        }
    }

    return false;
}

bool isNumberFromDate(const string &word) {
    bool result = false;
    if (word.length() == 4) {
        for (int i = 0; word[i] != '\0'; ++i) {
            if (!isDigit(word[i])) {
                return false;
            }
        }
        result = true;
    } else {
        result = false;
    }

    return result;
}

bool isCleanWord(const string &word) {
    if (isPronoun(word)) {
        return false;
    }
    if (isConjunction(word)) {
        return false;
    }
    if (isPreposition(word)) {
        return false;
    }
    if (isNumberFromDate(word)) {
        return false;
    }

    return true;
}

bool isSeparator(char currChar) {
    for (int i = 0; SEPARATORS[i] != '\0'; ++i) {
        if (currChar == SEPARATORS[i]) {
            return true;
        }
    }

    return false;
}

string toLowerCase(string currString) {
    for (int i = 0; currString[i] != '\0'; ++i) {
        if (currString[i] >= 'A' && currString[i] <= 'Z') {
            currString[i] = currString[i] + 32;
        }
    }
    return currString;
}

bool isDelimiterOfWord(char currChar) {
    char delimiters[]{'\'', '-'};
    int size = 2;
    for (int i = 0; i < size; ++i) {
        if (currChar == delimiters[i]) {
            return true;
        }
    }

    return false;
}

bool isIndexToSkip(int index, list<int> indexes) {
    for (auto const &i: indexes) {
        if (index == i) {
            return true;
        }
    }

    return false;
}

list<string> removeDuplicates(list<string> strings) {
    list<string> result;
    string stringsArr[strings.size()];

    int k = 0;
    for (auto &i: strings) {
        stringsArr[k++] = i;
    }

    list<int> indexToSkip;
    string currStr;
    for (int i = 0; i < strings.size(); ++i) {
        currStr = stringsArr[i];
        if (isIndexToSkip(i, indexToSkip)) {
            continue;
        } else {
            result.push_back(currStr);
        }
        if (strcmp(currStr.c_str(), stringsArr[i + 1].c_str()) == 0) {
            int counter = i + 1;
            while (strcmp(currStr.c_str(), stringsArr[counter].c_str()) == 0) {
                indexToSkip.push_back(counter);
                counter++;
            }
        }
    }

    return result;
}

list<string> cleanTextAndGetStringsList(string text) {
    list<string> resultList;
    string utilStr;
    string currStr;
    string delimitedWord;
    bool delimitedWordFlag = false;

    for (int i = 0; text[i] != '\0'; ++i) {
        if (i == text.size() - 1 && !isSeparator(text[i])) {
            utilStr = text[i];
            currStr.append(utilStr);
            utilStr.clear();
            resultList.push_back(currStr);
            break;
        }
        if (delimitedWordFlag) {
            if (!isDelimiterOfWord(text[i]) && isSeparator(text[i + 1])) {
                utilStr = text[i];
                delimitedWord.append(utilStr);
                resultList.push_back(delimitedWord);
                delimitedWord.clear();
                delimitedWordFlag = false;
                continue;
            }
            utilStr = text[i];
            delimitedWord.append(utilStr);
            utilStr.clear();
            continue;
        }
        if (isDelimiterOfWord(text[i]) && !isSeparator(text[i + 1])) {
            delimitedWord.append(currStr);
            currStr.clear();
            delimitedWordFlag = true;
            continue;
        }

        if (isSeparator(text[i])) {
            if (currStr.size() > 2) {
                currStr = toLowerCase(currStr);
                if (isCleanWord(currStr)) {
                    resultList.push_back(currStr);
                }
            }
            currStr.clear();
            continue;
        } else {
            utilStr = text[i];
            currStr.append(utilStr);
            utilStr.clear();
        }
    }

    return removeDuplicates(resultList);
}

double antiPlagiarism(string text, string fragment) {
    double rate = 0.0;

    //do some code

    return rate;
}

