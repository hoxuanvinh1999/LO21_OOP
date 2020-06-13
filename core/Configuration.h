#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QHash>
#include <QString>

class Configuration {
private:
    QHash<QString, QString> mapAttributs;
public:
    Configuration() = default;
    void setValeurAttribut(const QString& attribut, const QString& valeur) { mapAttributs.insert(attribut, valeur); }
    QString getValeurAttribut(const QString& attribut) const { return mapAttributs.value(attribut); }
    bool existeAttribut(const QString& attribut) const { return mapAttributs.contains(attribut); }
    void sauvegarder(const QString& nomFichier) const;
    static Configuration chargerFicher(const QString& nomFichier);
};

#endif // CONFIGURATION_H
