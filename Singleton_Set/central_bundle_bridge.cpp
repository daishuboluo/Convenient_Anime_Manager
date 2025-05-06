#include "central_bundle_bridge.h"

Q_GLOBAL_STATIC(Central_Bundle_Bridge, fileRelatedInstance)

Central_Bundle_Bridge::Central_Bundle_Bridge(QObject* parent)
    : QObject{ parent }
{
}

Central_Bundle_Bridge* Central_Bundle_Bridge::instance() {
    return fileRelatedInstance;
}
