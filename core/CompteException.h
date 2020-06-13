#ifndef COMPTEEXCEPTION_H
#define COMPTEEXCEPTION_H

#include <QString>
#include <exception>

using namespace std;

/**
 * @brief Gère les exceptions liées à une instance de Compte
 */
class CompteException : public exception {
private:
    QString message;
public:
    CompteException(const QString& message) noexcept : message(message) {}
    virtual ~CompteException() noexcept {}
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};

#endif // COMPTEEXCEPTION_H
