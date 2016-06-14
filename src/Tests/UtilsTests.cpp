#include <gtest/gtest.h>
#include "../Utils.h"


TEST(UtilsTests, HaverstineDistanceTest1) {
	double lat1 = 150;
	double lat2 = -20;
	double lon1 = 10;
	double lon2 = 1.534;
	float distance = 18614.713; // Should result in
	float distCalcu = harvestineDistance(lat1, lon1, lat2, lon2);
	ASSERT_FLOAT_EQ(distance, distCalcu);
}



TEST(UtilsTests, HaverstineDistanceTest2) {
	double lat1 = -10.5674;
	double lat2 = -20.4650;
	double lon1 = 10.57526;
	double lon2 = 10.8498;
	float distance = 1100.9547; // Should result in
	float distCalcu = harvestineDistance(lat1, lon1, lat2, lon2);
	ASSERT_FLOAT_EQ(distance, distCalcu);
}
