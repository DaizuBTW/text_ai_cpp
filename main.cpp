#include <iostream>
#include <cstring>
#include <list>

using namespace std;

const string SEPARATORS = " .,;:!?-\"“”'‘’()[]{}+-*/=«»—–\n";

//const string TEXT = "In 15.05.1476, Ezio Auditore witnesses his father's unjust execution, Ezio Auditore witnesses turmoil and artistic brilliance setting him on a quest for revenge. Uncovering a connection to the Assassins, Ezio navigates Renaissance Italy, encountering historical figures and unraveling a Templar plot for power.\n"
//                    "\n"
//                    "Honing his Assassin skills, Ezio discovers a conspiracy to control artifacts with world-altering potential. The narrative unfolds against the backdrop of political turmoil and artistic brilliance, leading to a climactic confrontation in 20.11.1499.\n"
//                    "\n"
//                    "The story explores themes of revenge, redemption, turmoil and artistic brilliance and the broader battle for freedom, leaving a lasting impact on the Assassins' legacy.";
//
//const string TEXT_FRAGMENT = "Honing his Assassin skills, Ezio discovers a conspiracy to control artifacts with world-altering potential. The narrative unfolds against the backdrop of political turmoil and artistic brilliance, leading to a climactic confrontation in 20.11.1499.\n"
//                             " word \n";

//const string TEXT = "one two three four five six seven eight nine ten";
const string TEXT = "Ezio navigates Renaissance Italy, encountering historical figures and unraveling a Templar plot for power.";

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
const int INSPECTION_RANGE = 3;
const string DIGITS = "0123456789";

double antiPlagiarism(string text, string fragment);
int countWordMatches(bool wordChecker[], int index);
void convertListToArray(list<string> list, string array[]);
string buildStringToCompare(string words[], int index);
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
void setFalseToWordChecker(bool wordChecker[], int size);

int main() {
    double result = 0.0;
    string fragment = "";
    string choice = "";

    while (true) {
        cout << endl << "The reference text is following: " << endl << endl;
        cout << TEXT << endl << endl;
        cout << "Enter a fragment to compare: " << endl;
        getline(cin, fragment);
        result = antiPlagiarism(TEXT, fragment);
        cout << endl << "Percentage of text matches is " << result << "%" << endl;
        cout << "Do you want to continue? (yes/no)" << endl;
        getline(cin, choice);
        if (choice == "no") {
            break;
        } else {
            choice.clear();
            fragment.clear();
            result = 0.0;
        }
    }
    return 0;
}

void setFalseToWordChecker(bool wordChecker[], int size) {
    for (int i = 0; i < size; ++i) {
        wordChecker[i] = false;
    }
}

double antiPlagiarism(string text, string fragment) {
    double rate = 0.0;
    int wordMatchesCounter = 0;
    list<string> textList = cleanTextAndGetStringsList(text);
    list<string> fragmentList = cleanTextAndGetStringsList(fragment);

    string textArr[textList.size()];
    string fragmentArr[fragmentList.size()];
    bool wordChecker[fragmentList.size()];

    setFalseToWordChecker(wordChecker, fragmentList.size());
    convertListToArray(textList, textArr);
    convertListToArray(fragmentList, fragmentArr);

    for (int i = 0; i < textList.size(); ++i) {
        string tempText = buildStringToCompare(textArr, i);
        for (int j = 0; j < fragmentList.size(); ++j) {
            string tempFragment = buildStringToCompare(fragmentArr, j);
            if (tempText == tempFragment) {
                wordMatchesCounter += countWordMatches(wordChecker, j);
                break;
            }
            if (fragmentList.size() == j + INSPECTION_RANGE)
                break;
        }

        if (textList.size() == i + INSPECTION_RANGE || wordMatchesCounter == fragmentList.size())
            break;
    }
    rate = (double) wordMatchesCounter / fragmentList.size() * 100;

    return rate;
}

int countWordMatches(bool wordChecker[], int index) {
    int result = 0;

    for (int i = 0; i < INSPECTION_RANGE; ++i) {
        if (!wordChecker[index + i]) {
            wordChecker[index + i] = true;
            result++;
        }
    }

    return result;
}

string buildStringToCompare(string words[], int index) {
    string result = "";

    for (int i = 0; i < INSPECTION_RANGE; ++i) {
        result.append(words[index + i]);
    }

    return result;
}

void convertListToArray(list<string> list, string array[]) {
    int k = 0;

    for (auto &i: list) {
        array[k++] = i;
    }
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
    for (int i = 0; DIGITS[i] != '\0'; ++i) {
        if (currChar == DIGITS[i]) {
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
            if (currStr.size() > 2) {
                currStr = toLowerCase(currStr);
                if (isCleanWord(currStr)) {
                    resultList.push_back(currStr);
                }
            }
            utilStr.clear();
            currStr.clear();
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

