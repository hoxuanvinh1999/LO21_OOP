#ifndef TYPEOPERATION_H
#define TYPEOPERATION_H

#include <QString>

/**
 * @brief Nombre de types d'opérations existantes.
 */
static const uint NombreTypesOperations = 2;

/**
  * @brief Tableau des noms des types d'opérations existantes.
  */
static const QString NomsTypeOperation[NombreTypesOperations] = { "Débit", "Crédit" };

/**
 * @enum TypeOperation
 * @brief Enumération des différentes types d'opérations.
 */
enum TypeOperation {
    DEBIT = 0,
    CREDIT
};

/**
 * @brief Récupère le type d'opération associé au nom fourni.
 * @param nom Nom du type d'opération à récupérer.
 * @return Le type d'opération associé au nom.
 */
TypeOperation getTypeOperation(const QString& nom);

/**
 * @class TypeOperationException
 * @brief Classe d'exception liée au type d'une opération.
 */
class TypeOperationException : public std::exception {
private:
    /**
     * @brief Message de l'exception.
     */
    QString message;
public:
    /**
     * @brief Constructeur d'une exception liée au type d'une opération.
     * @param message Message de l'exception.
     */
    TypeOperationException(const QString& message) noexcept : message(message) {}
    /**
     * @brief Destructeur de l'exception.
     */
    virtual ~TypeOperationException() noexcept {}
    /**
     * @brief Recupère le message propre à l'exception.
     * @return Le message propre à l'exception.
     */
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};

#endif // TYPEOPERATION_H
