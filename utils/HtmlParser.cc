//
// Created by Particle_G on 2021/8/6.
//

#include <iostream>
#include <utils/HtmlParser.h>
#include <utils/misc.h>

using namespace hdugo::utils;
using namespace std;

HtmlParser::HtmlParser(const std::string &rawHtml) : _docJson(Json::arrayValue) {
    htmlDocPtr htmlDoc = htmlReadMemory(
            rawHtml.c_str(),
            static_cast<int>(rawHtml.length()),
            "default.html",
            nullptr,
            HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NONET
    );
    _traverse(xmlDocGetRootElement(htmlDoc), _docJson);
    if (_docJson.empty()) {
        _docJson = Json::nullValue;
    }
    xmlFreeDoc(htmlDoc);
    xmlCleanupParser();
}

Json::Value HtmlParser::toJson() const {
    return _docJson;
}

Json::Value HtmlParser::getElements(
        const string &query,
        const HtmlParser::Selector &selector
) {
    Json::Value result = Json::arrayValue;
    _select(
            _docJson,
            result,
            selector,
            [query](const std::string &input) -> bool {
                return query == input;
            }
    );
    if (result.empty()) {
        result = Json::nullValue;
    }
    return result;
}

void HtmlParser::_traverse(
        xmlNode *currentNode,
        Json::Value &json
) const {
    if (currentNode == nullptr) {
        return;
    }
    int index = 0;
    for (xmlNode *tempNode = currentNode; tempNode; tempNode = tempNode->next) {
        bool isValid = false;
        if (tempNode->type == XML_ELEMENT_NODE) {
            json[index]["_name"] = string(reinterpret_cast<const char *>(tempNode->name));
            json[index]["_attributes"] = Json::objectValue;
            auto &attributes = json[index]["_attributes"];
            for (xmlAttr *tempAttr = tempNode->properties; tempAttr; tempAttr = tempAttr->next) {
                auto attributeName = string(reinterpret_cast<const char *>(tempAttr->name));
                if (!attributes.isMember(attributeName)) {
                    if (tempAttr->children) {
                        attributes[attributeName] = string(reinterpret_cast<const char *>(tempAttr->children->content));
                    } else {
                        attributes[attributeName] = Json::nullValue;
                    }
                }
            }
            if (tempNode->children != nullptr) {
                json[index]["_content"] = Json::arrayValue;
            } else {
                json[index]["_content"] = Json::nullValue;
            }
            isValid = true;
        } else if (tempNode->type == XML_TEXT_NODE) {
            string tempContent((char *) tempNode->content);
            if (tempContent.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
                json[index]["_name"] = "plain";
                json[index]["_content"] = tempContent;
                isValid = true;
            }
        }
        if (tempNode->children != nullptr) {
            _traverse(tempNode->children, json[index]["_content"]);
        }
        if (isValid) {
            ++index;
        }
    }
}

void HtmlParser::_select(
        const Json::Value &input,
        Json::Value &output,
        const HtmlParser::Selector &selector,
        const function<bool(const std::string &)> &filter
) const {
    if (input.isArray()) {
        for (const auto &item : input) {
            switch (selector) {
                case Selector::className:
                    if (item["_attributes"]["class"].isString() &&
                        filter(item["_attributes"]["class"].asString())) {
                        output.append(item);
                    }
                    break;
                case Selector::id:
                    if (item["_attributes"]["id"].isString() &&
                        filter(item["_attributes"]["id"].asString())) {
                        output.append(item);
                    }
                    break;
                case Selector::elementName:
                    if (item["_name"].isString() &&
                        filter(item["_name"].asString())) {
                        output.append(item);
                    }
                    break;
                case Selector::attributeName:
                    if (item["_attributes"].isObject()) {
                        bool hasAttribute = false;
                        for (const auto &name: item["_attributes"].getMemberNames()) {
                            if (filter(name)) {
                                hasAttribute = true;
                                break;
                            }
                        }
                        if (hasAttribute) {
                            output.append(item);
                        }
                    }
                    break;
            }
            if (item["_content"].isArray()) {
                _select(
                        item["_content"],
                        output,
                        selector,
                        filter
                );
            }
        }
    } else {
        return;
    }
}


