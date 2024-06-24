#include <iostream>
#include <fstream>
using namespace std;

struct Participante {
    int id;
    string nome;
    int semestre;
    int anoIngresso;
    string curso;
    Participante* avancar;  
};

void inserirParticipante(Participante*& turmaCafe) {
    Participante* novoParticipante = new Participante;

    cout << "Inserir novo participante" << endl;
    cout << "ID: ";
    cin >> novoParticipante->id;
    cin.ignore();
    cout << "Nome: ";
    getline(cin, novoParticipante->nome);
    cout << "Semestre: ";
    cin >> novoParticipante->semestre;
    cout << "Ano de ingresso: ";
    cin >> novoParticipante->anoIngresso;
    cin.ignore();
    cout << "Curso (DSM, SI, GE): ";
    getline(cin, novoParticipante->curso);

    novoParticipante->avancar = turmaCafe;  
    turmaCafe = novoParticipante;

    cout << "Participante inserido com sucesso" << endl;
}

void editarParticipante(Participante* turmaCafe) {
    int id;
    cout << "Digite o ID do participante para ser editado: ";
    cin >> id;

    Participante* atual = turmaCafe;
    while (atual != NULL) {
        if (atual->id == id) {
            cout << "Editar participante (ID: " << id << ")" << endl;
            cin.ignore();
            cout << "Novo Nome (" << atual->nome << "): ";
            getline(cin, atual->nome);
            cout << "Novo Semestre (" << atual->semestre << "): ";
            cin >> atual->semestre;
            cout << "Novo Ano de ingresso (" << atual->anoIngresso << "): ";
            cin >> atual->anoIngresso;
            cin.ignore();
            cout << "Novo Curso (" << atual->curso << "): ";
            getline(cin, atual->curso);

            cout << "Participante atualizado com sucesso" << endl;
            return;
        }
        atual = atual->avancar;  
    }

    cout << "Participante com ID " << id << " nao encontrado." << endl;
}

void lerParticipantesDeArquivo(Participante*& turmaCafe) {
    ifstream arquivo("participantes.txt");
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo participantes.txt" << endl;
        return;
    }

    Participante* ultimo = NULL;
    while (true) {
        Participante* p = new Participante;
        arquivo >> p->id;
        if (arquivo.fail()) {
            delete p;
            break;
        }
        arquivo.ignore();
        getline(arquivo, p->nome, ',');
        arquivo >> p->semestre;
        arquivo.ignore();
        arquivo >> p->anoIngresso;
        arquivo.ignore();
        getline(arquivo, p->curso);

        if (arquivo.fail()) {
            delete p;
            break;
        }

        p->avancar = NULL;  
        if (turmaCafe == NULL) {
            turmaCafe = p;
        } else {
            ultimo->avancar = p;
        }
        ultimo = p;
    }

    arquivo.close();
    cout << "Participantes carregados com sucesso" << endl;
}

void gravarParticipantesEmArquivo(Participante* turmaCafe) {
    ofstream arquivo("participantes.txt");
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo participantes.txt" << endl;
        return;
    }

    Participante* atual = turmaCafe;
    while (atual != NULL) {
        arquivo << atual->id << ","
                << atual->nome << ","
                << atual->semestre << ","
                << atual->anoIngresso << ","
                << atual->curso << endl;
        atual = atual->avancar;  
    }

    arquivo.close();
    cout << "Dados dos participantes gravados com sucesso" << endl;
}

void liberarMemoria(Participante* turmaCafe) {
    while (turmaCafe != NULL) {
        Participante* temp = turmaCafe;
        turmaCafe = turmaCafe->avancar; 
        delete temp;
    }
}

int main() {
    Participante* turmaCafe = NULL;
    int opcao;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Inserir novo participante" << endl;
        cout << "2. Editar participante" << endl;
        cout << "3. Ler participantes de arquivo" << endl;
        cout << "4. Gravar participantes em arquivo" << endl;
        cout << "5. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                inserirParticipante(turmaCafe);
                break;
            case 2:
                editarParticipante(turmaCafe);
                break;
            case 3:
                lerParticipantesDeArquivo(turmaCafe);
                break;
            case 4:
                gravarParticipantesEmArquivo(turmaCafe);
                break;
            case 5:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
        }
    } while (opcao != 5);

    liberarMemoria(turmaCafe);
    
    return 0;
}

