//
//  rate.cpp
//  Project5
//
//  Created by Brendon Ng on 11/7/18.
//  Copyright © 2018 Brendon Ng. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;


const int MAX_WORD_LENGTH = 20;

bool isValidWord(char word[]){
    if(word[0] == '\0')
        return false;
    for(int i = 0; word[i] != '\0'; i++){
        if(!isalpha(word[i]))
            return false;
        word[i] = tolower(word[i]); // Send characters to lower case as we go
    }
    return true;
}

int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int nPatterns) {
    
    if (nPatterns <= 0) //If nPatterns is negative or zero, treat as 0 patterns
        return 0;
    
    int editing = 0; //Index onto which we will copy valid patterns
    int inspecting = 0; //Index we are checking
    
    while(inspecting < nPatterns){ //Check all patterns
        
        //If separation is negative or if a word is invalid, skip pattern, do not copy
        if(separation[inspecting] < 0 || !isValidWord(word1[inspecting]) || !isValidWord(word2[inspecting])){
           
            inspecting++;
            continue;
        }
        
        //Check if the word combination has occurred in a previously "approved" pattern
        bool hasOccurred = false;
        int occurrIndex = -1;
        
        for(int i = 0; i < editing; i++){
            if(strcmp(word1[inspecting], word1[i])==0 && strcmp(word2[inspecting],word2[i])==0){
                hasOccurred = true;
                occurrIndex = i;
                break;
            }
            if(strcmp(word1[inspecting], word2[i])==0 && strcmp(word2[inspecting], word1[i])==0){
                hasOccurred = true;
                occurrIndex = i;
                break;
            }
        }
        
        // If the combo has occurred already, skip the current pattern and set separation of the other matching pattern to the max of the separations
        if(hasOccurred){
            separation[occurrIndex] = max(separation[occurrIndex], separation[inspecting]);
            inspecting++;
            continue;
        }

        // If a pattern makes it through all tests, copy it into the current editing index and increment
        if(editing != inspecting){
            strcpy(word1[editing], word1[inspecting]);
            strcpy(word2[editing], word2[inspecting]);
            separation[editing] = separation[inspecting];
        }
        
        inspecting++;
        editing++;
    }
    
    return editing;
}



int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns){
    
    if(nPatterns <= 0) // Treat negative nPatterns as 0
        return 0;
    
    int patterns = 0;
    int word = 0; // Which word we are on in the document
    int charInWord = 0; // Which character are we on within the word
    char prevChar = ' '; // Previously checked character
    char words[250][MAX_WORD_LENGTH+1]; // An array of C-strings to be filled w each word of document
    
    
    for(int i=0; document[i] != '\0'; i++){
        if(document[i] == ' ' && prevChar != ' '){ //Marks the end of a word
            words[word][charInWord] = '\0'; // Signify the end of the C-string
            charInWord = 0; //Reset
            word++;
            prevChar = document[i];
        }
        else{
            if(!isalpha(document[i])) //Ignore non letters
                continue;
            
            //Adds lower case character to current word if less than max word length
            if(charInWord < MAX_WORD_LENGTH){
                words[word][charInWord] = tolower(document[i]);
                charInWord++;
            }
            else // If word is too long, go back and insert a '-' so it wont match any patterns
                words[word][charInWord-1] = '-';
            
            prevChar = tolower(document[i]);
            
        }
        
        
    }
    
    words[word][charInWord] = '\0'; //End the final word
    word++;
    
    //Find Patterns using array of words
    for(int pat = 0; pat < nPatterns; pat++){ //Check for each pattern
        int previousMatch = -1; // Where was the last match
        int whichMatch = 0; // Was the last match word 1 or word 2?
        
        for(int w = 0; w < word; w++){
            if(strcmp(words[w], word1[pat]) == 0){
                //special case: word 1 and word 2 are equal
                if(strcmp(word1[pat], word2[pat])==0 && whichMatch == 1){
                    patterns++;
                    break;
                }
                if(whichMatch == 2){ // If this is the second match to (matching to word 2)
                    patterns++;
                    break;
                }
                else{ // If this is the first match
                    whichMatch = 1;
                    previousMatch = w;
                }
            }
            else if(strcmp(words[w], word2[pat]) == 0){
                if(whichMatch == 1){ // If this is the second match to (matching to word 1)
                    patterns++;
                    break;
                }
                else{ // If this is the first match
                    whichMatch = 2;
                    previousMatch = w;
                }
            }
            
            // If it has been too long since the last match, reset
            if(w > previousMatch + separation[pat]){
                whichMatch = 0;
                previousMatch = -1;
            }
        }
    }
    
    return patterns;
    
}





int main() {
    char word1[10][MAX_WORD_LENGTH+1] = {"mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS"};
    char word2[10][MAX_WORD_LENGTH+1] = {"scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT" };
    int separation[10] = {1, 3, 0, 2, 1, 0, 12, 0};
    int n = makeProper(word1, word2, separation, 8);
    cout << "Test 0" << endl;
    for (int i =0 ; i < n; i++){
        cout << word1[i] << " " << word2[i] << " " << separation[i] << endl;
    }
    cout << endl;
    
    char word11[10][MAX_WORD_LENGTH+1] = {""};
    char word21[10][MAX_WORD_LENGTH+1] = {"scientist"};
    int separation1[10] = {1};
    int n1 = makeProper(word11, word21, separation1, 1);
    cout << "Test 1" << endl;
    for (int i =0 ; i < n1; i++){
        cout << word11[i] << " " << word21[i] << " " << separation1[i] << endl;
    }
    cout << endl;
    
    char word12[10][MAX_WORD_LENGTH+1] = {"mad", "scientist", "ucla", "BRUINS", "beat", "bell", "mad"};
    char word22[10][MAX_WORD_LENGTH+1] = {"scientist", "mad", "bruins", "GO", "SC", "victory", "scientist"};
    int separation2[10] = {10, 10, 3, 1, 0, -1, 1};
    int n2 = makeProper(word12, word22, separation2, 7);
    cout << "Test 2" << endl;
    for (int i =0 ; i < n2; i++){
        cout << word12[i] << " " << word22[i] << " " << separation2[i] << endl;
    }
    cout << endl;
    
    char word13[10][MAX_WORD_LENGTH+1] = {"mad", "scientist", "ucla", "BRUINS", "beat", "bell", "mad"};
    char word23[10][MAX_WORD_LENGTH+1] = {"scientist", "mad", "bruins", "GO", "SC", "victory", "scientist"};
    int separation3[10] = {10, 10, 3, 1, 0, -1, 1};
    int n3 = makeProper(word13, word23, separation3, 10);
    cout << "Test 3" << endl;
    for (int i =0 ; i < n3; i++){
        cout << word13[i] << " " << word23[i] << " " << separation3[i] << endl;
    }
    cout << endl;
    
    char word14[10][MAX_WORD_LENGTH+1] = {"mad"};
    char word24[10][MAX_WORD_LENGTH+1] = {"scientist", "mad", "bruins", "GO", "SC", "victory", "scientist"};
    int separation4[10] = {};
    int n4 = makeProper(word14, word24, separation4, 10);
    cout << "Test 4" << endl;
    for (int i =0 ; i < n4; i++){
        cout << word14[i] << " " << word24[i] << " " << separation4[i] << endl;
    }
    cout << endl;
    
    char word15[10][MAX_WORD_LENGTH+1] = {"mad", "man", "bruin", "go", "beat", "fight", "smart"};
    char word25[10][MAX_WORD_LENGTH+1] = {"scientist", "mad", "bruins", "GO", "SC", "victory", "scientist"};
    int separation5[10] = {4,2,6,7,2,5,0};
    int n5 = makeProper(word15, word25, separation5, 7);
    cout << "Test 5" << endl;
    for (int i =0 ; i < n5; i++){
        cout << word15[i] << " " << word25[i] << " " << separation5[i] << endl;
    }
    cout << endl;
    
    
    
    

    
    const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test1dist[TEST1_NRULES] = {
        1,           3,          0,           12
    };
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("**** 2018 ****",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    assert(rate("  That plot: NEFARIOUS!",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("deranged deranged robot deranged robot robot",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    
    char test2w1[1][21] = {"deranged"};
    char test2w2[1][21] = {"robot"};
    int test2dist[1] = {3};
    assert(rate("deranged robot deranged deranged robot robot", test2w1, test2w2, test2dist, 1) == 1);
    
    char test3w1[1][21] = {"mad"};
    char test3w2[1][21] = {"scientist"};
    int test3dist[1] = {1};
    assert(rate("The mad scientist took over the world.", test3w1, test3w2, test3dist, 1) == 1);
    assert(rate("A scientist mad at the world invented C++.", test3w1, test3w2, test3dist, 1) == 1);
    assert(rate("A mad computer scientist invented C++.", test3w1, test3w2, test3dist, 1) == 1);
    assert(rate("The scientist went MaD!", test3w1, test3w2, test3dist, 1) == 1);
    assert(rate("The mad UCLA computer scientist unleashed a virus.", test3w1, test3w2, test3dist, 1) == 0);
    
    char test4w1[5][21] = {"mad", "ucla", "banana", "shoe", "professor"};
    char test4w2[5][21] = {"scientist", "bruins", "apple", "earring", "smallberg"};
    int test4dist[5] = {2, 0, 40, 5, 1};
    assert(rate("The mad scientist abcdefghijklmnopqrstuvwxyzshoe earring ucla bruinsabcdefghijklmnopqrstuvwxyz", test4w1, test4w2, test4dist, 5) == 1);
    assert(rate("The mad UClA scientist, professor Dr. Smallberg liked to eat Bruin's Banana bread while tying his shoe and looking for his apple earring.!!", test4w1, test4w2, test4dist, 5) == 4);
    assert(rate("Mad word mad word word mad word mad word mad word word scientist", test4w1, test4w2, test4dist, 5) == 1);

    
    char test5w1[5][21] = {"mad", "ucla", "banana", "shoe", "professor"};
    char test5w2[5][21] = {"mad", "bruins", "apple", "earring", "smallberg"};
    int test5dist[5] = {2, 0, 40, 5, 1};
    assert(rate("The mad dog", test5w1, test5w2, test5dist, 5) == 0);
    assert(rate("The mad dog went mad", test5w1, test5w2, test5dist, 5) == 1);
    assert(rate("The mad mad dog", test5w1, test5w2, test5dist, 5) == 1);
    assert(rate("The mad dog was very mad", test5w1, test5w2, test5dist, 5) == 0);
    assert(rate("The mad dog was very mad mad", test5w1, test5w2, test5dist, 5) == 1);
    assert(rate("The mad dog was very mad and he was very mad", test5w1, test5w2, test5dist, 5) == 0);
    assert(rate("The bruins of ucla loved smallberg the professor and his earring and shoe!!", test5w1, test5w2, test5dist, 5) == 2);
    
    
    
    cout << "All tests succeeded" << endl;
}
