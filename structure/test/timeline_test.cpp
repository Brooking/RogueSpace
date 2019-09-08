#include <iostream>
#include <bits/stdc++.h>
#include "catch.hpp"
#include "../game/timeline.h"
#include "ithing_mock.h"

TEST_CASE("timeline_withConstructor_shouldBeEmpty", "[timeline]")
{
    // arrange
    // act
    TimeLine timeline;

    // assert
    REQUIRE(timeline.is_empty() == true);
    REQUIRE(timeline.remove_next() == nullptr);
    REQUIRE(timeline.is_empty() == true);
}

TEST_CASE("timeline_withOneAdd_shouldNotBeEmpty", "[timeline]")
{
    // arrange
    TimeLine timeline;
    std::shared_ptr<iThingMock> thing = std::make_shared<iThingMock>(TokenType::test, nullptr);
    std::shared_ptr<TimeEntry> entry = std::make_shared<TimeEntry>(thing);

    // act
    timeline.insert(entry, 0);

    // assert
    REQUIRE(timeline.is_empty() == false);
}

TEST_CASE("timeline_withOneAdd_shouldContainThatEntryOnly", "[timeline]")
{
    // arrange
    TimeLine timeline;
    std::shared_ptr<iThingMock> thing = std::make_shared<iThingMock>(TokenType::test, nullptr);
    std::shared_ptr<TimeEntry> entry = std::make_shared<TimeEntry>(thing);
    entry->set_timestamp(11);
    timeline.insert(entry, 1);
    entry = nullptr;

    // act
    entry = timeline.remove_next();

    // assert
    REQUIRE(timeline.is_empty() == true);
    REQUIRE(entry->timestamp() == 12);
    REQUIRE(entry->actor().lock() == thing);
    REQUIRE(entry->next() == nullptr);
    REQUIRE(entry->is_hero() == false);
}

TEST_CASE("timeline_withTwoOutOfOrderAdds_shouldReturnInOrder", "[timeline]")
{
    // arrange
    TimeLine timeline;
    std::shared_ptr<iThingMock> thing1 = std::make_shared<iThingMock>(TokenType::test, nullptr);
    std::shared_ptr<TimeEntry> entry1 = std::make_shared<TimeEntry>(thing1);
    entry1->set_timestamp(24);
    timeline.insert(entry1, 6);

    std::shared_ptr<iThingMock> thing2 = std::make_shared<iThingMock>(TokenType::none, nullptr);
    std::shared_ptr<TimeEntry> entry2 = std::make_shared<TimeEntry>(thing2);
    entry2->set_timestamp(10);
    timeline.insert(entry2, 5);

    // act
    std::shared_ptr<TimeEntry> first_entry = timeline.remove_next();
    std::shared_ptr<TimeEntry> second_entry = timeline.remove_next();

    // assert
    REQUIRE(timeline.is_empty() == true);
    REQUIRE(first_entry == entry2);
    REQUIRE(first_entry->timestamp() == 15);
    REQUIRE(first_entry->actor().lock() == thing2);
    REQUIRE(second_entry == entry1);
    REQUIRE(second_entry->timestamp() == 30);
    REQUIRE(second_entry->actor().lock() == thing1);
}

TEST_CASE("timeline_withTwoAddsOverLimit_shouldReNumber", "[timeline]")
{
    // arrange
    // place an entry at max-10
    TimeLine timeline;
    std::shared_ptr<iThingMock> thing1 = std::make_shared<iThingMock>(TokenType::test, nullptr);
    std::shared_ptr<TimeEntry> entry1 = std::make_shared<TimeEntry>(thing1);
    entry1->set_timestamp(ULONG_MAX-10);
    timeline.insert(entry1, 0);

    // insert an entry (with a current timestamp of max-11) at a spot 12 spots forward 
    // (which should reset all timestamps)
    std::shared_ptr<iThingMock> thing2 = std::make_shared<iThingMock>(TokenType::none, nullptr);
    std::shared_ptr<TimeEntry> entry2 = std::make_shared<TimeEntry>(thing2);
    entry2->set_timestamp(ULONG_MAX-11);
    timeline.insert(entry2, 12);

    // act
    std::shared_ptr<TimeEntry> first_entry = timeline.remove_next();
    std::shared_ptr<TimeEntry> second_entry = timeline.remove_next();

    // assert
    REQUIRE(timeline.is_empty() == true);
    REQUIRE(first_entry == entry1);
    REQUIRE(first_entry->timestamp() == 0);
    REQUIRE(second_entry == entry2);
    REQUIRE(second_entry->timestamp() == 11);
}

TEST_CASE("timeline_withTimesTooWide_shouldFault", "[timeline]")
{
    // arrange
    TimeLine timeline;
    std::shared_ptr<iThingMock> thing1 = std::make_shared<iThingMock>(TokenType::test, nullptr);
    std::shared_ptr<TimeEntry> entry1 = std::make_shared<TimeEntry>(thing1);
    timeline.insert(entry1, 0);

    std::shared_ptr<iThingMock> thing2 = std::make_shared<iThingMock>(TokenType::none, nullptr);
    std::shared_ptr<TimeEntry> entry2 = std::make_shared<TimeEntry>(thing2);
    entry2->set_timestamp(ULONG_MAX);

    // act
    bool exception_thrown = false;
    try
    {
        timeline.insert(entry2, 1);
    }
    catch(const std::exception& e)
    {
        exception_thrown = true;
    }

    // assert
    REQUIRE(exception_thrown == true);
}

