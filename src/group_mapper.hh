#ifndef GROUP_MAPPER_HH
#define GROUP_MAPPER_HH

#include "http_getter.hh"

// Interface for group mapper

class GroupMapper {
public:
    virtual int getGroupIdByName() = 0;
};

class GroupMapperImpl : public GroupMapper {
public:
    GroupMapperImpl(HttpGetter* httpGetter) :  httpGetter(httpGetter) { }
    int getGroupIdByName();

private:
    HttpGetter* httpGetter;
};


#endif // GROUP_MAPPER_HH
