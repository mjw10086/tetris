#ifndef __TETROMINOES_H__
#define __TETROMINOES_H__

#include <key_value.h>
#include <functional>

enum TETROMINOES_TYPE
{
    TYPE_I,
    TYPE_J,
    TYPE_L,
    TYPE_O,
    TYPE_S,
    TYPE_T,
    TYPE_Z
};

// x = 0 x = 1 x = 2 ...
// ------------------------
// |                      | y = 0
// |                      | y = 1
// |                      | y = 2
// |                      |   .
// |                      |   .
// |                      |   .
// ------------------------
class Tetrominoes
{
public:
    int m_shape[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}}; // store coord 0-x 1-y

protected:
    void __filp();
    void __undo_filp();

public:
    Tetrominoes(){};
    ~Tetrominoes(){};

    static Tetrominoes *create(TETROMINOES_TYPE type);

    void drop();
    void move(KEYVALUE key);

    virtual void filp() = 0;
    virtual void undo_filp() = 0;
};

/* 子类 */
///////////////////////////////////////////////////////
class Tetrominoes_I : public Tetrominoes
{
private:
    int status = 0;

public:
    Tetrominoes_I();
    void filp() override;
    void undo_filp() override;
};

class Tetrominoes_J : public Tetrominoes
{
public:
    Tetrominoes_J();
    void filp() override;
    void undo_filp() override;
};

class Tetrominoes_L : public Tetrominoes
{
public:
    Tetrominoes_L();
    void filp() override;
    void undo_filp() override;
};

class Tetrominoes_O : public Tetrominoes
{
public:
    Tetrominoes_O();
    void filp() override;
    void undo_filp() override;
};

class Tetrominoes_S : public Tetrominoes
{
public:
    Tetrominoes_S();
    void filp() override;
    void undo_filp() override;
};

class Tetrominoes_T : public Tetrominoes
{
public:
    Tetrominoes_T();
    void filp() override;
    void undo_filp() override;
};

class Tetrominoes_Z : public Tetrominoes
{
public:
    Tetrominoes_Z();
    void filp() override;
    void undo_filp() override;
};

#endif