#ifndef DATA_TRANSFER_OBJECTS_HH
#define DATA_TRANSFER_OBJECTS_HH

namespace domain {
    struct FieldEncoderListOperation {
        int index;
        int targetFieldTypeId;
        string fieldName;
        vector<int> validationRuleIndices;
        int converterIndex;
    };
}

#endif /* DATA_TRANSFER_OBJECTS_HH */
