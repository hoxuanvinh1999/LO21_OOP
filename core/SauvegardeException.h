#ifndef SAUVEGARDEEXCEPTION_H
#define SAUVEGARDEEXCEPTION_H

#include <QString>
#include <exception>

using namespace std;

/**
 * @brief Gère les exceptions liées à la sauvegarde
 */

class SauvegardeException : public exception {
private:
    QString message;
public:
    SauvegardeException(const QString& message) noexcept : message(message) {}
    virtual ~SauvegardeException() noexcept {}
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};

#endif // SAUVEGARDEEXCEPTION_H
