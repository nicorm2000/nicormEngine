#ifndef SPACE_H
#define SPACE_H
namespace MikkaiEngine
{
    //
    // Resumen:
    //     The coordinate space in which to operate.
    enum Space
    {
        //
        // Resumen:
        //     Applies transformation relative to the world coordinate system.
        World,
        //
        // Resumen:
        //     Applies transformation relative to the local coordinate system.
        Self
    };
}
#endif // !SPACE_H
