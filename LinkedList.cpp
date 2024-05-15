#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;
typedef struct Node
{
    int iNum;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* newNode(int);
void addNodeFront(Node**,int);
void addNodeEnd(Node**,int);
void addNodeAfter(Node*, Node*,int);
Node* procuraNode(Node*,int);
void showNode(Node*);
void concatenaNode(Node**, Node*);
void removeNode(Node**,int);
void deleteLista(Node**);

int main()
{
    Node* node = nullptr;
    addNodeFront(&node, 1);
    addNodeFront(&node,2);
    addNodeFront(&node,4);
    addNodeFront(&node, 3);
    addNodeFront(&node, 5);
    addNodeEnd(&node, 111);
    
    Node* node1 = nullptr;
    addNodeFront(&node1,10);
    addNodeFront(&node1,12);
    addNodeFront(&node1,13);
    addNodeFront(&node1,14);
    concatenaNode(&node,node1);
    removeNode(&node,13);
    showNode(node);
    deleteLista(&node);
    return 0;
}

Node* newNode(int iValor)
{
    Node* ptrtemp = (Node*)malloc(sizeof(Node)); //aloca memoria 
    ptrtemp->iNum = iValor;
    ptrtemp->ptrNext = nullptr;//atualizando parametros
    ptrtemp->ptrPrev = nullptr;
}

void addNodeFront(Node** head, int iValor)
{
    Node* ptrtemp = newNode(iValor);
    if((*head) == nullptr)
    {
        (*head) = ptrtemp;//Numa lista vazia adiciona no começo
        return; //para a função se esse if for verdadeiro
    }
    //se o if não for verdade 
    ptrtemp->ptrNext = (*head);
    (*head)->ptrPrev = ptrtemp;
    (*head) = ptrtemp;//atualizando todos os parametros
}

void addNodeEnd(Node** head, int iValor)
{
    Node* ptrtemp = newNode(iValor);
    if((*head) == nullptr)
    {
        (*head) = ptrtemp;//como a lista é vazia adicionamos no começo
        return;
    }
    Node* current = (*head);
    while(current ->ptrNext != nullptr) current = current->ptrNext; // levando o ponteiro para o final
    current->ptrNext = ptrtemp;
    ptrtemp->ptrPrev = current;//atualizando os parametros
}

void addNodeAfter(Node* head,Node* node, int iValor)
{
    Node* ptrtemp = newNode(iValor);
    if(head == nullptr || node == nullptr)
    {
        cout<<"Entrada iválida"<<endl;//verifica se a pessoa passou uma lista válida
        return;
    }

    ptrtemp->ptrNext = node->ptrNext;
    ptrtemp->ptrPrev = node;
    node->ptrNext->ptrPrev = ptrtemp;
    node->ptrNext = ptrtemp; //atualiza os parametros

}

Node* procuraNode(Node* head, int iValor)
{
    if(head == nullptr) return head; //verificando se o primeiro no é nulo

    Node* current = head; //inicia um no que vai percorrer a lista
    while(current != nullptr && current->iNum != iValor) current = current->ptrNext;

    if(current == nullptr)
    {
        cout<<"elemento não encontrado"<<endl;
        return current;//como o elemento não foi encontrado vamos retornar um ponteriro nulo
    }

    return current; // se o elemento for achado sera retornado
}

void showNode(Node* head)
{
    if(head == nullptr)
    {
        cout<<"Lista vazia"<<endl;
        return; 
    }
    Node* current = head;
    cout<<"Elementos:   "<<endl;
    while(current != nullptr) 
    {
        cout<<" "<<current->iNum;// printa os elementos da lista
        current = current->ptrNext;
    }
    cout<<endl; 
}

void concatenaNode(Node** head, Node* node)
{
    if((*head) == nullptr)
    {
        (*head) = node;//se a primira lista é vazia só retorna a segunda lista
        return;
    }
    else if(node == nullptr)
    {
        return; // como o restante da lista que quer adicionar é nula não precisa adicionar
    }
    Node* current = (*head);

    while(current->ptrNext != nullptr) current = current->ptrNext;//leva o ponteiro pro final

    current->ptrNext = node; 
}

void removeNode(Node** head, int iValor)
{
    Node* ptrTemp = procuraNode((*head), iValor);
    if((*head) == ptrTemp)
    {
        (*head) = (*head)->ptrNext;//como o elemento que queremos remover esta no começo só trocamos
        free(ptrTemp);//limpando a memoria
        return;
    }
    
    ptrTemp->ptrPrev->ptrNext = ptrTemp->ptrNext;
    ptrTemp->ptrNext->ptrPrev = ptrTemp->ptrPrev;
    free(ptrTemp);
}

void deleteLista(Node** head)
{
    if((*head) == nullptr)
    {
        cout<<"Lista vazia"<<endl;
        return; //se a lista ta vazia não vamos apagar ela 
    }

    while((*head) != nullptr)
    {
        Node* ptrTemp = (*head); //salva o nó que será apagado
        (*head) = (*head)->ptrNext;
        free(ptrTemp);
    }

    if((*head) == nullptr)
    {
        cout<<"Lista apagada"<<endl;
    }
}