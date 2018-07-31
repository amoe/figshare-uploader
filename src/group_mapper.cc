#include <iostream>
#include <string>
#include "http_getter.hh"
#include "group_mapper.hh"

int GroupMapperImpl::getGroupIdByName(string groupName) {
    string result = httpGetter->request("foo");
    return 11611;
}


