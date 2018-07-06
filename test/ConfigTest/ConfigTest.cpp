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


}
