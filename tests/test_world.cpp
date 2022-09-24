#include <gtest/gtest.h>
#include "engine.hpp"

class WorldTest : public ::testing::Test {
    protected:
        World testWorld;
        void SetUp() override {
            testWorld.initWorld("../story.xml");
        }
        void TearDown() override {
            testWorld.destroyWorld();
        }
};

TEST_F(WorldTest, test_xml_module) {
    // load world element of xml doc
    tinyxml2::XMLElement* worldEle = testWorld.getStory().FirstChildElement("world");
    // get title of world  
    const char* title = worldEle->FirstChildElement("title")->GetText();
    std::string expectedTitle("SpaceWalk");
    EXPECT_STREQ(expectedTitle.c_str(), title);
    // get xml element name
    const char* eleTitle = worldEle->Value();
    std::string eleTitleExpected = "world";
    EXPECT_STREQ(eleTitle, eleTitleExpected.c_str());
    // get id of first room
    int firstRoomID = 0;
    worldEle->FirstChildElement("room")->FirstChildElement("id")->QueryIntText(&firstRoomID);
    EXPECT_EQ(firstRoomID, 1);
    // test NextSiblingElement()
}

/*TEST_F(WorldTest, test_initWorld) {
    std::string expectedName("TestRoom1");
    std::string expectedDescription("This is the first test room");
    int expectedID = 1;
    std::string expectedObjectName("TestObject1");
    std::string expectedObjectDescription("This is test object 1");
    int expectedObjectID = 1;
    EXPECT_STREQ(testWorld.getWorldRooms()[0]->getName().c_str(), expectedName.c_str());
    EXPECT_STREQ(testWorld.getWorldRooms()[0]->getDescription().c_str(), expectedDescription.c_str());
    EXPECT_EQ(testWorld.getWorldRooms()[0]->getID(), expectedID);
    EXPECT_STREQ(testWorld.getWorldRooms()[0]->getItems()[0]->getName().c_str(), expectedObjectName.c_str());
    EXPECT_STREQ(testWorld.getWorldRooms()[0]->getItems()[0]->getDescription().c_str(), expectedObjectDescription.c_str());
    EXPECT_EQ(testWorld.getWorldRooms()[0]->getItems()[0]->getID(), expectedObjectID);
}*/