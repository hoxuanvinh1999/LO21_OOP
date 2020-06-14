#ifndef COMPTEEXCEPTION_H
#define COMPTEEXCEPTION_H

#include <QString>

/**
 * @class CompteException
 * @brief Classe d'exception liée aux comptes.
 */
class CompteException : public std::exception {
private:
    /**
     * @brief Message de l'exception.
     */
    QString message;
public:
    /**
     * @brief Constructeur d'une exception liée aux comptes.
     * @param message Message de l'exception.
     */
    CompteException(const QString& message) noexcept : message(message) {}
    /**
     * @brief Destructeur de l'exception.
     */
    virtual ~CompteException() noexcept {}
    /**
     * @brief Recupère le message propre à l'exception.
     * @return Le message propre à l'exception.
     */
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};

#endif // COMPTEEXCEPTION_H
