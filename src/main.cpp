#include "gitlab-api.h"
#include "commit.h"

#include <iostream>
#include <string>
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

int main(int argc, char** argv) {
    std::string token;
    std::string project_id;
    getstatus::GitlabApi *api;
    std::vector<getstatus::Commit> commits;

    try {
        token = mustget(KEY_TOKEN);
        project_id = mustget(KEY_PROJECTID);
    }
    catch (std::runtime_error e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }

    api = new getstatus::GitlabApi(token, project_id);
    
    try {
        commits = api->get_commits_all();
    }
    catch (std::runtime_error e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }

    commits = api->filter_unique(commits);
    for (int i = 0; i < commits.size(); i++) {
        std::cout << commits[i] << std::endl;
    }
    
    return 0;
}
