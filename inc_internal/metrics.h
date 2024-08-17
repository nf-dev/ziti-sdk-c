// Copyright (c) 2019-2023.  NetFoundry Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ZITI_SDK_METRICS_H
#define ZITI_SDK_METRICS_H

#include <stdint.h>
#include <stdbool.h>
#include <ziti/enums.h>

#ifdef __cplusplus
#include <atomic>
using namespace std;
#else
#if defined(__linux) || defined(__FreeBSD__)

/* 20230621:NFRAGALE@NETFOUNDRY:Build assurance against a missing macro in features.h. */
#  if defined __GNUC__ && defined __GNUC_MINOR__ && ! __clang__
#    include <features.h>
#    ifndef __GNUC_PREREQ
#      define __GNUC_PREREQ(maj, min) ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#    endif
/* gcc 4.8 does not have <stdatomic.h> and does not set the flag */
#    if ! __GNUC_PREREQ(4,9)
#      define __STDC_NO_ATOMICS__ 1
#    endif
#  endif

# if __STDC_NO_ATOMICS__
#   include <bits/atomic.h>

#   define atomic_llong uatomic_fast64_t
#   define atomic_long uatomic_fast32_t
# else
#   include <stdatomic.h>
# endif
#elif defined(__APPLE__)
# include <stdatomic.h>
#elif _WIN32
#include <stdatomic.h>
#endif
#endif

struct rate_s {
    atomic_llong delta;
    atomic_llong rate;
    atomic_llong param;

    uint64_t last_tick;
    void (*tick_fn)(struct rate_s *);

    atomic_long init;
    bool active;
};

typedef struct rate_s rate_t;

#ifdef __cplusplus
extern "C" {
#endif

// return millisecond precision time
typedef uint64_t (*time_fn)(void *ctx);
extern void metrics_init(long interval_secs, time_fn, void *time_ctx);

extern int metrics_rate_init(rate_t *r, rate_type type);
extern void metrics_rate_close(rate_t* r);

extern void metrics_rate_update(rate_t *r, long delta);
extern double metrics_rate_get(rate_t *r);

#ifdef __cplusplus
}
#endif

#endif //ZITI_SDK_METRICS_H
