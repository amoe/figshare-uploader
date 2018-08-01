#include <iostream>
#include <string>
#include "http_getter.hh"
#include "group_mapper.hh"


GroupMapperImpl::GroupMapperImpl(HttpGetter* httpGetter) : httpGetter(httpGetter) {
    std::ostringstream stringStream;
    stringStream << "https://api.figshare.com/v2"
                 << "/account/institution/groups";
    
    string result = httpGetter->request(stringStream.str());

    std::cout << "result was " << result << std::endl;
}

int GroupMapperImpl::getGroupIdByName(string groupName) {
    return 11611;
}


