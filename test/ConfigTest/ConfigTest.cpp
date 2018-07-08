//
// Created by Nguyen Tran on 1/25/2018.
//
#include "catch/catch.hpp"
#include "Config.h"

TEST_CASE("Config", "[Core]") {

	SECTION("Config can get config item value") {
    Config c;
	  REQUIRE(1000 == c.total_time());
	}

	SECTION("Config can set config item value") {
		Config c;
		c.total_time() = 5000;

		REQUIRE(5000 == c.total_time());
	}

	SECTION("Config can read from file") {
		Config c;
		c.read_from_file("input.yml");

		REQUIRE(10000== c.total_time());
	}

	SECTION("If file is not exist config item read default value") {
		Config c;
		c.read_from_file("input1.yml");

		REQUIRE(1000 == c.total_time());
		REQUIRE(10 == c.number_of_location());
	}


}
