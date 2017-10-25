#ifndef GS_COMMIT_H
#define GS_COMMIT_H

#include <iostream>
#include <string>

namespace getstatus {

class Commit {
private:
    std::string committer;
    std::string title;
    std::string message;
    std::string id;
    std::string timestamp;
public:
    Commit() { };
    Commit(std::string,
           std::string,
           std::string,
           std::string,
           std::string);
    ~Commit() {};
    friend std::ostream& operator<< (std::ostream&, const Commit&);

    std::string get_committer();

    std::string get_id();
};

} // namespace getstatus

#endif
