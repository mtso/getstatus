#include <vector>
#include <time>
#include <string>

namespace getstatus {

class ApiInterface {
public:
    // Entry-point Stub:
    // auto api = new getstatus::GitlabApi(token, project_id);
    // api->display_data(renderer);
    // return 0;
    virtual void display_data(void (* renderer)(ApiInterface&)) = 0;

    virtual std::vector<Commit> get_commits(std::time_t) = 0;
    virtual std::vector<std::string> get_branches() = 0;
};

}
