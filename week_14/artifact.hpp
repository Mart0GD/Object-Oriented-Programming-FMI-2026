#ifndef __ARTIFACT_HPP_INCLUDED__
#define __ARTIFACT_HPP_INCLUDED__

/*
    Интерфейсен клас Артефакт. Дефинира логиката за всеки предмет в играта 
*/

class player; // forward декларация, за да не става кръгова зависимост

class artifact{
public:

    artifact() = default;
    virtual ~artifact() = default;

    virtual void draw() const = 0;
    virtual bool on_player_enter(player& p) = 0;
};

#endif