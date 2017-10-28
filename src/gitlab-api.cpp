#include "gitlab-api.h"
#include "util.h"
#include "commit.h"

#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <cpr/cpr.h>
#include <json.hpp>
#include <channel>

namespace getstatus {

GitlabApi::GitlabApi(std::string api_token, std::string project_id) {
    this->api_token = api_token;
    this->project_id = project_id;
}

std::vector<std::string> GitlabApi::get_branches() {
    std::vector<std::string> branches;

    std::string fetch_url = this->api_url
        + this->project_id
        + "/repository/branches?private_token="
        + this->api_token;

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

std::vector<Commit>
GitlabApi::get_commits(std::string ref_name) {
    std::vector<Commit> commits;

    std::string fetch_url = this->api_url
        + this->project_id
        + "/repository/commits?private_token="
        + this->api_token
        + "&since="
        + get_midnight()
        + "&ref_name="
        + ref_name;

    auto response = cpr::Get(cpr::Url{fetch_url});
    if (response.status_code >= 400) {
        throw std::runtime_error(response.text.c_str());
    }

    auto json = nlohmann::json::parse(response.text);

    for (int i = 0; i < json.size(); i++) {
        auto curr = json[i];
        auto commit = Commit(curr["committer_name"],
                             curr["title"],
                             curr["message"],
                             curr["short_id"],
                             curr["committed_date"]);
        commits.push_back(commit);
    }

    return commits;
}

std::vector<Commit> GitlabApi::filter_unique(std::vector<Commit> commits) {
    std::map<std::string, Commit> set;
    std::vector<Commit> unique;
    std::map<std::string, Commit>::iterator it;

    for (int i = 0; i < commits.size(); i++) {
        auto commit = commits[i];
        set[commit.get_id()] = commit;
    }
    
    for (it = set.begin(); it != set.end(); it++) {
        auto c = it->second;
        unique.push_back(c);
    }

    return unique;
}

// `thread_get_commit` fetches the commits and passes them into the done
// channel. Used to fetch commits asynchronously with <channel> lib.
void thread_get_commit(cpp::channel<std::vector<Commit>> done,
                       std::string ref_name,
                       GitlabApi *api) {
    std::vector<Commit> commits = api->get_commits(ref_name);
    done.send(commits);
}

std::vector<Commit> GitlabApi::get_commits_all() {
    using namespace std;

    cpp::channel<std::vector<Commit>> ch;
    vector<Commit> commits;
    vector<thread*> threads;
    vector<string> branches = this->get_branches();

    for (int i = 0; i < branches.size(); i++) {
        std::thread *th = new thread(thread_get_commit,
                                          ch,
                                          branches[i],
                                          this);
        threads.push_back(th);
    }

    for (int i = 0; i < threads.size(); i++) {
        vector<Commit> got = ch.recv();

        // Append got into commits (+= impl from util.h)
        commits += got;
    }

    for (int i = 0; i < threads.size(); i++) {
        threads[i]->join();
    }

    return commits;
}

} // namespace getstatus
