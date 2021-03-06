#pragma once

#include <QtCore>
#include <QImage>

#include "../Utility/i_user_task_data_ext.h"

#define IUserTaskImageDataExtention_EXTENTION_PROPERTY \
	Q_PROPERTY(QByteArray image READ image)

class IUserTaskImageDataExtention : public IUserTaskDataExtention
{
public:
	IUserTaskImageDataExtention_EXTENTION_PROPERTY
	virtual QByteArray image() = 0;
};
Q_DECLARE_INTERFACE(IUserTaskImageDataExtention, "IUserTaskImageDataExtention/1.0")
