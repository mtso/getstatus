#include <gtest/gtest.h>

#include "gitlab-api.h"
#include "commit.h"

#include <cstdlib>
#include <stdexcept>

const char* KEY_TOKEN = "GITLAB_TOKEN";
const char* KEY_PROJECTID = "GITLAB_PROJECTID";

std::string mustget(std::string key) {
    const char* var = std::getenv(key.c_str());
    if (var) {
        return std::string(var);
    }

    std::string message = key + " is required as an environment variable";
    throw std::runtime_error(message.c_str());
}

TEST(GetStatusTests, GetCommitsAllTest) {
    auto token = mustget(KEY_TOKEN);
    auto project_id = mustget(KEY_PROJECTID);
    auto api = new getstatus::GitlabApi(token, project_id);
    
    try {
        api->get_commits_all();
    }
    catch (std::runtime_error e) {
        ASSERT_EQ(e.what(), "Not ok");
    }
}

int main(int argc, char** argv) {
    // Require API token
    try {
        mustget(KEY_TOKEN);
        mustget(KEY_PROJECTID);
    }
    catch (std::runtime_error e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
