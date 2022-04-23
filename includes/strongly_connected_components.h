#ifndef _STRONGLY_CONNECTED_COMPONENTS
#define _STRONGLY_CONNECTED_COMPONENTS

#include <list>

#include "type.h"

std::list<std::list<size_t> > StronglyConnectedComponents(const AdjList& graph);

#endif