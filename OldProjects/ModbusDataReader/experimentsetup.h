#pragma once


#include <QtGlobal>
#include <QObject>

#include "iexperimentcontrolmodel.h"

class ExperimentSetup : public IExperimentControlModel::IExperimentSetup
{
public:
    ExperimentSetup();

    // IExperimentSetup interface
private:
    QString GetExperimentSetupName() override;
    void SetExperimentSetupName(QString name) override;
    QMap<QString, IExperimentControlModel::IDataChannel*> GetDataChannels() override;
};


