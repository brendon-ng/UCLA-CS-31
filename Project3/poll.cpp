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

bool hasProperSyntax(string pollData)
{
    if (pollData == "")
        return true;
    //TODO
    return true;
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
    int seatTally = 0;
    int s = tallySeats("no8", 'k', seatTally);
    cout << s;
}
