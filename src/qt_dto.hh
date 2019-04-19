#ifndef QT_DTO_HH
#define QT_DTO_HH

#include <QModelIndex>
#include <QVariant>

namespace qt_dto {
    struct MappingEncoderSetOperation {
        MappingEncoderSetOperation(
            const QModelIndex& index, const QVariant& value
        ): index(index), value(value) { }

        const QModelIndex& index;
        const QVariant& value;
    };
}

#endif /* QT_DTO_HH */
