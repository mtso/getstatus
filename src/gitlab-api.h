#ifndef GITLAB_API
#define GITLAB_API

#include <string>

namespace getstatus {

class GitlabApi {
private:
    std::string api_token;
    std::string api_url = "https://gitlab.com/api/v4/projects/";
    std::string project_id;

public:
    GitlabApi(std::string api_token, std::string project_id);
    ~GitlabApi() { }

    std::string get_token();
    std::string get_branches();
};

}

#endif
