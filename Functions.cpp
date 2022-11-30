#include "Functions.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int getLines(std::string ff) {
    int count = 0;
    std::string line_str;
    std::fstream strm;
    strm.open(ff, std::ios::in);
    while (getline(strm, line_str))
    {
        count++;
    }
    strm.close();
    return count;
}

int getNON(std::string ff) {
    int count = 0;
    std::string line_str;
    std::fstream strm;
    strm.open(ff, std::ios::in);
    getline(strm, line_str);
    for (int i = 0; i < line_str.length(); i++) {
        if (line_str[i] == ' ') {
            count++;
        }
    }
    strm.close();
    return count + 1;
}

void printResult(std::string ff, int lines, int nums, vector<int> vec) {
    std::fstream strm;
    strm.open(ff, std::ios::out);

    for (int j = 0; j < lines; j++) {
        for (int k = 0; k < nums; k++) {
            strm << std::to_string(vec[0]);
            vec.erase(vec.begin());
            if (k + 1 != nums) {
                strm << ' ';
            }
        }
        if (j + 1 != lines) {
            strm << "\n";
        }
    }
    strm.close();
}

void mul(std::string fa, std::string fb, std::string output) {
    std::fstream aa;
    aa.open(fa, std::ios::in);
    std::fstream bb;
    bb.open(fb, std::ios::in);

    std::string line;
    vector <vector<int>> va;
    vector <vector<int>> vb;
    int num_lines_A = getLines(fa);
    int num_nums_A = getNON(fa);
    int num_lines_B = getLines(fb);
    int num_nums_B = getNON(fb);
    int counter = 0;
    vector <int> temp;

    while (aa >> line) {
        if (counter == num_nums_A) {
            counter = 0;
            va.push_back(temp);
            temp.clear();
        }
        temp.push_back(stoi(line));
        counter++;
    }

    va.push_back(temp);
    temp.clear();
    counter = 0;

    while (bb >> line) {
        if (counter == num_nums_B) {
            counter = 0;
            vb.push_back(temp);
            temp.clear();
        }
        temp.push_back(stoi(line));
        counter++;
    }
    vb.push_back(temp);

    // mtx = row.col
    //a.b x b.c = a.c 
    vector <int> vc;

    // iter thru row of mtx1 and then col of mtx2
    int sol;
    for (int i = 0; i < num_lines_A; i++) {
        for (int j = 0; j < num_nums_B; j++) {
            // go through every row in mtx2
            sol = 0;
            for (int r = 0; r < num_lines_B; r++) {
                sol += vb[r][j] * va[i][r];
                // abxbc = ac; sol should be result of all
            }
        vc.push_back(sol);
        }
    }
    printResult(output, num_lines_A, num_nums_B, vc);
    aa.close();
    bb.close();
}

void add(std::string fa, std::string fb, std::string output) {
    std::string line;
    int num_lines = getLines(fa);
    int num_nums = getNON(fa);
    std::fstream aa;
    aa.open(fa, std::ios::in);
    std::fstream bb;
    bb.open(fb, std::ios::in);

    vector <int> va;
    vector <int> vb;
    while (aa >> line) {
        va.push_back(stoi(line));
    }
    while (bb >> line) {
        vb.push_back(stoi(line));
    }
    vector <int> vc;
    for (int i = 0; i < vb.size(); i++) {
        vc.push_back(va[i] + vb[i]);
    }
    printResult(output, num_lines, num_nums, vc);
    aa.close();
    bb.close();
}

void sub(std::string fa, std::string fb, std::string output) {
    std::string line;
    int num_lines = getLines(fa);
    int num_nums = getNON(fa);
    vector <int> va;
    vector <int> vb;
    vector <int> vc;

    std::fstream aa;
    aa.open(fa, std::ios::in);
    std::fstream bb;
    bb.open(fb, std::ios::in);
    
    while (aa >> line) {
        va.push_back(stoi(line));
    }
    while (bb >> line) {
        vb.push_back(stoi(line));
    }
    for (int i = 0; i < vb.size(); i++) {
        vc.push_back(va[i] - vb[i]);
    }
    printResult(output, num_lines, num_nums, vc);
    aa.close();
    bb.close();
}