#pragma once


#include <QtGlobal>
#include <QVariant>


class QAbstractItemModel;

//!  \defgroup ExtendableDataManager ExtendableDataManager
//!      \ingroup Plugins
//! \defgroup ExtendableDataManager_int Interfaces
//!     \ingroup ExtendableDataManager
//! \defgroup ExtendableDataManager_imp Implementation
//!     \ingroup ExtendableDataManager
//!  \defgroup ExtendableDataManager_dep Dependent plugins
//!      \ingroup ExtendableDataManager

//! \addtogroup ExtendableDataManager_int
//! \{
class IExtendableDataManager
{
public:
    virtual bool RegisterExtentionFieldEditor(QString relation, QString field, QWidget *widget) = 0;
    virtual QWidget *GetExtentionFieldEditor(QString relation, QString field) = 0;

    virtual QMap<QString, QVariant::Type> GetTableHeader(QString treeName) = 0;

    virtual QPointer<QAbstractItemModel> GetDataModel(QString treeName) = 0;
    virtual QPointer<QAbstractItemModel> GetDataModel(QVector<QPair<QString, QString> > dataModelFields) = 0;

    virtual bool AddExtention(QString mainName, QString relationName,
                              QMap<QString, QVariant::Type> fields,
                              QVector<QVariant> defaultData) = 0;
    virtual bool DeleteExtention(QString mainName, QString relationName) = 0;
};
Q_DECLARE_INTERFACE(IExtendableDataManager, "IExtendableDataManager/1.0")
//! \}

