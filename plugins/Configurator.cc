//
// Created by Parti on 2021/2/4.
//

#include <plugins/Configurator.h>

using namespace hdugo::plugins;

void Configurator::initAndStart(const Json::Value &config) {
    if (config.isMember("version") && config["version"].isObject() &&
        config["version"].isMember("name") && config["version"]["name"].isString() &&
        config["version"].isMember("code") && config["version"]["code"].isUInt64()) {
        _versionName = config["version"]["name"].asString();
        _versionCode = config["version"]["code"].asUInt64();
        LOG_INFO << "Running Version: " << _versionName;
    } else {
        LOG_ERROR << R"(Requires unsigned int value "name" and "code" in plugin Configurator's config item "version")";
        abort();
    }
    if (config.isMember("superusers") && config["superusers"].isArray()) {
        for (const auto &superuser : config["superusers"]) {
            _superusers.insert(superuser.asInt64());
        }
    }
    if (config.isMember("tokenExpireTime") && config["tokenExpireTime"].isObject() &&
        config["tokenExpireTime"].isMember("auth") && config["tokenExpireTime"]["auth"].isUInt()) {
        _authTokenExpireTime = config["tokenExpireTime"]["auth"].asUInt();
    } else {
        LOG_ERROR << R"(Requires unsigned int value "auth", "access" and "email" in plugin Configurator's config item "tokenExpireTime")";
        abort();
    }
    LOG_INFO << "Configurator loaded.";
}

void Configurator::shutdown() { LOG_INFO << "Configurator shutdown."; }

bool Configurator::isSuperusers(const int64_t &uid) const { return _superusers.contains(uid); }

uint64_t Configurator::getAuthExpire() const { return _authTokenExpireTime; }

uint64_t Configurator::getVersionCode() const { return _versionCode; }

std::string Configurator::getVersionName() const { return _versionName; }