#include <string>
#include <cpr/cpr.h>
#include <json.hpp>

#include "gitlab-api.h"

namespace getstatus {

GitlabApi::GitlabApi(std::string api_token, std::string project_id) {
    this->api_token = api_token;
    this->project_id = project_id;
}

std::string GitlabApi::get_token() {
    return this->api_token;
}

std::string GitlabApi::get_branches() {
    std::string json_url = this->api_url + this->project_id + "/repository/branches?private_token=" + this->api_token;
    auto response = cpr::Get(cpr::Url{json_url});
    auto json = nlohmann::json::parse(response.text);

    std::string branches = "";

    for (int i = 0; i < json.size(); i++) {
        if (i != 0) {
            branches += ", ";
        }

        std::string name = json[i]["name"];
        branches += name;
    }

    return branches;
}

}
