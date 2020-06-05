#ifndef TRANSACTIONEXCEPTION_H
#define TRANSACTIONEXCEPTION_H

#include <QString>
#include <exception>

using namespace std;

class TransactionException : public exception {
private:
    QString message;
public:
    TransactionException(const QString& message) noexcept : message(message) {}
    virtual ~TransactionException() noexcept {}
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};

#endif // TRANSACTIONEXCEPTION_H
