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

void deleteAndCopy(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int inspecting, int editing){
    
    strcpy(word1[editing], word1[inspecting]);
    strcpy(word2[editing], word2[inspecting]);
    separation[editing] = separation[inspecting];
}

bool isValidWord(char word[]){
    if(word[0] == '\0')
        return false;
    for(int i = 0; word[i] != '\0'; i++){
        if(!isalpha(word[i]))
            return false;
        word[i] = tolower(word[i]);
    }
    return true;
}


int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int nPatterns) {
    
    if (nPatterns <= 0)
        return 0;
    
    int editing = 0;
    int inspecting = 0;
    while(inspecting < nPatterns){
        if(separation[inspecting] < 0 || !isValidWord(word1[inspecting]) || !isValidWord(word2[inspecting])){
           
            inspecting++;
            continue;
        }
        
        
        char firstWord[MAX_WORD_LENGTH+1];
        strcpy(firstWord, word1[inspecting]);
        char secondWord[MAX_WORD_LENGTH+1];
        strcpy(secondWord, word2[inspecting]);
        
        bool hasOccurred = false;
        int deleteIndex = -1;
        
        for(int i = 0; i < editing; i++){
            if(firstWord == word1[i] && secondWord == word2[i]){
                hasOccurred = true;
                deleteIndex = i;
                break;
            }
            if(firstWord == word2[i] && secondWord == word1[i]){
                hasOccurred = true;
                deleteIndex = i;
                break;
            }
        }
        
        if(hasOccurred){
            cout << "ocurrr" << endl;
            separation[deleteIndex] = max(separation[deleteIndex], separation[inspecting]);
            inspecting++;
            continue;
        }
        
        
        
        
        
        
        
        deleteAndCopy(word1, word2, separation, inspecting, editing);
        inspecting++;
        editing++;
    }
    
    
    
    return editing;
}


int main() {
    char i[6] = "UCLA";
    char j[10] = "UCLA";
    bool equal = (i == j);
    cout << equal << endl;
    char word1[5][MAX_WORD_LENGTH+1] = {"Bruin", "computer", "stats", "bruin", "UCLA"};
    char word2[5][MAX_WORD_LENGTH+1] = {"Bear", "science!", "math", "bear", "LA"};
    int separation[5] = {1, 2, -1, 5, 8};
    
    int n = makeProper(word1, word2, separation, 5);
    
    for (int i =0 ; i < n; i++){
        cout << word1[i] << " " << word2[i] << " " << separation[i] << endl;
    }
}
