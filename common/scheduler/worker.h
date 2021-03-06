/*
 * Copyright (c) 2009-2018 NLNet Labs.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * The hard workers.
 *
 */

#ifndef DAEMON_WORKER_H
#define DAEMON_WORKER_H

#include "janitor.h"
#include "scheduler/task.h"

struct engine_struct;

typedef struct worker_struct worker_type;
struct worker_struct {
    const char* name;
    schedule_type* taskq;
    janitor_thread_t thread_id;
    int need_to_exit;
    void* context;
    int tasksOutstanding;
    int tasksFailed;
    pthread_cond_t tasksBlocker;
};

/**
 * Create worker.
 * \param[in] num thread number
 * \param[in] type type of worker
 * \return worker_type* created worker
 *
 */
worker_type* worker_create(const char* name, schedule_type* taskq);

/**
 * Start working.
 * \param[in] worker worker to start working
 *
 */
void worker_start(worker_type* worker);

/**
 * Clean up worker.
 * \param[in] worker worker to clean up
 *
 */
void worker_cleanup(worker_type* worker);

#endif /* DAEMON_WORKER_H */
