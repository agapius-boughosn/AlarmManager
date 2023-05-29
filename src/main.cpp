#include <csignal>
#include <iostream>
#include <AlarmManager.h>

// AlarmManager declared here for usability by main and signalHandler
AlarmManager alarmManager;

// Ctrl+C signal handler
void signalHandler(int signal) {
    if (signal == SIGINT) {
        // Stop all alarms
        alarmManager.stopAlarm(AlarmManager::Priority::LOW, 0);
        alarmManager.stopAlarm(AlarmManager::Priority::MEDIUM, 0);
        alarmManager.stopAlarm(AlarmManager::Priority::HIGH, 0);

        // Calculate summary info
        auto endTime = std::chrono::steady_clock::now();
        auto duration = endTime-alarmManager.getStartTime();
        auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        
        // Print summary
        std::cout << "\n\n Characters printed: " << alarmManager.getPrintedCharacters() << ", Time elapsed (ms): " << durationMs.count() <<   std::endl;
        exit(0);

    }
}

int main(){
    // Declare interrupt signal handler
    std::signal(SIGINT, signalHandler);

    while(1){
        char input;
        std::cin.get(input);
        
        // Toggle alarms based on received inputs
        if (input == 'h') {
            alarmManager.toggleAlarm(AlarmManager::Priority::HIGH);
        } else if (input == 'm') {
            alarmManager.toggleAlarm(AlarmManager::Priority::MEDIUM);
        } else if (input == 'l') {
            alarmManager.toggleAlarm(AlarmManager::Priority::LOW);
        }
        }
        
   
}