#ifndef JSONREADER_H
#define JSONREADER_H

#include <QObject>
#include <QQuickItem>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class JsonReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentKey READ getCurrentKey WRITE setCurrentKey NOTIFY keyChanged)
    Q_PROPERTY(QJsonValue currentValue READ getCurrentValue WRITE setCurrentValue NOTIFY valueChanged)
    Q_PROPERTY(QVector<QString> keysToSave READ getKeysToSave WRITE setKeysToSave NOTIFY keysToSaveChanged)

public:
    explicit JsonReader(QObject *parent = nullptr);

    Q_INVOKABLE QString getCurrentKey();
    Q_INVOKABLE QJsonValue getCurrentValue();
    Q_INVOKABLE std::string getJsonDoc();
    Q_INVOKABLE QJsonObject getJsonObj();
    Q_INVOKABLE QVector<QString> getKeysToSave();
    Q_INVOKABLE bool valueIsBool(QJsonValue);
    Q_INVOKABLE bool valueIsDouble(QJsonValue);
    Q_INVOKABLE bool valueIsInt(QJsonValue);
    Q_INVOKABLE bool valueIsString(QJsonValue);
    Q_INVOKABLE QString stringifyObject(QJsonObject);

signals:
    void listChanging();
    void finalizeCreation();
    void keyChanged();
    void throwToHeap();
    void valueString();
    void valueBool();
    void valueInt();
    void valueDouble();
    void keysToSaveChanged();
    void valueChanged();

public slots:
    void setCurrentKey(QString);
    void setCurrentValue(QJsonValue);
    void setKeysToSave(QVector<QString>);
    Q_INVOKABLE void readJson(std::string);
    Q_INVOKABLE void writeJson();
    Q_INVOKABLE void setJsonPair();
    Q_INVOKABLE void addValue(QString, QVariant);

private:
    QVector<QString> m_keysToSave;
    QString m_currentKey;
    QJsonValue m_currentValue;
    std::string m_jsonDoc;
    QJsonObject m_jsonObj;
};

#endif // JSONREADER_H
