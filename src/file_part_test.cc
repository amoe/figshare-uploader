#include <gmock/gmock.h>
#include <QJsonObject>
#include <QJsonDocument>
#include "raw_literals.hh"
#include "file_part.hh"

using ::testing::Eq;


TEST(FilePartTest, CanDeserializePart) {
    string json = raw_literals::serializedFilePartInfo;
    auto document = QJsonDocument::fromJson(QString::fromStdString(json).toUtf8());
    QJsonObject object = document.object();

    auto deserialized = FilePart::fromJson(object);

    ASSERT_THAT(deserialized.getPartNumber(), Eq(1));
    ASSERT_THAT(deserialized.isLocked(), Eq(false));
    ASSERT_THAT(deserialized.getStartOffset(), Eq(0));
    ASSERT_THAT(deserialized.getEndOffset(), Eq(10485759));
    ASSERT_THAT(deserialized.getStatus(), Eq(FilePartStatus::PENDING));
}

