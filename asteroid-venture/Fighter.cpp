#include "Fighter.h"

const char Fighter::GRAPHIC[7 * 7] =
{
    ' ', ' ', ' ', 'X', 'X', 'X', 'X',
    ' ', ' ', 'X', 'X', 'X', ' ', ' ',
    ' ', 'X', 'X', 'X', 'X', ' ', ' ',
    'X', 'X', 'X', 'X', 'X', 'X', ' ',
    ' ', 'X', 'X', 'X', 'X', ' ', ' ',
    ' ', ' ', 'X', 'X', 'X', ' ', ' ',
    ' ', ' ', ' ', 'X', 'X', 'X', 'X'
};

Fighter::Fighter(const short _x, const short _y)
: Entity(FIGHTER, _x, _y, 7, 7, GRAPHIC, 0x0A), alive(true), invulnerable(false), flashing(false), 
 nuke(false), rapid_fire(false), score(0), lives(MAX_LIVES), active_lasers(0),
  respawn_time(0), invulnerability_time(0), invulnerability_flash_time(0),
  rapid_fire_time(0)
{}
Fighter::~Fighter() {}

void Fighter::think()
{
    time_t curtick = clock();
    time_t curtime = time(nullptr);
    if (rapid_fire) {
        if (curtime >= rapid_fire_time) {
            rapid_fire = false;
        }
    }
    if (invulnerable) {
        if (curtime >= invulnerability_time) {
            if (flashing) { // Better safe than sorry.
                flashing = false;
                fillBuffer(GRAPHIC, 0x0A);
            }
            invulnerable = false;
        }
        else if (curtick >= invulnerability_flash_time) {
            flashing = !flashing;
            fillBuffer(GRAPHIC, flashing ? 0x09 : 0x0A);
            invulnerability_flash_time = curtick + 250;
        }
    }
    else if (!alive && curtime >= respawn_time) {
        spawn();
    }
}

void Fighter::updatePos(const short _x, const short _y)
{
    position.X += _x, position.Y += _y;
}
void Fighter::updateScore(const int _score)
{
    score += _score;
}
void Fighter::updateLives(const int _lives)
{
    lives += _lives;
}
void Fighter::updateActiveLasers(const int _lasers)
{
    active_lasers = (active_lasers + _lasers) < 0 ? 0 : (active_lasers + _lasers);
}

int Fighter::getScore() const
{
    return score;
}
int Fighter::getLives() const
{
    return lives;
}
int Fighter::getActiveLasers() const
{
    return active_lasers;
}
const COORD& Fighter::getPos() const
{
    return position;
}

bool Fighter::isAlive() const
{
    return alive;
}
bool Fighter::isInvulnerable() const
{
    return invulnerable;
}
bool Fighter::isNuking() const
{
    return nuke;
}
bool Fighter::isRapidFiring() const
{
    return rapid_fire;
}

void Fighter::kill()
{
    alive = false;
    setDraw(false);
    respawn_time = time(nullptr) + 3;
    lives--;
}
void Fighter::spawn()
{
    setInvulnerable(3);
    setDraw(true);
    alive = true;
    active_lasers = 0;
    position.X = 0, position.Y = 23;
}
void Fighter::setNuke(const bool _nuke)
{
    nuke = _nuke;
}
void Fighter::setInvulnerable(const int _time)
{
    invulnerability_time = time(nullptr) + _time;
    invulnerable = true;
}
void Fighter::setRapidFire(const int _time)
{
    rapid_fire_time = time(nullptr) + _time;
    rapid_fire = true;
}