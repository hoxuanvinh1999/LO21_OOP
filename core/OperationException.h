#ifndef OPERATIONEXCEPTION_H
#define OPERATIONEXCEPTION_H

#include <QString>

/**
 * @class OperationException
 * @brief Classe d'exception liée aux opérations.
 */
class OperationException : public std::exception {
private:
    /**
     * @brief Message de l'exception.
     */
    QString message;
public:
    /**
     * @brief Constructeur d'une exception liée aux opérations.
     * @param message Message de l'exception.
     */
    OperationException(const QString& message) noexcept : message(message) {}
    /**
     * @brief Destructeur de l'exception.
     */
    virtual ~OperationException() noexcept {}
    /**
     * @brief Recupère le message propre à l'exception.
     * @return Le message propre à l'exception.
     */
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};

#endif // OPERATIONEXCEPTION_H
