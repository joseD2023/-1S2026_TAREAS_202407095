#include <iostream>
#include "cctype"
#include "string"
#include "vector"
using namespace std;

enum TipoToken {
    IDENTIFICADOR,
    RESERVADA,
    OPERADOR,
    NUMERO,
    PARENTESIS,
    PUNTOYCOMA,
    LLAVES,
    DESCONOCIDO
};

struct Token {
    TipoToken tipo;
    string lexema;
    int columna;
    int fila;
};


string tipoTokensString(TipoToken tipo) {
    switch (tipo) {
        case IDENTIFICADOR:
            return "identificador";
        case RESERVADA:
            return "Palabra Reservada";
        case OPERADOR:
            return "Operador";
        case NUMERO:
            return "Numero";
        case PARENTESIS:
            return "Parentesis";
        case PUNTOYCOMA:
            return "Punto y Coma";
        case LLAVES:
            return  "llaves";
        case DESCONOCIDO:
            return "Error Lexico : Simbolo No Reconocido, No pertence al Lenguaje";
        default:
            return "Desconocido";
    }
}

bool esReservada(const string& palabra) {
    return palabra == "int" || palabra == "if" || palabra == "while" || palabra == "for" || palabra == "return" || palabra == "float";
}

/*Entonces qui vamos a colocar la logica del analizador lexico para poder trabajar: Lo que debemos tener en cuenta
 * es que tenemos que cada token es una clasificacion del lexema correpondiente que cumple con un patron, si ese patron se cumple se convierte
 * en lo que conocemos como token.
 */

vector<Token> analizadorLexico(const string& entrada, int numeroFila) {

    vector<Token> tokens; /*vamos a guardar nuestros tokens de cada linea*/
    int columna = 0;
    string lexema;

    while (columna < entrada.length()) {

        /*No nos importa los espacios*/
        if (isspace(entrada[columna])) {
            columna++; /*pasamos al siguiente posicion*/
            continue;
        }

        /*aqui empezamos otra ves ver a validar si viene un caracter o no*/

        if (isalpha(entrada[columna])) {
            int inicio = columna;
            string constructorLexemas;

            while (isalnum(entrada[columna]) || entrada[columna] == '_') {
                constructorLexemas += entrada[columna];
                columna++; /*aumentamos la posicion para ir verificando*/
            }

            if (!isalnum(entrada[columna]) && !isspace(entrada[columna]) && entrada[columna] != '_'  && entrada[columna] != '(' && entrada[columna] != ')' && entrada[columna] != ';') {
                constructorLexemas += entrada[columna];
                columna++;
                tokens.push_back({DESCONOCIDO, constructorLexemas, inicio+1, numeroFila});
            }

            /*Una vez construido verificamos si ese texto es una palabra reservada o un identificador*/
            else if (esReservada(constructorLexemas)) {
                tokens.push_back({RESERVADA, constructorLexemas, inicio+1,numeroFila});
            }else {
                tokens.push_back({IDENTIFICADOR, constructorLexemas, inicio+1, numeroFila});
            }

            continue;
        }


        /*Dado caso inicie con un digito digamos 12456 entonces vamos a poder construir el lexema para verificar*/

        if (isdigit(entrada[columna])) {
            int inicio = columna;

            string constructorLexemas;
            while (isdigit(entrada[columna])) {
                constructorLexemas += entrada[columna];
                columna++;
            }

            /*vamos a verificar si tiene parte decimal*/


            if (entrada[columna] == '.' && isdigit(entrada[columna+1])) {
                constructorLexemas += entrada[columna];
                columna++;

                while (isdigit(entrada[columna])) {
                    constructorLexemas += entrada[columna];
                    columna++;
                }

                /*Numero real*/
                tokens.push_back({NUMERO, constructorLexemas, inicio+1, numeroFila});


            }else if (isalpha(entrada[columna])) {

                while (isalnum(entrada[columna])) {
                    constructorLexemas += entrada[columna];
                    columna ++;
                }

                tokens.push_back({DESCONOCIDO, constructorLexemas, inicio+1, numeroFila});

            }else {
                tokens.push_back({NUMERO, constructorLexemas, inicio+1, numeroFila});
            }

            continue;

        }




        if (entrada[columna] == '=' || entrada[columna] == '>' || entrada[columna] == '<' || entrada[columna] == '+'
            || entrada[columna] == '-' || entrada[columna] == '/' || entrada[columna] == '*') {
            int inicio = columna;
            tokens.push_back({OPERADOR, string(1,entrada[columna]), inicio+1, numeroFila});
            columna++;
            continue;
        }



        /*ahora vamos con las llaves y parentesis*/

        if (entrada[columna] == '{' || entrada[columna] == '}') {
            int inicio = columna;
            tokens.push_back({LLAVES, string(1,entrada[columna]), inicio+1, numeroFila});
            columna++;
            continue;
        }


        if (entrada[columna] == '(' || entrada[columna] == ')') {
            int inicio = columna;
            tokens.push_back({PARENTESIS, string(1, entrada[columna]), inicio+1, numeroFila});
            columna++;
            continue;
        }


        if (entrada[columna] == ';') {
            int inicio = columna;
            tokens.push_back({PUNTOYCOMA, string(1,entrada[columna]), inicio, numeroFila});
            columna++;
            continue;
        }

        int inicio = columna;
        tokens.push_back({DESCONOCIDO, string(1, entrada[columna]), inicio+1, numeroFila});
        columna++;
        continue;
    }
    return tokens;
}


void imprimirTokens(const vector<Token>& tokens) {
    vector<Token> errores;
    cout << "Fila \t Columna   Token \t Lexema " << endl;
    cout << "------------------------------------------------------" << endl;
    for (const auto& t : tokens) {
        if (t.tipo != DESCONOCIDO) {
            cout << t.fila << "\t" << t.columna << "\t" << tipoTokensString(t.tipo) << ":  " <<  "[" << t.lexema <<  "]" << endl;
            continue;
        }
        errores.push_back(t);
    }

    cout << "Fila \t Columna   Token \t Error Lexico " << endl;
    cout << "------------------------------------------------------" << endl;
    for (const auto& l : errores) {
        cout << l.fila << "\t" << l.columna << "\t" << tipoTokensString(l.tipo) << ":  " <<  "[" << l.lexema <<  "]" << endl;
    }

}





int main() {

    vector<string> lineas = {
        "int 123numero = 5;",
        "float valor# = 10.5;",
        "if (123numero > valor#) { return 0; }"
    };

    vector<Token> vectorTokens;
    int fila = 1;

    for (const auto& linea : lineas ) {
        vector<Token> tokensLinea = analizadorLexico(linea, fila);
        vectorTokens.insert(vectorTokens.end(), tokensLinea.begin(), tokensLinea.end());;
        fila ++;
    }

    imprimirTokens(vectorTokens);

    return 0;
}