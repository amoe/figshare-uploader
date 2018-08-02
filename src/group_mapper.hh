#ifndef GROUP_MAPPER_HH
#define GROUP_MAPPER_HH

#include <map>
#include "http_getter.hh"

using std::map;

// Interface for group mapper

class GroupMapper {
public:
    virtual int getGroupIdByName(string groupName) = 0;
};

class GroupMapperImpl : public GroupMapper {
public:
    GroupMapperImpl(HttpGetter* httpGetter);
    int getGroupIdByName(string groupName);

private:
    HttpGetter* httpGetter;
    map<string, int> lookup;
};


#endif // GROUP_MAPPER_HH
