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
    const int tam[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 
	                   11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 
					   20000};

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

    ofstream ofs1("resultados/resultadoInsertionSort.txt", ofstream::out);

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
        ofs1 << tamanho_vetor << " " << duracao_media_insertion << "\n";
    }

    ofs1.close();

    ofstream ofs2("resultados/resultadoSelectionSort.txt", ofstream::out);

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

            auto duracao_selection = chrono::duration_cast<chrono::microseconds>(fim - ini).count();

            duracao_media_selection += duracao_selection;
        }

        duracao_media_selection = duracao_media_selection / 5.0;
        cout << "[Selection] N = " << tamanho_vetor << ", tempo medio de execucao = " << duracao_media_selection << " microssegundos" << endl;
        ofs2 << tamanho_vetor << " " << duracao_media_selection << "\n";
    }

    ofs2.close();

    ofstream ofs3("resultados/resultadomerge.txt", ofstream::out);

    for (int iteracao = 0; iteracao < TOTAL_N; iteracao++) {
        long double duracao_media_merge = 0.0;
        const int tamanho_vetor = tam[iteracao];
        List lst;

        for (int semente = 0; semente < 5; semente++) {
            string nome_arquivo = "dados/random" + to_string(iteracao) + "_" + to_string(semente) + ".dat";

            lst.clear();
            ler_dados(lst, nome_arquivo.c_str());

            auto ini = chrono::high_resolution_clock::now();

            lst.mergeConfiguration();

            auto fim = chrono::high_resolution_clock::now();

            auto duracao_merge = chrono::duration_cast<chrono::microseconds>(fim - ini).count();

            duracao_media_merge += duracao_merge;
        }

        duracao_media_merge = duracao_media_merge / 5.0;
        cout << "[Merge] N = " << tamanho_vetor << ", tempo medio de execucao = " << duracao_media_merge << " microssegundos" << endl;
        ofs3 << tamanho_vetor << " " << duracao_media_merge << "\n";
    }

    ofs3.close();


    ofstream ofs4("resultados/resultadoquick.txt", ofstream::out);

    for (int iteracao = 0; iteracao < TOTAL_N; iteracao++) {
        long double duracao_media_quick = 0.0;
        const int tamanho_vetor = tam[iteracao];
        List lst;

        for (int semente = 0; semente < 5; semente++) {
            string nome_arquivo = "dados/random" + to_string(iteracao) + "_" + to_string(semente) + ".dat";

            lst.clear();
            ler_dados(lst, nome_arquivo.c_str());

            auto ini = chrono::high_resolution_clock::now();

            lst.quickConfiguration();

            auto fim = chrono::high_resolution_clock::now();

            auto duracao_quick = chrono::duration_cast<chrono::microseconds>(fim - ini).count();

            duracao_media_quick += duracao_quick;
        }

        duracao_media_quick = duracao_media_quick / 5.0;
        cout << "[Quick] N = " << tamanho_vetor << ", tempo medio de execucao = " << duracao_media_quick << " microssegundos" << endl;
        ofs4 << tamanho_vetor << " " << duracao_media_quick << "\n";
    }

    ofs4.close();

    ofstream ofs5("resultados/resultadocounting.txt", ofstream::out);

    for (int iteracao = 0; iteracao < TOTAL_N; iteracao++) {
        long double duracao_media_counting = 0.0;
        const int tamanho_vetor = tam[iteracao];
        List lst;

        for (int semente = 0; semente < 5; semente++) {
            string nome_arquivo = "dados/random" + to_string(iteracao) + "_" + to_string(semente) + ".dat";

            lst.clear();
            ler_dados(lst, nome_arquivo.c_str());

            auto ini = chrono::high_resolution_clock::now();

            lst.countingSort();

            auto fim = chrono::high_resolution_clock::now();

            auto duracao_counting = chrono::duration_cast<chrono::microseconds>(fim - ini).count();

            duracao_media_counting += duracao_counting;
        }

        duracao_media_counting = duracao_media_counting / 5.0;
        cout << "[Counting] N = " << tamanho_vetor << ", tempo medio de execucao = " << duracao_media_counting << " microssegundos" << endl;
        ofs5 << tamanho_vetor << " " << duracao_media_counting << "\n";
    }

    ofs5.close();


    return 0;
}
