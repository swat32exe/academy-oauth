#include <Utility.h>

#include <sstream>
#include <iomanip>

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
            std::ostringstream encodedStream;

            for (size_t i = 0; i < data.length(); ++i) {
                if (isUnreservedUrlCharacter(data[i]))
                    encodedStream << data[i];
                else
                    encodedStream << "%" << std::uppercase << std::setfill('0') << std::setw(2)
                        << std::hex << static_cast<unsigned int>(data[i]);
            }
            return encodedStream.str();
        }

        std::string urlDecode(std::string data)
        {
            std::ostringstream decodedStream;

            for (size_t i = 0; i < data.length(); ++i) {
                unsigned int currentCharacter = data[i];
                if (currentCharacter == '%') {
                    std::istringstream encodedChar(data.substr(i + 1, 2));
                    encodedChar >> std::hex >> currentCharacter;
                    i += 2;
                }
                decodedStream << static_cast<char>(currentCharacter);
            }
            return decodedStream.str();
        }
    }
}
