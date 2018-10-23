//
//  poll.cpp
//  Project3
//
//  Created by Brendon Ng on 10/22/18.
//  Copyright © 2018 Brendon Ng. All rights reserved.
//

#include <iostream>
using namespace std;

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

bool isProperStateForecast(string stateForecast)
{
    if(stateForecast=="") //Empty string is valid
        return true;
    if(stateForecast.size()==1) //Cannot be valid if length is 1
        return false;
    
    //Check first two chars for valid state code
    string stateCode = "";
    stateCode+=toupper(stateForecast[0]);
    stateCode+=toupper(stateForecast[1]);
    if(!isValidUppercaseStateCode(stateCode))
        return false;
    
    //Check each char in the rest of the state forecast
    for(int i=2; i<stateForecast.size(); i++)
    {
        if(isdigit(stateForecast[i])) //If the current char is a digit
        {
            //If the current char(digit) is the last one in the forecast, it is invalid
            if(i==stateForecast.size()-1)
                return false;
            
            //If the current char(digit) is the third digit in a row, forecast is invalid
            if(isdigit(stateForecast[i-1]) && isdigit(stateForecast[i-2]))
            {
                return false;
            }
        }
        else if(isalpha(stateForecast[i])) //If the current char is a letter
        {
            //If the current char(letter) is the second letter in a row, forecast is invalid
            if(isalpha(stateForecast[i-1]))
                return false;
        }
        else //If the current char is anything but a digit or letter
            return false;
    }
    
    return true;
}

bool hasProperSyntax(string pollData)
{
    string stateForecast = "";
    for(int i=0; i<pollData.size(); i++)
    {
        //If theres a char that is anything but a digit, letter, or comma, string has invalid syntax
        if(!isalnum(pollData[i]) && pollData[i] != ',')
            return false;
        
        if(pollData[i] == ',')
        {
            //When a comma is reached, test the current state forecast string
            if(isProperStateForecast(stateForecast))
            {
                //if state forecast string is valid, clear it then move on to the next one
                stateForecast="";
                continue;
            }
            else //If state forecast string is invalid, poll Data string has invalid syntax
                return false;
        }
        else //if the current char is not a comma, add it to the state forecast string being built
            stateForecast += pollData[i];
    }
    
    return (isProperStateForecast(stateForecast));
}

int tallySeats(string pollData, char party, int& seatTally)
{
    if(!hasProperSyntax(pollData))
        return 1;
    if(!isalpha(party))
        return 2;
    
    //TODO: Finish
    
    return 0;
}


int main(){
    cout << hasProperSyntax("") << endl;
    cout << hasProperSyntax("Ca38d24r,IL22w3u,RI3e34i,AK93w42k89e8s0w9m,") << endl;
    if (hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D"))
        cout << "Passed test 1: hasProperSyntax(\"CT5D,NY9R17D1I,VT,ne3r00D\")" << endl;
    if (!hasProperSyntax("ZT5D,NY9R17D1I,VT,ne3r00D"))
        cout << "Passed test 2: !hasProperSyntax(\"ZT5D,NY9R17D1I,VT,ne3r00D\")" << endl;
}
