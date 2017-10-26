#include <time>
#include <string>

namespace getstatus {

struct Options {
    std::time_t since;
    std::time_t until;
    std::string ref_name;

    std::string project_id;
}

}