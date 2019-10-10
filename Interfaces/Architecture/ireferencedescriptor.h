#pragma once

#include "interface.h"

//! \brief Holds basic information about plugin.
class IReferenceDescriptor
{
public:
    //! \brief Plugin unique id. Every plugin in system guaranteed to have unique id.
    virtual uid_t uid() = 0;
    //! \brief Plugin interface name. By this field all plugins are linked.
    virtual const QVector<Interface>& interfaces() = 0;
    //! \brief Plugin name.
    virtual const QString& name() = 0;
    //! \brief Description of features and purpose of this plugin.
    virtual const QString& about() = 0;

    virtual QObject *object() = 0;
};
typedef QWeakPointer<IReferenceDescriptor> IReferenceDescriptorPtr;
