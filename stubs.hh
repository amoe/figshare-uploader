#ifndef STUBS_HH
#define STUBS_HH

#include "http_poster.hh"
#include "http_getter.hh"
#include "size_getter.hh"

using std::string;

class StubHttpGetter : public HttpGetter {
public:
    StubHttpGetter(string cannedResponse)
        : cannedResponse(cannedResponse) {} 

    string request(const string url);

private:
    string cannedResponse;
};

class StubHttpPoster : public HttpPoster {
public:
    StubHttpPoster(string cannedResponse)
        : cannedResponse(cannedResponse) {} 

    string request(const string url, const string payload);

private:
    string cannedResponse;
};


class StubFileSizeGetter : public SizeGetter {
public:
    StubFileSizeGetter(int64_t cannedResponse)
        : cannedResponse(cannedResponse) {}
    int64_t getSize(string path);
    
private:
    int64_t cannedResponse;
};

#endif // STUBS_HH
