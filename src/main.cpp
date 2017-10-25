#include <iostream>
#include <string>
#include <cstdlib>

#include "gitlab-api.h"

int main(int argc, char** argv) {
    std::string token = std::getenv("GITLAB_TOKEN");
    std::string project_id = std::getenv("GITLAB_PROJECTID");
    getstatus::GitlabApi *api = new getstatus::GitlabApi(token, project_id);

    std::cout << api->get_branches() << std::endl;
}
