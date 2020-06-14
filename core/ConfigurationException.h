#ifndef CONFIGURATIONEXCEPTION_H
#define CONFIGURATIONEXCEPTION_H

#include <QString>

/**
 * @class ConfigurationException
 * @brief Classe d'exception liée aux configurations.
 */
class ConfigurationException : public std::exception {
private:
    /**
     * @brief Message de l'exception.
     */
    QString message;
public:
    /**
     * @brief Constructeur d'une exception liée aux configurations.
     * @param message Message de l'exception.
     */
    ConfigurationException(const QString& message) noexcept : message(message) {}
    /**
     * @brief Destructeur de l'exception.
     */
    virtual ~ConfigurationException() noexcept {}
    /**
     * @brief Recupère le message propre à l'exception.
     * @return Le message propre à l'exception.
     */
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};

#endif // CONFIGURATIONEXCEPTION_H
