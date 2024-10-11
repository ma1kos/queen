#include <iostream>
#include <vector>
#include <string.h>

// Шахматная доска `S × S`
int n_sol = 0; char P;
size_t S;

// Функция для проверки, угрожают ли два ферзя друг другу или нет
int isSafe(std::vector<std::vector<char>>&mat, int rows, int cols)
{
    // возвращаем 0, если два ферзя делят один и тот же столбец
    for (int i = 0; i < rows; i++)
    {
        if (mat[i][cols] == 'X') {
            return 0;
        }
    }

    // вернуть 0, если два ферзя делят одну и ту же диагональ
    for (int i = rows, j = cols; i >= 0 && j >= 0; i--, j--)
    {
        if (mat[i][j] == 'X') {
            return 0;
        }
    }

    // вернуть 0, если два ферзя делят одну и ту же диагональ `/`
    for (int i = rows, j = cols; i >= 0 && j < S; i--, j++)
    {
        if (mat[i][j] == 'X') {
            return 0;
        }
    }

    return 1;
}

void printSolution(std::vector<std::vector<char>>& mat)
{
    for (int i = 0; i < S; i++)
    {
        for (int j = 0; j < S; j++) {
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void nQueen(std::vector<std::vector<char>>& mat, int rows)
{
    // если `S` ферзей расставлены успешно, выводим решение
    if (rows == S)
    {
        if (P == 'Y' || P == 'y')
        {
            printSolution(mat);
        }
        n_sol++;
        return;
    }

    // помещаем ферзя на каждую клетку в текущем столбце `cols`
    // и повторяться для каждого допустимого движения
    for (int j = 0; j < S; j++)
    {
        // если никакие два ферзя не угрожают друг другу
        if (isSafe(mat, rows, j))
        {
            // ставим ферзя на текущую клетку
            mat[rows][j] = 'X';

            // повторить для следующей строки
            nQueen(mat, rows + 1);

            // возвращаемся назад и удаляем ферзя с текущей клетки
            mat[rows][j] = '_';
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    // `mat[][]` отслеживает положение ферзей в текущей конфигурации
    std::cout << "Введите размерность задачи: ";
    std::cin >> S;
    std::vector<std::vector<char>> mat(S);
    for (auto& e : mat)
        e.resize(S);
    std::cout << "Выводить возможные расстановки?(Y/N):";
    std::cin >> P;

    // заполняем `mat[][]` с помощью `-`
    for (int i = 0; i < S; i++)
    {
        for (int j = 0; j < S; j++)
            mat[i][j] = '_';
    }
    nQueen(mat, 0);
    printf("Колличество возможных расстановок: %d\n", n_sol);
    system("pause");
    return 0;
}