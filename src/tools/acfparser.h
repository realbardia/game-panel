#ifndef ACFPARSER_H
#define ACFPARSER_H

#include <QVariantMap>

class ACFParser
{
    struct Token;
public:
    static QVariantMap parseACFFileContent(const QString& acfContent, bool* ok, QString* errorMsg);

private:
    static bool tokenizeACF(const QString& input, QList<Token>& tokens, QString& errorMsg);
    static bool parseKeyValueSequence(const QList<Token>& tokens, int& index, bool untilBlockClose, QVariantMap& result, QString& errorMsg);
};

#endif // ACFPARSER_H
