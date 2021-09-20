#include "jsonreader.h"
JsonReader::JsonReader(QObject *parent) : QObject(parent)
{

}
void JsonReader::readJson(std::string jsonStdString)
{
    QJsonDocument document = QJsonDocument::fromJson(QByteArray::fromStdString(jsonStdString));
    QJsonObject root = document.object();
    emit listChanging(); //listModel.clear()
    for (int i = 0; i < root.keys().size(); i++)
    {
        auto bufferKey = root.keys().at(i);
        JsonReader::setCurrentKey(bufferKey); //
        QJsonValue bufferValue = root.value(bufferKey);
        if(bufferValue.isNull())
        {
            continue;
        }
        if(bufferValue.isUndefined())
        {
            continue;
        }
        if(bufferValue.isArray())
        {
            continue;
        }
        if(bufferValue.isObject())
        {
            continue;
        }
        JsonReader::setCurrentValue(bufferValue); //listModel.append()
    }
}
void JsonReader::writeJson()
{
    m_jsonDoc = QJsonDocument::fromVariant(m_jsonObj).toJson(QJsonDocument::Indented);
    emit finalizeCreation();
}

void JsonReader::setJsonPair()
{
    for(unsigned int i = 0; i < m_keysToSave.size(); i++){
        m_jsonObj.insert(m_keysToSave[i], "temporary");
    }
    emit throwToHeap();
    JsonReader::writeJson();
}
QJsonValue JsonReader::getCurrentValue()
{
    return m_currentValue;
}

std::string JsonReader::getJsonDoc()
{
    return m_jsonDoc;
}

QJsonObject JsonReader::getJsonObj()
{
    return m_jsonObj;
}

QVector<QString> JsonReader::getKeysToSave()
{
    return m_keysToSave;
}

bool JsonReader::valueIsBool(QJsonValue compareValue)
{
    return compareValue.isBool();
}

bool JsonReader::valueIsDouble(QJsonValue compareValue)
{
    return compareValue.isDouble();
}

bool JsonReader::valueIsInt(QJsonValue compareValue)
{
    QString tempString = compareValue.toString();
    for(unsigned int i = 0; i < tempString.size(); i++)
    {
        if((tempString[i] < '0' && tempString[i] > '9') || (tempString[i] != '-'))
        {
            return false;
        }
    }
    return true;
}

bool JsonReader::valueIsString(QJsonValue compareValue)
{
    return compareValue.isString();
}

QString JsonReader::stringifyObject(QJsonObject jsonObject)
{
    QString string;
    for (int i = 0; i < jsonObject.keys().size(); i++)
    {
        QString bufferKey = jsonObject.keys().at(i);
        QJsonValue bufferValue = jsonObject.value(bufferKey);
        if(bufferValue.isNull())
        {
            continue;
        }
        if(bufferValue.isUndefined())
        {
            continue;
        }
        if(bufferValue.isArray())
        {
            QJsonArray tempArray = bufferValue.toArray();
            for(unsigned int i = 0; i < tempArray.size(); i++)
            {
                string.append(tempArray[i].toVariant().toString());
            }
            continue;
        }
        if(bufferValue.isObject())
        {
            string.append(JsonReader::stringifyObject(bufferValue.toObject()));
            continue;
        }
        string.append(bufferValue.toString()); //listModel.append()
    }
    return string;
}
void JsonReader::setCurrentKey(QString newKey)
{
    if (m_currentKey != newKey)
    {
        m_currentKey = newKey;
    }
    emit keyChanged();
}
void JsonReader::setCurrentValue(QJsonValue newValue)
{
    if (m_currentValue != newValue)
    {
        m_currentValue = newValue;
    }
    if(JsonReader::valueIsBool(m_currentValue))
    {
        emit valueBool();
        return;
    }
    if(JsonReader::valueIsString(m_currentValue))
    {
        emit valueString();
        return;
    }
    if(JsonReader::valueIsDouble(m_currentValue))
    {
        emit valueDouble();
        return;
    }
    if(JsonReader::valueIsInt(m_currentValue))
    {
        emit valueInt();
        return;
    }
}
void JsonReader::addValue(QString key, QVariant value)
{
    m_jsonObj.insert(key, QJsonValue::fromVariant(value));
    if(m_jsonObj.size() == m_keysToSave.length())
    {
        m_jsonDoc = QJsonDocument::fromVariant(m_jsonObj.toVariantMap()).toJson().toStdString();
        emit finalizeCreation();
    }
}
void JsonReader::setKeysToSave(QVector<QString> newVecKeys)
{
    m_keysToSave = newVecKeys;
    emit throwToHeap();
}
QString JsonReader::getCurrentKey()
{
    return m_currentKey;
}
