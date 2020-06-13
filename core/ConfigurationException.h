#ifndef CONFIGURATIONEXCEPTION_H
#define CONFIGURATIONEXCEPTION_H

#include <QString>
#include <exception>

using namespace std;

class ConfigurationException : public exception {
private:
    QString message;
public:
    ConfigurationException(const QString& message) noexcept : message(message) {}
    virtual ~ConfigurationException() noexcept {}
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};

#endif // CONFIGURATIONEXCEPTION_H
