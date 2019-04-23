#ifndef QT_DTO_HH
#define QT_DTO_HH

#include <QModelIndex>
#include <QVariant>
#include "mapping_types.hh"

namespace qt_dto {
    // Because these are const references (they're provided by
    // QAbstractItemModel#setData), we need to have this
    // constructor-enforces-validity model.
    struct MappingEncoderSetOperation {
        MappingEncoderSetOperation(
            const QModelIndex& index, const QVariant& value
        ): index(index), value(value) { }

        const QModelIndex& index;
        const QVariant& value;
    };

    struct FieldEncoderConfigurationOperation {
        QModelIndex index;
        bool targetFieldControlsChecked;
        int targetFieldTypeId;
        QString fieldName;
        QModelIndex selectedConverter;
        QModelIndexList selectedValidationRules;
        OptionsMap optionsMap;
    };
}

#endif /* QT_DTO_HH */
