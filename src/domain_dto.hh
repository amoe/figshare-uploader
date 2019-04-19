#ifndef DOMAIN_DTO_HH
#define DOMAIN_DTO_HH

namespace domain {
    struct FieldEncoderListOperation {
        int index;
        int targetFieldTypeId;
        string fieldName;
        vector<int> validationRuleIndices;
        int converterIndex;
    };
}

#endif /* DOMAIN_DTO_HH */
