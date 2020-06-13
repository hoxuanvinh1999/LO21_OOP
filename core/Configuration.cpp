#include "Configuration.h"
#include "ConfigurationException.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDomDocument>

void Configuration::sauvegarder(const QString& nomFichier) const {
    if(nomFichier.isNull() || nomFichier.isEmpty())
        throw ConfigurationException("Le nom du fichier dans lequel sauvegarder la configuration ne peut être nul ou vide !");
    QFile fichier(nomFichier);
    if(!fichier.open(QIODevice::WriteOnly))
        throw ConfigurationException("Erreur lors de la création du fichier " + nomFichier + " !");
    QDomDocument doc("Configuration");
    QDomElement racineDoc = doc.createElement("Attributs");
    doc.appendChild(racineDoc);
    for(QString attribut : mapAttributs.keys()) {
        QString valeur = mapAttributs.value(attribut);
        QDomElement attributXml = doc.createElement("Attribut");
        attributXml.setAttribute("attribut", attribut);
        attributXml.setAttribute("valeur", valeur);
        racineDoc.appendChild(attributXml);
    }
    QTextStream stream(&fichier);
    stream << doc.toString();
    fichier.close();
}


Configuration Configuration::chargerFicher(const QString& nomFichier) {
    if(nomFichier.isNull() || nomFichier.isEmpty())
        throw ConfigurationException("Le nom du fichier à charger ne peut être nul ou vide !");
    QFile fichier(nomFichier);
    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        throw ConfigurationException("Erreur de lecture du fichier de configuration !");
    QTextStream in(&fichier);
    in.setCodec(QTextCodec::codecForName("ISO 8859-1"));
    QString content = in.readAll();
    QDomDocument doc;
    doc.setContent(content);
    Configuration configuration;
    QDomNodeList attributsXml = doc.elementsByTagName("Attribut");
    for(int i = 0; i < attributsXml.size(); ++i) {
        QDomElement attributXml = attributsXml.item(i).toElement();
        QString attribut = attributXml.attribute("attribut");
        QString valeur = attributXml.attribute("valeur");
        configuration.setValeurAttribut(attribut, valeur);
    }
    fichier.close();
    return configuration;
}
