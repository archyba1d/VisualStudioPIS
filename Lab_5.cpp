#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

double solveT(double x)
{
    return pow(x + 1, 0.5) / 2;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    const double h = 0.01, tau = (h * h) / 2.0 - 0.00001, timeFinish = 1.0;
    const int a = 0, b = 1, N = (int)(b - a) / h;
    double timeStart = 0.0;

    ofstream out;

    vector<double> bottom(N + 2), top(N + 2), thermalCoeff(N);

    for (int i = 1; i <= N; i++)
    {
        if (h * i == 0.4)
            bottom[i] = 100.0;
        else
            bottom[i] = 0.0;

        thermalCoeff[i - 1] = solveT(h * i);
    }

    bottom[0] = 0.0;
    bottom[N + 1] = 0.0;

    while (timeStart <= timeFinish)
    {
        for (int i = 1; i <= N; i++)
        {
            top[i] = bottom[i] + ((thermalCoeff[i - 1] * tau) / (h * h)) * (bottom[i + 1] - 2.0 * bottom[i] + bottom[i - 1]);
        }

        timeStart = timeStart + tau;

        top[0] = top[1];

        top[N + 1] = top[N];

        for (int i = 0; i <= N + 1; i++)
            bottom[i] = top[i];


        if ((timeStart >= 0) && (timeStart <= tau))
        {
            out.open("1File.csv");

            for (int i = 1; i <= N; i++)
                out << h * i << ";" << top[i] << endl;

            out.close();
        }

        if ((timeStart >= tau) && (timeStart <= 2 * tau))
        {
            out.open("2File.csv");

            for (int i = 1; i <= N; i++)
                out << h * i << ";" << top[i] << endl;

            out.close();
        }

        if ((timeStart >= 100 * tau) && (timeStart <= 200 * tau))
        {
            out.open("3File.csv");

            for (int i = 1; i <= N; i++)
                out << h * i << ";" << top[i] << endl;

            out.close();
        }

        if ((timeStart >= 1.0) && (timeStart <= 1.0 + tau))
        {
            out.open("4File.csv");

            for (int i = 1; i <= N; i++)
                out << h * i << ";" << top[i] << endl;

            out.close();
        }


    }



    cout << "Количество узлов сетки: " << N << endl;

    cout << "Шаг сетки: " << h << endl;

    cout << "Шаг по времени: " << tau << endl;

    return 0;
}

