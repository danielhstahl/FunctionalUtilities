#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "FunctionalUtilities.h"


TEST_CASE("Test for_each_parallel", "[Functional]"){
    std::vector<int> testV={5, 6, 7};
    auto squareTestV=[](auto& val){
        return val*val;
    };
    REQUIRE(futilities::for_each_parallel(std::move(testV), squareTestV)==std::vector<int>({25, 36, 49}));
}
TEST_CASE("Test for_each", "[Functional]"){
    std::vector<int> testV={5, 6, 7};
    auto squareTestV=[](auto& val){
        return val*val;
    };
    REQUIRE(futilities::for_each(std::move(testV), squareTestV)==std::vector<int>({25, 36, 49}));
}