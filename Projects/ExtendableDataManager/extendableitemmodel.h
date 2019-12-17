#ifndef EXTENDABLEITEMMODEL_H
#define EXTENDABLEITEMMODEL_H

#include <QAbstractItemModel>
#include <QVariant>
#include <QVector>
#include <QDebug>
#include <QMimeData>
#include <QDataStream>
#include <QMap>
#include <QObject>

#include "../../Interfaces/Middleware/iextendabledatamanager.h"
#include "../../Interfaces/Architecture/referenceinstance.h"
#include "item.h"

//! \addtogroup ExtendableDataManager_imp
//!  \{
class ExtendableItemModel : public QAbstractItemModel
{
	typedef IExtendableDataManager::ManagerDataItem ManagerDataItem;
	typedef QMap<QString, QVariant::Type> TableStructMap;
public:
	ExtendableItemModel(QString tableName, IExtendableDataManager *dataManager, QObject *parent = nullptr);
	virtual ~ExtendableItemModel() override;

public:
	void LoadData();
	bool AttachRelation(QString relationName, TableStructMap fields, QVector<QVariant> defaultData);
	void SetActiveRelation(QString relationName);
	void SetDataTypeEditor(QString dataChunk, QString fieldName, QWidget *widget);

	virtual QVariant data(const QModelIndex &index, int role) const override;
	QMap<int, QVariant> itemData(const QModelIndex &index) const override;
	bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles) override;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	virtual QModelIndex parent(const QModelIndex &index) const override;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	virtual bool insertRows(int row, int count, const QModelIndex &parent) override;
	virtual bool insertColumns(int column, int count, const QModelIndex &parent) override;
	virtual bool removeRows(int row, int count, const QModelIndex &parent) override;
	virtual bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) override;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
	virtual QStringList mimeTypes() const override;
	virtual QMimeData *mimeData(const QModelIndexList &indexes) const override;
	virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

	Item *AddItem(int row, Item *taskParent, Item *taskData = nullptr);
	bool UpdateItem(Item *task);
	bool UpdateItemsPosition(Item *parent, int from);
	bool DeleteItem(Item *task);
	void DeleteFromManagerRecursive(Item *task);

	QMap<QString, QVariant> ConvertFromHeadedMap(QMap<QString, QVariant> dataMap);
	QMap<QString, QVariant> ConvertToHeadedMap(QMap<QString, QVariant> headerMap, QMap<QString, QVariant> valuesMap) const;
	void ReadSameModelMime(int beginRow, int row, const QModelIndex &parent, QMap<quintptr, QMap<int, quintptr> > &newItems);

private:
	QString tableName;
	QString coreRelationName;
	IExtendableDataManager* dataManager;
	
	int nameIndex;
	int parentIndex;
	int positionIndex;

	QHash<int, Item*> internalList;
	QString currentActiveChunkName;
	Item defaultTask;
	Item header;
	Item dataTypeEditors;
	Item *rootItem;
};
//!  \}
#endif // EXTENDABLEITEMMODEL_H
