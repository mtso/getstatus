#ifndef GS_GITLABAPI_H
#define GS_GITLABAPI_H

#include "commit.h"

#include <string>
#include <vector>

namespace getstatus {

class GitlabApi {
private:
    /// GitLab Private Access Token.
    std::string api_token;

    /// GitLab project_id from /api/v4/projects?search=[name]
    std::string project_id;

    /// Base GitLab API URL.
    std::string api_url = "https://gitlab.com/api/v4/projects/";

public:
    /// Construct with credentials and config ID.
    GitlabApi(std::string api_token, std::string project_id);
    ~GitlabApi() { }

    /// Returns a list of commits found unique by hash ID.
    std::vector<Commit> filter_unique(std::vector<Commit>);

    /// Fetch branches.
    std::vector<std::string> get_branches();

    /// Fetch commits from one ref_name.
    std::vector<Commit> get_commits(std::string);

    /// Fetch all commits from this repository.
    std::vector<Commit> get_commits_all();
};

} // namespace getstatus

#endif
