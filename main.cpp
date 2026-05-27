#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

struct WorkSession {
    std::string focusArea;
    int durationMinutes;
};

const std::string FILENAME = "sessions.txt";


int getValidInteger(const std::string& prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid whole number: ";
    }
    return value;
}

// Loads sessions from the file into the vector at startup
void loadSessions(std::vector<WorkSession>& log) {
    std::ifstream inFile(FILENAME);
    if (!inFile.is_open()) return;

    int duration;
    std::string focus;
    while (inFile >> duration) {
        inFile.ignore(); // Discard newline after number
        std::getline(inFile, focus);
        log.push_back({focus, duration});
    }
    inFile.close();
}

// Appends a single new session to the file
void saveSession(const WorkSession& session) {
    std::ofstream outFile(FILENAME, std::ios::app);
    if (outFile.is_open()) {
        outFile << session.durationMinutes << "\n" << session.focusArea << "\n";
        outFile.close();
        std::cout << "Session logged and saved to file successfully!\n";
    } else {
        std::cout << "Error: Could not open file for saving.\n";
    }
}

void viewLogs(const std::vector<WorkSession>& log) {
    std::cout << "\n--- Your Sessions ---\n";
    if (log.empty()) {
        std::cout << "[No sessions logged yet]\n";
        return;
    }

    int totalTime = 0;
    for (const auto& session : log) {
        std::cout << "- " << session.focusArea << ": " << session.durationMinutes << " mins\n";
        totalTime += session.durationMinutes;
    }
    std::cout << "Total deep work: " << totalTime << " mins\n";
}

void clearAllLogs(std::vector<WorkSession>& log) {
    char confirmation;
    std::cout << "Are you sure you want to clear all logs? (y/n): ";
    std::cin >> confirmation;

    if (confirmation == 'y' || confirmation == 'Y') {
        log.clear();
        std::ofstream outFile(FILENAME, std::ios::trunc);
        if (outFile.is_open()) {
            outFile.close();
            std::cout << "All logs cleared successfully.\n";
        } else {
            std::cout << "Error: Could not open file to clear logs.\n";
        }
    } else {
        std::cout << "Clear logs canceled.\n";
    }
}

void handleLogSession(std::vector<WorkSession>& log) {
    WorkSession session;
    std::cout << "What was your focus area?: ";
    std::getline(std::cin >> std::ws, session.focusArea);
    
    session.durationMinutes = getValidInteger("Duration (minutes): ");
    
    log.push_back(session);
    saveSession(session);
}


int main() {
    std::vector<WorkSession> log;
    loadSessions(log);

    std::cout << "--- Deep Work Logger ---\n";
    std::cout << "[" << log.size() << " past sessions loaded from file]\n";

    int choice = 0;
    do {
        std::cout << "\n1. Log a Session\n2. View Log\n3. Exit\n4. Clear All Logs\n";
        choice = getValidInteger("Choose an option: ");

        switch (choice) {
            case 1:
                handleLogSession(log);
                break;
            case 2:
                viewLogs(log);
                break;
            case 3:
                std::cout << "Stay disciplined. Goodbye!\n";
                break;
            case 4:
                clearAllLogs(log);
                break;
            default:
                std::cout << "Invalid option. Please choose 1, 2, 3, or 4.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}
