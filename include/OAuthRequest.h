#ifndef OAUTHREQUEST_H_
#define OAUTHREQUEST_H_

#include "HttpRequest.h"
#include "ParameterList.h"

namespace OAuth
{
    enum TransmissionType {HEADER, BODY, QUERY};

    class OAuthRequest : public HttpRequest
    {
    public:
        static const std::string OAUTH_PREFIX;
        static const std::string DEFAULT_CONTENT_TYPE;

        OAuthRequest(HttpRequestType httpRequestType, const std::string &url,
                TransmissionType type = HEADER);


        /**
         * Add OAuth parameter to request
         * @param name Name of parameter. It must start with "oauth_" prefix
         * @param value Value of parameter
         */
        void addOAuthParameter(const std::string &name, const std::string &value);

        /**
         * Get all OAuth parameters
         * @returns ParameterList with OAuth authorization parameters
         */
        const ParameterList &getOAuthParameters() const;

    private:
        ParameterList oauthParameters;
        TransmissionType transmissionType;
    };
}
#endif
