#include "MyThread.h"

using namespace std;

MyThread::MyThread(pthread_t ident)
{
    this->id = ident;
}

void MyThread::setId(pthread_t ident)
{
    this->id = ident;
}

pthread_t MyThread::getId()
{
    return this->id;
}

const vector<Client*>  &MyThread::getTabClient() const
{
    return this->tabClient;
}

void            MyThread::addClient(Client *c)
{
       this->tabClient.push_back(c);

}

void            MyThread::removeClient(int indice)
{
    delete this->tabClient[indice];
    this->tabClient.erase(this->tabClient.begin() + indice);
}

MyThread::~MyThread()
{
}
