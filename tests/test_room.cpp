#include <gtest/gtest.h>
#include "engine.hpp"

class RoomTest : public ::testing:Test {
    items shared_testItems_;
    nodes shared_testRooms_;
protected:
    void setUp() override {
        for (int i = 0; i < 10; i++) {
            shared_testItem_.push_back()
        }
    }
};

TEST(roomtest, testconstructor1) {
	node testRoom(new Room("testroom"));
    EXPECT_EQ(testRoom->getName(), "testroom") << "The name of the room could be returned by getName() method.";
}

// TODO finish implementing tests
TEST(roomtest, testconstructor2) {
    item item1 = item(new Object("FirstItem"));
    node roomThree(new Room("Third", item1));
    EXPECT_EQ(roomThree->getName(), "Third") << "The room's name should be Third.";
    EXPECT_EQ(roomThree->getItems()[0]->getName(), "FirstItem") << "The item is moved to the inventory of the Third room.";
}

TEST(roomtest, testconstructor3) {
    /* items can be only constructed with the initial constructor, only with push_back can it be filled, or else the compiler throws an exeption */
    items inventory;
    item items[] = {item(new Object("FirstItem")), item(new Object("SecondItem")), item(new Object("ThirdItem")), item(new Object("FourthItem"))};
    //std::vector<std::unique_ptr<Object>> iv({item(new Object("FirstItem")), item(new Object("SecondItem")), item(new Object("ThirdItem")), item(new Object("FourthItem"))});
    for (int i = 0; i < 4; i++) {
        inventory.push_back(item(std::move(items[i])));
    }
    EXPECT_EQ(inventory.size(), 4) << "Size of item vector should be 4.";
    node testRoom(new Room("TestRoom", inventory));
    for (items::iterator it = inventory.begin(); it != inventory.end(); it++) {
        EXPECT_EQ(*it, nullptr);
    }
    EXPECT_EQ(testRoom->getItems().size(), 4) << "The TestRoom's inventory should have 4 items in it.";
}

TEST(roomtest, testconstructor4) {
    node Room1(new Room("Room1"));
    node Room2(new Room("Room2", Room1));
    EXPECT_EQ(Room2->getNeighbours().size(), 1) << "Room2's neighbour count should be 1.";
    node Room3(new Room("Room3", Room1));
    EXPECT_EQ(Room3->getNeighbours().size(), 1) << "Room3's neighbour count should be 1.";
    Room1->addNeighbour(Room2).addNeighbour(Room3);
    EXPECT_EQ(Room1->getNeighbours().size(), 2) << "Room1's neighbour count should be 2.";
    EXPECT_EQ(Room2->getNeighbours()[0]->getName(), Room1->getName());
    EXPECT_EQ(Room3->getNeighbours()[0]->getName(), Room1->getName());
    EXPECT_EQ(Room1->getNeighbours()[0]->getName(), Room2->getName());
    EXPECT_EQ(Room1->getNeighbours()[1]->getName(), Room3->getName());
    EXPECT_EQ(Room2.use_count(), 2);
    EXPECT_EQ(Room3.use_count(), 2);
    EXPECT_EQ(Room1.use_count(), 3);
    Room1.reset();
    Room2.reset();
    Room3.reset();
    EXPECT_EQ(Room2.use_count(), 0);
    EXPECT_EQ(Room3.use_count(), 0);
    EXPECT_EQ(Room1.use_count(), 0);
    std::cerr << "testconstructor4 finished" << std::endl;
}

TEST(roomtest, testconstructor5) {
    nodes rooms({node(new Room("Room4")), node(new Room("Room5")), node(new Room("Room6")), node(new Room("Room7"))});
    node StartArea(new Room("StartArea", rooms));
    EXPECT_EQ(StartArea->getNeighbours().size(), rooms.size()) << "The size of StartArea's neighbours vector should be the same size of rooms.";
    for (nodes::const_iterator cit = rooms.cbegin(); cit != rooms.cend(); cit++) {
        EXPECT_EQ(cit->use_count(), 2);
    }
    for (int i = 0; i < rooms.size(); i++) {
        rooms[0].reset();
    }
}

//TODO: Do test for all constructor of Room