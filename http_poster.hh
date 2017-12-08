#include <string>

using std::string;

class HttpPoster {
public:
    virtual string request(const string url, const string payload) = 0;
};

class QtHttpPoster : public HttpPoster {
public:
    string request(const string url, const string payload);
};
