//
//  array.cpp
//  Project4
//
//  Created by Brendon Ng on 10/31/18.
//  Copyright © 2018 Brendon Ng. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value) {
    if(n < 0)
        return -1;
    for(int i=0; i < n; i++){ //Iterate through array and append value
        a[i] =  a[i] + value;
    }
    return n;
}

int lookup(const string a[], int n, string target) {
    for(int i=0; i < n; i++){ //Iterate through array, trying to find target
        if(a[i] == target)
            return i; //When target is found, it is the first appearance so return the index
    }
    return -1;
}

int positionOfMax(const string a[], int n){
    if(n <= 0)
        return -1;
    string max = "";
    int index = 0;
    for(int i=0; i < n; i++){ //Iterate through array
        //If current element is > than previous max, we dont use >= because we want first instance of the max
        if(a[i] > max){
            index = i;
            max = a[i];
        }
    }
    return index;
}

int rotateLeft(string a[], int n, int pos){
    if (n < 0 || pos >= n)
        return -1;
    string move = a[pos];
    for(int i=pos; i < n-1; i++){ //start at pos and go until the second to last element of the array
        a[i] = a[i+1]; //assign next element to current element
    }
    a[n-1] = move; //set the final element as the element at pos
    return pos;
}

int countRuns(const string a[], int n){
    if(n < 0)
        return -1;
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    int count = 1;
    for(int i=1; i < n; i++){ //start at second element in array (already know n > 1
        if(a[i] != a[i-1]) //if the previous element != current, then it marks the end of a run
            count++;
    }
    return count;
}

int flip(string a[], int n){
    if(n < 0)
        return -1;
    for(int i=0; i<n/2; i++){ //iterate through half of the array, rounds down so middle element of odd value of n stays the same
        string temp = a[i]; //switch current element and corresponding element at the end of array
        a[i] = a[n-i-1];
        a[n-i-1] = temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2){
    if(n1 < 0 || n2 < 0)
        return -1;
    for(int i=0; i < min(n1, n2); i++){ //iterate through enough elements for the smaller array
        if(a1[i] != a2[i]) // finds earliest index where elements dont match
            return i;
    }
    return min(n1,n2);
}

int subsequence(const string a1[], int n1, const string a2[], int n2){
    if(n1 < 0 || n2 < 0 || n1 < n2)
        return -1;
    if(n2 == 0) // Zero element sequence is subsequence of any sequence
        return 0;
    for(int i=0; i <= n1-n2; i++){ //Iterate through all elements in array that will allow subsequence to fit afterwards
        if(a1[i]==a2[0]){ // If the current element is equal to the first in a2 then we can search the upcoming elements
            bool cont = false;
            for(int j=i+1, k=1; j < i+n2; j++, k++){ // Iterate through both arrays now
                if(a1[j] != a2[k]){ //If corresponding elements aren't equal, continue outer loop
                    cont = true;
                    break;
                }
            }
            if(cont)
                continue;
            return i;
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2){
    if(n1<=0 || n2<=0)
        return -1;
    for(int i=0; i<n1; i++){ // Iterate thru each element in a1 array
        for(int j=0; j<n2; j++){ // Compare current element to each one in a2 array
            if(a1[i]==a2[j])
                return i;
        }
    }
    return -1;
}

int divide(string a[], int n, string divider){
    if(n<0)
        return -1;
    int i = 0; // Index from front
    int j = n-1; // Index from end
    
    string stringi = "";
    string stringj = "";
    bool iLoaded = false;
    bool jLoaded = false;
    while(i<=j){
        if(a[i] >= divider){ // If current element from the front is >= divider, it needs to be moved
            stringi = a[i]; // Load the current value into temporary place holder to be swapped
            iLoaded = true;
        }
        else{ // Increment index and ensure nothing is "loaded" or pending to be moved from front
            i++;
            stringi = "";
            iLoaded = false;
        }
        
        if(a[j] < divider){ // If current element from the back is < divider, it needs to be moved
            stringj = a[j]; // // Load the current value into temporary place holder to be swapped
            jLoaded = true;
        }
        else{ // Decrememnt index and ensure nothing is "loaded" or pending to be moved from back
            j--;
            stringj = "";
            jLoaded = false;
        }
        
        if(iLoaded && jLoaded){ // If there are two elements waiting to be swapped
            a[i] =  stringj; // Swap and increment/decrement both indexes
            a[j] =  stringi;
            i++;
            j--;
        }
    }
    

    return i;
}



string c[6] = {
    "alpha", "beta", "beta", "delta", "gamma", "gamma"
};

bool dividecheck(const string a[], int n, int p, string divider)
{
    for (int k = 0; k < p; k++)
        if (a[k] >= divider)
            return false;
    for ( ; p < n  &&  a[p] == divider; p++)
        ;
    for (int k = p; k < n; k++)
        if (a[k] <= divider)
            return false;
    string b[100];
    copy(a, a+n, b);
    sort(b, b+n);
    return equal(b, b+n, c);
}

void testone(int n)
{
    const int N = 6;
    
    // Act as if  a  were declared:
    //   string a[N] = {
    //       "alpha", "beta", "gamma", "gamma", "beta", "delta"
    //   };
    // This is done in a way that will probably cause a crash if
    // a[-1] or a[N] is accessed:  We place garbage in those positions.
    string aa[1+N+1] = {
        "", "alpha", "beta", "gamma", "gamma", "beta", "delta", ""
    };
    string* a = &aa[1];
    string* z = aa;
    a[-1].string::~string();
    a[N].string::~string();
    fill_n(reinterpret_cast<char*>(&a[-1]), sizeof(a[-1]), 0xEF);
    fill_n(reinterpret_cast<char*>(&a[N]), sizeof(a[N]), 0xEF);
    
    string b[N] = {
        "alpha", "beta", "gamma", "delta", "beta", "delta"
    };
    
    string d[9] = {
        "alpha", "beta",  "beta", "beta", "alpha",
        "alpha", "delta", "beta", "beta"
    };
    
    switch (n)
    {
        case  1: {
            assert(appendToAll(z, -1, "rho") == -1 && a[0] == "alpha");
        } break; case  2: {
            assert(appendToAll(z, 0, "rho") == 0 && a[0] == "alpha");
        } break; case  3: {
            assert(appendToAll(a, 1, "rho") == 1 && a[0] == "alpharho" &&
                   a[1] == "beta");
        } break; case  4: {
            assert(appendToAll(a, 6, "rho") == 6 && a[0] == "alpharho" &&
                   a[1] == "betarho" && a[2] == "gammarho" &&
                   a[3] == "gammarho" && a[4] == "betarho" &&
                   a[5] == "deltarho");
        } break; case  5: {
            assert(lookup(z, -1, "alpha") == -1);
        } break; case  6: {
            assert(lookup(z, 0, "alpha") == -1);
        } break; case  7: {
            assert(lookup(a, 1, "alpha") == 0);
        } break; case  8: {
            assert(lookup(a, 6, "delta") == 5);
        } break; case  9: {
            assert(lookup(a, 6, "beta") == 1);
        } break; case 10: {
            assert(lookup(a, 6, "zeta") == -1);
        } break; case 11: {
            assert(positionOfMax(z, -1) == -1);
        } break; case 12: {
            assert(positionOfMax(z, 0) == -1);
        } break; case 13: {
            assert(positionOfMax(a, 1) == 0);
        } break; case 14: {
            assert(positionOfMax(a, 3) == 2);
        } break; case 15: {
            assert(positionOfMax(a, 6) == 2);
        } break; case 16: {
            assert(positionOfMax(a+3, 3) == 0);
        } break; case 17: {
            a[0] = "";
            a[1] = " ";
            a[2] = "";
            assert(positionOfMax(a, 3) == 1);
        } break; case 18: {
            assert(rotateLeft(z, -1, 0) == -1 &&
                   a[0] == "alpha" && a[1] == "beta");
        } break; case 19: {
            assert(rotateLeft(a, 6, -1) == -1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 20: {
            assert(rotateLeft(a, 6, 6) == -1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 21: {
            assert(rotateLeft(z, 0, 0) == -1 &&
                   a[0] == "alpha" && a[1] == "beta");
        } break; case 22: {
            assert(rotateLeft(a, 1, 0) == 0 &&
                   a[0] == "alpha" && a[1] == "beta");
        } break; case 23: {
            assert(rotateLeft(a, 6, 0) == 0 &&
                   a[0] == "beta" && a[1] == "gamma" && a[2] == "gamma" &&
                   a[3] == "beta" && a[4] == "delta" && a[5] == "alpha");
        } break; case 24: {
            assert(rotateLeft(a, 6, 5) == 5 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 25: {
            assert(rotateLeft(a, 6, 3) == 3 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "beta" && a[4] == "delta" && a[5] == "gamma");
        } break; case 26: {
            assert(rotateLeft(a, 5, 3) == 3 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "beta" && a[4] == "gamma" && a[5] == "delta");
        } break; case 27: {
            assert(countRuns(z, -1) == -1);
        } break; case 28: {
            assert(countRuns(z, 0) == 0);
        } break; case 29: {
            assert(countRuns(a, 1) == 1);
        } break; case 30: {
            assert(countRuns(a, 3) == 3);
        } break; case 31: {
            assert(countRuns(a, 4) == 3);
        } break; case 32: {
            assert(countRuns(a+2, 4) == 3);
        } break; case 33: {
            assert(countRuns(d, 9) == 5);
        } break; case 34: {
            assert(flip(z, -1) == -1 && a[0] == "alpha");
        } break; case 35: {
            assert(flip(z, 0) == 0 && a[0] == "alpha");
        } break; case 36: {
            assert(flip(a, 1) == 1 && a[0] == "alpha" &&
                   a[1] == "beta");
        } break; case 37: {
            assert(flip(a, 2) == 2 && a[0] == "beta" &&
                   a[1] == "alpha" && a[2] == "gamma");
        } break; case 38: {
            assert(flip(a, 5) == 5 && a[0] == "beta" &&
                   a[1] == "gamma" && a[2] == "gamma" && a[3] == "beta" &&
                   a[4] == "alpha" && a[5] == "delta");
        } break; case 39: {
            a[2] = "zeta";
            assert(flip(a,6) == 6 && a[0] == "delta" && a[1] == "beta" &&
                   a[2] == "gamma" && a[3] == "zeta" && a[4] == "beta" &&
                   a[5] == "alpha");
        } break; case 40: {
            assert(differ(z, -1, b, 6) == -1);
        } break; case 41: {
            assert(differ(a, 6, z, -1) == -1);
        } break; case 42: {
            assert(differ(z, 0, b, 0) == 0);
        } break; case 43: {
            assert(differ(a, 3, b, 3) == 3);
        } break; case 44: {
            assert(differ(a, 3, b, 2) == 2);
        } break; case 45: {
            assert(differ(a, 2, b, 3) == 2);
        } break; case 46: {
            assert(differ(a, 6, b, 6) == 3);
        } break; case 47: {
            assert(subsequence(z, -1, b, 6) == -1);
        } break; case 48: {
            assert(subsequence(a, 6, z, -1) == -1);
        } break; case 49: {
            assert(subsequence(z, 0, b, 6) == -1);
        } break; case 50: {
            assert(subsequence(a, 6, z, 0) == 0);
        } break; case 51: {
            assert(subsequence(a, 6, b, 1) == 0);
        } break; case 52: {
            assert(subsequence(a, 6, b+4, 2) == 4);
        } break; case 53: {
            assert(subsequence(a, 6, b+3, 1) == 5);
        } break; case 54: {
            assert(subsequence(a, 6, b+3, 2) == -1);
        } break; case 55: {
            assert(subsequence(a, 6, b+2, 2) == -1);
        } break; case 56: {
            assert(subsequence(a, 6, a, 6) == 0);
        } break; case 57: {
            assert(lookupAny(a, 6, z, -1) == -1);
        } break; case 58: {
            assert(lookupAny(z, -1, b, 6) == -1);
        } break; case 59: {
            assert(lookupAny(z, 0, b, 1) == -1);
        } break; case 60: {
            assert(lookupAny(a, 6, z, 0) == -1);
        } break; case 61: {
            assert(lookupAny(a, 1, b, 1) == 0);
        } break; case 62: {
            assert(lookupAny(a, 6, b+3, 3) == 1);
        } break; case 63: {
            assert(lookupAny(a, 4, b+3, 3) == 1);
        } break; case 64: {
            assert(lookupAny(a, 2, b+2, 2) == -1);
        } break; case 65: {
            assert(divide(z, -1, "beta") == -1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 66: {
            assert(divide(z, 0, "beta") == 0 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 67: {
            assert(divide(a, 1, "aaa") == 0 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 68: {
            assert(divide(a, 1, "alpha") == 0 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 69: {
            assert(divide(a, 1, "zeta") == 1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 70: {
            assert(divide(a, 2, "aaa") == 0 &&
                   dividecheck(a, 2, 0, "aaa") && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 71: {
            assert(divide(a, 2, "alpha") == 0 &&
                   dividecheck(a, 2, 0, "alpha") && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 72: {
            assert(divide(a, 2, "beta") == 1 &&
                   dividecheck(a, 2, 1, "beta") && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 73: {
            assert(divide(a, 2, "zeta") == 2 &&
                   dividecheck(a, 2, 2, "zeta") && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 74: {
            assert(divide(a, 6, "aaa") == 0 && dividecheck(a, 6, 0, "aaa"));
        } break; case 75: {
            assert(divide(a, 6, "alpha") == 0 &&
                   dividecheck(a, 6, 0, "alpha"));
        } break; case 76: {
            assert(divide(a, 6, "beta") == 1 &&
                   dividecheck(a, 6, 1, "beta"));
        } break; case 77: {
            assert(divide(a, 6, "delta") == 3 &&
                   dividecheck(a, 6, 3, "delta"));
        } break; case 78: {
            assert(divide(a, 6, "gamma") == 4 &&
                   dividecheck(a, 6, 4, "gamma"));
        } break; case 79: {
            assert(divide(a, 6, "zeta") == 6 &&
                   dividecheck(a, 6, 6, "zeta"));
        } break; case 80: {
            a[2] = "mu";
            c[5] = "mu";
            assert(divide(a, 6, "mu") == 5 && dividecheck(a, 6, 5, "mu"));
        } break; case 81: {
            assert(divide(a, 6, "chi") == 3 && dividecheck(a, 6, 3, "chi"));
        } break; case 82: {
            // To earn the bonus point for rotateLeft, this and all other
            // rotateLeft tests must pass, and that function must not
            // use any additional arrays.
            const int BIG = 500;
            string h[BIG];
            for (int k = 0; k < BIG; k++)
                h[k] = (k % 2 == 0 ? "alpha" : "beta");
            h[BIG-2] = "gamma";
            h[BIG-1] = "delta";
            rotateLeft(h, BIG, 0);
            assert(h[BIG-3] == "gamma"  &&  h[BIG-2] == "delta");
        } break; case 83: {
            // To earn the bonus point for flip, this and all other
            // flip tests must pass, and that function must not
            // use any additional arrays.
            const int BIG = 500;
            string h[BIG];
            for (int k = 0; k < BIG; k++)
                h[k] = (k % 2 == 0 ? "alpha" : "beta");
            h[0] = "gamma";
            h[BIG-1] = "delta";
            flip(h, BIG);
            assert(h[0] == "delta"  &&  h[BIG-1] == "gamma");
        } break; case 84: {
            // To earn the bonus point for divide, this and all other
            // divide tests must pass, and that function must not
            // use any additional arrays.
            const int BIG = 500;
            string h[BIG];
            string i[3] = { "alpha", "beta", "gamma" };
            for (int k = 0; k < BIG; k++)
                h[k] = i[k % 3];
            divide(h, BIG, "beta");
            int m = 0;
            for (m = 0; m < (BIG+2)/3; m++)
                assert(h[m] == "alpha");
            for ( ; m < (BIG+1)/3; m++)
                assert(h[m] == "beta");
            for ( ; m < BIG/3; m++)
                assert(h[m] == "gamma");
        } break;
    }
    
    new (&a[-1]) string;
    new (&a[N]) string;
}

int main()
{
    cout << "Enter a test number (1 to 84): ";
    int n;
    cin >> n;
    if (n < 1  ||  n > 84)
    {
        cout << "Bad test number" << endl;
        return 1;
    }
    testone(n);
    cout << "Passed test " << n << endl;
}

/*
int main() {
    //Test cases for appendToAll()
    string people[5] = { "dianne", "fiona", "ed", "xavier", "greg" };
    int j = appendToAll(people, 5, "!!!");  // returns 5
    assert(j==5 && people[0] == "dianne!!!" && people[4] == "greg!!!" && people[1] == "fiona!!!");
    
    string peopletwo[5] = { "dianne", "fiona", "ed", "xavier", "greg" };
    j = appendToAll(peopletwo, 0, "!!!");
    assert(j == 0 && peopletwo[0] == "dianne" && peopletwo[1] == "fiona" && peopletwo[4] == "greg");
    
    j = appendToAll(peopletwo, -4, "!!!");
    assert(j == -1 && peopletwo[0] == "dianne" && peopletwo[1] == "fiona" && peopletwo[4] == "greg");
    
    j = appendToAll(peopletwo, 2, "!!!");
    assert(j == 2 && peopletwo[0] == "dianne!!!" && peopletwo[1] == "fiona!!!" && peopletwo[4] == "greg");
    
    cout << "Tests for appendToAll() passed!" << endl;
    
    //Test cases for lookup()
    string lookupStr[6] = { "dianne", "fiona", "ed", "xavier", "greg", "ed"};
    assert(lookup(lookupStr, 5, "fiona") == 1);
    assert(lookup(lookupStr, -1, "fiona") == -1);
    assert(lookup(lookupStr, 6, "ed") == 2);
    assert(lookup(lookupStr, 5, "Xavier") == -1);
    assert(lookup(lookupStr, 0, "fiona") == -1);
    assert(lookup(lookupStr, 5, "dianne") == 0);
    assert(lookup(lookupStr, 1, "dianne") == 0);
    cout << "Tests for lookup() passed!" << endl;
    
    //Test cases for positionOfMax()
    string candidate[7] = { "dianne", "fiona", "gavin", "xavier", "ed", "betty", "xavier"};
    assert(positionOfMax(candidate, 6) == 3);
    assert(positionOfMax(candidate, 7) == 3);
    assert(positionOfMax(candidate, 0) == -1);
    assert(positionOfMax(candidate, -1) == -1);
    assert(positionOfMax(candidate, 1) == 0);
    cout << "Tests for positionOfMax() passed!" << endl;

    
    //Test cases for rotateLeft()
    string politician[5] = { "eleni", "dianne", "fiona", "kevin", "gavin" };
    assert(rotateLeft(politician, 5, 1) == 1 && politician[0] == "eleni" && politician[1] == "fiona" && politician[2] == "kevin" && politician[3] == "gavin" && politician[4] == "dianne");
    string testRotate[5] = { "eleni", "dianne", "fiona", "kevin", "gavin" };
    assert(rotateLeft(testRotate, 5, 4) ==4 && testRotate[0] == "eleni" && testRotate[1] == "dianne" && testRotate[2] == "fiona" && testRotate[3] == "kevin" && testRotate[4] == "gavin");
    assert(rotateLeft(testRotate, 5, 3) == 3 && testRotate[0] == "eleni" && testRotate[1] == "dianne" && testRotate[2] == "fiona" && testRotate[3] == "gavin" && testRotate[4] == "kevin");
    assert(rotateLeft(testRotate, 3, 1) == 1 && testRotate[0] == "eleni" && testRotate[1] == "fiona" && testRotate[2] == "dianne" && testRotate[3] == "gavin" && testRotate[4] == "kevin");
    assert(rotateLeft(testRotate, -1, -4) == -1);
    assert(rotateLeft(testRotate, 2, 4) == -1);
    cout << "Tests for rotateLeft() passed!" << endl;
    
    //Test cases for countRuns()
    string d[9] = {"xavier", "betty", "john", "john", "ed", "ed", "ed", "john", "john"};
    assert(countRuns(d, 9) == 5);
    assert(countRuns(d, 1) == 1);
    assert(countRuns(d, 2) == 2);
    assert(countRuns(d, 4) == 3);
    assert(countRuns(d, 0) == 0);
    assert(countRuns(d, -1) == -1);
    cout << "Tests for countRuns() passed!" << endl;
    
    //Test cases for flip()
    string folks[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    assert(flip(folks, 4)==4 && folks[0]=="xavier" && folks[1]=="" && folks[2]=="john" && folks[3]=="betty" && folks[4]=="kevin" && folks[5]=="dianne");
    assert(flip(folks, 1)==1 && folks[0]=="xavier" && folks[1]=="" && folks[2]=="john" && folks[3]=="betty" && folks[4]=="kevin" && folks[5]=="dianne");
    assert(flip(folks, 0)==0 && folks[0]=="xavier" && folks[1]=="" && folks[2]=="john" && folks[3]=="betty" && folks[4]=="kevin" && folks[5]=="dianne");
    assert(flip(folks, -1)==-1 && folks[0]=="xavier" && folks[1]=="" && folks[2]=="john" && folks[3]=="betty" && folks[4]=="kevin" && folks[5]=="dianne");
    assert(flip(folks, 5)==5 && folks[0]=="kevin" && folks[1]=="betty" && folks[2]=="john" && folks[3]=="" && folks[4]=="xavier" && folks[5]=="dianne");
    assert(flip(folks, 6)==6 && folks[0]=="dianne" && folks[1]=="xavier" && folks[2]=="" && folks[3]=="john" && folks[4]=="betty" && folks[5]=="kevin");
    string t[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(flip(t, 7)==7 && t[0]=="fiona" && t[1]=="eleni" && t[2]=="" && t[3]=="xavier" && t[4]=="ed" && t[5]=="gavin" && t[6]=="greg");
    cout << "Tests for flip() passed!" << endl;
    
    //Test cases for differ()
    string folks2[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    string group[5] = { "betty", "john", "dianne", "", "xavier" };
    assert(differ(folks2, 6, group, 5) == 2);
    assert(differ(folks2, 2, group, 1) == 1);
    assert(differ(folks2, 0, group, 1) == 0);
    assert(differ(folks2, 3, group, 6) == 2);
    assert(differ(folks2, 2, group, 6) == 2);
    string str1[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    string str2[5] = { "john", "john", "dianne", "", "xavier" };
    assert(differ(str1, 2, str2, 6) == 0);
    string str3[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    string str4[5] = { "betty", "john", "", "xavier", "kevin" };
    assert(differ(str3, 6, str4, 5) == 5);
    cout << "Tests for differ() passed!" << endl;
    
    //Test cases for subsequence()
    string names[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
    string names1[10] = { "gavin", "kevin", "greg" };
    assert(subsequence(names, 6, names1, 3) == 1);
    string names2[10] = { "eleni", "greg" };
    assert(subsequence(names, 5, names2, 2) == -1);
    assert(subsequence(names, 5, names2, 0) == 0);
    assert(subsequence(names, 0, names2, 2) == -1);
    assert(subsequence(names, 1, names2, 2) == -1);
    string names3[5] ={"eleni", "gavin", "kevin", "greg", "betty"};
    string names4[5] = {"greg","betty"};
    string names5[5] = {"greg", "alex"};
    assert(subsequence(names3, 5, names3, 3) == 0);
    assert(subsequence(names3, 5, names4, 2) == 3);
    assert(subsequence(names3, 5, names3, 5) == 0);
    assert(subsequence(names3, 5, names5, 1) == 3);
    assert(subsequence(names3, 5, names5, 2) == -1);
    
    //Test cases for lookupAny()
    string lookupNames[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
    string set1[10] = { "dianne", "betty", "greg", "gavin" };
    assert(lookupAny(lookupNames, 6, set1, 4) == 1);
    string set2[10] = { "xavier", "ed" };
    assert(lookupAny(lookupNames, 6, set2, 2) == -1);
    assert(lookupAny(lookupNames, 4, lookupNames, 4) == 0);
    set2[2] = "eleni";
    assert(lookupAny(lookupNames, 4, set2, 3) == 0);
    set2[2] = "fiona";
    assert(lookupAny(lookupNames, 4, set2, 3) == -1);
    assert(lookupAny(lookupNames, 6, set2, 3) == 5);
    
    //Test cases for divide()
    string candidates[6] = { "dianne", "fiona", "gavin", "xavier", "ed", "betty" };
    int n = 6;
    string divider = "eleni";
    int dividei = divide(candidates, n, divider);
    assert(dividei == 3);
    for(int i=0; i<n; i++){
        if(i < dividei)
            assert(candidates[i] < divider);
        else
            assert(candidates[i] >= divider);
    }
    
    // candidate must now be
    //      "dianne"  "ed"  "betty"  "fiona"  "xavier"  "gavin"
    // or   "ed"  "betty"  "dianne"  "gavin"  "fiona"  "xavier"
    // or one of several other orderings.
    // All elements < "eleni" (i.e., "ed", "betty", and "dianne")
    //   come before all others
    // All elements > "eleni" (i.e., "xavier", "fiona", and "gavin")
    //   come after all others
    string candidate2[4] = { "gavin", "kevin", "fiona", "john" };
    n = 4;
    divider = "john";
    dividei = divide(candidate2, n, divider);
    assert(dividei == 2);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(candidate2[i] < divider);
        }
        else{
            assert(candidate2[i] >= divider);
        }
    }
    // candidate2 must now be either
    //      "gavin"  "fiona"  "john"  "kevin"
    // or   "fiona"  "gavin"  "john"  "kevin"
    // All elements < "john" (i.e., "fiona" and "gavin") come
    // before all others.
    // All elements > "john" (i.e., "kevin") come after all others.
    
    string abcs[7] = {"b", "c", "d", "e", "f", "g", "h"};
    n = 7;
    divider = "z";
    dividei = divide(abcs, n, divider);
    assert(dividei == n);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(abcs[i] < divider);
        }
        else{
            assert(abcs[i] >= divider);
        }
    }
    
    n = 7;
    divider = "a";
    dividei = divide(abcs, n, divider);
    assert(dividei == 0);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(abcs[i] < divider);
        }
        else{
            assert(abcs[i] >= divider);
        }
    }
    
    n = 7;
    divider = "e";
    dividei = divide(abcs, n, divider);
    assert(dividei == 3);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(abcs[i] < divider);
        }
        else{
            assert(abcs[i] >= divider);
        }
    }
    
    n = 7;
    divider = "f";
    dividei = divide(abcs, n, divider);
    assert(dividei == 4);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(abcs[i] < divider);
        }
        else{
            assert(abcs[i] >= divider);
        }
    }
    n = 7;
    divider = "h";
    dividei = divide(abcs, n, divider);
    assert(dividei == 6);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(abcs[i] < divider);
        }
        else{
            assert(abcs[i] >= divider);
        }
    }
    
    n = 7;
    divider = "b";
    dividei = divide(abcs, n, divider);
    assert(dividei == 0);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(abcs[i] < divider);
        }
        else{
            assert(abcs[i] >= divider);
        }
    }
    
    string abcsScattered[10] = {"s","c","e","j","q","y","a","z","x","x"};
    n = 10;
    divider = "b";
    dividei = divide(abcsScattered, n, divider);
    assert(dividei == 1);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(abcsScattered[i] < divider);
        }
        else{
            assert(abcsScattered[i] >= divider);
        }
    }
    
    n = 10;
    divider = "a";
    dividei = divide(abcsScattered, n, divider);
    assert(dividei == 0);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(abcsScattered[i] < divider);
        }
        else{
            assert(abcsScattered[i] >= divider);
        }
    }
    
    n = 10;
    divider = "z";
    dividei = divide(abcsScattered, n, divider);
    assert(dividei == 9);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(abcsScattered[i] < divider);
        }
        else{
            assert(abcsScattered[i] >= divider);
        }
    }
    
    n = 10;
    divider = "ze";
    dividei = divide(abcsScattered, n, divider);
    assert(dividei == 10);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(abcsScattered[i] < divider);
        }
        else{
            assert(abcsScattered[i] >= divider);
        }
    }
    
    n = 10;
    divider = "m";
    dividei = divide(abcsScattered, n, divider);
    assert(dividei == 4);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(abcsScattered[i] < divider);
        }
        else{
            assert(abcsScattered[i] >= divider);
        }
    }
    
    n = 10;
    divider = "x";
    dividei = divide(abcsScattered, n, divider);
    assert(dividei == 6);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(abcsScattered[i] < divider);
        }
        else{
            assert(abcsScattered[i] >= divider);
        }
    }
    
    string abcsScattered2[10] = {"s","c","e","j","q","x","x","a","y","y"};
    n = 10;
    divider = "x";
    dividei = divide(abcsScattered2, n, divider);
    assert(dividei == 6);
    for(int i=0; i<n; i++){
        if(i < dividei){
            assert(abcsScattered2[i] < divider);
        }
        else{
            assert(abcsScattered2[i] >= divider);
        }
    }


    
    
    
    
    
    //More tests from spec
    string h[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(lookup(h, 7, "eleni") == 5);
    assert(lookup(h, 7, "ed") == 2);
    assert(lookup(h, 2, "ed") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "greg", "gavin", "fiona", "kevin" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "greg?" && g[3] == "kevin?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "fiona?" && g[3] == "gavin?");
    
    string e[4] = { "ed", "xavier", "", "eleni" };
    assert(subsequence(h, 7, e, 4) == 2);
    
    string d1[5] = { "gavin", "gavin", "gavin", "xavier", "xavier" };
    assert(countRuns(d1, 5) == 2);
    
    string f[3] = { "fiona", "ed", "john" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "john" && f[2] == "fiona");
    
    assert(divide(h, 7, "fiona") == 3);
    assert(divide(h, 7, "eleni") == 2);
    assert(divide(h, 7, "ed") == 1);

    assert(divide(h, 7, "") == 0);
    
    cout << "All Tests Passed!" << endl;
    
    string a[6] = {"alpha", "beta", "gamma", "gamma", "beta", "delta"};
    
    assert(divide(a, 6, "alpha") == 0 &&
           dividecheck(a, 6, 0, "alpha"));
}
*/
