#include <bits/stdc++.h>
using namespace std;

string infixaParaPrefixa( string inf ) {
    reverse( inf.begin(), inf.end() );
    for( int i = 0; i < inf.size(); i++ ) {
        if( inf[i] == '(' ) inf[i] = ')';
        else if( inf[i] == ')' ) inf[i] = '(';
    }
    string pref = "";
    stack<char> pilha;

    for( int i = 0; i < inf.size(); i++ )
        switch( inf[i] ) {
            case '(':
                pilha.push( inf[i] );
                break;
            case ')':
                while( !pilha.empty() && pilha.top() != '(' ) {
                    pref += pilha.top();
                    pilha.pop();
                }
                if( pilha.top() == '(' )
                    pilha.pop();
                break;
            case '+':
            case '-':
                while( !pilha.empty() && ( pilha.top() == '*' || pilha.top() == '/' || pilha.top() == '^' ) ) {
                    pref += pilha.top();
                    pilha.pop();
                }
                pilha.push( inf[i] );
                break;
            case '*':
            case '/':
                while( !pilha.empty() && pilha.top() == '^' ) {
                    pref += pilha.top();
                    pilha.pop();
                }
                pilha.push( inf[i] );
                break;
            case '^':
                pilha.push( inf[i] );
                break;
            default:
                pref += inf[i];
        }
    while( !pilha.empty() )
        pref += pilha.top(), pilha.pop();

    reverse( pref.begin(), pref.end() );
    return pref;
}

string infixaParaPosfixa( string inf ) {
    string posf = "";
    stack<char> pilha;

    for( int i = 0; i < inf.size(); i++ )
        switch( inf[i] ) {
            case '(':
                pilha.push( inf[i] );
                break;
            case ')':
                while( !pilha.empty() && pilha.top() != '(' ) {
                    posf += pilha.top();
                    pilha.pop();
                }
                if( pilha.top() == '(' )
                	pilha.pop();
                break;
            case '+':
            case '-':
                while( !pilha.empty() && pilha.top() != '(' ) {
                    posf += pilha.top();
                    pilha.pop();
                }
                pilha.push( inf[i] );
                break;
            case '*':
            case '/':
                while( !pilha.empty() && pilha.top() != '(' && pilha.top() != '+' && pilha.top() != '-' ) {
                    posf += pilha.top();
                    pilha.pop();
                }
                pilha.push( inf[i] );
                break;
            case '^':
                while( !pilha.empty() && pilha.top() != '(' && pilha.top() != '+' && pilha.top() != '-' && pilha.top() != '/' && pilha.top() != '*' ) {
                    posf += pilha.top();
                    pilha.pop();
                }
                pilha.push( inf[i] );
                break;
            default:
                posf += inf[i];
        }
    while( !pilha.empty() )
        posf += pilha.top(), pilha.pop();

    return posf;
}

double calculaPosfixa( string posf ) {
    double a, b, result;
    stack<double> pilha;

    for( int i = 0; i < posf.size(); i++ ) {
        if( isdigit( posf[i] ) )
            pilha.push( double((int)posf[i]-(int)'0') );

        else {
            b = pilha.top(); pilha.pop();
            a = pilha.top(); pilha.pop();
            switch( posf[i] ) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b; //tratar divisão por 0
                    break;
                case '^':
                    result = pow( a, b );
                    break;
            }
            cout << a << posf[i] << b << " = " << result << endl;
            pilha.push( result );
        }
    }
    result = pilha.top();
    pilha.pop();

    return result;
}

struct Tnode {
    char data;
    Tnode *l, *r;

    Tnode( char _data ) : data(_data) {
        l = r = NULL;
    }
};

int id;

Tnode* parse( string pref ) {
    char data = pref[id++];
    Tnode *node = new Tnode( data );

    if( data == '+' || data == '-' || data == '*' || data == '/' ) {
        node->l = parse( pref );
        node->r = parse( pref );
    }

    return node;
}

void bsf( Tnode* node ) {
    queue< Tnode* > fila;
    fila.push( node );

    while( !fila.empty() ) {
        node = fila.front(); fila.pop();

        if( node == NULL ) continue;
        cout << node->data;
        fila.push( node->l );
        fila.push( node->r );
    }
    cout << endl;
}

int main() {
    string inf, pref, posf;
    Tnode * tree;

    cin >> inf;

    pref = infixaParaPrefixa( inf );
    cout << "pref: " << pref << endl;
    id = 0;
    tree = parse( pref );
    bsf( tree );

    posf = infixaParaPosfixa( inf );
    cout << "pos: " << posf << endl;
    cout << calculaPosfixa( posf ) << endl;
}