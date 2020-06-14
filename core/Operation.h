#ifndef OPERATION_H
#define OPERATION_H

#include "ISerialisable.h"
#include "TypeOperation.h"

/**
 * @class Operation
 * @brief Classe représentant une opération dans une transaction.
 */
class Operation : public ISerialisable {
private:
    /**
     * @brief Montant de l'opération.
     */
    double montant;
    /**
     * @brief Type de l'opération.
     */
    TypeOperation type;
    /**
     * @brief Nom du compte ciblé par l'opération.
     */
    QString nomCompte;
public:
    Operation() = delete;
    /**
     * @brief Constructeur d'une opération.
     * @param montant Montant de l'opération.
     * @param type Type de l'opération.
     * @param nomCompte Nom du compte ciblé par l'opération.
     */
    Operation(double montant, const TypeOperation& type, const QString& nomCompte);
    /**
     * @brief Récupère le montant de l'opération.
     * @return Le montant de l'opération.
     */
    double getMontant() const { return montant; }
    /**
     * @brief Récupère le type de l'opération.
     * @return Le type de l'opération.
     */
    const TypeOperation& getType() const { return type; }
    /**
     * @brief Récupère le nom du compte ciblé par l'opération.
     * @return Le nom du compte ciblé par l'opération.
     */
    const QString& getNomCompte() const { return nomCompte; }
    /**
     * @brief Sérialise l'opération sous forme d'un élément XML.
     * @param doc Document XML dans lequel doit se trouver l'opération sérialisé.
     * @return L'opération sous forme d'un élément XML.
     */
    QDomElement serialiser(QDomDocument &doc) const override;
};

#endif // OPERATION_H
