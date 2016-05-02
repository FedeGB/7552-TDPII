#include <gtest/gtest.h>
#include "../SharedClient/SharedManager.h"
#include "json/json.h"


TEST(SharedGetUser,TestGetUser) {
	SharedManager* sManager = new SharedManager();
	sManager->getUsers();
}