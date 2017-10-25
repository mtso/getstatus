#ifndef GS_COMMIT_H
#define GS_COMMIT_H

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

} // namespace getstatus

#endif
