#pragma once

#include "Entity.h"
#include <ctime>

class Fighter : public Entity
{
protected:
    bool alive, invulnerable, flashing, nuke, rapid_fire;
    int score, lives, active_lasers;
    time_t respawn_time, invulnerability_time, invulnerability_flash_time, rapid_fire_time;
    static const char GRAPHIC[];
public:
    static const int MAX_LASERS = 4;
    static const int MAX_LIVES = 3;

    Fighter(const short, const short);
    ~Fighter();

    void think();

    void updatePos(const short, const short);
    void updateScore(const int);
    void updateLives(const int);
    void updateActiveLasers(const int);

    int getScore() const;
    int getLives() const;
    int getActiveLasers() const;
    const COORD& getPos() const;

    bool isAlive() const;
    bool isInvulnerable() const;
    bool isNuking() const;
    bool isRapidFiring() const;

    void kill();
    void spawn();
    void setNuke(const bool);
    void setInvulnerable(const int);
    void setRapidFire(const int);
};