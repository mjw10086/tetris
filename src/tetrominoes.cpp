#include <tetrominoes.h>
#include <iostream>
#include <consts.h>

Tetrominoes_I::Tetrominoes_I()
{
    int mid_x = X_COUNT / 2;
    int arr[4][2] = {{mid_x - 2, 0}, {mid_x - 1, 0}, {mid_x, 0}, {mid_x + 1, 0}};
    for (int i = 0; i < 4; i++)
    {
        m_shape[i][0] = arr[i][0];
        m_shape[i][1] = arr[i][1];
    }
}

void Tetrominoes_I::filp()
{
    if (status == 0)
    {
        m_shape[0][0] = m_shape[2][0];
        m_shape[0][1] = m_shape[2][1] + 2;
        m_shape[1][0] = m_shape[2][0];
        m_shape[1][1] = m_shape[2][1] + 1;
        m_shape[3][0] = m_shape[2][0];
        m_shape[3][1] = m_shape[2][1] - 1;
        status = 1;
    }
    else if (status == 1)
    {
        m_shape[0][0] = m_shape[1][0] - 2;
        m_shape[0][1] = m_shape[1][1];
        m_shape[2][0] = m_shape[1][0] - 1;
        m_shape[2][1] = m_shape[1][1];
        m_shape[3][0] = m_shape[1][0] + 1;
        m_shape[3][1] = m_shape[1][1];
        status = 2;
    }
    else if (status == 2)
    {
        m_shape[0][0] = m_shape[2][0];
        m_shape[0][1] = m_shape[2][1] + 1;
        m_shape[1][0] = m_shape[2][0];
        m_shape[1][1] = m_shape[2][1] - 1;
        m_shape[3][0] = m_shape[2][0];
        m_shape[3][1] = m_shape[2][1] - 2;
        status = 3;
    }
    else if (status == 3)
    {
        m_shape[0][0] = m_shape[1][0] - 1;
        m_shape[0][1] = m_shape[1][1];
        m_shape[2][0] = m_shape[1][0] + 1;
        m_shape[2][1] = m_shape[1][1];
        m_shape[3][0] = m_shape[1][0] + 2;
        m_shape[3][1] = m_shape[1][1];
        status = 0;
    }
}

void Tetrominoes_I::undo_filp()
{
    if (status == 0)
    {
        m_shape[0][0] = m_shape[1][0];
        m_shape[0][1] = m_shape[1][1] - 1;
        m_shape[2][0] = m_shape[1][0];
        m_shape[2][1] = m_shape[1][1] + 1;
        m_shape[3][0] = m_shape[1][0];
        m_shape[3][1] = m_shape[1][1] + 2;
        status = 3;
    }
    else if (status == 3)
    {
        m_shape[0][0] = m_shape[2][0] - 1;
        m_shape[0][1] = m_shape[2][1];
        m_shape[1][0] = m_shape[2][0] + 1;
        m_shape[1][1] = m_shape[2][1];
        m_shape[3][0] = m_shape[2][0] + 2;
        m_shape[3][1] = m_shape[2][1];
        status = 2;
    }
    else if (status == 2)
    {
        m_shape[0][0] = m_shape[1][0];
        m_shape[0][1] = m_shape[1][1] + 1;
        m_shape[2][0] = m_shape[1][0];
        m_shape[2][1] = m_shape[1][1] - 1;
        m_shape[3][0] = m_shape[1][0];
        m_shape[3][1] = m_shape[1][1] - 2;
        status = 1;
    }
    else if (status == 1)
    {
        m_shape[0][0] = m_shape[2][0] - 2;
        m_shape[0][1] = m_shape[2][1];
        m_shape[1][0] = m_shape[2][0] - 1;
        m_shape[1][1] = m_shape[2][1];
        m_shape[3][0] = m_shape[2][0] + 1;
        m_shape[3][1] = m_shape[2][1];
        status = 0;
    }
}

Tetrominoes_J::Tetrominoes_J()
{
    int mid_x = X_COUNT / 2;
    int arr[4][2] = {{mid_x - 1, 0}, {mid_x - 2, 0}, {mid_x, 0}, {mid_x - 2, -1}};
    for (int i = 0; i < 4; i++)
    {
        m_shape[i][0] = arr[i][0];
        m_shape[i][1] = arr[i][1];
    }
}

void Tetrominoes_J::filp()
{
    __filp();
}

void Tetrominoes_J::undo_filp()
{
    __undo_filp();
}

Tetrominoes_L::Tetrominoes_L() : Tetrominoes()
{
    int mid_x = X_COUNT / 2;
    int arr[4][2] = {{mid_x - 1, 0}, {mid_x - 2, 0}, {mid_x, 0}, {mid_x, -1}};
    for (int i = 0; i < 4; i++)
    {
        m_shape[i][0] = arr[i][0];
        m_shape[i][1] = arr[i][1];
    }
}

void Tetrominoes_L::filp()
{
    __filp();
}

void Tetrominoes_L::undo_filp()
{
    __undo_filp();
}

Tetrominoes_O::Tetrominoes_O() : Tetrominoes()
{
    int mid_x = X_COUNT / 2;
    int arr[4][2] = {{mid_x, -2}, {mid_x - 1, -2}, {mid_x, -1}, {mid_x - 1, -1}};
    for (int i = 0; i < 4; i++)
    {
        m_shape[i][0] = arr[i][0];
        m_shape[i][1] = arr[i][1];
    }
}

void Tetrominoes_O::filp()
{
}

void Tetrominoes_O::undo_filp()
{
}

Tetrominoes_S::Tetrominoes_S() : Tetrominoes()
{
    int mid_x = X_COUNT / 2;
    int arr[4][2] = {{mid_x - 1, -1}, {mid_x, -2}, {mid_x - 1, -2}, {mid_x - 2, -1}};
    for (int i = 0; i < 4; i++)
    {
        m_shape[i][0] = arr[i][0];
        m_shape[i][1] = arr[i][1];
    }
}

void Tetrominoes_S::filp()
{
    __filp();
}

void Tetrominoes_S::undo_filp()
{
    __undo_filp();
}

Tetrominoes_T::Tetrominoes_T() : Tetrominoes()
{
    int mid_x = X_COUNT / 2;
    int arr[4][2] = {{mid_x - 1, -1}, {mid_x - 1, -2}, {mid_x - 2, -1}, {mid_x, -1}};
    for (int i = 0; i < 4; i++)
    {
        m_shape[i][0] = arr[i][0];
        m_shape[i][1] = arr[i][1];
    }
}

void Tetrominoes_T::filp()
{
    __filp();
}

void Tetrominoes_T::undo_filp()
{
    __undo_filp();
}

Tetrominoes_Z::Tetrominoes_Z() : Tetrominoes()
{
    int mid_x = X_COUNT / 2;
    int arr[4][2] = {{mid_x - 1, -1}, {mid_x - 2, -2}, {mid_x - 1, -2}, {mid_x, -1}};
    for (int i = 0; i < 4; i++)
    {
        m_shape[i][0] = arr[i][0];
        m_shape[i][1] = arr[i][1];
    }
}

void Tetrominoes_Z::filp()
{
    __filp();
}

void Tetrominoes_Z::undo_filp()
{
    __undo_filp();
}

void Tetrominoes::drop()
{
    for (int i = 0; i < 4; i++)
    {
        m_shape[i][1] += 1;
    }
}

void Tetrominoes::__filp()
{
    int middle[2] = {m_shape[0][0], m_shape[0][1]};

    for (int i = 1; i < 4; i++)
    {
        int x_offset = m_shape[i][0] - middle[0];
        int y_offset = m_shape[i][1] - middle[1];

        m_shape[i][0] = middle[0] - y_offset;
        m_shape[i][1] = middle[1] + x_offset;
    }
}

void Tetrominoes::__undo_filp()
{
    int middle[2] = {m_shape[0][0], m_shape[0][1]};

    for (int i = 1; i < 4; i++)
    {
        int x_offset = m_shape[i][0] - middle[0];
        int y_offset = m_shape[i][1] - middle[1];

        m_shape[i][0] = middle[0] + y_offset;
        m_shape[i][1] = middle[1] - x_offset;
    }
}

void Tetrominoes::move(KEYVALUE key)
{
    for (auto shape : m_shape)
    {
        switch (key)
        {
        case RIGHT:
                ++shape[0];
            break;

        case LEFT:
                --shape[0];
            break;

        default:
            break;
        }
    }
}

Tetrominoes *Tetrominoes::create(TETROMINOES_TYPE type)
{
    switch (type)
    {
    case TYPE_I:
        return new Tetrominoes_I();
        break;
    case TYPE_J:
        return new Tetrominoes_J();
        break;
    case TYPE_L:
        return new Tetrominoes_L();
        break;
    case TYPE_O:
        return new Tetrominoes_O();
        break;
    case TYPE_S:
        return new Tetrominoes_S();
        break;
    case TYPE_T:
        return new Tetrominoes_T();
        break;
    case TYPE_Z:
        return new Tetrominoes_Z();
        break;

    default:
        return NULL;
    }
}