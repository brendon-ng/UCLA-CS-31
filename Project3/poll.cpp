//
//  poll.cpp
//  Project3
//
//  Created by Brendon Ng on 10/22/18.
//  Copyright © 2018 Brendon Ng. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
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
    if(pollData[0] == ',' || pollData[pollData.size()-1] == ',')
        return false;
    
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
    //If not a proper poll data string
    if(!hasProperSyntax(pollData))
        return 1;
    
    //If party is not a letter
    if(!isalpha(party))
        return 2;
    
    seatTally=0;
    
    for(int i=2; i<pollData.size(); i++)
    {
        if(toupper(pollData[i]) == toupper(party)) //Identify party by letter
        {
            if(!isdigit(pollData[i-1])) //If the prev char is not a digit it is part of a state code
            {
                continue;
            }
            
            if(isdigit(pollData[i-2])) //If a two digit number precedes
            {
                int tens = pollData[i-2] - '0';
                int ones = pollData[i-1] - '0';
                seatTally += tens * 10 + ones;
            }
            else //If a one digit number precedes
            {
                int ones = pollData[i-1] - '0';
                seatTally += ones;
            }
            
            
        }
    }
    
    return 0;
}


int main(){
    
    
    
    
    
    int seats;
    
    seats = -999;
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 0 && seats == 17+5);
    
    seats = -999;
    assert(tallySeats("KS4R, NV3D1R", 'd', seats) == 1 && seats == -999);

    seats = -999;
    assert(tallySeats("", 'd', seats) == 0 && seats == 0);
    
    seats = -999;
    assert(tallySeats("NY9R17D1I,VT,NJ3D5R4D,KS4R", 'd', seats) == 0 && seats == 24);
    
    seats = -999;
    assert(tallySeats("NY9R17D1I,VT,NJ3D5R4D,KS4R", 'R', seats) == 0 && seats == 18);
    
    seats = -999;
    assert(tallySeats("NY9R17D1I,VT,NJ3D5R4D,KS4R", 'i', seats) == 0 && seats == 1);
    
    //tests from spec
    assert(hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D"));
    assert(!hasProperSyntax("ZT5D,NY9R17D1I,VT,ne3r00D"));
    seats = 0;
    seats = -999;    // so we can detect whether tallySeats sets seats
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 22);
    seats = -999;    // so we can detect whether tallySeats sets seats
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999);
    cout << "All tests succeeded (From Project 3 Spec)" << endl;
    
    seats = -999;
    assert(tallySeats("CA4s53j3d32i53D", 'd', seats) == 0 && seats == 3+53);
    
    seats = -999;
    assert(tallySeats("CA4s53j3d32i53dD", 'd', seats) == 1 && seats == -999);
    
    seats = -999;
    assert(tallySeats("CA4s73j3d32i53D", 'j', seats) == 0 && seats == 73);

    seats = -999;
    assert(tallySeats("CA4s53j3d32i53D", '9', seats) == 2 && seats == -999);

    seats = -999;
    assert(tallySeats("CA4s53j3d32i53D,MT83d2g24l2j,VT42y00d13k,NY,HI32k", 'd', seats) == 0 && seats == 3+53+83+0);
    
    seats = -999;
    assert(tallySeats("CA4s53j3d32i53D,MT83d2c24l2j,VT42y00d13k,NY,HI32T", 'T', seats) == 0 && seats == 32);
    
    seats = -999;
    assert(tallySeats("CA4s53j3d32i53D,MT83m2c24l2j,VT42y00d13m,NY,HI32T", 'm', seats) == 0 && seats == 83+13);
    
    seats = -999;
    assert(tallySeats("CA4s53j3d32i53D,MT83m2CA24l2j,VT42y00d13m,NY,HI32T", 'm', seats) == 1 && seats == -999);
    
    seats = -999;
    assert(tallySeats("CA4s53j3d32i53D,MT83m2C24l2j, VT42y00d13m,NY,HI32T", 'm', seats) == 1 && seats == -999);
    
    seats = -999;
    assert(tallySeats("CA4s53j3d32i53D,MZ83m2C24l2j,VT42y00d13m,NY,HI32T", 'm', seats) == 1 && seats == -999);
           
    seats = -999;
    assert(tallySeats("CA4s53j3d32i53D,MT83m2C24l2j,VT42y00d13m,NY,HI32T", 'n', seats) == 0 && seats == 0);
    
    seats = -999;
    assert(tallySeats("CA4s53j3d32i53D,MT83m2C24l2j,VT42y00d13m,,HI32T", 'm', seats) == 0 && seats == 83+13);
    
    assert(hasProperSyntax("MA9D,KS4R")  &&  hasProperSyntax("KS4R,MA9D"));
    assert(hasProperSyntax("MA9D,,KS4R") == hasProperSyntax("KS4R,,MA9D"));
    
    seats = -999;
    assert(tallySeats(",CA4s53j3d32i53D,MT83m2C24l2j,VT42y00d13m,,HI32T", 'm', seats) == 1 && seats == -999);
    
    seats = -999;
    assert(tallySeats("CA4s53j3d32i53D,MT83m2C24l2j,VT42y00d13m,,HI32T,", 'm', seats) == 1 && seats == -999);

    
    cout << "ALL tests succeeded" << endl;
}
