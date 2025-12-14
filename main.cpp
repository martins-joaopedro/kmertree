#include <bits/stdc++.h>
using namespace std;

int main() {

    int N = 2;
    int k = 4;

    ifstream file("instances.txt");
    string line;

    vector<string> instances;
    map<string, vector<int>> kmerFrequency;
    int id = 0;
    while(getline(file, line)) {
        cout << line << "\n";

        instances.push_back(line.substr(0, 15) + "...");

        for(int i=0; i<=line.size() -k; i++) {
            string kmer = line.substr(i, k); 
            cout << kmer << " ";

            if(kmerFrequency[kmer].size() != N)
                kmerFrequency[kmer].resize(N);
            
            if(kmerFrequency[kmer][id] == 0)
                kmerFrequency[kmer][id] = 1;
            else kmerFrequency[kmer][id]++;
        }
        cout << endl;
        id++;
    }

    // cabeçalho
    cout << setw(8) << "kmer";
    for (int i = 0; i < N; i++)
        cout << setw(6) << ("S" + to_string(i));
    cout << "\n";

    // linhas
    for (auto& [kmer, vet] : kmerFrequency) {
        cout << setw(8) << kmer;
        for (int freq : vet)
            cout << setw(6) << freq;
        cout << "\n";
    }
    
    return 0;
}