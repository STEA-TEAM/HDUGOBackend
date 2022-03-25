//
// Created by Parti on 2021/2/4.
//

#pragma once

#include <drogon/plugins/Plugin.h>

namespace hdugo::plugins {

    class TaskManager : public drogon::Plugin<TaskManager> {
    public:
        TaskManager() = default;

        void initAndStart(const Json::Value &config) override;

        void shutdown() override;
    };

}
