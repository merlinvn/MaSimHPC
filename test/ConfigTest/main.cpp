//
// Created by Nguyen Tran on 6/25/18.
//

#define CATCH_CONFIG_RUNNER
#include "catch/catch.hpp"

int main(int argc, char* argv[]) {
	// global setup...

	const auto result = Catch::Session().run(argc, argv);

	// global clean-up...

	return result;
}
