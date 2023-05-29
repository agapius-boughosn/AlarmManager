#include <gtest/gtest.h>
#include <AlarmManager.h>

// Turns all alarms on then off then checks for currently active alarm
TEST(AlarmManagerTest, ActivationTest) {
    AlarmManager alarmManager;
    alarmManager.startAlarm(AlarmManager::Priority::LOW, 1);
    alarmManager.startAlarm(AlarmManager::Priority::MEDIUM, 1);
    alarmManager.startAlarm(AlarmManager::Priority::HIGH, 1);
    alarmManager.stopAlarm(AlarmManager::Priority::LOW, 1);
    alarmManager.stopAlarm(AlarmManager::Priority::MEDIUM, 1);
    alarmManager.stopAlarm(AlarmManager::Priority::HIGH, 1);
    EXPECT_EQ(alarmManager.getCurrentAlarm(), AlarmManager::Priority::NONE);
}

// Turns on all alarms and checks that the HIGH priority alarm is the active one
TEST(AlarmManagerTest, HighestPriorityDominanceTest) {
    AlarmManager alarmManager;
    alarmManager.startAlarm(AlarmManager::Priority::HIGH, 1);
    alarmManager.startAlarm(AlarmManager::Priority::MEDIUM, 1);
    alarmManager.startAlarm(AlarmManager::Priority::LOW, 1);
    EXPECT_EQ(alarmManager.getCurrentAlarm(), AlarmManager::Priority::HIGH);
   
}

// Turns on the LOW priority alarm then the HIGH one, 
// then turn off the HIGH priority alarm and check if the LOW one is still active
TEST(AlarmManagerTest, LowerPriorityStatusTest) {
    AlarmManager alarmManager;
    alarmManager.startAlarm(AlarmManager::Priority::LOW, 1);
    alarmManager.startAlarm(AlarmManager::Priority::HIGH, 1);
    alarmManager.stopAlarm(AlarmManager::Priority::HIGH, 1);
    EXPECT_EQ(alarmManager.getCurrentAlarm(), AlarmManager::Priority::LOW);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}