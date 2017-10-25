#include "commit.h"

#include <iostream>
#include <string>

namespace getstatus {

Commit::Commit(std::string committer,
               std::string title,
               std::string message,
               std::string id,
               std::string timestamp) {
    this->committer = committer;
    this->title = title;
    this->message = message;
    this->id = id;
    this->timestamp = timestamp;
}

std::ostream& operator << (std::ostream &out, const Commit &c) {
    out << c.id << ": " << c.title;
    return out;
}

} // namespace getstatus
