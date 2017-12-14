#ifndef HTTP_PUTTER_HH
#define HTTP_PUTTER_HH

#include <string>

using std::string;

class HttpPutter {
public:
    virtual string request(const string url, const string payload) = 0;
};

class QtHttpPutter : public HttpPutter {
public:
    QtHttpPutter(string token) : token(token) { }
    string request(const string url, const string payload);

private:
    string token;
};

#endif // HTTP_PUTTER_HH
