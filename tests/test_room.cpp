#include <gtest/gtest.h>
#include "engine.hpp"

class RoomTest : public ::testing::Test {
    protected:
        items testItems;
        nodes testRooms;
        void SetUp() override {
            for (int i = 0; i < 10; i++) {
                testRooms.emplace_back(new Room("Room", i, "This is a test room."));
                testItems.emplace_back(new Object("Item No." + std::to_string(i), i, "This is a test item."));
            }
        }
        void TearDown() {
            for (int i = 0; i < 10; i++) {
                testRooms[i].reset();
            }
        }
};

TEST(RoomTest, constructor_test) {
    node Room1(new Room("Room1", 1, "This room is created to test the constructor."));
    EXPECT_EQ("Room1", Room1->getName());
    EXPECT_EQ(1, Room1->getID());
    EXPECT_EQ("This room is created to test the constructor.", Room1->getDescription());
}

TEST(FailTest, tofail) {
    EXPECT_EQ(1, 2);
}