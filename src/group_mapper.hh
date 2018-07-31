#ifndef GROUP_MAPPER_HH
#define GROUP_MAPPER_HH

// Interface for group mapper

class GroupMapper {
public:
    virtual ~GroupMapper();
    virtual int getGroupIdByName() = 0;
};


#endif // GROUP_MAPPER_HH
