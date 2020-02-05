#pragma once

#include "doomdef.h"
#include "helion/util/Math.hpp"

namespace Helion {
    
struct ServerUnlaggedPlayer {
    Vec3Fixed Position{0, 0, 0};
};

class ServerUnlagged {
public:
    // The major index is the player, and the minor index is all the other
    // players from this players POV. Ex: Players[2][4] is the third player
    // view of the fifth player.
    ServerUnlaggedPlayer Players[MAXPLAYERS][MAXPLAYERS];

    ServerUnlagged();

    void Clear();
    void SetSelf(int playerIndex, fixed_t x, fixed_t y, fixed_t z);
    void Set(int playerIndex, int targetPlayerIndex, fixed_t x, fixed_t y, fixed_t z);
};


extern ServerUnlagged ServerUnlag;

}
