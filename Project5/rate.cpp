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
    
    if (nPatterns <= 0) //If nPatters is negative or zero, treat as 0 patterns
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

void checkPatterns(char words[250][MAX_WORD_LENGTH+1], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns, int word){
    
    for(int i=0; i<nPatterns; i++){
        if(strcmp(words[word], word1[i]) == 0){
            
        }
    }
    
}

int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns){
    
    if(nPatterns <= 0)
        return 0;
    
    int patterns = 0;
    int word = 0;
    int charInWord = 0;
    char prevChar = ' ';
    char words[250][MAX_WORD_LENGTH+1];
    
    
    for(int i=0; document[i] != '\0'; i++){
        if(document[i] == ' ' && prevChar != ' '){ //Marks the end of a word
            words[word][charInWord] = '\0';
            charInWord = 0;
            
            checkPatterns(words, word1, word2, separation, nPatterns, word);
            
            word++;
            prevChar = document[i];
        }
        else{
            if(!isalpha(document[i]))
                continue;
            
            if(charInWord < MAX_WORD_LENGTH)
                words[word][charInWord] = tolower(document[i]);
            else
                words[word][charInWord] = '-';
            
            prevChar = tolower(document[i]);
            charInWord++;
        }
        
        
    }
    
    words[word][charInWord] = '\0';
    
    
    return patterns;
    
}





int main() {
    char word1[10][MAX_WORD_LENGTH+1] = {"mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS"};
    char word2[10][MAX_WORD_LENGTH+1] = {"scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT" };
    int separation[10] = {1, 3, 0, 2, 1, 0, 12, 0};
    
    int n = makeProper(word1, word2, separation, 8);
    
    for (int i =0 ; i < n; i++){
        cout << word1[i] << " " << word2[i] << " " << separation[i] << endl;
    }
    
    cout << rate("That. mad  scientist said two mad. scientists suffer from deranged-robot fever.", word1, word2, separation, 1000) <<  endl;
}
