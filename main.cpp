#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

int main() {

    fs::path dir = "instances";
    int N = distance(fs::directory_iterator(dir), fs::directory_iterator{});
    int k = 21;

    // vetor pra guardar um apelido pra cada sequencia
    vector<string> instances;

    // estrutura que guarda todos os kmers e para cada kmer o vetor que armazena as ocorrencias de cada genoma
    map<string, vector<int>> kmerFrequency;

    // guarda a distancia de cada genoma
    vector<vector<double>> distances(N, vector<double>(N, 0.0));
    
    int id = 0;
    for (const auto& entry : fs::directory_iterator(dir)) {

        if (!entry.is_regular_file())
            continue;

        const fs::path& file_path = entry.path();

        ifstream file(file_path);
        if (!file) {
            std::cerr << "Erro ao abrir: " << file_path << '\n';
            continue;
        }

        string line;
        string filename = file_path.stem().string();

        cout << "Arquivo: " << filename << '\n';

         while(getline(file, line)) {
            // ignora cabeçalho
            if (line.empty() || line[0] == '>')
                continue;

            //cout << line << "\n";

            instances.push_back(line.substr(0, 15) + "...");

            for(int i=0; i<=line.size() -k; i++) {
                string kmer = line.substr(i, k); 
                //cout << id << " ";

                if(kmerFrequency[kmer].size() != N)
                    kmerFrequency[kmer].resize(N);
                
                if(kmerFrequency[kmer][id] == 0)
                    kmerFrequency[kmer][id] = 1;
                else kmerFrequency[kmer][id]++;
            }
            //cout << endl;
        }
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

    // calcula a distancia euclidiana
    for(int i=0; i<N; i++) {
        for(int j=i+1; j<N; j++) {
           double sum = 0.0;
            // pega o kmer e o vetor que guarda todos as ocorrencias
            for (auto& [kmer, vet] : kmerFrequency)
                sum += pow(vet[i] - vet[j], 2);
            distances[i][j] = sqrt(sum);
            distances[j][i] = sqrt(sum);
        }   
    }

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++)
            cout << distances[i][j] << " ";
        cout << endl;
    }
    
    return 0;
}