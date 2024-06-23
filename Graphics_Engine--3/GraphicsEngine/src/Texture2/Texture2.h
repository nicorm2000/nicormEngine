#ifndef TEXTURE2
#define TEXTURE2
#include <string>
namespace MikkaiEngine
{
    enum class TEXTURE_TYPE
    {
        BASE,
        DIFFUSE,
        SPECULAR
    };

    struct Texture{
        unsigned int id;
        float width;
        float height;
        std::string type;
        std::string path;
    };
}
#endif