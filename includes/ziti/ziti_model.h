/*
Copyright (c) 2020 Netfoundry, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

https://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


#ifndef ZITI_SDK_ZITI_MODEL_H
#define ZITI_SDK_ZITI_MODEL_H

#include "model_support.h"

#define ZITI_ID_CFG_MODEL(XX, ...) \
XX(cert, string, none, cert, __VA_ARGS__) \
XX(key, string, none, key, __VA_ARGS__) \
XX(ca, string, none, ca, __VA_ARGS__)

#define ZITI_CONFIG_MODEL(XX, ...) \
XX(controller_url, string, none, ztAPI, __VA_ARGS__) \
XX(id, ziti_id_cfg, none, id, __VA_ARGS__)

#define ZITI_VERSION_MODEL(XX, ...) \
XX(version, string, none, version, __VA_ARGS__) \
XX(revision, string, none, revision, __VA_ARGS__) \
XX(build_date, string, none, buildDate, __VA_ARGS__)

#define ZITI_IDENTITY_MODEL(XX, ...) \
XX(id, string, none, id, __VA_ARGS__) \
XX(name, string, none, name, __VA_ARGS__)\
XX(tags, tag, map, tags, __VA_ARGS__)

#define ZITI_SERVICE_MODEL(XX, ...) \
XX(id, string, none, id, __VA_ARGS__) \
XX(name, string, none, name, __VA_ARGS__) \
XX(permissions, string, array, permissions, __VA_ARGS__) \
XX(perm_flags, int, none, NULL, __VA_ARGS__) \
XX(config, json, map, config, __VA_ARGS__)

#define ZITI_INTERCEPT_MODEL(XX, ...) \
XX(hostname, string, none, hostname, __VA_ARGS__) \
XX(port, int, none, port, __VA_ARGS__)

#define ZITI_SERVER_CFG_V1_MODEL(XX, ...) \
XX(protocol, string, none, protocol, __VA_ARGS__) \
XX(hostname, string, none, hostname, __VA_ARGS__) \
XX(port, int, none, port, __VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

// make sure ziti model functions are properly exported
#ifdef MODEL_API
#undef MODEL_API
#endif
#define MODEL_API ZITI_FUNC

DECLARE_MODEL(ziti_version, ZITI_VERSION_MODEL)

DECLARE_MODEL(ziti_id_cfg, ZITI_ID_CFG_MODEL)

DECLARE_MODEL(ziti_config, ZITI_CONFIG_MODEL)

DECLARE_MODEL(ziti_identity, ZITI_IDENTITY_MODEL)

DECLARE_MODEL(ziti_service, ZITI_SERVICE_MODEL)

DECLARE_MODEL(ziti_intercept, ZITI_INTERCEPT_MODEL)

DECLARE_MODEL(ziti_server_cfg_v1, ZITI_SERVER_CFG_V1_MODEL)

ZITI_FUNC const char *ziti_service_get_raw_config(ziti_service *service, const char *cfg_type);

ZITI_FUNC int ziti_service_get_config(ziti_service *service, const char *cfg_type, void *cfg,
                                      int (*parse_func)(void *, const char *, size_t));

#ifdef __cplusplus
}
#endif

#endif //ZITI_SDK_ZITI_MODEL_H
