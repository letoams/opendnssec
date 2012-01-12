#ifndef _KEYSTATE_ZONE_DEL_CMD_H_
#define _KEYSTATE_ZONE_DEL_CMD_H_

#include "daemon/engine.h"

#ifdef __cplusplus
extern "C" {
#endif

void help_zone_del_cmd(int sockfd);

int handled_zone_del_cmd(int sockfd, engine_type* engine, const char *buf,
                          ssize_t n);

#ifdef __cplusplus
}
#endif

#endif
