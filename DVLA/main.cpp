#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip> // For std::setw and std::setfill

using namespace std;

// A simple structure to hold date information
struct Date {
    int day;
    int month;
    int year;
};

// Function to get the current date
Date getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    Date currentDate;
    currentDate.day = ltm->tm_mday;
    currentDate.month = 1 + ltm->tm_mon;
    currentDate.year = 1900 + ltm->tm_year;
    return currentDate;
}

// Function to check if a license is valid
bool isLicenseValid(const Date& expiryDate) {
    Date currentDate = getCurrentDate();
    if (expiryDate.year > currentDate.year) return true;
    if (expiryDate.year == currentDate.year && expiryDate.month > currentDate.month) return true;
    if (expiryDate.year == currentDate.year && expiryDate.month == currentDate.month && expiryDate.day >= currentDate.day) return true;
    return false;
}

// Global counter for generating unique IDs
int licenseCounter = 1000;
int vehicleRegCounter = 10;

// Driver Class
class Driver {
private:
    string firstName;
    string lastName;
    string otherNames;
    char gender;
    int age;
    string nationality;
    string licenseNumber;
    Date licenseIssueDate;
    Date licenseExpiryDate;

public:
    Driver() {}

    void setDetails(string fname, string lname, string onames, char gen, int age_in, string nat) {
        firstName = fname;
        lastName = lname;
        otherNames = onames;
        gender = gen;
        age = age_in;
        nationality = nat;
    }

    void generateLicense() {
        if (age < 18) {
            cout << "Applicant is not qualified to attain a license." << endl;
            return;
        }

        // Generate a unique license number
        licenseCounter++;
        string initials = nationality.substr(0, 3);
        for (char& c : initials) {
            c = toupper(c);
        }
        licenseNumber = initials + to_string(licenseCounter);

        // Set issue and expiry dates
        licenseIssueDate = getCurrentDate();
        licenseExpiryDate = licenseIssueDate;
        licenseExpiryDate.year += 1;

        cout << "License generated successfully for " << firstName << "." << endl;
    }

    void renewLicense() {
        if (isLicenseValid(licenseExpiryDate)) {
            cout << "License is not expired yet. Renewal not needed." << endl;
        } else {
            Date renewalDate = getCurrentDate();
            licenseExpiryDate.year = renewalDate.year + 1;
            licenseExpiryDate.month = renewalDate.month;
            licenseExpiryDate.day = renewalDate.day;
            cout << "License for " << firstName << " " << lastName << " has been renewed." << endl;
            cout << "New expiry date: " << licenseExpiryDate.day << "/" << licenseExpiryDate.month << "/" << licenseExpiryDate.year << endl;
        }
    }

    void displayLicenseInfo() const {
        cout << "\n------------------ DRIVER INFO ------------------" << endl;
        cout << "Name: " << firstName << " " << otherNames << " " << lastName << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Nationality: " << nationality << endl;
        cout << "License Number: " << licenseNumber << endl;
        cout << "Issue Date: " << licenseIssueDate.day << "/" << licenseIssueDate.month << "/" << licenseIssueDate.year << endl;
        cout << "Expiry Date: " << licenseExpiryDate.day << "/" << licenseExpiryDate.month << "/" << licenseExpiryDate.year << endl;
        cout << "Validity Status: " << (isLicenseValid(licenseExpiryDate) ? "Valid" : "Expired") << endl;
        cout << "---------------------------------------------------" << endl;
    }

    string getLicenseNumber() const {
        return licenseNumber;
    }

    string getFullName() const {
        return firstName + " " + otherNames + " " + lastName;
    }
};

// Vehicle Class
class Vehicle {
private:
    string registrationNumber;
    string brand;
    string type;
    string colour;
    string ownerLicenseNumber; // Foreign key to link to a driver

public:
    Vehicle() {}

    void setDetails(string regNum, string brnd, string typ, string clr, string ownerLicNum) {
        registrationNumber = regNum;
        brand = brnd;
        type = typ;
        colour = clr;
        ownerLicenseNumber = ownerLicNum;
    }

    void displayVehicleInfo() const {
        cout << "\n------------------ VEHICLE INFO -------------------" << endl;
        cout << "Registration Number: " << registrationNumber << endl;
        cout << "Brand: " << brand << endl;
        cout << "Type: " << type << endl;
        cout << "Colour: " << colour << endl;
        cout << "Owner's License No.: " << ownerLicenseNumber << endl;
        cout << "---------------------------------------------------" << endl;
    }

    string getRegistrationNumber() const {
        return registrationNumber;
    }
};

// Global data storage
vector<Driver> allDrivers;
vector<Vehicle> allVehicles;

// --- Function Prototypes ---
void registerNewDriver();
void registerNewVehicle();
void renewLicense();
void showAllDrivers();
void showAllVehicles();
void showMenu();

int main() {
    char choice;
    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Consume the newline character

        switch (toupper(choice)) {
            case 'A':
                registerNewDriver();
                break;
            case 'B':
                registerNewVehicle();
                break;
            case 'C':
                renewLicense();
                break;
            case 'D':
                showAllDrivers();
                break;
            case 'E':
                showAllVehicles();
                break;
            case 'Q':
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    } while (toupper(choice) != 'Q');

    return 0;
}

// --- Function Definitions ---
void showMenu() {
    cout << "\n\n--- DVLA Management System ---" << endl;
    cout << "A. Register a New Driver" << endl;
    cout << "B. Register a New Vehicle" << endl;
    cout << "C. Renew an Expired License" << endl;
    cout << "D. Show All Registered Drivers" << endl;
    cout << "E. Show All Registered Vehicles" << endl;
    cout << "Q. Quit" << endl;
}

void registerNewDriver() {
    Driver newDriver;
    string fname, lname, onames, nationality;
    char gender;
    int age;

    cout << "\n--- New Driver Registration ---" << endl;
    cout << "Enter applicant's first name: ";
    getline(cin, fname);
    cout << "Enter applicant's last name: ";
    getline(cin, lname);
    cout << "Enter applicant's other names (if none, press Enter): ";
    getline(cin, onames);
    cout << "Enter applicant's gender (M/F): ";
    cin >> gender;
    cin.ignore();
    cout << "Enter applicant's age: ";
    cin >> age;
    cin.ignore();
    cout << "Enter applicant's nationality: ";
    getline(cin, nationality);

    newDriver.setDetails(fname, lname, onames, toupper(gender), age, nationality);
    newDriver.generateLicense();
    allDrivers.push_back(newDriver);
}

void registerNewVehicle() {
    string ownerLicenseNum;
    cout << "\n--- New Vehicle Registration ---" << endl;
    cout << "Enter owner's license number: ";
    getline(cin, ownerLicenseNum);

    bool driverFound = false;
    for (const auto& driver : allDrivers) {
        if (driver.getLicenseNumber() == ownerLicenseNum) {
            driverFound = true;
            break;
        }
    }

    if (!driverFound) {
        cout << "Error: No driver found with that license number. Please register the driver first." << endl;
        return;
    }

    Vehicle newVehicle;
    string brand, type, colour;

    cout << "Enter vehicle brand: ";
    getline(cin, brand);
    cout << "Enter vehicle type: ";
    getline(cin, type);
    cout << "Enter vehicle colour: ";
    getline(cin, colour);

    // Generate a unique registration number
    vehicleRegCounter++;
    string regNum = "GHA" + to_string(vehicleRegCounter);

    newVehicle.setDetails(regNum, brand, type, colour, ownerLicenseNum);
    allVehicles.push_back(newVehicle);
    cout << "Vehicle registered successfully! Registration number: " << regNum << endl;
}

void renewLicense() {
    string licenseNum;
    cout << "\n--- Renew License ---" << endl;
    cout << "Enter license number to renew: ";
    getline(cin, licenseNum);

    bool found = false;
    for (auto& driver : allDrivers) {
        if (driver.getLicenseNumber() == licenseNum) {
            driver.renewLicense();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Error: License number not found." << endl;
    }
}

void showAllDrivers() {
    cout << "\n\n--- ALL REGISTERED DRIVERS ---" << endl;
    if (allDrivers.empty()) {
        cout << "No drivers have been registered yet." << endl;
        return;
    }
    for (const auto& driver : allDrivers) {
        driver.displayLicenseInfo();
    }
}

void showAllVehicles() {
    cout << "\n\n--- ALL REGISTERED VEHICLES ---" << endl;
    if (allVehicles.empty()) {
        cout << "No vehicles have been registered yet." << endl;
        return;
    }
    for (const auto& vehicle : allVehicles) {
        vehicle.displayVehicleInfo();
    }
}