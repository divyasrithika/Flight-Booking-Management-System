#include<iostream>
#include <ctime>
#include <cstdlib>
#include "User/UserManager.h"
#include "Flight/FlightManager.h"
#include <stdexcept>
using namespace std;


//Inhertance and virtual class implementation

class Meal {
protected:
    int price;

public:
    Meal(int p) : price(p) {}

    virtual ~Meal() {}

    virtual double calculateCharge(int quantity) = 0;
};

class VegMeal : public Meal {
public:
    VegMeal() : Meal(250) {}

    double calculateCharge(int quantity) override {
        return price * quantity;
    }
};

class NonVegMeal : public Meal {
public:
    NonVegMeal() : Meal(350) {}

    double calculateCharge(int quantity) override {
        return price * quantity;
    }
};

void displaySeats(vector<vector<int>>& a) {

    cout << "\n========== SEAT MAP ==========\n\n";

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 8; j++) {

            if (a[i][j] == 0) {
                cout << "[ ]" << char(65 + i) << j + 1 << "  ";
            }
            else {
                cout << "[X]" << char(65 + i) << j + 1 << "  ";
            }
        }

        cout << endl;
    }

    cout << "\n[ ] Available    [X] Booked\n";
}


int main(){
    UserManager manager;
    manager.loadusers();

    FlightManager flightManager;
    flightManager.loadFlights();

    string source;
    string destination;
    string date;
    Flight* selectedFlight;

        int choice;
        bool loggedin=false;
        cout << "\n";
        cout << "==============================" << endl;
        cout << "    FLIGHT BOOKING SYSTEM" << endl;
        cout << "==============================" << endl;
        cout<<endl;
        cout<<"1. Sign Up"<<endl;
        cout<<"2. Log in"<<endl;
        cout<<"3. Exit Application";
        cout<<endl;
        cout<<"\nEnter your choice: ";
        cin>>choice;
    do{
            
        
        cout<<endl;
        switch(choice){
            case 1:
                // sign up function
                manager.signup();
                cout<<"signed up"<<endl;
            case 2:
                //log in function
                
                while(loggedin==false){
                    loggedin=manager.login();
                }

                 if(loggedin){
                        cout << "\nEnter source: ";
                        cin >> source;

                        cout << "Enter destination: ";
                        cin >> destination;

                        
                        try
                        {
                            if (source == destination)
                            {
                                throw invalid_argument(
                                    "Source and destination cannot be the same."
                                );
                            }
                        }
                        catch (const invalid_argument& e)
                        {
                            cout << "Error: " << e.what() << endl;
                            return 0;
                        }
                        cout << "Enter date (YYYY-MM-DD): ";
                        cin >> date;

                        

selectedFlight = flightManager.searchFlights(
    source,
    destination,
    date
);
while(selectedFlight==nullptr){
    selectedFlight = flightManager.searchFlights(
    source,
    destination,
    date
);
}


    cout << "\nYou selected:\n";

    cout << "Flight Number : "
         << selectedFlight->getFlightNumber() << endl;

    cout << "Airline       : "
         << selectedFlight->getAirline() << endl;

    cout << "From          : "
         << selectedFlight->getSource() << endl;

    cout << "To            : "
         << selectedFlight->getDestination() << endl;

    cout << "Date          : "
         << selectedFlight->getDate() << endl;

    cout << "Departure     : "
         << selectedFlight->getDepartureTime() << endl;

    cout << "Arrival       : "
         << selectedFlight->getArrivalTime() << endl;

    cout << "Price         : Rs. "
         << selectedFlight->getPrice() << endl;
        
        vector<vector<int>> a={{0,1,0,1,1,0,0,1},{0,1,0,0,1,0,1,0},{1,1,1,0,1,1,0,1},{0,1,1,1,0,0,0,0}};
        displaySeats(a);


    // Number of tickets
    int tickets;

    cout << "\nHow many tickets do you want to book? ";
    cin >> tickets;


    // Select seats
    for (int k = 0; k < tickets; k++) {

        string seat;

        cout << "\nEnter seat " << k + 1 << ": ";
        cin >> seat;

        // Check format
        if (seat.length() < 2) {
            cout << "Invalid seat!\n";
            k--;
            continue;
        }

        // Convert A/B/C/D -> 0/1/2/3
        int row = seat[0] - 'A';

        // Convert 1/2/3... -> 0/1/2...
        int col = stoi(seat.substr(1)) - 1;


        // Check whether seat exists
        if (row < 0 || row >= 4 ||
            col < 0 || col >= 8) {

            cout << "Invalid seat number! Try again.\n";

            k--;
            continue;
        }


        // Check whether already booked
        if (a[row][col] == 1) {

            cout << "Sorry! Seat " << seat
                 << " is already booked.\n";

            k--;
            continue;
        }


        // Book the seat
        a[row][col] = 1;

        cout << "Seat " << seat
             << " booked successfully!\n";
    }


    // Display updated map
    cout << "\n\n========== UPDATED SEAT MAP ==========\n";

    displaySeats(a);


    double baggageWeight;
double baggageCharge = 0;

cout << "\n==============================" << endl;
cout << "       BAGGAGE DETAILS" << endl;
cout << "==============================" << endl;

cout << "Maximum baggage allowed: "<<15*tickets<<" kg" << endl;
cout << "Extra baggage charge: Rs. 500/kg" << endl;

cout << "Enter your baggage weight: ";
cin >> baggageWeight;

if (baggageWeight < 0)
{
    cout << "Invalid baggage weight!" << endl;
}
else if (baggageWeight > 15*tickets)
{
    double extraWeight = baggageWeight - 15*tickets;

    baggageCharge = extraWeight * 500;

    cout << "Extra baggage: "
         << extraWeight << " kg" << endl;

    cout << "Extra baggage charge: Rs. "
         << baggageCharge << endl;
}
else
{
    cout << "Baggage within allowed limit." << endl;
    cout << "No extra baggage charge." << endl;
}

int mealChoice;
int mealType;
int numberOfMeals;
double mealCharge = 0;

cout << "\n==============================" << endl;
cout << "          MEAL OPTIONS" << endl;
cout << "==============================" << endl;

cout << "Do you want to add a meal?" << endl;
cout << "1. Yes" << endl;
cout << "2. No" << endl;

cout << "Enter choice: ";
cin >> mealChoice;

if (mealChoice == 1)
{
    cout << "\nSelect meal type:" << endl;
    cout << "1. Veg Meal      - Rs. 250" << endl;
    cout << "2. Non-Veg Meal  - Rs. 350" << endl;

    cout << "Enter choice: ";
    cin >> mealType;

    if (mealType == 1 || mealType == 2)
    {
        cout << "Enter number of meals: ";
        cin >> numberOfMeals;

        if (numberOfMeals <= 0)
        {
            cout << "Invalid quantity!" << endl;
            mealCharge = 0;
        }
        else
        {
           Meal* selectedMeal = nullptr;

                if (mealType == 1)
                {
                    selectedMeal = new VegMeal();
                    cout << "\nVeg Meal selected." << endl;
                }
                else
                {
                    selectedMeal = new NonVegMeal();
                    cout << "\nNon-Veg Meal selected." << endl;
                }

                mealCharge = selectedMeal->calculateCharge(numberOfMeals);

                cout << "Quantity: " << numberOfMeals << endl;
                cout << "Meal charge: Rs. " << mealCharge << endl;

                delete selectedMeal; // Clean up memory
        }
    }
    else
    {
        cout << "Invalid meal choice!" << endl;
        mealCharge = 0;
    }
}
else if (mealChoice == 2)
{
    mealCharge = 0;

    cout << "\nNo meal selected." << endl;
}
else
{
    cout << "\nInvalid choice!" << endl;
    mealCharge = 0;
}

double flightFare = selectedFlight->getPrice() * tickets;

double totalFare =
    flightFare +
    baggageCharge +
    mealCharge;

cout << "\n========================================" << endl;
cout << "             FARE SUMMARY" << endl;
cout << "========================================" << endl;

cout << "Flight Fare        : Rs. " << flightFare << endl;
cout << "Baggage Charge     : Rs. " << baggageCharge << endl;
cout << "Meal Charge        : Rs. " << mealCharge << endl;

cout << "----------------------------------------" << endl;

cout << "Total Fare         : Rs. " << totalFare << endl;

cout << "========================================" << endl;

// =================================================
//              CONFIRM TICKET
// =================================================

int confirmChoice;

cout << "\n========================================" << endl;
cout << "          CONFIRM YOUR TICKET" << endl;
cout << "========================================" << endl;

cout << "Total Fare: Rs. " << totalFare << endl;

cout << "\nDo you want to confirm your ticket?" << endl;
cout << "1. Confirm Ticket and Proceed to Payment" << endl;
cout << "2. Cancel Booking" << endl;

cout << "\nEnter your choice: ";
cin >> confirmChoice;
int paymentChoice;
if (confirmChoice == 1)
{
    // =================================================
    //              PAYMENT OPTIONS
    // =================================================

    

    cout << "\n========================================" << endl;
    cout << "           PAYMENT OPTIONS" << endl;
    cout << "========================================" << endl;

    cout << "Amount Payable: Rs. " << totalFare << endl;

    cout << "\n1. UPI" << endl;
    cout << "2. Credit/Debit Card" << endl;
    cout << "3. Net Banking" << endl;
    cout << "4. Cancel Payment" << endl;

    cout << "\nEnter your choice: ";
    cin >> paymentChoice;

    switch(paymentChoice)
    {
        case 1:
            cout << "\nUPI Payment selected." << endl;
            cout << "Proceeding to UPI payment..." << endl;
            break;

        case 2:
            cout << "\nCredit/Debit Card selected." << endl;
            cout << "Proceeding to card payment..." << endl;
            break;

        case 3:
            cout << "\nNet Banking selected." << endl;
            cout << "Proceeding to net banking..." << endl;
            break;

        case 4:
            cout << "\nPayment cancelled." << endl;
            return 0;

        default:
            cout << "\nInvalid payment choice." << endl;
            return 0;
    }
}
else if (confirmChoice == 2)
{
    cout << "\nTicket confirmation cancelled." << endl;
    cout << "Thank you for using our Flight Booking System!" << endl;

    return 0;
}
else
{
    cout << "\nInvalid choice." << endl;
    return 0;
}

cout << "\n========================================" << endl;
cout << "          PAYMENT DETAILS" << endl;
cout << "========================================" << endl;

if (paymentChoice == 1)
{
    cout << "Payment Method : UPI" << endl;
}
else if (paymentChoice == 2)
{
    cout << "Payment Method : Credit/Debit Card" << endl;
}
else if (paymentChoice == 3)
{
    cout << "Payment Method : Net Banking" << endl;
}

cout << "Amount         : Rs. " << totalFare << endl;

cout << "\n========================================" << endl;
cout << "          CONFIRM PAYMENT" << endl;
cout << "========================================" << endl;

cout << "Amount to Pay : Rs. " << totalFare << endl;

cout << "\nDo you want to proceed with the payment?" << endl;
cout << "1. Confirm Payment" << endl;
cout << "2. Cancel Payment" << endl;

int paymentConfirm;

cout << "\nEnter your choice: ";
cin >> paymentConfirm;


// =================================================
//              PAYMENT CONFIRMATION
// =================================================

if (paymentConfirm == 1)
{
    cout << "\nProcessing payment..." << endl;

    // Payment is considered successful
    cout << "\n========================================" << endl;
    cout << "          PAYMENT SUCCESSFUL!" << endl;
    cout << "========================================" << endl;

    cout << "Amount Paid    : Rs. " << totalFare << endl;
    cout << "Payment Status : SUCCESS" << endl;

    cout << "\nYour ticket has been successfully booked!" << endl;
}
else if (paymentConfirm == 2)
{
    cout << "\n========================================" << endl;
    cout << "           PAYMENT CANCELLED" << endl;
    cout << "========================================" << endl;

    cout << "Your booking has been cancelled." << endl;
    cout << "No ticket has been generated." << endl;

    return 0;
}
else
{
    cout << "\nInvalid choice." << endl;
    cout << "Payment cancelled." << endl;

    return 0;
}

// =================================================
//             PAYMENT SUCCESSFUL
// =================================================

cout << "\n========================================" << endl;
cout << "          PAYMENT SUCCESSFUL!" << endl;
cout << "========================================" << endl;

cout << "Amount Paid  : Rs. " << totalFare << endl;
cout << "Payment Status : SUCCESS" << endl;

cout << "\nYour ticket has been successfully booked!" << endl;


// =================================================
//                GENERATE PNR
// =================================================

srand(time(0));

string pnr = "FB" + to_string(100000 + rand() % 900000);

cout << "\n========================================" << endl;
cout << "           BOOKING CONFIRMED" << endl;
cout << "========================================" << endl;

cout << "PNR Number : " << pnr << endl;


// =================================================
//                BOARDING PASS
// =================================================

cout << "\n\n";
cout << "============================================================" << endl;
cout << "                    BOARDING PASS" << endl;
cout << "============================================================" << endl;

cout << "  FLIGHT BOOKING SYSTEM" << endl;

cout << "------------------------------------------------------------" << endl;


cout << "  PNR            : " << pnr << endl;

cout << "------------------------------------------------------------" << endl;

cout << "  AIRLINE        : " << selectedFlight->getAirline() << endl;
cout << "  FLIGHT         : " << selectedFlight->getFlightNumber() << endl;

cout << "  FROM           : " << selectedFlight->getSource() << endl;
cout << "  TO             : " << selectedFlight->getDestination() << endl;

cout << "------------------------------------------------------------" << endl;

cout << "  DATE           : " << selectedFlight->getDate() << endl;
cout << "  DEPARTURE      : " << selectedFlight->getDepartureTime() << endl;
cout << "  ARRIVAL        : " << selectedFlight->getArrivalTime() << endl;

cout << "------------------------------------------------------------" << endl;


cout << "  PASSENGERS     : " << tickets << endl;

cout << "------------------------------------------------------------" << endl;

cout << "  BAGGAGE        : " << baggageWeight << " kg" << endl;

cout << "  MEAL           : ";

if (mealChoice == 1)
{
    if (mealType == 1)
        cout << "Veg Meal";
    else if (mealType == 2)
        cout << "Non-Veg Meal";
}
else
{
    cout << "Not Selected";
}

cout << endl;

cout << "------------------------------------------------------------" << endl;

cout << "  TOTAL PAID     : Rs. " << totalFare << endl;

cout << "------------------------------------------------------------" << endl;

cout << "              HAVE A SAFE JOURNEY!" << endl;

cout << "============================================================" << endl;
cout << "         THANK YOU FOR BOOKING WITH US" << endl;
cout << "============================================================" << endl;

                 }

                return 0;
                break;

                
            case 3:
                cout << "\nExiting application..." << endl;
                return 0;
            default:
                cout<<"\nChoose again! NOT a valid choice"<<endl;


        };



        if(choice>3){
          
            cout<<endl;
            cout<<"1. Sign Up"<<endl;
            cout<<"2. Log in"<<endl;
            cout<<"3. Exit Application";
            cout<<endl;
            cout<<"\nEnter your choice: ";
            cin>>choice;
        }

    }while(choice!=3 || choice>3);
    return 0;
}