#pragma once

#include <QtCore>

#include "../../Interfaces/Architecture/interface.h"
#include "../IDataExtention.h"

#define DATA_EXTENTION_BASE_DEFINITIONS(ExtentionDataInterfaceType, ExtendableDataInterfaceType, ...) \
	ExtentionDataInterfaceType##_EXTENTION_PROPERTY \
	ExtendableDataInterfaceType##_EXTENTION_PROPERTY \
	Q_PROPERTY(QObject* model READ model NOTIFY modelChanged) \
	public: \
	QPointer<IExtendableDataModel> getModel() override \
	{ \
		return m_model; \
	} \
	Interface getExtentionInterface() override \
	{ \
		return m_extentionInterface; \
	} \
	Interface getExtendableInterface() override \
	{ \
		return m_extendableInterface; \
	} \
	QObject* model() override \
	{ \
		return static_cast<QObject*>(m_model.data()); \
	} \
	void setModel(QPointer<IExtendableDataModel> model) override \
	{ \
		bool isChanged = m_model != model; \
		m_model = model; \
		if(isChanged) \
			emit modelChanged(); \
	} \
	QVector<QString> getDataFields() override \
	{ \
		return __VA_ARGS__; \
	} \
protected: \
	QPointer<IExtendableDataModel> m_model; \
	Interface m_extentionInterface = INTERFACE(ExtentionDataInterfaceType); \
	Interface m_extendableInterface = INTERFACE(ExtendableDataInterfaceType); \
public:

