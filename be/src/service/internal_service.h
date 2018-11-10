// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include "common/status.h"
#include "gen_cpp/internal_service.pb.h"
#include "gen_cpp/palo_internal_service.pb.h"
#include "util/thread_pool.hpp"

namespace brpc {
class Controller;
}

namespace doris {

class ExecEnv;

template<typename T>
class PInternalServiceImpl : public T {
public:
    PInternalServiceImpl(ExecEnv* exec_env);
    virtual ~PInternalServiceImpl();

    void transmit_data(::google::protobuf::RpcController* controller,
                       const ::doris::PTransmitDataParams* request,
                       ::doris::PTransmitDataResult* response,
                       ::google::protobuf::Closure* done) override;

    void exec_plan_fragment(
        google::protobuf::RpcController* controller,
        const PExecPlanFragmentRequest* request,
        PExecPlanFragmentResult* result,
        google::protobuf::Closure* done) override;

    void cancel_plan_fragment(
        google::protobuf::RpcController* controller,
        const PCancelPlanFragmentRequest* request,
        PCancelPlanFragmentResult* result,
        google::protobuf::Closure* done) override;

    void fetch_data(
        google::protobuf::RpcController* controller,
        const PFetchDataRequest* request,
        PFetchDataResult* result,
        google::protobuf::Closure* done) override;

    void tablet_writer_open(google::protobuf::RpcController* controller,
                            const PTabletWriterOpenRequest* request,
                            PTabletWriterOpenResult* response,
                            google::protobuf::Closure* done) override;

    void tablet_writer_add_batch(google::protobuf::RpcController* controller,
                                 const PTabletWriterAddBatchRequest* request,
                                 PTabletWriterAddBatchResult* response,
                                 google::protobuf::Closure* done) override;

    void tablet_writer_cancel(google::protobuf::RpcController* controller,
                              const PTabletWriterCancelRequest* request,
                              PTabletWriterCancelResult* response,
                              google::protobuf::Closure* done) override;

    void fetch_fragment_exec_infos(
        google::protobuf::RpcController* controller,
        const PFetchFragmentExecInfoRequest* request,
        PFetchFragmentExecInfosResult* result,
        google::protobuf::Closure* done) override;

private:
    Status _exec_plan_fragment(brpc::Controller* cntl);
private:
    ExecEnv* _exec_env;
    ThreadPool _tablet_worker_pool;
};

}
