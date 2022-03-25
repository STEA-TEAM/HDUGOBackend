//
// Created by Parti on 2021/2/4.
//

#pragma once

#include <drogon/plugins/Plugin.h>
#include <unordered_set>

namespace hdugo::plugins {
    class Configurator : public drogon::Plugin<Configurator> {
    public:
        Configurator() = default;

        void initAndStart(const Json::Value &config) override;

        void shutdown() override;

        [[nodiscard]] bool isSuperusers(const int64_t &uid) const;

        [[nodiscard]] uint64_t getAuthExpire() const;

        [[nodiscard]] uint64_t getVersionCode() const;

        [[nodiscard]] std::string getVersionName() const;

    private:
        uint64_t _authTokenExpireTime{}, _versionCode{};
        std::string _versionName{};
        std::unordered_set<int64_t> _superusers{};
    };
}

