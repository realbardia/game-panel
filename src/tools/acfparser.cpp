#include "acfparser.h"

struct ACFParser::Token {
    enum Type { String, BlockOpen, BlockClose };
    Type type;
    QString value; // Only used for String type

    Token(Type type, const QString& value = "") : type(type), value(value) {}
};

bool ACFParser::tokenizeACF(const QString &input, QList<Token> &tokens, QString &errorMsg) {
    tokens.clear();
    errorMsg.clear();
    int index = 0;
    const int len = input.length();

    auto addError = [&](const QString& msg) {
        errorMsg = msg;
        return false;
    };

    while (index < len) {
        QChar c = input[index];

        // Skip whitespace
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            index++;
            continue;
        }

        // Parse string
        if (c == '"') {
            index++; // Skip opening quote
            QString str;
            bool escape = false;
            bool inString = true;

            while (index < len && inString) {
                c = input[index];
                if (escape) {
                    switch (c.unicode()) {
                    case 'n': str += '\n'; break;
                    case 't': str += '\t'; break;
                    case 'r': str += '\r'; break;
                    case '"': str += '"'; break;
                    case '\\': str += '\\'; break;
                    default: str += '\\'; str += c; // Treat invalid escape literally
                    }
                    escape = false;
                    index++;
                } else if (c == '\\') {
                    escape = true;
                    index++;
                } else if (c == '"') {
                    inString = false;
                    index++; // Skip closing quote
                } else {
                    str += c;
                    index++;
                }
            }

            if (inString) {
                return addError("Unterminated string");
            }
            tokens.append(Token(Token::String, str));
        }
        // Parse block open
        else if (c == '{') {
            tokens.append(Token(Token::BlockOpen));
            index++;
        }
        // Parse block close
        else if (c == '}') {
            tokens.append(Token(Token::BlockClose));
            index++;
        }
        // Invalid character
        else {
            return addError(QString("Unexpected character '%1' at position %2").arg(c).arg(index));
        }
    }
    return true;
}

bool ACFParser::parseKeyValueSequence(const QList<Token> &tokens, int &index, bool untilBlockClose, QVariantMap &result, QString &errorMsg) {
    result.clear();
    const int tokenCount = tokens.size();

    while (index < tokenCount) {
        // Check for closing brace if required
        if (untilBlockClose && tokens[index].type == Token::BlockClose) {
            break;
        }

        // Key must be a string
        if (tokens[index].type != Token::String) {
            errorMsg = "Expected string key";
            return false;
        }
        QString key = tokens[index++].value;

        // Ensure value exists
        if (index >= tokenCount) {
            errorMsg = "Unexpected end after key";
            return false;
        }

        Token valueToken = tokens[index++];

        // String value
        if (valueToken.type == Token::String) {
            result[key] = valueToken.value;
        }
        // Nested block
        else if (valueToken.type == Token::BlockOpen) {
            QVariantMap innerMap;
            if (!parseKeyValueSequence(tokens, index, true, innerMap, errorMsg)) {
                return false;
            }
            // Check block close
            if (index >= tokenCount || tokens[index].type != Token::BlockClose) {
                errorMsg = "Expected closing brace after block";
                return false;
            }
            index++; // Skip closing brace
            result[key] = innerMap;
        }
        // Invalid value type
        else {
            errorMsg = "Expected string or block after key";
            return false;
        }
    }
    return true;
}

QVariantMap ACFParser::parseACFFileContent(const QString &acfContent, bool *ok, QString *errorMsg) {
    QList<Token> tokens;
    QString tokenizeError;
    QVariantMap result;

    // Tokenize input
    if (!tokenizeACF(acfContent, tokens, tokenizeError)) {
        if (ok) *ok = false;
        if (errorMsg) *errorMsg = "Tokenization error: " + tokenizeError;
        return result;
    }

    // Parse tokens
    int index = 0;
    QString parseError;
    if (!parseKeyValueSequence(tokens, index, false, result, parseError) || index != tokens.size()) {
        if (ok) *ok = false;
        if (errorMsg) *errorMsg = "Parse error: " + parseError;
        return QVariantMap();
    }

    if (ok) *ok = true;
    return result;
}
