#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Funcionario
	{
	private:
	int prontuario;
    string nome;
	double salario;
	
	
	public:
	Funcionario(int ra,string nome, double sal)
	{
		setProntuario(ra);
		setNome(nome);
		setSalario(sal);   	
	}
	
	Funcionario() {
    prontuario = 0;
    nome = "";
    salario = 0;
}
	
	 void setProntuario(int ra)
	{
		if(ra <= 0){
			throw invalid_argument("insira uma prontuario corretamente");
		}
		prontuario = ra;
	}
	
		 void setNome(string nomeF)
	{
		if(nomeF.empty()){
			throw invalid_argument("insira um nome corretamente");
		}
		nome = nomeF;
	}
	
		 void setSalario(double sal)
	{
			if(sal < 0){
			throw invalid_argument("insira um salario corretamente");
		}
		salario = sal;
	}
	
		 int getProntuario()
		{
			return prontuario;
		}
		
		 string getNome()
		{
			return nome;
		}
		
		 double getSalario()
		{
			return salario;
		}
	
	};
	
	struct Lista {
    Funcionario dado;
    Lista* prox;
};
Lista* find(Lista* lista, int prontuario);

Lista* init() {
    return NULL;
}

Lista* insert(Lista* lista, Funcionario dado) {
    if (find(lista, dado.getProntuario()) != NULL) {
        cout << "Ja existe funcionario com esse prontuario\n";
        return lista;
    }

    Lista* novo = new Lista();
    novo->dado = dado;
    novo->prox = lista;

    return novo;
}

void print(Lista* lista) {
    Lista* aux = lista;
    double total = 0;

    cout << "-----------" << endl;

    while (aux != NULL) {
        cout << "Prontuario: " << aux->dado.getProntuario() << endl;
        cout << "Nome: " << aux->dado.getNome() << endl;
        cout << "Salario: " << aux->dado.getSalario() << endl;
        cout << "------------------" << endl;

        total += aux->dado.getSalario();
        aux = aux->prox;
    }

    cout << "Total de salarios: " << total << endl;
}

Lista* find(Lista* lista, int prontuario) {
    Lista* aux = lista;

    while (aux != NULL) {
        if (aux->dado.getProntuario() == prontuario) {
            return aux;
        }
        aux = aux->prox;
    }

    return NULL;
}

Lista* removeFunc(Lista* lista, int prontuario) {
    Lista* ant = NULL;
    Lista* aux = lista;

    while (aux != NULL && aux->dado.getProntuario() != prontuario) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) return lista;

    if (ant == NULL) {
        lista = aux->prox;
    } else {
        ant->prox = aux->prox;
    }

    delete aux; 
    return lista;
}

void freeLista(Lista* lista) {
    Lista* aux = lista;

    while (aux != NULL) {
        Lista* temp = aux;
        aux = aux->prox;
        delete temp; 
    }
}
int main(int argc, char** argv)
{
	Lista* lista = init();
    int opcao;

    do {
        cout << "\nSelecione uma das opcoes:\n";
        cout << "0. Sair\n";
        cout << "1. Incluir\n";
        cout << "2. Excluir\n";
        cout << "3. Pesquisar\n";
        cout << "4. Listar\n";
        cout << "Opcao: ";

        cin >> opcao;

        switch(opcao) {

        case 1: {
            int p;
            string nome;
            double sal;

            cout << "Prontuario: ";
            cin >> p;

            cin.ignore(); // importante

            cout << "Nome: ";
            getline(cin, nome);

            cout << "Salario: ";
            cin >> sal;

            lista = insert(lista, Funcionario(p, nome, sal));
            break;
        }

        case 2: {
            int p;
            cout << "Digite o prontuario para remover: ";
            cin >> p;

            lista = removeFunc(lista, p);
            break;
        }

        case 3: {
            int p;
            cout << "Digite o prontuario para buscar: ";
            cin >> p;

            Lista* resultado = find(lista, p);

            if (resultado != NULL) {
                cout << "Funcionario encontrado:\n";
                cout << "Prontuario: " << resultado->dado.getProntuario() << endl;
                cout << "Nome: " << resultado->dado.getNome() << endl;
                cout << "Salario: " << resultado->dado.getSalario() << endl;
            } else {
                cout << "Funcionario nao encontrado\n";
            }
            break;
        }

        case 4:
            print(lista);
            break;

        case 0:
            cout << "Saindo...\n";
            break;

        default:
            cout << "Opcao invalida!\n";
        }

    } while(opcao != 0);

    freeLista(lista);
	return 0;
}