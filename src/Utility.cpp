#include <Utility.h>

#include <stdio.h>

namespace OAuth
{
    namespace Utility
    {
        bool isUnreservedUrlCharacter(int character)
        {
            std::string otherUnreserved = "-._~";
            return isalnum(character) || otherUnreserved.find(character) != std::string::npos;
        }

        std::string urlEncode(std::string data)
        {
            std::string encoded = "";

            // Encoded string will be at least same length.
            encoded.reserve(data.length());

            for (size_t i = 0; i < data.length(); ++i) {
                if (isUnreservedUrlCharacter(data[i]))
                    encoded += data[i];
                else {
                    char buffer[3];
                    sprintf(buffer, "%X", (unsigned int)data[i]);
                    encoded += "%" + std::string(buffer);
                }
            }

            return encoded;
        }

        std::string urlDecode(std::string data)
        {
            std::string decoded = "";

            // In most cases new string will not be much shorter.
            decoded.reserve(data.length());

            for (size_t i = 0; i < data.length(); ++i) {
                unsigned int currentCharacter = data[i];
                if (currentCharacter == '%') {
                    sscanf(data.substr(i+1, 2).c_str(), "%X", &currentCharacter);
                    i += 2;
                }
                decoded += static_cast<char> (currentCharacter);
            }
            return decoded;
        }
    }
}
