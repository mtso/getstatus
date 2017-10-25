#include <iostream>
#include <string>
#include <cstdlib>

#include <cpr/cpr.h>
#include <json.hpp>

int main(int argc, char** argv) {
    std::string json_url = "https://jsonbin.io/b/59eeea97ed25d0573bf19888";

    auto response = cpr::Get(cpr::Url{json_url});
    auto json = nlohmann::json::parse(response.text);
    auto list = json["list"];

    for (int i = 0; i < list.size(); i++) {
        std::cout << list[i] << std::endl;
    }
}
