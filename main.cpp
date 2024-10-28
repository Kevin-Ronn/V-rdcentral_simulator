#include <iostream>
#include <string>
#include <chrono>
#include <queue>

// Patient-klass som håller kölappsnummer, namn och ankomsttid
class Patient {
public:
    int queueNumber;
    std::string name;
    std::chrono::time_point<std::chrono::steady_clock> arrivalTime;

    Patient(int queueNumber, const std::string& name) 
        : queueNumber(queueNumber), name(name), arrivalTime(std::chrono::steady_clock::now()) {}
};

// Vårdcentral simulator-klass
class HealthCenterSimulator {
private:
    std::queue<Patient> waitingQueue; // Använd std::queue för köhantering
    int queueCounter = 1;             // Börjar kölappsräkningen från 1

public:
    // Lägg till en ny patient i kön
    void addPatient(const std::string& name) {
        Patient newPatient(queueCounter++, name);
        waitingQueue.push(newPatient);
        std::cout << "Patient " << newPatient.name << " (Kölappsnummer: " 
                  << newPatient.queueNumber << ") har lagts till i väntekön.\n";
    }

    // Ropa in nästa patient och beräkna väntetid
    void callNextPatient() {
        if (waitingQueue.empty()) {
            std::cout << "Ingen patient i kön.\n";
            return;
        }

        Patient nextPatient = waitingQueue.front();
        waitingQueue.pop();

        // Beräkna väntetiden
        auto now = std::chrono::steady_clock::now();
        auto waitDuration = std::chrono::duration_cast<std::chrono::seconds>(now - nextPatient.arrivalTime).count();

        std::cout << "Nästa patient: " << nextPatient.name << " (Kölappsnummer: " 
                  << nextPatient.queueNumber << "). Har väntat i " 
                  << waitDuration << " sekunder.\n";
    }
};

int main() {
    HealthCenterSimulator simulator;
    std::string command;

    while (true) {
        std::cout << "\nVälj ett kommando:\n"
                     "1. Lägg till patient (skriv 'add')\n"
                     "2. Ropa in nästa patient (skriv 'call')\n"
                     "3. Avsluta programmet (skriv 'exit')\n";
        std::cin >> command;

        if (command == "add") {
            std::string name;
            std::cout << "Ange patientens namn: ";
            std::cin >> name;
            simulator.addPatient(name);
        }
        else if (command == "call") {
            simulator.callNextPatient();
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "Okänt kommando. Försök igen.\n";
        }
    }

    return 0;
}
