// Copyright (c) 2022-2023.  NetFoundry Inc.
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


#ifndef ZITI_SDK_POOL_H
#define ZITI_SDK_POOL_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct pool_s pool_t;

pool_t *pool_new(size_t objsize, size_t count, void (*clear_func)(void *));

void pool_destroy(pool_t *pool);

bool pool_has_available(pool_t *p);

typedef void (*pool_available_cb)(void *ctx);
void pool_set_available_cb(pool_t *p, pool_available_cb, void *ctx);

void *pool_alloc_obj(pool_t *pool);

// allocate object that can be freed by [pool_return_obj]
// useful when you need alloc before pool is available or need an object larger that normal
void *alloc_unpooled_obj(size_t size, void (*clear_func)(void *));

void pool_return_obj(void *obj);

size_t pool_mem_size(pool_t *pool);

size_t pool_obj_size(void *obj);

#ifdef __cplusplus
}
#endif

#endif //ZITI_SDK_POOL_H
