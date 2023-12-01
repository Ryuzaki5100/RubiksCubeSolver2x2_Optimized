#include <bits/stdc++.h>
using namespace std;
typedef vector<int> cornerPos;
typedef vector<int> cornerOrientation;
typedef pair<cornerPos, cornerOrientation> Cube;
map<char, cornerPos> nextCornerPos = {{'R', {0, 5, 1, 3, 4, 6, 2, 7}},
                                      {'U', {1, 2, 3, 0, 4, 5, 6, 7}},
                                      {'F', {0, 1, 6, 2, 4, 5, 7, 3}},
                                      {'B', {4, 0, 2, 3, 5, 1, 6, 7}},
                                      {'L', {3, 1, 2, 7, 0, 5, 6, 4}},
                                      {'D', {0, 1, 2, 3, 7, 4, 5, 6}}};
map<char, vector<map<int, int>>> nextCornerOrientation = {{'R', {{{-1, -1}, {2, 2}, {3, 3}}, {{1, 1}, {2, -3}, {3, 2}}, {{1, 1}, {-2, 3}, {3, 2}}, {{-1, -1}, {-2, -2}, {3, 3}}, {{-1, -1}, {2, 2}, {-3, -3}}, {{1, 1}, {2, -3}, {-3, -2}}, {{1, 1}, {-2, 3}, {-3, -2}}, {{-1, -1}, {-2, -2}, {-3, -3}}}},
                                                          {'U', {{{-1, 2}, {2, 1}, {3, 3}}, {{1, -2}, {2, 1}, {3, 3}}, {{1, -2}, {-2, -1}, {3, 3}}, {{-1, 2}, {-2, -1}, {3, 3}}, {{-1, -1}, {2, 2}, {-3, -3}}, {{1, 1}, {2, 2}, {-3, -3}}, {{1, 1}, {-2, -2}, {-3, -3}}, {{-1, -1}, {-2, -2}, {-3, -3}}}},
                                                          {'F', {{{-1, -1}, {2, 2}, {3, 3}}, {{1, 1}, {2, 2}, {3, 3}}, {{1, -3}, {-2, -2}, {3, 1}}, {{-1, 3}, {-2, -2}, {3, 1}}, {{-1, -1}, {2, 2}, {-3, -3}}, {{1, 1}, {2, 2}, {-3, -3}}, {{1, -3}, {-2, -2}, {-3, -1}}, {{-1, 3}, {-2, -2}, {-3, -1}}}},
                                                          {'B', {{{-1, -3}, {2, 2}, {3, -1}}, {{1, 3}, {2, 2}, {3, -1}}, {{1, 1}, {-2, -2}, {3, 3}}, {{-1, -1}, {-2, -2}, {3, 3}}, {{-1, -3}, {2, 2}, {-3, 1}}, {{1, 3}, {2, 2}, {-3, 1}}, {{1, 1}, {-2, -2}, {-3, -3}}, {{-1, -1}, {-2, -2}, {-3, -3}}}},
                                                          {'L', {{{-1, -1}, {2, 3}, {3, -2}}, {{1, 1}, {2, 2}, {3, 3}}, {{1, 1}, {-2, -2}, {3, 3}}, {{-1, -1}, {-2, -3}, {3, -2}}, {{-1, -1}, {2, 3}, {-3, 2}}, {{1, 1}, {2, 2}, {-3, -3}}, {{1, 1}, {-2, -2}, {-3, -3}}, {{-1, -1}, {-2, -3}, {-3, 2}}}},
                                                          {'D', {{{-1, -1}, {2, 2}, {3, 3}}, {{1, 1}, {2, 2}, {3, 3}}, {{1, 1}, {-2, -2}, {3, 3}}, {{-1, -1}, {-2, -2}, {3, 3}}, {{-1, -2}, {2, -1}, {-3, -3}}, {{1, 2}, {2, -1}, {-3, -3}}, {{1, 2}, {-2, 1}, {-3, -3}}, {{-1, -2}, {-2, 1}, {-3, -3}}}}};
cornerPos SOLVED_CORNER_POS = {0, 1, 2, 3, 4, 5, 6, 7};
cornerOrientation SOLVED_CORNER_ORIENTATION = {3, 3, 3, 3, -3, -3, -3, -3};
Cube Execute(Cube c, string s)
{
    Cube temp = c;
    for (auto i : s)
        for (int j = 0; j < 8; j++)
            temp.second[j] = nextCornerOrientation[i][temp.first[j]][temp.second[j]],
            temp.first[j] = nextCornerPos[i][temp.first[j]];
    return temp;
}
vector<string> algProcessor(string moves)
{
    stack<pair<char, int>> s;
    vector<string> v = {"", "", "2", "'"}, result;
    for (auto i : moves)
    {
        if (s.empty() || s.top().first != i)
            s.push({i, 1});
        else
        {
            auto x = s.top();
            s.pop();
            if (x.second != 3)
                s.push({x.first, x.second + 1});
        }
    }
    while (!s.empty())
    {
        auto x = s.top();
        if (x.second)
            result.insert(begin(result), x.first + v[x.second]);
        s.pop();
    }
    return result;
}
vector<int> convert(Cube c)
{
    vector<int> v;
    for (auto i : c.first)
        v.push_back(i);
    for (auto i : c.second)
        v.push_back(i);
    return v;
}
string reverseAlgorithm(string s)
{
    string result = "";
    for (auto i : s)
        for (int j = 0; j < 3; j++)
            result += i;
    reverse(result.begin(), result.end());
    return result;
}
vector<string> solve(Cube c)
{
    Cube source = c, destination = {SOLVED_CORNER_POS, SOLVED_CORNER_ORIENTATION};
    if (c == destination)
        return {};
    vector<string> operations = {"R", "U", "F", "RRR", "UUU", "FFF"};
    queue<pair<Cube, string>> forward, backward;
    map<vector<int>, string> f_sol, b_sol;
    f_sol[convert(source)] = b_sol[convert(destination)] = "";
    forward.push({source, ""});
    backward.push({destination, ""});
    while (true)
    {
        auto f = forward.front();
        forward.pop();
        for (auto i : operations)
        {
            Cube temp = Execute(f.first, i);
            vector<int> x = convert(temp);
            if (b_sol.count(x))
                return algProcessor(f.second + i + reverseAlgorithm(b_sol[x]));
            if (!f_sol.count(x))
            {
                f_sol[x] = f.second + i;
                forward.push({temp, f.second + i});
            }
        }
        auto b = backward.front();
        backward.pop();
        for (auto i : operations)
        {
            Cube temp = Execute(b.first, i);
            vector<int> x = convert(temp);
            if (f_sol.count(x))
                return algProcessor(f_sol[x] + reverseAlgorithm(b.second + i));
            if (!b_sol.count(x))
            {
                b_sol[x] = b.second + i;
                backward.push({temp, b.second + i});
            }
        }
    }
}
int main()
{
    string input;
    cin >> input;
    Cube c = {SOLVED_CORNER_POS, SOLVED_CORNER_ORIENTATION};
    c = Execute(c, input);
    vector<string> result = solve(c);
    for (auto i : result)
        cout << i << " ";
}