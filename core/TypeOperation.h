#ifndef TYPEOPERATION_H
#define TYPEOPERATION_H

#include <QString>

static const uint NombreTypesOperations = 2;
static const QString NomsTypeOperation[NombreTypesOperations] = { "Débit", "Crédit" };

enum TypeOperation {
    DEBIT = 0,
    CREDIT
};

TypeOperation getTypeOperation(const QString& nom);


using namespace std;

class TypeOperationException : public exception {
private:
    QString message;
public:
    TypeOperationException(const QString& message) noexcept : message(message) {}
    virtual ~TypeOperationException() noexcept {}
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};

#endif // TYPEOPERATION_H
