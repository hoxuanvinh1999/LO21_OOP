#ifndef SAUVEGARDEEXCEPTION_H
#define SAUVEGARDEEXCEPTION_H

#include <QString>

/**
 * @class SauvegardeException
 * @brief Classe d'exception liée aux sauvegardes.
 */
class SauvegardeException : public std::exception {
private:
    /**
     * @brief Message de l'exception.
     */
    QString message;
public:
    /**
     * @brief Constructeur d'une exception liée aux sauvegardes.
     * @param message Message de l'exception.
     */
    SauvegardeException(const QString& message) noexcept : message(message) {}
    /**
     * @brief Destructeur de l'exception.
     */
    virtual ~SauvegardeException() noexcept {}
    /**
     * @brief Recupère le message propre à l'exception.
     * @return Le message propre à l'exception.
     */
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};

#endif // SAUVEGARDEEXCEPTION_H
