#include <gtest/gtest.h>
#include "../SharedManager.h"


TEST(SharedGetUser,TestGetUser) {
	SharedManager sManager;
	sManager.getUser("1");
}