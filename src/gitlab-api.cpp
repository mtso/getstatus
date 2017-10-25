#include <string>
#include <vector>
#include <cpr/cpr.h>
#include <json.hpp>

#include "gitlab-api.h"

namespace getstatus {

GitlabApi::GitlabApi(std::string api_token, std::string project_id) {
    this->api_token = api_token;
    this->project_id = project_id;
}

std::vector<std::string> GitlabApi::get_branches() {
    std::vector<std::string> branches;

    std::string fetch_url = this->api_url + this->project_id + "/repository/branches?private_token=" + this->api_token;

    auto response = cpr::Get(cpr::Url{fetch_url});
    if (response.status_code >= 400) {
        throw std::runtime_error(response.text.c_str());
    }

    auto json = nlohmann::json::parse(response.text);

    for (int i = 0; i < json.size(); i++) {
        std::string name = json[i]["name"];
        branches.push_back(name);
    }

    return branches;
}

std::vector<std::string> GitlabApi::get_commits() {
    std::vector<std::string> commits;
    std::vector<std::string> branches;

    // branches = this->get_
}

}
