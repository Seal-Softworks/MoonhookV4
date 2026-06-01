#include "webhook.hpp"
#include <curl/curl.h>
#include <iostream>

namespace moon {

class CurlGlobal {
public:
    CurlGlobal() {
        curl_global_init(CURL_GLOBAL_ALL);
    }
    ~CurlGlobal() {
        curl_global_cleanup();
    }
};

static CurlGlobal g_curl_global;

nlohmann::json Webhook::Embed::to_json() const {
    nlohmann::json j;
    if (!title.empty()) j["title"] = title;
    if (!description.empty()) j["description"] = description;
    j["color"] = color;
    if (!footer.empty()) j["footer"]["text"] = footer;
    if (!thumbnail.empty()) j["thumbnail"]["url"] = thumbnail;
    if (!image.empty()) j["image"]["url"] = image;

    if (!fields.empty()) {
        for (const auto& field : fields) {
            j["fields"].push_back({
                {"name", field.name},
                {"value", field.value},
                {"inline", field.is_inline}
            });
        }
    }
    return j;
}

Webhook::Webhook(const std::string& url) : m_url(url) {}

void Webhook::set_proxy(const std::string& proxy) {
    m_proxy = proxy;
}

const std::string& Webhook::get_proxy() const {
    return m_proxy;
}

const std::string& Webhook::last_error() const {
    return m_last_error;
}

int Webhook::retry_after_ms() const {
    return m_retry_after_ms;
}

bool Webhook::send(const std::string& content) {
    return send(content, {});
}

bool Webhook::send(const Embed& embed) {
    return send("", {embed});
}

bool Webhook::send(const std::string& content, const std::vector<Embed>& embeds) {
    nlohmann::json payload;
    if (!content.empty()) payload["content"] = content;
    
    for (const auto& embed : embeds) {
        payload["embeds"].push_back(embed.to_json());
    }

    std::string payload_str = payload.dump();

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize cURL" << std::endl;
        return false;
    }

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, m_url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)payload_str.size());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    if (!m_proxy.empty()) {
        curl_easy_setopt(curl, CURLOPT_PROXY, m_proxy.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
    }

    std::string response_body;
    auto write_callback = [](char* data, size_t size, size_t nmemb, void* clientdata) -> size_t {
        reinterpret_cast<std::string*>(clientdata)->append(data, size * nmemb);
        return size * nmemb;
    };
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

    CURLcode res = curl_easy_perform(curl);
    long response_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

    bool success = false;
    m_retry_after_ms = 0;
    if (res != CURLE_OK) {
        m_last_error = std::string("cURL error: ") + curl_easy_strerror(res);
    } else {
        if (response_code == 204 || response_code == 200) {
            m_last_error.clear();
            success = true;
        } else if (response_code == 429) {
            double retry_after_secs = 1.0;
            try {
                auto j = nlohmann::json::parse(response_body);
                if (j.contains("retry_after")) {
                    retry_after_secs = j["retry_after"].get<double>();
                }
            } catch (...) {}
            m_retry_after_ms = static_cast<int>(retry_after_secs * 1000.0) + 50;
            m_last_error = "Rate limited (429) — retry after " + std::to_string(m_retry_after_ms) + "ms";
        } else {
            m_last_error = "HTTP " + std::to_string(response_code) + ": " + response_body;
        }
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return success;
}

bool Webhook::set_name(const std::string& name)
{
    CURL* curl = curl_easy_init();
    if (!curl)
    {
        m_last_error = "Failed to init cURL";
        return false;
    }

    nlohmann::json payload;
    payload["name"] = name;

    std::string payload_str = payload.dump();

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    std::string url = m_url;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)payload_str.size());

    std::string response;

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
        +[](char* data, size_t size, size_t nmemb, void* userdata) -> size_t {
            reinterpret_cast<std::string*>(userdata)->append(data, size * nmemb);
            return size * nmemb;
        });

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    long code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
    {
        m_last_error = curl_easy_strerror(res);
        return false;
    }

    if (code != 200)
    {
        m_last_error = "HTTP " + std::to_string(code) + ": " + response;
        return false;
    }

    m_name = name;
    m_last_error.clear();
    return true;
}

} // namespace moon