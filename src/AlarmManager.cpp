#include <AlarmManager.h>

// Constructor
AlarmManager::AlarmManager(){
    // Set the NONE alarm to active (true) and all other alarms to false
    activeAlarms = {
        { Priority::NONE, 1 },
        { Priority::LOW, 0 },
        { Priority::MEDIUM, 0 },
        { Priority::HIGH, 0 }
    };
    // Store starting time
    startTime = std::chrono::steady_clock::now();
    // Initialize variables
    stopRequested=0;
    printedCharacters = 0;
    // Set currently active alarm to None
    currentPriority = Priority::NONE;
    
}


void AlarmManager::startAlarm(Priority priority, bool testing){
        // Activate alarm flag
        activateAlarm(priority);
        // If a higher alarm is active, quit 
        if(checkHigherPriority(priority)) {
            return;
        } 
        // Else the input alarm should be played (printed)
        // Set the current alarm to the input alarm 
        currentPriority = priority;
        // Stop the already active alarm
        stopActiveAlarm();
        
        // Alarm should be played if not in testing mode (google tests)
        if(!testing){ 
            // An alarm thread is initiated and the requested input alarm is played
            alarmThread = std::thread([this, priority]() {
            switch (priority) {
                case Priority::LOW:
                    playLowPriorityAlarm();
                    break;
                case Priority::MEDIUM:
                    playMediumPriorityAlarm();
                    break;
                case Priority::HIGH:
                    playHighPriorityAlarm();
                    break;
            }
    });}
    }

void AlarmManager::stopAlarm(Priority priority, bool testing) {
    // Stop currently playing alarm
    stopActiveAlarm();
    // Desactivate alarm flag
    desactivateAlarm(priority);
    // Check if another alarm is active
    Priority highestActiveAlarm = getHighestActiveAlarm();
    currentPriority = highestActiveAlarm;
    // In case another alarm is active, it will be activated
    if(highestActiveAlarm != Priority::NONE)
        startAlarm(highestActiveAlarm, testing);
    }

// Toggle alarm based on its status
void AlarmManager::toggleAlarm(Priority priority){
    if(returnAlarmStatus(priority))
        stopAlarm(priority, 0);
    else
        startAlarm(priority, 0);
}

// Return number of printed characters so far
int AlarmManager::getPrintedCharacters(){
    return printedCharacters;
}

// Return the currently playing alarm
AlarmManager::Priority AlarmManager::getCurrentAlarm(){
    return currentPriority;
}

// Return starting time
std::chrono::time_point<std::chrono::steady_clock> AlarmManager::getStartTime(){
    return startTime;
}

// Activate alarm flag
void AlarmManager::activateAlarm(Priority priority) {
    activeAlarms[priority] = 1;
}

// Desactivate alarm flag
void AlarmManager::desactivateAlarm(Priority priority) {
    activeAlarms[priority] = 0;
}

// Return the highest priority alarm
bool AlarmManager::checkHigherPriority(Priority priority){
    for(auto& pair : activeAlarms){
        if(pair.second && pair.first > priority){   
            return 1;}
    }
    return 0;
}

// Return alarm status
bool AlarmManager::returnAlarmStatus(Priority priority){
    return activeAlarms[priority];
}

// Return the highest active alarm
AlarmManager::Priority AlarmManager::getHighestActiveAlarm(){
    Priority toReturn;
    for(auto& pair : activeAlarms){
        if(pair.second)    
            toReturn = pair.first;
    }
    return toReturn;
}

// Stop the alarm being played
void AlarmManager::stopActiveAlarm() {
    if (alarmThread.joinable()) {
    stopRequested = true;

    alarmThread.join();

    stopRequested = false;
    }
}

// Print the state of all the alarms
void AlarmManager::printActiveAlarms() {
    for (const auto& pair : activeAlarms) {
        Priority priority = pair.first;
        bool isActive = pair.second;

        std::string status = isActive ? "Active" : "Inactive";
        std::cout << "Priority: " << static_cast<int>(priority) << ", Status: " << status << std::endl;
    }
}

// Sleep unless a stop alarm is requested
void AlarmManager::sleepMilliseconds(){
    auto limitTime = std::chrono::milliseconds(250);
    auto startTime = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - startTime < limitTime) {
        if (stopRequested)
            break;
    }}

// Play the requested character for the requested time (1 char = 250 ms)
void AlarmManager::printCharacter(char character, int time){
    int iterations = time/250;
    for(int i=0; i<iterations && !stopRequested; i++){
        std::cout << character << std::flush; 
        sleepMilliseconds();
        printedCharacters+=1;
    }
    
}

// Play low priority alarm
void AlarmManager::playLowPriorityAlarm() {
    while (!stopRequested) {
        printCharacter('X', 1000);
        printCharacter('_', 29000);        
    }
}

// Play medium alarm
void AlarmManager::playMediumPriorityAlarm() {
    while (!stopRequested) {
        printCharacter('X', 250);
        printCharacter('_', 750);
    }
}

// Play high priority alarm
void AlarmManager::playHighPriorityAlarm() {
    while (!stopRequested) {
        for (int i = 0; i < 5; i++) {
            printCharacter('X', 250);
            printCharacter('_', 250);
        }
        printCharacter('_', 2000);
        }
}

