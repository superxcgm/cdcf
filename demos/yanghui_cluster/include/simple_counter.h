/*
 * Copyright (c) 2020 ThoughtWorks Inc.
 */

#ifndef DEMOS_YANGHUI_CLUSTER_SIMPLE_COUNTER_H_
#define DEMOS_YANGHUI_CLUSTER_SIMPLE_COUNTER_H_

#include "./yanghui_config.h"
#include "caf/all.hpp"
#include "caf/io/all.hpp"

caf::behavior simple_counter(caf::event_based_actor* self);

#endif  // DEMOS_YANGHUI_CLUSTER_SIMPLE_COUNTER_H_
