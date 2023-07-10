#include <iostream>
#include <fstream>
#include <chrono>
#include "List.h"

using namespace std;

void BubbleSort(List& lst) {
    size_t n = lst.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = n - 1; j > i; --j) {
            if (lst[j] < lst[j - 1]) {
                int aux = lst[j];
                lst[j] = lst[j - 1];
                lst[j - 1] = aux;
            }
        }
    }
}

void gera_dados(const int& num_iteracoes, const int vetor_tam[]) {
    for (int n = 0; n < num_iteracoes; ++n) {
        for (int semente = 0; semente < 5; semente++) {
            string nome_arquivo = "dados/random" + to_string(n) + "_" + to_string(semente) + ".dat";
            ofstream fout(nome_arquivo.c_str(), ios::binary);
            srand(time(NULL));
            int r;
            int tamanho_vetor = vetor_tam[n];
            for (int i = 0; i < tamanho_vetor; i++) {
                r = rand();
                fout.write((char*)&r, sizeof(r));
            }
            fout.close();
        }
    }
}

void ler_dados(List& lst, const char* nomeArquivo) {
    ifstream input_file(nomeArquivo, ios::binary);
    int value;
    while (input_file.read((char*)&value, sizeof(value))) {
        lst.push_back(value);
    }
    input_file.close();
}

int main() {
    const int tam[] = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 };

    const int TOTAL_N = sizeof(tam) / sizeof(tam[0]);

    gera_dados(TOTAL_N, tam);

    ofstream ofs("resultados/resultadoBubble.txt", ofstream::out);

    for (int iteracao = 0; iteracao < TOTAL_N; iteracao++) {
        long double duracao_media_bubble = 0.0;
        const int tamanho_vetor = tam[iteracao];
        List lst;

        for (int semente = 0; semente < 5; semente++) {
            string nome_arquivo = "dados/random" + to_string(iteracao) + "_" + to_string(semente) + ".dat";

            lst.clear();
            ler_dados(lst, nome_arquivo.c_str());

            auto ini = chrono::high_resolution_clock::now();

            lst.BubbleSort();

            auto fim = chrono::high_resolution_clock::now();

            auto duracao_bubble = chrono::duration_cast<chrono::microseconds>(fim - ini).count();

            duracao_media_bubble += duracao_bubble;
        }

        duracao_media_bubble = duracao_media_bubble / 5.0;
        cout << "[Bubble] N = " << tamanho_vetor << ", tempo medio de execucao = " << duracao_media_bubble << " microssegundos" << endl;
        ofs << tamanho_vetor << " " << duracao_media_bubble << "\n";
    }

    ofs.close();

    ofstream ofs("resultados/resultadoInsertionSort.txt", ofstream::out);

    for (int iteracao = 0; iteracao < TOTAL_N; iteracao++) {
        long double duracao_media_insertion = 0.0;
        const int tamanho_vetor = tam[iteracao];
        List lst;

        for (int semente = 0; semente < 5; semente++) {
            string nome_arquivo = "dados/random" + to_string(iteracao) + "_" + to_string(semente) + ".dat";

            lst.clear();
            ler_dados(lst, nome_arquivo.c_str());

            auto ini = chrono::high_resolution_clock::now();

            lst.InsertionSort();

            auto fim = chrono::high_resolution_clock::now();

            auto duracao_bubble = chrono::duration_cast<chrono::microseconds>(fim - ini).count();

            duracao_media_insertion += duracao_bubble;
        }

        duracao_media_insertion = duracao_media_insertion / 5.0;
        cout << "[Insertion] N = " << tamanho_vetor << ", tempo medio de execucao = " << duracao_media_insertion << " microssegundos" << endl;
        ofs << tamanho_vetor << " " << duracao_media_insertion << "\n";
    }

    ofs.close();

    ofstream ofs("resultados/resultadoSelectionSort.txt", ofstream::out);

    for (int iteracao = 0; iteracao < TOTAL_N; iteracao++) {
        long double duracao_media_selection = 0.0;
        const int tamanho_vetor = tam[iteracao];
        List lst;

        for (int semente = 0; semente < 5; semente++) {
            string nome_arquivo = "dados/random" + to_string(iteracao) + "_" + to_string(semente) + ".dat";

            lst.clear();
            ler_dados(lst, nome_arquivo.c_str());

            auto ini = chrono::high_resolution_clock::now();

            lst.SelectionSort();

            auto fim = chrono::high_resolution_clock::now();

            auto duracao_bubble = chrono::duration_cast<chrono::microseconds>(fim - ini).count();

            duracao_media_selection += duracao_bubble;
        }

        duracao_media_selection = duracao_media_selection / 5.0;
        cout << "[SelectionSort] N = " << tamanho_vetor << ", tempo medio de execucao = " << duracao_media_selection << " microssegundos" << endl;
        ofs << tamanho_vetor << " " << duracao_media_selection << "\n";
    }

    ofs.close();

    ofstream ofs("resultados/resultadomerge.txt", ofstream::out);

    for (int iteracao = 0; iteracao < TOTAL_N; iteracao++) {
        long double duracao_media_merge = 0.0;
        const int tamanho_vetor = tam[iteracao];
        List lst;

        for (int semente = 0; semente < 5; semente++) {
            string nome_arquivo = "dados/random" + to_string(iteracao) + "_" + to_string(semente) + ".dat";

            lst.clear();
            ler_dados(lst, nome_arquivo.c_str());

            auto ini = chrono::high_resolution_clock::now();

            lst.mergeSort();

            auto fim = chrono::high_resolution_clock::now();

            auto duracao_bubble = chrono::duration_cast<chrono::microseconds>(fim - ini).count();

            duracao_media_merge += duracao_bubble;
        }

        duracao_media_merge = duracao_media_merge / 5.0;
        cout << "[Bubble] N = " << tamanho_vetor << ", tempo medio de execucao = " << duracao_media_merge << " microssegundos" << endl;
        ofs << tamanho_vetor << " " << duracao_media_merge << "\n";
    }

    ofs.close();



    return 0;
}
