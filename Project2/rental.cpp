//
//  rental.cpp
//  Project2
//
//  Created by Brendon Ng on 10/10/18.
//  Copyright © 2018 Brendon Ng. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;


int main() {
    
    // get odometer at start input
    cout << "Odometer at start: ";
    int start;
    cin >> start;
    if (start < 0) // If the starting odometer reading is negative
    {
        cout << "---" << endl;
        cout << "The starting odometer reading must be nonnegative." << endl;
        return 1;
    }
    
    // get odometer at end input
    cout << "Odometer at end: ";
    int end;
    cin >> end;
    if (end < start) // If the ending odometer reading is less than the starting reading
    {
        cout << "---" << endl;
        cout << "The final odometer reading must be at least as large as the starting reading." << endl;
        return 1;
    }
    
    // get rental days input
    cout << "Rental days: ";
    int days;
    cin >> days;
    if (days <= 0) // If the number of rental days is not positive
    {
        cout << "---" << endl;
        cout << "The number of rental days must be positive." << endl;
        return 1;
    }
    
    cin.ignore(10000, '\n'); // ignore new line left over from cin of int so getline() works
    
    // get customer name input
    cout << "Customer name: ";
    string name;
    getline(cin, name);
    if (name.length() == 0) // If an empty string was provided for the customer name:
    {
        cout << "---" << endl;
        cout << "You must enter a customer name." << endl;
        return 1;
    }
    
    // get yes or no input for luxury car
    cout << "Luxury car? (y/n): ";
    string luxury;
    getline(cin, luxury);
    if (luxury != "y" && luxury != "n") // If the luxury status is not y or n (must be lower case)
    {
        cout << "---" << endl;
        cout << "You must enter y or n." << endl;
        return 1;
    }
    
    // get month number input
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    int month;
    cin >> month;
    if (month <= 0 || month > 12) // If the month number is not an integer between 1 and 12 inclusive:
    {
        cout << "---" << endl;
        cout << "The month number must be in the range 1 through 12." << endl;
        return 1;
    }
    
    double cost = 0.0; // initialize total cost variable
    
    // add base charge - $33 per day for non-luxury, $61 per day for luxury
    if (luxury == "y")
    {
        cost += 61 * days;
    }
    else
    {
        cost += 33 * days;
    }
    
    int miles = end - start; // calculate miles driven
    
    // Add cost for first 100 miles
    if (miles > 100)
    {
        cost += 100 * 0.27;
        miles -= 100;
    }
    else
    {
        cost += 0.27 * miles;
        miles = 0;
    }
    
    // Set rate depending on month
    double rate;
    if (month == 12 || month == 1 || month == 2 || month ==3)
        rate = 0.27;
    else
        rate = 0.21;
    
    // Add cost for next 300 miles
    if (miles > 300)
    {
        cost += 300 * rate;
        miles -= 300;
    }
    else
    {
        cost += rate * miles;
        miles = 0;
    }
    
    // Add cost for remaining miles
    cost += miles * 0.19;
    
    
    cout.setf(ios :: fixed); // set format so monetary values are not expressed in scientific notation
    cout.precision(2); // ensures two digits after decimal points are printed
    
    cout << "---" << endl;
    cout << "The rental charge for " << name << " is $" << cost << endl;

}
