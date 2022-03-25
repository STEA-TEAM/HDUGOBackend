//
// Created by Parti on 2021/2/3.
//

#include <controllers/User_HTTP.h>

using namespace hdugo::api::v1;
using namespace hdugo::utils;
using namespace drogon;
using namespace std;

void User::loginAccount(const HttpRequestPtr &req, function<void(const drogon::HttpResponsePtr &)> &&callback) {
    HttpStatusCode code = HttpStatusCode::k200OK;
    Json::Value request, response;
    string parseError = http::toJson(req, request);
    if (!parseError.empty()) {
        code = k400BadRequest;
        response["type"] = "Error";
        response["reason"] = "Wrong format: " + parseError;
        http::fromJson(code, response, callback);
        return;
    }
    response = _service.loginAccount(code, request);
    http::fromJson(code, response, callback);
}

void User::getUserInfo(const HttpRequestPtr &req, function<void(const drogon::HttpResponsePtr &)> &&callback) {
    HttpStatusCode code = HttpStatusCode::k200OK;
    Json::Value request, response;
    string parseError = http::toJson(req, request);
    if (!parseError.empty()) {
        code = k400BadRequest;
        response["type"] = "Error";
        response["reason"] = "Wrong format: " + parseError;
        http::fromJson(code, response, callback);
        return;
    }
    response = _service.getUserBrief(code, request);
    http::fromJson(code, response, callback);
}
