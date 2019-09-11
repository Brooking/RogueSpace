#include <iostream>
#include "catch.hpp"
#include "iactor_mock.h"
#include "time_entry.h"

TEST_CASE("timeEntry_withDefaultConstructor_shouldCreate", "[timeEntry]")
{
    // arrange
    std::shared_ptr<iActor> actor = std::make_shared<iActorMock>(1);

    // act
    std::shared_ptr<TimeEntry> time_entry = std::make_shared<TimeEntry>(actor);

    // assert
    REQUIRE(time_entry->actor().lock() == actor);
    REQUIRE(time_entry->timestamp() == 0);
    REQUIRE(time_entry->next() == nullptr);
    REQUIRE(time_entry->is_hero() == false);
}

TEST_CASE("timeEntry_withHeroConstructor_shouldCreate", "[timeEntry]")
{
    // arrange
    std::shared_ptr<iActor> actor = std::make_shared<iActorMock>(1);

    // act
    std::shared_ptr<TimeEntry> time_entry = std::make_shared<TimeEntry>(
        actor, /*is_hero*/true);

    // assert
    REQUIRE(time_entry->actor().lock() == actor);
    REQUIRE(time_entry->timestamp() == 0);
    REQUIRE(time_entry->next() == nullptr);
    REQUIRE(time_entry->is_hero() == true);
}

TEST_CASE("timeEntry_withSetTimestamp_shouldSetTimestamp", "[timeEntry]")
{
    // arrange
    std::shared_ptr<iActor> actor = std::make_shared<iActorMock>(1);
    std::shared_ptr<TimeEntry> time_entry = std::make_shared<TimeEntry>(actor);

    // act
    time_entry->set_timestamp(1001);

    // assert
    REQUIRE(time_entry->timestamp() == 1001);
}

TEST_CASE("timeEntry_withSetNext_shouldSetNext", "[timeEntry]")
{
    // arrange
    std::shared_ptr<iActor> actor = std::make_shared<iActorMock>(1);
    std::shared_ptr<TimeEntry> time_entry = std::make_shared<TimeEntry>(actor);
    std::shared_ptr<iActor> another_actor = std::make_shared<iActorMock>(2);
    std::shared_ptr<TimeEntry> another_time_entry = std::make_shared<TimeEntry>(actor);

    // act
    time_entry->set_next(another_time_entry);

    // assert
    REQUIRE(time_entry->next() == another_time_entry);
}

TEST_CASE("timeEntry_withDefaultSetNext_shouldSetNextTONull", "[timeEntry]")
{
    // arrange
    std::shared_ptr<iActor> actor = std::make_shared<iActorMock>(1);
    std::shared_ptr<TimeEntry> time_entry = std::make_shared<TimeEntry>(actor);
    std::shared_ptr<iActor> another_actor = std::make_shared<iActorMock>(2);
    std::shared_ptr<TimeEntry> another_time_entry = std::make_shared<TimeEntry>(actor);
    time_entry->set_next(another_time_entry);

    // act
    time_entry->set_next();

    // assert
    REQUIRE(time_entry->next() == nullptr);
}
