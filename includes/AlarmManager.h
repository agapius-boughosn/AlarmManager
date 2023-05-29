#include <iostream>
#include <thread>
#include <atomic>
#include <map>

class AlarmManager{
public:
    // Set alarm labels with priority values
    enum class Priority{
        NONE,
        LOW,
        MEDIUM,
        HIGH
    };
    
    AlarmManager();
    void startAlarm(Priority priority, bool testing);
    void stopAlarm(Priority priority, bool testing);
    void toggleAlarm(Priority priority);
    int getPrintedCharacters();
    Priority getCurrentAlarm();
    std::chrono::time_point<std::chrono::steady_clock> getStartTime();

private:
    std::thread alarmThread;
    std::atomic<bool> stopRequested;
    Priority currentPriority;
    std::atomic<int> printedCharacters;
    std::map<Priority, bool> activeAlarms;
    std::chrono::time_point<std::chrono::steady_clock> startTime;

    void activateAlarm(Priority priority);
    void desactivateAlarm(Priority priority);
    bool checkHigherPriority(Priority priority);
    bool returnAlarmStatus(Priority priority);
    Priority getHighestActiveAlarm();
    void stopActiveAlarm();
    void printActiveAlarms();
    void sleepMilliseconds();
    void printCharacter(char character, int time);

    void playLowPriorityAlarm();
    void playMediumPriorityAlarm();
    void playHighPriorityAlarm();
    
};