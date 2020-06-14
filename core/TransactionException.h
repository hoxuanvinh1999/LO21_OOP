#ifndef TRANSACTIONEXCEPTION_H
#define TRANSACTIONEXCEPTION_H

#include <QString>

/**
 * @class TransactionException
 * @brief Classe d'exception liée aux transactions.
 */
class TransactionException : public std::exception {
private:
    /**
     * @brief Message de l'exception.
     */
    QString message;
public:
    /**
     * @brief Constructeur d'une exception liée aux transactions.
     * @param message Message de l'exception.
     */
    TransactionException(const QString& message) noexcept : message(message) {}
    /**
     * @brief Destructeur de l'exception.
     */
    virtual ~TransactionException() noexcept {}
    /**
     * @brief Recupère le message propre à l'exception.
     * @return Le message propre à l'exception.
     */
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};

#endif // TRANSACTIONEXCEPTION_H
