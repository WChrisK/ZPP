#include "helion/server/ServerUnlagged.hpp"

namespace Helion {

ServerUnlagged ServerUnlag;


ServerUnlagged::ServerUnlagged() {
    Clear();
}

void ServerUnlagged::Clear() {
    for (int player = 0; player < MAXPLAYERS; player++)
        for (int target = 0; target < MAXPLAYERS; target++)
            Players[player][target].Position = Vec3Fixed(0, 0, 0);
}

void ServerUnlagged::SetSelf(int playerIndex, fixed_t x, fixed_t y, fixed_t z) {
    Players[playerIndex][playerIndex].Position = Vec3Fixed(x, y, z);
}

void ServerUnlagged::Set(int playerIndex, int targetPlayerIndex, fixed_t x, fixed_t y, fixed_t z) {
    Players[playerIndex][targetPlayerIndex].Position = Vec3Fixed(x, y, z);
}

}
