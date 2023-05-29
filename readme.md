# Alarm System
This script implements an alarm system that can be controlled using the keyboard. 

Three types of alarms are introduced with different priorities: HIGH, MEDIUM and LOW, and they are controlled using an Alarm manager. The highest priority active alarm is the one that will be seen by the user. The user has the capibility of turning on and off one, two or all three alarms. 

The implemented solution includes a series of Google tests to ensure its functioning.

The script was tested on Ubuntu 22.04.1 LTS.

## Running the code
To run the code open a terminal in the root folder and create a build directory:
```
mkdir build
```
Go to the build directory, cmake then make:
```
cd build
cmake ..
make
```
Run the tests:
```
./runTests
```
Run the code:
```
./solution
```

## Using the code
When the code runs as specified in the previous section, the script will wait till the user inserts an input and presses the Enter key. The code expects as inputs the keys 'h', 'm' or 'l' referring to High priority, Medium priority and Low priority alarms respectively. 
For example, when the script runs, pressing the 'm' key (then Enter) starts the Medium priority alarm, then pressing the 'h'  key (then Enter) starts the high priority alarm which will be shown, then pressing the 'l' key (then Enter) won't change anything because higher priority alarms are still active. If after this procedure, the 'h' key (then Enter) is pressed, the high priority alarm turns off and the medium priority alarm shows as it is still active; pressing the 'm' key (then Enter) shows the low priority alarm for the same reasons; finally pressing the 'l' key (then Enter) turns off all the alarms. 

Many combinations can be tried by the user but the concept remains the same: highest active priority alarm would be playing (printing).

## Functioning of the code
The code lies on the `AlarmManager.cpp` script to run. The AlarmManager class provides functionality to manage and control different priority alarms. It allows starting, stopping, toggling, and retrieving information about alarms.
The main points are the following:
* An `enum class Priority` defines the NONE, LOW, MEDIUM and HIGH priority alarms in an incremental manner to allow their comparison (integer values are assigned to each of them by default).  
* A single alarm thread plays the highest active alarm in the terminal.
* An `activeAlarms` map indicates the state of each of the LOW, MEDIUM, HIGH priority alarms at all times. It also includes a NONE alarm indicating that no alarm is active.
* Whenever an alarm is requested to start, its flag is turned on but it is only played if no higher priority alarm is active.
* Whenever an alarm is requested to stop, the script will check for other active alarms in the map, the next higher priority alarm is played.
* When in testing mode (testing flag is on), nothing is printed. Only the `currentPriority` variable is updated indicating the currently active alarm.

The class is detailed next. 
### Constructor
```
AlarmManager::AlarmManager()
```
The constructor initializes the AlarmManager object. It sets the active status of alarms, stores the starting time, and initializes variables.

### Methods
#### Start Alarm
```
void AlarmManager::startAlarm(Priority priority, bool testing)
```
This method starts an alarm of the specified priority. It activates the alarm flag and checks if a higher priority alarm is already active. If no higher priority alarm is active, it  stops the currently active alarm, updates the `currentPriority` variable and starts playing the requested alarm.

Parameters:
* priority: The priority of the alarm to start (High, Medium or Low).
* testing: A boolean flag indicating if the alarm is being started during testing (Google tests).

#### Stop Alarm
```
void AlarmManager::stopAlarm(Priority priority, bool testing)
```
This method stops the alarm of the specified priority. It stops the currently playing alarm, desactivates the alarm flag, checks if there is another active alarm, and starts the next highest priority alarm if available.

Parameters:
* priority: The priority of the alarm to stop.
* testing: A boolean flag indicating if the alarm is being stopped during testing.

#### Toggle Alarm
```
void AlarmManager::toggleAlarm(Priority priority)
```
This method toggles the alarm based on its current status. If the alarm is currently active, it will be stopped, and if it is inactive, it will be started.

Parameters:
* priority: The priority of the alarm to toggle.

#### Get Printed Characters
```
int AlarmManager::getPrintedCharacters()
```
This method returns the number of printed characters so far during the alarm.

Returns:
* An integer representing the number of printed characters.

#### Get Current Alarm 
```
AlarmManager::Priority AlarmManager::getCurrentAlarm()
```
This method returns the currently playing alarm.

Returns:
* An enum value representing the current alarm's priority.

#### Get Start Time
```
std::chrono::time_point<std::chrono::steady_clock> AlarmManager::getStartTime()
```
This method returns the starting time of the AlarmManager object.

Returns:
* A std::chrono::time_point object representing the starting time.

#### Activate Alarm
```
void AlarmManager::activateAlarm(Priority priority)
```
This method activates the alarm flag for the specified priority.

Parameters:
* priority: The priority of the alarm to activate.

#### Desactivate Alarm
```
void AlarmManager::desactivateAlarm(Priority priority) 
```
This method desactivates the alarm flag for the specified priority.

Parameters:
* priority: The priority of the alarm to deactivate.

#### Check Higher Priority
```
bool AlarmManager::checkHigherPriority(Priority priority)
```
This method checks if there is a higher priority alarm already active.

Parameters:
* priority: The priority of the alarm to compare with.

Returns:
* true if a higher priority alarm is active, false otherwise.

#### Return Alarm Status
```
bool AlarmManager::returnAlarmStatus(Priority priority)
```
This method returns the status of the alarm for the specified priority.

Parameters:
* priority: The priority of the alarm to check.

Returns:
* true if the alarm is active, false if inactive.

#### Get Highest Active Alarm
```
AlarmManager::Priority AlarmManager::getHighestActiveAlarm()
```
This method returns the highest priority alarm that is currently active.

Returns:
* An enum value representing the highest active alarm's priority.

#### Stop Active Alarm
```
void AlarmManager::stopActiveAlarm()
```
This method stops the currently playing alarm by turning on the stop flag.

#### Print Active Alarms
```
void AlarmManager::printActiveAlarms()
```
This method prints the status of all the alarms, indicating their priority and active/inactive status.

#### Sleep in Milliseconds
```
void AlarmManager::sleepMilliseconds()
```
This method sleeps for 250 milliseconds (time representation of a single character) unless a stop alarm is requested.

#### Print Character
```
void AlarmManager::printCharacter(char character, int time)
```
This method prints the requested character for the given time. It considers that each character represents 250 ms.

Parameters:
* character: The character to be printed.
* time: The requested playing time. 

#### Play Low Priority Alarm
```
void AlarmManager::playLowPriorityAlarm()
```
This method plays (prints) the low priority alarm.

#### Play Medium Priority Alarm
```
void AlarmManager::playMediumPriorityAlarm()
```
This method plays (prints) the medium priority alarm.

#### Play High Priority Alarm
```
void AlarmManager::playHighPriorityAlarm()
```
This method plays (prints) the high priority alarm.

