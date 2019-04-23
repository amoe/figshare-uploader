#ifndef DOMAIN_DTO_HH
#define DOMAIN_DTO_HH

#include "optional.hpp"

using nonstd::optional;

namespace domain {
    struct FieldEncoderListOperation {
        int index;
        bool isTargetFieldSet;
        int targetFieldTypeId;
        string fieldName;
        vector<int> validationRuleIndices;
        int converterIndex;
        map<string, optional<string>> newOptions;
    };

    struct MappingEncoderSetOperation {
        int excelRowIndex;
        int fieldEncoderIndex;
    };
}

#endif /* DOMAIN_DTO_HH */
