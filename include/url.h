#include <map>

namespace getstatus {

class Url {
public:
    Url(std::string);
    bool set_param(std::string, std::string);
    bool remove_param(std::string, std::string);

    bool set_query(std::string, std::string);
    bool remove_query(std::string);
    std::string to_string();

private:
    std::map<std::string, std::string> params;
    std::map<std::string, std::string> queries;
}

} // namespace getstatus
