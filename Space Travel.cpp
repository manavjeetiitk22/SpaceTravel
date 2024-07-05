#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;
// Planet class
class Planet
{
    // Data members
    string name;          // name of the planet
    int x, y, z;          // coordinates of the planet
    string color;         // color of the planet
    string water_content; // water content of the planet
    string inhabitants;   // inhabitation of the planet
    string size;          // size of the planet
    string atmosphere;    // atmosphere of the planet

public:
    // Default constructor
    Planet()
    {
        name = "";
        x = 0;
        y = 0;
        z = 0;
        color = "";
        water_content = "";
        inhabitants = "";
        size = "";
        atmosphere = "";
    }

    // Constructor with parameters
    Planet(string name, int x, int y, int z, string color, string water_content, string inhabitants, string size, string atmosphere)
    {
        this->name = name;
        this->x = x;
        this->y = y;
        this->z = z;
        this->color = color;
        this->water_content = water_content;
        this->inhabitants = inhabitants;
        this->size = size;
        this->atmosphere = atmosphere;
    }

    // Getter for name
    string getName()
    {
        return name;
    }

    // Getter for coordinates
    vector<int> getCoordinates()
    {
        return {x, y, z};
    }

    // Getter for x coordinate
    int getX()
    {
        return x;
    }

    // Getter for y coordinate
    int getY()
    {
        return y;
    }

    // Getter for z coordinate
    int getZ()
    {
        return z;
    }

    // Print the details of the planet
    void printDetails()
    {
        cout << "\nName: " << getName() << endl;
        cout << "Coordinates: (" << getX() << ", " << getY() << ", " << getZ() << ")" << endl;
        cout << "Color of the planet: " << color << endl;
        cout << "Water content of the planet: " << water_content << endl;
        cout << "Inhabitation of the planet: " << inhabitants << endl;
        cout << "Size of the planet: " << size << endl;
        cout << "Atmosphere of the planet: " << atmosphere << endl;
    }

    // Calculate the distance between two planets
    double get_distance(Planet other)
    {
        double dx = x - other.getX();
        double dy = y - other.getY();
        double dz = z - other.getZ();
        return sqrt(dx * dx + dy * dy + dz * dz);
    }
};

// A class to represent a ticket for interplanetary travel
class Ticket
{
private:
    double price;              // Price of the ticket
    double distance;           // Distance between the source and destination planets
    string travelDate;         // Date of travel in DD/MM/YYYY format
    Planet sourceStation;      // The source planet
    Planet destinationStation; // The destination planet
    string travelerName;       // Name of the traveler
    int ticketValidity;        // Validity of the ticket in years

public:
    // Constructor to initialize the ticket object
    Ticket(Planet src, Planet dest, string date, string name, int val)
    {
        sourceStation = src;
        destinationStation = dest;
        travelDate = date;
        travelerName = name;
        ticketValidity = val;
        distance = src.get_distance(dest); // Calculate the distance between the source and destination planets
        this->calcPrice();                 // Calculate the price of the ticket based on the distance and number of days left for travel
    }

    // Getter function to return the price of the ticket
    double getPrice()
    {
        return price;
    }

    // Function to update date of travel
    void updateDate(string d)
    {
        string olddate = getTravelDate();
        travelDate = d;
        if (this->checkValidity())
            this->calcPrice();
        else
        {
            travelDate = olddate;
            cout << "Ticket could not be updated due to lesser validity" << endl;
        }
    }

    // Function to update destination planet
    void updateDest(Planet p)
    {
        destinationStation = p;
        distance = sourceStation.get_distance(destinationStation);
        this->calcPrice();
    }

    // Getter function to return the distance between the source and destination planets
    double getDistance()
    {
        return distance;
    }

    // Getter function to return the date of travel
    string getTravelDate()
    {
        return travelDate;
    }

    // Getter function to return the name of the source planet
    string getSourceStation()
    {
        return sourceStation.getName();
    }

    // Getter function to return the name of the destination planet
    string getDestinationStation()
    {
        return destinationStation.getName();
    }

    // Getter function to return the name of the traveler
    string getTravelerName()
    {

        return travelerName;
    }

    // Function to calculate the number of days left
    int daysLeft()
    {
        int dd, mm, yyyy;
        dd = (travelDate[0] - '0') * 10 + (travelDate[1] - '0');
        mm = (travelDate[3] - '0') * 10 + (travelDate[4] - '0');
        yyyy = (travelDate[6] - '0') * 1000 + (travelDate[7] - '0') * 100 + (travelDate[8] - '0') * 10 + (travelDate[9] - '0');

        time_t now = time(0);
        tm *local = localtime(&now);

        tm tDate = {};
        tDate.tm_year = yyyy - 1900; // year is relative to 1900
        tDate.tm_mon = mm - 1;       // month is zero-based
        tDate.tm_mday = dd;

        // Calculate time difference in seconds
        time_t target_time = mktime(&tDate);
        double diff_seconds = difftime(target_time, now);

        // Convert time difference from seconds to days
        const int SECONDS_PER_DAY = 60 * 60 * 24;
        int diff_days = diff_seconds / SECONDS_PER_DAY;

        return diff_days;
    }

    // Function to check the validity of the ticket
    bool checkValidity()
    {
        if (ticketValidity == INT_MAX)
            return true;
        int days = daysLeft();
        if ((double)days / 365.25 > (double)ticketValidity)
            return false;
        else
            return true;
    }

    // Getter function to get validity of ticket
    int getValidity()
    {
        return ticketValidity;
    }

    // Function to calculate the price for the ticket
    void calcPrice()
    {
        // calculate price based on distance
        price = (distance * 1000) / (1 + daysLeft());
    }

    // Function to print the details of the ticket
    void printDetails()
    {
        cout << "\nTicket Details:" << endl;
        cout << "Source Station: " << sourceStation.getName() << endl;
        cout << "Destination Station: " << destinationStation.getName() << endl;
        cout << "Travel Date: " << travelDate << endl;
        cout << "Traveler Name: " << travelerName << endl;
        cout << "Ticket Price: " << price << endl;
        cout << "Distance: " << distance << endl;
        if (ticketValidity != INT_MAX)
            cout << "Validity: " << ticketValidity << " years" << endl;
    }
};

class Passenger
{
private:
    int traveler_id; // private attribute

public:
    string name;
    vector<Ticket> list_of_tickets; // public attribute

    // Constructor
    Passenger() {}
    Passenger(string n, int id)
    {
        traveler_id = id;
        name = n;
    }

    // Getter methods
    int get_traveler_id()
    {
        return traveler_id;
    }

    // Other methods
    void print_ticket_details()
    {
        for (int i = 0; i < list_of_tickets.size(); i++)
        {
            Ticket t = list_of_tickets[i];
            cout << "\nTicket " << i + 1 << " details:\n";
            cout << "Traveler Name: " << name << "\n";
            cout << "Source Planet: " << t.getSourceStation() << "\n";
            cout << "Destination Planet: " << t.getDestinationStation() << "\n";
            cout << "Travel Date: " << t.getTravelDate() << "\n";
            cout << "Price: " << t.getPrice() << "\n";
            cout << "Validity: " << t.getValidity() << endl;
        }
    }

    // Function to book a ticket
    void book_ticket(Ticket t)
    {
        list_of_tickets.push_back(t);
    }

    // Function to cancel a ticket
    void cancel_ticket(int ticket_num)
    {
        if (ticket_num < 1 || ticket_num > list_of_tickets.size())
        {
            cout << "Invalid ticket number!\n";
        }
        else
        {
            list_of_tickets.erase(list_of_tickets.begin() + ticket_num - 1);
            cout << "Ticket " << ticket_num << " cancelled successfully!\n";
        }
    }

    // Function to update a ticket
    void update_ticket(int ticket_num, Ticket new_ticket)
    {
        if (ticket_num < 1 || ticket_num > list_of_tickets.size())
        {
            cout << "Invalid ticket number!\n";
        }
        else
        {
            list_of_tickets[ticket_num - 1] = new_ticket;
            cout << "Ticket " << ticket_num << " updated successfully!\n";
        }
    }
};

class Astronaut
{
private:
    string name;           // a private string attribute to store the name of the traveler
    int id;                // a private integer attribute to store the ID of the traveler
    int yearsOfExperience; // private attributes
    int licenseId;

public:
    vector<Ticket> list_of_tickets; // a public vector attribute to store the list of tickets of the traveler
    Astronaut(string name, int id, int yearsOfExperience, int licenseId)
    {
        this->name = name;
        this->id = id;
        this->yearsOfExperience = yearsOfExperience;
        this->licenseId = licenseId;
    }

    Astronaut() {}

    string getName()
    { // a method to get the name of the traveler
        return name;
    }

    int getID()
    { // a method to get the ID of the traveler
        return id;
    }

    // Getter function to get experience
    int getExperience()
    {
        return yearsOfExperience;
    }

    // Function to get Licencse ID
    int getLicenseId()
    {
        return licenseId;
    }

    // Function to print details
    void printDetails()
    {
        cout << "\nAstronaut Name: " << getName() << endl;
        cout << "ID: " << getID() << endl;
        cout << "Years of Experience: " << yearsOfExperience << endl;
        cout << "License ID: " << licenseId << endl;
    }

    void print_ticket_details()
    { // a method to print the details of all the tickets of the traveler
        for (int i = 0; i < list_of_tickets.size(); i++)
        {
            Ticket t = list_of_tickets[i]; // get the ith ticket from the vector
            cout << "\nTicket " << i << " details:\n";
            cout << "Traveler Name: " << name << "\n";
            cout << "Source Planet: " << t.getSourceStation() << "\n";           // get the source planet of the ticket
            cout << "Destination Planet: " << t.getDestinationStation() << "\n"; // get the destination planet of the ticket
            cout << "Travel Date: " << t.getTravelDate() << "\n";                // get the travel date of the ticket
            cout << "Price: " << t.getPrice() << "\n";                           // get the price of the ticket
            cout << "Validity: " << t.getValidity() << endl;                     // get the validity of the ticket
        }
    }

    void book_ticket(Ticket t)
    { // a method to add a ticket to the list of tickets of the traveler
        list_of_tickets.push_back(t);
    }

    void cancel_ticket(int ticket_num)
    { // a method to cancel a ticket from the list of tickets of the traveler
        if (ticket_num < 1 || ticket_num > list_of_tickets.size())
        { // check if the ticket number is valid
            cout << "Invalid ticket number!\n";
        }
        else
        {
            list_of_tickets.erase(list_of_tickets.begin() + ticket_num - 1); // remove the ticket from the vector
            cout << "Ticket " << ticket_num << " cancelled successfully!\n";
        }
    }

    void update_ticket(int ticket_num, Ticket new_ticket)
    { // a method to update a ticket in the list of tickets of the traveler
        if (ticket_num < 1 || ticket_num > list_of_tickets.size())
        { // check if the ticket number is valid
            cout << "Invalid ticket number!\n";
        }
        else
        {
            list_of_tickets[ticket_num - 1] = new_ticket; // replace the ticket with the new ticket
            cout << "Ticket " << ticket_num << " updated successfully!\n";
        }
    }
};

// Define a class named "Commander"
class Commander
{
private:
    string authority_;     // Private attribute for authority
    string name;           // a private string attribute to store the name of the traveler
    int id;                // a private integer attribute to store the ID of the traveler
    int yearsOfExperience; // private attributes
    int licenseId;

public:
    // Constructor to initialize the Commander object with the given parameters
    Commander(string name, int id, string authority, int experience, int license_id)
        : name(name), id(id), authority_{authority}, yearsOfExperience{experience}, licenseId{license_id} {}

    Commander() {}

    vector<Ticket> list_of_tickets; // a public vector attribute to store the list of tickets of the traveler

    // Getter method to retrieve the authority of the Commander object
    string getAuthority()
    {
        return authority_;
    }

    string getName()
    { // a method to get the name of the traveler
        return name;
    }

    int getID()
    { // a method to get the ID of the traveler
        return id;
    }

    // Getter function to get experience
    int getExperience()
    {
        return yearsOfExperience;
    }

    // Function to get Licencse ID
    int getLicenseId()
    {
        return licenseId;
    }

    // Method to print the details of the Commander object
    void printDetails()
    {
        cout << "\nName: " << getName() << endl;
        cout << "ID: " << getID() << endl;
        cout << "Authority: " << getAuthority() << endl;
        cout << "Experience: " << getExperience() << endl;
        cout << "License ID: " << getLicenseId() << endl;
    }

    void print_ticket_details()
    { // a method to print the details of all the tickets of the traveler
        for (int i = 0; i < list_of_tickets.size(); i++)
        {
            Ticket t = list_of_tickets[i]; // get the ith ticket from the vector
            cout << "Ticket " << i + 1 << " details:\n";
            cout << "Traveler Name: " << name << "\n";
            cout << "Source Planet: " << t.getSourceStation() << "\n";           // get the source planet of the ticket
            cout << "Destination Planet: " << t.getDestinationStation() << "\n"; // get the destination planet of the ticket
            cout << "Travel Date: " << t.getTravelDate() << "\n";                // get the travel date of the ticket
            cout << "Price: " << t.getPrice() << "\n";                           // get the price of the ticket
            cout << "Validity: " << t.getValidity() << endl;                     // get the validity of the ticket
        }
    }

    void book_ticket(Ticket t)
    { // a method to add a ticket to the list of tickets of the traveler
        list_of_tickets.push_back(t);
    }

    void cancel_ticket(int ticket_num)
    { // a method to cancel a ticket from the list of tickets of the traveler
        if (ticket_num < 1 || ticket_num > list_of_tickets.size())
        { // check if the ticket number is valid
            cout << "Invalid ticket number!\n";
        }
        else
        {
            list_of_tickets.erase(list_of_tickets.begin() + ticket_num - 1); // remove the ticket from the vector
            cout << "Ticket " << ticket_num << " cancelled successfully!\n";
        }
    }

    void update_ticket(int ticket_num, Ticket new_ticket)
    { // a method to update a ticket in the list of tickets of the traveler
        if (ticket_num < 1 || ticket_num > list_of_tickets.size())
        { // check if the ticket number is valid
            cout << "Invalid ticket number!\n";
        }
        else
        {
            list_of_tickets[ticket_num - 1] = new_ticket; // replace the ticket with the new ticket
            cout << "Ticket " << ticket_num << " updated successfully!\n";
        }
    }
};

class SpaceTravel
{
private:
    vector<string> travellers;
    string astronaut;
    string commander;

public:
    // Constructor
    SpaceTravel(vector<string> newTravellers, string newAstronaut, string newCommander)
    {
        travellers = newTravellers;
        astronaut = newAstronaut;
        commander = newCommander;
    }

    // Add new travellers
    void addTraveller(string newTraveller)
    {
        if (travellers.size() < 10)
        {
            travellers.push_back(newTraveller);
        }
        else
        {
            cout << "Maximum number of travellers reached." << endl;
        }
    }

    // List all travellers
    void listTravellers()
    {
        cout << "Travellers: ";
        for (int i = 0; i < travellers.size(); i++)
        {
            cout << travellers[i] << ", ";
        }
        cout << endl;
    }

    // Set the astronaut ID
    void setAstronaut(string newAstronaut)
    {
        astronaut = newAstronaut;
    }

    // Set the commander ID
    void setCommander(string newCommander)
    {
        commander = newCommander;
    }

    // Update the astronaut ID, while changing the astronaut
    void updateAstronaut(string newAstronaut)
    {
        astronaut = newAstronaut;
    }

    // Change the commander ID, while changing the commander
    void updateCommander(string newCommander)
    {
        commander = newCommander;
    }
};

Planet earth("Earth", 0, 0, 0, "Blue", "Wet", "Inhabited", "Medium", "Breathable");
Planet mercury("Mercury", 1, 1, 1, "Gray", "Dry", "Uninhabited", "Small", "Thin");
Planet venus("Venus", 2, 2, 2, "Yellow", "Wet", "Uninhabitable", "Large", "Toxic");
Planet mars("Mars", 3, 3, 3, "Red", "Dry", "Uninhabited", "Small", "Thin");
Planet jupiter("Jupiter", 4, 4, 4, "Orange", "Moist", "Uninhabitable", "Large", "Toxic");
Planet saturn("Saturn", 5, 5, 5, "Yellow", "Moist", "Uninhabitable", "Large", "Toxic");
Planet uranus("Uranus", 6, 6, 6, "Blue", "Moist", "Uninhabitable", "Medium", "Toxic");
Planet neptune("Neptune", 7, 7, 7, "Blue", "Moist", "Uninhabitable", "Medium", "Toxic");
Planet moon("Moon", 8, 8, 8, "Gray", "Dry", "Uninhabited", "Small", "None");
Planet sun("Sun", 9, 9, 9, "Yellow", "None", "Uninhabitable", "Large", "None");

Planet *getPlanet(string name)
{
    Planet *givenPlanet;
    if (name == "earth")
        givenPlanet = &earth;
    else if (name == "mercury")
        givenPlanet = &mercury;
    else if (name == "venus")
        givenPlanet = &venus;
    else if (name == "mars")
        givenPlanet = &mars;
    else if (name == "jupiter")
        givenPlanet = &jupiter;
    else if (name == "saturn")
        givenPlanet = &saturn;
    else if (name == "uranus")
        givenPlanet = &uranus;
    else if (name == "neptune")
        givenPlanet = &neptune;
    else if (name == "moon")
        givenPlanet = &moon;
    else if (name == "sun")
        givenPlanet = &sun;
    else
    {
        cout << "Please enter the name of the Planet in lowercase letters only. Here is the list of valid names: earth, mercury, venus, mars, jupiter, saturn, uranus, neptune, moon, sun\n";
        cout << "Re-enter the Planet name: " << endl;
        string planetName;
        cin >> planetName;
        return getPlanet(planetName);
    }
    return givenPlanet;
}

int main()
{
    char var, type, task, choice, change;
    string name, source, destination, date, authority;
    int id, experience, licenseID, validity;
    Planet *sourcePlanet;
    Planet *destPlanet;
    vector<Ticket> allTickets;
    map<int, Passenger> allPassengers;
    map<int, Commander> allCommanders;
    map<int, Astronaut> allAstronauts;

    Passenger p1("Alice Brown", 25);
    Passenger p2("Bob Johnson", 30);
    Passenger p3("Charlie Lee", 20);
    Passenger p4("David Davis", 28);
    Passenger p5("Emily Wang", 22);
    Passenger p6("Frank Wilson", 45);
    Passenger p7("Grace Kim", 29);
    Passenger p8("Henry Chen", 32);
    Passenger p9("Isabelle Lee", 27);
    Passenger p10("Jackie Chan", 50);
    Passenger p11("Karen Smith", 35);

    allPassengers[25] = p1;
    allPassengers[30] = p2;
    allPassengers[20] = p3;
    allPassengers[28] = p4;
    allPassengers[22] = p5;
    allPassengers[45] = p6;
    allPassengers[29] = p7;
    allPassengers[32] = p8;
    allPassengers[27] = p9;
    allPassengers[50] = p10;
    allPassengers[35] = p11;

    cout << " Hi, Welcome to the Space Travel System." << endl;
    while (1)
    {
        cout << "How can I help you" << endl;
        cout << " Enter \nC: to continue the converstion\nE: End this conversation" << endl;
        cin >> var;
        if (var != 'C')
        {
            cout << "Thank you!";
            break;
        }
        cout << "Please specify the type of traveller " << endl;
        cout << "Enter \nP: Passeneger \nA: Astronaut \nC: Commander\nG: Get Admin access" << endl;
        cin >> type;
        if (type == 'G')
        {
            cout << "Enter Password: \n{Pass word is \"admin@123\" without the double quotes}" << endl;
            cout << "{Password is being shown here just for grader's help}" << endl;
            string password;
            cin >> password;
            if (password != "admin@123")
            {
                cout << "Wrong password! Access Forbidden" << endl;
                continue;
            }
            while (true)
            {
                cout << "What do you want to do: \nPress T to get the list of all Tickets\nPress P to get the list of all Passengers\nPress A to get the list of all Astronauts\nPress C to get the list of all Commanders" << endl;
                char response;
                cin >> response;
                if (response == 'T')
                {
                    cout << "Here is the list of all tickets: \n";
                    for (int i = 0; i < allTickets.size(); i++)
                    {
                        cout << "Ticket id: " << i << endl;
                        allTickets[i].printDetails();
                        cout << endl;
                    }
                }
                else if (response == 'P')
                {
                    cout << "Here is the list of all Passengers: \n\n";
                    for (auto it = allPassengers.begin(); it != allPassengers.end(); ++it)
                    {
                        cout << "Traveller id: " << it->first << " and name = " << it->second.name << endl;
                    }
                }
                else if (response == 'A')
                {
                    cout << "Here is the list of all Astronauts: \n\n";
                    for (auto it = allAstronauts.begin(); it != allAstronauts.end(); ++it)
                    {
                        it->second.printDetails();
                        cout << endl;
                    }
                }
                else if (response == 'C')
                {
                    cout << "Here is the list of all Commanders: \n\n";
                    for (auto it = allCommanders.begin(); it != allCommanders.end(); ++it)
                    {
                        it->second.printDetails();
                        cout << endl;
                    }
                }
                else
                {
                    cout << "Invalid Response" << endl;
                }
                cout << "\n\nThat's it. Do you want to do anything else?" << endl;
                cout << "Press Y to continue using the Admin account else press N\n";
                char yn;
                cin >> yn;
                if (yn != 'Y')
                    break;
            }
            continue;
        }
        cout << "Enter your id" << endl;
        cin >> id;

        if (type == 'P')
        {
            if (allPassengers.count(id) == 0)
            {
                cout << "Welcome new traveller. Please enter your details." << endl;
                cout << "Enter your name" << endl;
                cin >> name;
                Passenger *p = new Passenger(name, id);
                allPassengers[id] = *p;
            }
            else
                name = allPassengers[id].name;
        }
        else if (type == 'A')
        {
            if (allAstronauts.count(id) == 0)
            {
                cout << "Welcome new traveller. Please enter your details." << endl;
                cout << "Enter your name" << endl;
                cin >> name;
                cout << "Enter Years of experience" << endl;
                cin >> experience;
                cout << "Enter your License ID" << endl;
                cin >> licenseID;
                Astronaut *a = new Astronaut(name, id, experience, licenseID);
                allAstronauts[id] = *a;
            }
            else
                name = allAstronauts[id].getName();
        }
        else if (type == 'C')
        {
            if (allCommanders.count(id) == 0)
            {
                cout << "Welcome new traveller. Please enter your details." << endl;
                cout << "Enter your name" << endl;
                cin >> name;
                cout << "Enter Authority" << endl;
                cin >> authority;
                cout << "Enter Years of experience" << endl;
                cin >> experience;
                cout << "Enter your License ID" << endl;
                cin >> licenseID;
                Commander *c = new Commander(name, id, authority, experience, licenseID);
                allCommanders[id] = *c;
            }
            else
                name = allAstronauts[id].getName();
        }
        else
        {
            cout << "Invalid Response" << endl;
            continue;
        }

        cout << "Welcome " << name << endl;

        cout << " Enter \nB: to book a ticket \nU: Update a ticket \nD: Delete an existing ticket\nH: to get the history of your booked tickets\nP to know about any Planet" << endl;
        cin >> task;

        if (task == 'B')
        {
            cout << "Enter source planet" << endl;
            cin >> source;
            cout << "Enter destination planet" << endl;
            cin >> destination;
            cout << "Enter the date of travel in DD/MM/YYYY format" << endl;
            cin >> date;

            sourcePlanet = getPlanet(source);
            destPlanet = getPlanet(destination);

            validity = INT_MAX;

            if (type == 'P')
                validity = 10;

            Ticket t(*sourcePlanet, *destPlanet, date, name, validity);

            if (type == 'P')
            {
                allPassengers[id].list_of_tickets.push_back(t);
            }
            if (type == 'A')
            {
                allAstronauts[id].list_of_tickets.push_back(t);
            }
            if (type == 'C')
            {
                allCommanders[id].list_of_tickets.push_back(t);
            }
            if (t.checkValidity())
            {
                int ticketid = allTickets.size();
                allTickets.push_back(t);
                cout << "Ticket Booked.\nPrinting the details of the ticket:\n";
                t.printDetails();
                cout << "Your ticket id is: " << ticketid << endl;
            }
            else
            {
                cout << "Invalid Ticket. Booking outside window of 10 years for a Passenger." << endl;
            }

            // Extra functionality added to get planet information
            cout << "Do you want to get to know the details about your destination planet?" << endl;
            cout << "Type Y for yes and N for no" << endl;
            char a;
            cin >> a;
            if (a == 'Y')
            {
                destPlanet->printDetails();
            }
        }

        else if (task == 'U')
        {
            int ticketID;
            cout << "Enter ticket id" << endl;
            cin >> ticketID;
            if (ticketID >= allTickets.size())
            {
                cout << "Invalid Ticket ID\n";
                continue;
            }
            cout << "What do you want to update?" << endl;
            cout << " Enter \nD: Date of Travel \nP: Destination Planet" << endl;
            cin >> change;
            if (change == 'D')
            {
                string newDate;
                cout << "Enter new date of travel in DD/MM/YYYY format" << endl;
                cin >> newDate;
                allTickets[ticketID].updateDate(newDate);
            }
            else if (change == 'P')
            {
                string newDest;
                cout << "Enter new destination planet in lowercase" << endl;
                cin >> newDest;
                destPlanet = getPlanet(newDest);

                allTickets[ticketID].updateDest(*destPlanet);

                // Extra functionality added to get planet information
                cout << "Do you want to get to know the details about your destination planet?" << endl;
                cout << "Type Y for yes and N for no" << endl;
                char a;
                cin >> a;
                if (a == 'Y')
                {
                    destPlanet->printDetails();
                }
            }
            cout << "Your ticket is updated.\n The new ticket details are as follows:" << endl;
            allTickets[ticketID].printDetails();
        }
        else if (task == 'D')
        {
            int ticketID;
            cout << "Enter ticket id" << endl;
            cin >> ticketID;
            if (ticketID >= allTickets.size())
            {
                cout << "Invalid Ticket ID\n";
                continue;
            }
            Ticket deletedTicket = allTickets[ticketID];
            allTickets.erase(allTickets.begin() + ticketID);

            cout << "Your ticket has been deleted." << endl;
        }
        else if (task == 'H')
        {
            cout << "Here are the details of all your booked tickets\n\n";
            if (type == 'P')
            {
                int num = allPassengers[id].list_of_tickets.size();
                for (int i = 0; i < num; i++)
                {
                    allPassengers[id].list_of_tickets[i].printDetails();
                    cout << endl;
                }
            }
            else if (type == 'A')
            {
                int num = allAstronauts[id].list_of_tickets.size();
                for (int i = 0; i < num; i++)
                {
                    allAstronauts[id].list_of_tickets[i].printDetails();
                    cout << endl;
                }
            }
            else if (type == 'C')
            {
                int num = allCommanders[id].list_of_tickets.size();
                for (int i = 0; i < num; i++)
                {
                    allCommanders[id].list_of_tickets[i].printDetails();
                    cout << endl;
                }
            }
        }
        else if (task == 'P')
        {
            cout << "Enter the name of the planet in lowercase: " << endl;
            string planetName;
            cin >> planetName;
            getPlanet(planetName)->printDetails();
        }
        else
        {
            cout << "Invalid Response" << endl;
        }
        cout << "Thanks" << endl;
    }
}