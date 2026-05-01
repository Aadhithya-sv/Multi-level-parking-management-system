#include <iostream>
#include <string>
using namespace std;

// ── Constants ──────────────────────────────────────────────────────
const int MAX_SLOTS = 10;
const int MAX_FLOORS = 3;

// ══════════════════════════════════════════════
// BASE CLASS: Vehicle
// ══════════════════════════════════════════════
class Vehicle {
public:
    string number;
    string type;
    int hours;

    void setDetails(string n, string t, int h) {
        number = n;
        type = t;
        hours = h;
    }

    virtual double calculateFee() {
        return 0;
    }

    virtual void showInfo() {
        cout << "Vehicle: " << number << " | Type: " << type << " | Hours: " << hours << endl;
    }
};

// ══════════════════════════════════════════════
// DERIVED CLASS: Car
// ══════════════════════════════════════════════
class Car : public Vehicle {
public:
    double calculateFee() {
        return hours * 20;   // Rs.20 per hour
    }

    void showInfo() {
        cout << "[Car] " << number << " | Hours: " << hours
             << " | Fee: Rs." << calculateFee() << endl;
    }
};

// ══════════════════════════════════════════════
// DERIVED CLASS: TwoWheeler
// ══════════════════════════════════════════════
class TwoWheeler : public Vehicle {
public:
    double calculateFee() {
        return hours * 10;   // Rs.10 per hour
    }

    void showInfo() {
        cout << "[Two-Wheeler] " << number << " | Hours: " << hours
             << " | Fee: Rs." << calculateFee() << endl;
    }
};

// ══════════════════════════════════════════════
// DERIVED CLASS: HeavyVehicle
// ══════════════════════════════════════════════
class HeavyVehicle : public Vehicle {
public:
    double calculateFee() {
        return hours * 30;   // Rs.30 per hour
    }

    void showInfo() {
        cout << "[Heavy Vehicle] " << number << " | Hours: " << hours
             << " | Fee: Rs." << calculateFee() << endl;
    }
};

// ══════════════════════════════════════════════
// CLASS: ParkingSlot
// ══════════════════════════════════════════════
class ParkingSlot {
public:
    int slotId;
    bool isOccupied;
    string vehicleNumber;

    ParkingSlot() {
        slotId = 0;
        isOccupied = false;
        vehicleNumber = "";
    }
};

// ══════════════════════════════════════════════
// CLASS: ParkingFloor
// ══════════════════════════════════════════════
class ParkingFloor {
public:
    int floorNumber;
    ParkingSlot slots[MAX_SLOTS];

    ParkingFloor() {
        floorNumber = 0;
        for (int i = 0; i < MAX_SLOTS; i++) {
            slots[i].slotId = i + 1;
            slots[i].isOccupied = false;
        }
    }

    // Park a vehicle — returns slot number, or -1 if full
    int parkVehicle(string num) {
        for (int i = 0; i < MAX_SLOTS; i++) {
            if (!slots[i].isOccupied) {
                slots[i].isOccupied = true;
                slots[i].vehicleNumber = num;
                return slots[i].slotId;
            }
        }
        return -1;  // No slot available
    }

    // Remove a vehicle — returns true if found
    bool removeVehicle(string num) {
        for (int i = 0; i < MAX_SLOTS; i++) {
            if (slots[i].vehicleNumber == num) {
                slots[i].isOccupied = false;
                slots[i].vehicleNumber = "";
                return true;
            }
        }
        return false;
    }

    // Show all slots on this floor
    void showStatus() {
        cout << "  Floor " << floorNumber << ":" << endl;
        for (int i = 0; i < MAX_SLOTS; i++) {
            cout << "    Slot " << slots[i].slotId << ": ";
            if (slots[i].isOccupied)
                cout << "Occupied (" << slots[i].vehicleNumber << ")" << endl;
            else
                cout << "Available" << endl;
        }
    }
};

// ══════════════════════════════════════════════
// CLASS: ParkingLot (Main System)
// ══════════════════════════════════════════════
class ParkingLot {
public:
    ParkingFloor floors[MAX_FLOORS];

    ParkingLot() {
        for (int i = 0; i < MAX_FLOORS; i++) {
            floors[i].floorNumber = i + 1;
        }
    }

    void parkVehicle(string num) {
        for (int i = 0; i < MAX_FLOORS; i++) {
            int slot = floors[i].parkVehicle(num);
            if (slot != -1) {
                cout << "Vehicle " << num << " parked at Floor "
                << floors[i].floorNumber << ", Slot " << slot << endl;
                return;
            }
        }
        cout << "Sorry! No slots available." << endl;
    }

    void removeVehicle(string num) {
        for (int i = 0; i < MAX_FLOORS; i++) {
            if (floors[i].removeVehicle(num)) {
                cout << "Vehicle " << num << " removed from Floor "
                     << floors[i].floorNumber << endl;
                return;
            }
        }
        cout << "Vehicle not found!" << endl;
    }

    void showStatus() {
        cout << "\n=== Parking Lot Status ===" << endl;
        for (int i = 0; i < MAX_FLOORS; i++) {
            floors[i].showStatus();
        }
    }

    void searchVehicle(string num) {
        for (int i = 0; i < MAX_FLOORS; i++) {
            for (int j = 0; j < MAX_SLOTS; j++) {
                if (floors[i].slots[j].vehicleNumber == num) {
                    cout << "Vehicle " << num << " is at Floor "
                         << floors[i].floorNumber
                         << ", Slot " << floors[i].slots[j].slotId << endl;
                    return;
                }
            }
        }
        cout << "Vehicle not found!" << endl;
    }
};

// ══════════════════════════════════════════════
// Fee Calculator (separate function)
// ══════════════════════════════════════════════
void calculateFee() {
    int choice, hours;
    string num;

    cout << "Enter Vehicle Number: ";
    cin >> num;
    cout << "Select Type:" << endl;
    cout << "  1. Car" << endl;
    cout << "  2. Two-Wheeler" << endl;
    cout << "  3. Heavy Vehicle" << endl;
    cout << "Your choice: ";
    cin >> choice;
    cout << "Enter hours parked: ";
    cin >> hours;

    if (choice == 1) {
        Car c;
        c.setDetails(num, "Car", hours);
        c.showInfo();
    } else if (choice == 2) {
        TwoWheeler t;
        t.setDetails(num, "Two-Wheeler", hours);
        t.showInfo();
    } else {
        HeavyVehicle h;
        h.setDetails(num, "Heavy Vehicle", hours);
        h.showInfo();
    }
}

// ══════════════════════════════════════════════
// MAIN FUNCTION
// ══════════════════════════════════════════════
int main() {
    ParkingLot lot;
    int choice;
    string num;

    cout << "======================================" << endl;
    cout << " Multi-Level Parking Management System" << endl;
    cout << "======================================" << endl;

    while (true) {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Park Vehicle" << endl;
        cout << "2. Remove Vehicle" << endl;
        cout << "3. Show Parking Status" << endl;
        cout << "4. Search Vehicle" << endl;
        cout << "5. Calculate Fee" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Vehicle Number: ";
            cin >> num;
            lot.parkVehicle(num);

        } else if (choice == 2) {
            cout << "Enter Vehicle Number: ";
            cin >> num;
            lot.removeVehicle(num);

        } else if (choice == 3) {
            lot.showStatus();

        } else if (choice == 4) {
            cout << "Enter Vehicle Number: ";
            cin >> num;
            lot.searchVehicle(num);

        } else if (choice == 5) {
            calculateFee();

        } else if (choice == 6) {
            cout << "Thank you! Goodbye." << endl;
            break;

        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
