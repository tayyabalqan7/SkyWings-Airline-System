#include<iostream>
#include<string>
using namespace std;

void printLine(char ch = '-', int n = 55) {
    for(int i = 0; i < n; i++) cout << ch;
    cout << endl;
}

void printHeader(string title) {
    printLine('=');
    cout << "       " << title << endl;
    printLine('=');
}

class Meal {
private:
    string mealType;
    double mealPrice;
    bool   isVeg;
public:
    Meal() {
        mealType  = "Standard";
        mealPrice = 500.0;
        isVeg     = false;
    }
    Meal(string type, double price, bool veg) {
        mealType  = type;
        mealPrice = price;
        isVeg     = veg;
    }
    string getMealType()  { return mealType; }
    double getMealPrice() { return mealPrice; }
    bool   getIsVeg()     { return isVeg; }
    void display() {
        cout << "  Meal     : " << mealType << endl;
        cout << "  Price    : Rs. " << mealPrice << endl;
        cout << "  Type     : " << (isVeg ? "Veg" : "Non-Veg") << endl;
    }
};

class Luggage {
private:
    double weightKg;
    int    bags;
    double extraCharges;
public:
    Luggage() {
        weightKg     = 0.0;
        bags         = 0;
        extraCharges = 0.0;
    }
    Luggage(double w, int b) {
        weightKg = w;
        bags     = b;
        if(weightKg > 23.0)
            extraCharges = (weightKg - 23.0) * 150.0;
        else
            extraCharges = 0.0;
    }
    double getExtraCharges() { return extraCharges; }
    double getWeight()       { return weightKg; }
    void display() {
        cout << "  Bags     : " << bags << endl;
        cout << "  Weight   : " << weightKg << " kg" << endl;
        cout << "  Extra    : Rs. " << extraCharges << endl;
    }
};

class Flight {
private:
    string flightCode;
    string origin;
    string destination;
    string departureTime;
    int    totalSeats;
    int    bookedSeats;
    double basePrice;
public:
    static int totalFlights;
    Flight() {
        flightCode    = "XX-000";
        origin        = "Unknown";
        destination   = "Unknown";
        departureTime = "00:00";
        totalSeats    = 100;
        bookedSeats   = 0;
        basePrice     = 10000.0;
        totalFlights++;
    }
    Flight(string code, string org, string dest, string time, int seats, double price) {
        flightCode    = code;
        origin        = org;
        destination   = dest;
        departureTime = time;
        totalSeats    = seats;
        bookedSeats   = 0;
        basePrice     = price;
        totalFlights++;
    }
    string getCode()       { return flightCode; }
    string getOrigin()     { return origin; }
    string getDest()       { return destination; }
    double getBasePrice()  { return basePrice; }
    int    getAvailSeats() { return totalSeats - bookedSeats; }
    void bookSeat()        { if(bookedSeats < totalSeats) bookedSeats++; }
    void cancelSeat()      { if(bookedSeats > 0) bookedSeats--; }
    static int getTotalFlights() { return totalFlights; }
    void display() {
        printLine();
        cout << "Flight Code  : " << flightCode << endl;
        cout << "Route        : " << origin << " --> " << destination << endl;
        cout << "Departure    : " << departureTime << endl;
        cout << "Seats Left   : " << getAvailSeats() << endl;
        cout << "Base Price   : Rs. " << basePrice << endl;
        printLine();
    }
};
int Flight::totalFlights = 0;

class Person {
protected:
    string name;
    int    age;
    string cnic;
    string phone;
public:
    Person() {
        name  = "Unknown";
        age   = 0;
        cnic  = "00000-0000000-0";
        phone = "0000-0000000";
    }
    Person(string n, int a, string c, string p) {
        name  = n;
        age   = a;
        cnic  = c;
        phone = p;
    }
    string getName()  { return name; }
    int    getAge()   { return age; }
    string getCNIC()  { return cnic; }
    string getPhone() { return phone; }
    virtual void display() {
        cout << "Name   : " << name  << endl;
        cout << "Age    : " << age   << endl;
        cout << "CNIC   : " << cnic  << endl;
        cout << "Phone  : " << phone << endl;
    }
    virtual ~Person() {}
};

class Passenger : public Person {
private:
    int     passengerID;
    string  seatClass;
    string  seatNumber;
    Meal    meal;
    Luggage luggage;
    double  totalFare;
    bool    checkedIn;
public:
    static int totalPassengers;
    Passenger() : Person(), meal(), luggage() {
        passengerID = 0;
        seatClass   = "Economy";
        seatNumber  = "00A";
        totalFare   = 0.0;
        checkedIn   = false;
        totalPassengers++;
    }
    Passenger(int id, string n, int a, string c, string ph,
              string cls, string seat, Meal m, Luggage l, double fare)
        : Person(n, a, c, ph), meal(m), luggage(l) {
        passengerID = id;
        seatClass   = cls;
        seatNumber  = seat;
        totalFare   = fare + l.getExtraCharges() + m.getMealPrice();
        checkedIn   = false;
        totalPassengers++;
    }
    void   checkIn()     { checkedIn = true; }
    bool   isCheckedIn() { return checkedIn; }
    double getFare()     { return totalFare; }
    int    getID()       { return passengerID; }
    string getSeatClass(){ return seatClass; }
    void applyDiscount(double percent) {
        double disc = totalFare * (percent / 100.0);
        totalFare  -= disc;
        cout << "Discount " << percent << "% applied. New Fare: Rs. " << totalFare << endl;
    }
    void display() override {
        printLine('*');
        cout << "--- PASSENGER RECORD ---" << endl;
        cout << "Passenger ID : " << passengerID << endl;
        Person::display();
        cout << "Seat Class   : " << seatClass << endl;
        cout << "Seat Number  : " << seatNumber << endl;
        cout << "Checked In   : " << (checkedIn ? "Yes" : "No") << endl;
        cout << "--- Meal ---" << endl;
        meal.display();
        cout << "--- Luggage ---" << endl;
        luggage.display();
        cout << "Total Fare   : Rs. " << totalFare << endl;
        printLine('*');
    }
    static int getTotalPassengers() { return totalPassengers; }
};
int Passenger::totalPassengers = 0;

class Staff : public Person {
protected:
    int    staffID;
    string designation;
    double salary;
public:
    static int totalStaff;
    Staff() : Person() {
        staffID     = 0;
        designation = "General";
        salary      = 0.0;
        totalStaff++;
    }
    Staff(int id, string n, int a, string c, string ph, string desig, double sal)
        : Person(n, a, c, ph) {
        staffID     = id;
        designation = desig;
        salary      = sal;
        totalStaff++;
    }
    void display() override {
        printLine('-');
        cout << "--- STAFF RECORD ---" << endl;
        cout << "Staff ID     : " << staffID << endl;
        Person::display();
        cout << "Designation  : " << designation << endl;
        cout << "Salary       : Rs. " << salary << endl;
        printLine('-');
    }
    static int getTotalStaff() { return totalStaff; }
};
int Staff::totalStaff = 0;

class Pilot : public Staff {
private:
    string licenseNumber;
    int    flightHours;
    string assignedFlight;
public:
    Pilot() : Staff() {
        licenseNumber  = "LIC-000";
        flightHours    = 0;
        assignedFlight = "None";
    }
    Pilot(int id, string n, int a, string c, string ph,
          double sal, string lic, int hours, string flight)
        : Staff(id, n, a, c, ph, "Captain", sal) {
        licenseNumber  = lic;
        flightHours    = hours;
        assignedFlight = flight;
    }
    void display() override {
        Staff::display();
        cout << "License No.  : " << licenseNumber << endl;
        cout << "Flight Hours : " << flightHours << endl;
        cout << "Assigned     : " << assignedFlight << endl;
        printLine('-');
    }
};

class Reservation {
private:
    int    reservationID;
    string flightCode;
    string passengerName;
    string bookingDate;
    string status;
public:
    static int totalReservations;
    Reservation() {
        reservationID = 0;
        flightCode    = "XX-000";
        passengerName = "Unknown";
        bookingDate   = "00/00/0000";
        status        = "Pending";
        totalReservations++;
    }
    Reservation(int id, string fc, string pn, string date) {
        reservationID = id;
        flightCode    = fc;
        passengerName = pn;
        bookingDate   = date;
        status        = "Confirmed";
        totalReservations++;
    }
    void cancel()  { status = "Cancelled"; }
    void confirm() { status = "Confirmed"; }
    string getStatus()        { return status; }
    string getFlightCode()    { return flightCode; }
    string getPassengerName() { return passengerName; }
    void display() {
        cout << "Reservation ID : " << reservationID << endl;
        cout << "Flight Code    : " << flightCode << endl;
        cout << "Passenger      : " << passengerName << endl;
        cout << "Date           : " << bookingDate << endl;
        cout << "Status         : " << status << endl;
    }
    static int getTotalReservations() { return totalReservations; }
};
int Reservation::totalReservations = 0;

void compareFares(Passenger p1, Passenger p2) {
    printHeader("FARE COMPARISON");
    cout << p1.getName() << " : Rs. " << p1.getFare() << endl;
    cout << p2.getName() << " : Rs. " << p2.getFare() << endl;
    if(p1.getFare() > p2.getFare())
        cout << p1.getName() << " has a higher fare." << endl;
    else if(p2.getFare() > p1.getFare())
        cout << p2.getName() << " has a higher fare." << endl;
    else
        cout << "Both passengers have equal fares." << endl;
}

void applyAgeDiscount(Passenger &p) {
    if(p.getAge() >= 60) {
        cout << "Senior Citizen Discount (15%) for " << p.getName() << ":" << endl;
        p.applyDiscount(15.0);
    } else if(p.getAge() <= 5) {
        cout << "Infant Discount (50%) for " << p.getName() << ":" << endl;
        p.applyDiscount(50.0);
    } else {
        cout << p.getName() << " : No age-based discount." << endl;
    }
}

void processCheckIn(Passenger &p) {
    if(!p.isCheckedIn()) {
        p.checkIn();
        cout << p.getName() << " successfully checked in!" << endl;
    } else {
        cout << p.getName() << " is already checked in." << endl;
    }
}

int main() {

    printHeader("SKY WINGS AIRLINE RESERVATION SYSTEM");

    Flight flights[3] = {
        Flight("PK-101", "Karachi",   "Lahore",    "08:00", 150, 12000.0),
        Flight("PK-202", "Islamabad", "Dubai",      "14:30", 200, 45000.0),
        Flight("PK-303", "Lahore",    "London",     "22:00", 180, 95000.0)
    };

    printHeader("AVAILABLE FLIGHTS");
    for(int i = 0; i < 3; i++) {
        flights[i].display();
    }

    Meal m1("Chicken Biryani", 650.0, false);
    Meal m2("Veg Pulao",       400.0, true);
    Meal m3("Pasta",           550.0, true);

    Luggage l1(20.0, 1);
    Luggage l2(30.0, 2);
    Luggage l3(15.0, 1);

    Passenger passengers[3] = {
        Passenger(1, "Ali Raza",    28, "42101-1234567-1", "0301-1111111",
                  "Economy",  "12A", m1, l1, 12000.0),
        Passenger(2, "Sara Khan",   65, "42101-7654321-2", "0312-2222222",
                  "Business", "3B",  m2, l2, 45000.0),
        Passenger(3, "Hamza Baig",   4, "42101-1111111-3", "0333-3333333",
                  "Economy",  "18C", m3, l3, 12000.0)
    };

    printHeader("PASSENGER RECORDS");
    for(int i = 0; i < 3; i++) {
        passengers[i].display();
    }

    printHeader("AGE-BASED DISCOUNTS");
    for(int i = 0; i < 3; i++) {
        applyAgeDiscount(passengers[i]);
    }

    printHeader("CHECK-IN PROCESS");
    for(int i = 0; i < 3; i++) {
        processCheckIn(passengers[i]);
    }

    compareFares(passengers[0], passengers[1]);

    Pilot pilot1(101, "Capt. Usman", 45, "42101-9999999-1", "0300-9999999",
                 250000.0, "LIC-PK-4521", 8500, "PK-101");
    Pilot pilot2(102, "Capt. Zara",  38, "42101-8888888-2", "0311-8888888",
                 230000.0, "LIC-PK-3310", 6200, "PK-202");

    printHeader("PILOT PROFILES");
    pilot1.display();
    pilot2.display();

    Reservation reservations[3] = {
        Reservation(501, "PK-101", "Ali Raza",  "09/05/2026"),
        Reservation(502, "PK-202", "Sara Khan", "09/05/2026"),
        Reservation(503, "PK-303", "Hamza Baig","09/05/2026")
    };

    printHeader("RESERVATIONS");
    for(int i = 0; i < 3; i++) {
        reservations[i].display();
        printLine();
    }

    printHeader("CANCELLATION - Sara Khan");
    reservations[1].cancel();
    cout << "Status after cancellation: " << reservations[1].getStatus() << endl;

    printHeader("SEAT CLASS SWITCH MENU");
    for(int i = 0; i < 3; i++) {
        string cls = passengers[i].getSeatClass();
        int choice = 0;
        if(cls == "Economy")  choice = 1;
        if(cls == "Business") choice = 2;
        if(cls == "First")    choice = 3;
        cout << passengers[i].getName() << " -> ";
        switch(choice) {
            case 1: cout << "Economy Class  | Standard service." << endl; break;
            case 2: cout << "Business Class | Premium lounge access." << endl; break;
            case 3: cout << "First Class    | Luxury suite & chef." << endl; break;
            default: cout << "Unknown Class." << endl;
        }
    }

    printHeader("FLIGHT SEAT BOOKING (WHILE LOOP)");
    int i = 0;
    while(i < 3) {
        flights[i].bookSeat();
        cout << "Seat booked on " << flights[i].getCode()
             << " | Remaining: " << flights[i].getAvailSeats() << endl;
        i++;
    }

    printHeader("POLYMORPHISM - STAFF & PILOTS VIA BASE POINTER");
    Person* staffList[2];
    staffList[0] = &pilot1;
    staffList[1] = &pilot2;
    for(int j = 0; j < 2; j++) {
        staffList[j]->display();
    }

    printHeader("SYSTEM STATISTICS");
    cout << "Total Flights       : " << Flight::getTotalFlights()           << endl;
    cout << "Total Passengers    : " << Passenger::getTotalPassengers()     << endl;
    cout << "Total Staff         : " << Staff::getTotalStaff()              << endl;
    cout << "Total Reservations  : " << Reservation::getTotalReservations() << endl;

    printHeader("THANK YOU - SKY WINGS AIRLINES");

    return 0;
}
