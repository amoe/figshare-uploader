#include "http_poster.hh"

using std::string;

class StubHttpPoster : public HttpPoster {
public:
    StubHttpPoster(string cannedResponse)
        : cannedResponse(cannedResponse) {} 

    string request(const string url, const string payload);

private:
    string cannedResponse;
};
