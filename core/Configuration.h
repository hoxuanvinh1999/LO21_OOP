#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QHash>
#include <QString>

/**
 * @class Configuration
 * @brief Classe représentant une configuration avec des associations (attribut -> valeur).
 */
class Configuration {
private:
    /**
     * @brief Map d'associations attribut -> valeur de la configuration.
     */
    QHash<QString, QString> mapAttributs;
public:
    /**
      * @brief Constructeur par défaut d'une configuration.
      */
    Configuration() = default;
    /**
     * @brief Défini la valeur d'un attribut dans la configuration.
     * @param attribut Nom de l'attribut auquel affecter une valeur.
     * @param valeur Valeur à affecter à l'attribut.
     */
    void setValeurAttribut(const QString& attribut, const QString& valeur) { mapAttributs.insert(attribut, valeur); }
    /**
     * @brief Récupère la valeur d'un attribut dans la configuration.
     * @param attribut Nom de l'attribut dont on veut récupérer la valeur.
     * @return La valeur de l'attribut.
     */
    QString getValeurAttribut(const QString& attribut) const { return mapAttributs.value(attribut); }
    /**
     * @brief Indique si un attribut existe ou non dans la configuration.
     * @param attribut Nom de l'attribut dont on veut savoir si il existe ou non.
     * @return Vrai si l'attribut existe dans la configuration, faux sinon.
     */
    bool existeAttribut(const QString& attribut) const { return mapAttributs.contains(attribut); }
    /**
     * @brief Sauvegarde la configuration dans un fichier au format XML.
     * @param nomFichier Nom du fichier dans lequel sauvegarder la configuration.
     */
    void sauvegarder(const QString& nomFichier) const;
    /**
     * @brief Charge un configuration à partir d'un fichier XML.
     * @param nomFichier Nom du fichier XML à partir duquel charger la configuration.
     * @return La configuration chargée à partir du fichier XMl.
     */
    static Configuration chargerFicher(const QString& nomFichier);
};

#endif // CONFIGURATION_H
