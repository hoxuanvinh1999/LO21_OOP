#ifndef OPERATIONEXCEPTION_H
#define OPERATIONEXCEPTION_H

#include <QString>
#include <exception>

using namespace std;

/**
 * @brief Gère les exceptions liées à une opération
 */
class OperationException : public exception {
private:
    QString message;
public:
    OperationException(const QString& message) noexcept : message(message) {}
    virtual ~OperationException() noexcept {}
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};

#endif // OPERATIONEXCEPTION_H
