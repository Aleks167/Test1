#include <iostream>
#include <vector>
#include <future>

using namespace std;
double mul1(const vector <double> & vec, const vector<vector<double>>& matr2, size_t j)
{
    double sum=0;
    for(size_t i=0; i<vec.size(); i++)
        sum+=vec[i]*matr2[i][j];
    return sum;
}

vector<vector<double>> mul_matr(const vector<vector<double>>& matr1,
                                const vector<vector<double>>& matr2)
{
    vector<vector<double>> matr(matr1.size());
    for(size_t i=0; i<matr.size(); i++)
    {
        matr[i].resize(matr2[0].size());
        for(size_t j=0; j<matr2[0].size(); j++)
          matr[i][j]=mul1(matr1[i], matr2, j);
    }
    return matr;
}

vector<vector<double>> mul_matr2(const vector<vector<double>>& matr1,
                                const vector<vector<double>>& matr2)
{
    vector<vector<double>> matr(matr1.size());
    vector<vector<future<double>>> matr_Fut(matr1.size());
    for(size_t i=0; i<matr.size(); i++)
    {
        matr[i].resize(matr2[0].size());
        matr_Fut[i].resize(matr2[0].size());
        for(size_t j=0; j<matr2[0].size(); j++)
          matr_Fut[i][j]=async(mul1, ref(matr1[i]), ref(matr2), j);
    }
    for(size_t i=0; i<matr.size(); i++)
        for(size_t j=0; j<matr[i].size(); j++) // Здесь была ошибка вместо j++ было i++
            matr[i][j]=matr_Fut[i][j].get();
    return matr;
}
void print(const vector<vector<double>>& matr)
{
    for(const auto & pos: matr)
    {
        for(auto pos2: pos)
            cout<<pos2<<' ';
        cout<<endl;
    }
}

int main()
{
    vector<vector<double>> matr1={{1, 2, 3}, {2, 4, 1}}; // 2 x 3
    vector<vector<double>> matr2={{1, 2, 3}, {2, 4, 1}, {2, 2, 1}}; // 3 x 3
    // 2 x 3 = 6
  //  cout << "Hello World!" << endl;
    vector<vector<double>> matr;
    matr=mul_matr2(matr1, matr2);
    print(matr);
    return 0;
}
