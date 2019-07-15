#if defined(PLUGIN_BASE_QOBJECT)
#include "plugin_base.h"

PluginBase::PluginBase(QObject *object) :
    m_object(object)
{
    constructorInit();
}
#endif
