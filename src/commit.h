#ifndef GS_COMMIT
#define GS_COMMIT

namespace getstatus {

class Commit {
private:
    std::string committer;
    std::string title;
    std::string message;
    std::string id;
    std::string timestamp;
public:
    Commit(std::string,
           std::string,
           std::string,
           std::string,
           std::string);
}

}

#endif
