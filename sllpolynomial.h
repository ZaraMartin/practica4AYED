// AUTOR: Zara Martín Bolaños 
// FECHA: 27/03/24
// EMAIL: alu0101493381@ull.edu.es
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 4
// ESTILO: Google C++ Style Guide
// COMENTARIOS:
// 

#ifndef SLLPOLYNOMIAL_H_
#define SLLPOLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "pair_t.h"
#include "sll_t.h"
#include "vector_t.h"

#define EPS 1.0e-6

typedef pair_t<double> pair_double_t;  // Campo data_ de SllPolynomial
// valor e índice
typedef sll_node_t<pair_double_t> SllPolyNode;  // Nodos de SllPolynomial
// valor y next

// Clase para polinomios basados en listas simples de pares
class SllPolynomial : public sll_t<pair_double_t> {
public:
  // constructores
  SllPolynomial(void) : sll_t() {};
  SllPolynomial(const vector_t<double>&, const double = EPS);

  // destructor
  ~SllPolynomial() {};

  // E/S
  void Write(std::ostream & = std::cout) const;

  // operaciones
  double Eval(const double) const;
  bool IsEqual(const SllPolynomial&, const double = EPS) const;
  void Sum(const SllPolynomial&, SllPolynomial&, const double = EPS);
  void Nodo(const SllPolynomial& p);
};


bool IsNotZero(const double val, const double eps = EPS) {
  return fabs(val) > eps;
}

// FASE II
// constructor
SllPolynomial::SllPolynomial(const vector_t<double>& v, const double eps) {
  // SllPolyNode* head = get_head();
  // SllPolyNode* next = head->get_next();
  sll_node_t<pair_double_t>* head_nodo;
  sll_node_t<pair_double_t>* nodo_anterior;
  sll_node_t<pair_double_t>* nodo_nuevo;

  for (int i{ 0 }; i < v.get_size(); i++) {
    if (fabs(v.get_val(i)) > eps) {
      if (this->get_head() == NULL) {  // si la lista está vacía
        head_nodo = new sll_node_t<pair_double_t>;
        pair_double_t primer_monomio{ v.get_val(i), i };
        head_nodo->set_data(primer_monomio);
        this->push_front(head_nodo);
        nodo_anterior = head_nodo;
      }
      else {
        nodo_nuevo = new sll_node_t<pair_double_t>; //inicializamos el espacio de memoria 
        pair_double_t nuevo_monomio{ v.get_val(i), i };
        nodo_nuevo->set_data(nuevo_monomio);
        this->insert_after(nodo_anterior, nodo_nuevo); //ponerlo después del primer nodo. (último).
        nodo_anterior = nodo_nuevo;
      }

      pair_double_t monomio1{ v.get_val(i), i }; // valor , índice 
    }
  }
}


//   for (int i{ v.get_size() - 1 }; i >= 0; i--) { // va desde la última posición del vector hacia atrás
//     if (IsNotZero(v.at(i), eps) == true) {       // si el vector no es cero 
//       pair_double_t pair(v.get_val(i), i);       // se crea un nuevo nodo con el valor del vector y el valor del índice
//       SllPolyNode* aux = new         // constructor para crear un nuevo nodo de la lista enlazada que almacenará un 
//         // polinomio, el asterisco es para declarar un objeto sllpolynomial 

// new es para crear un espacio de memoria para el nodo. Para inicializar siempre 

//         SllPolyNode(pair);       // guardar dentro de la lista enlazada los nodos
//       push_front(aux);         // meter en la lista enlzada los nodos, lo mete de 5, 4, 3, 2, 1   a   1, 2, 3, 4, 5. LIFO

// insert after en la posicion del 5, coloca el numero que quieres 

//       // aux es un parametro de tipo sllpolynomial
//       // El parámetro aux es un puntero al nodo que se quiere agregar al principio de la lista
//     }
//   }
// }



// E/S
void SllPolynomial::Write(std::ostream& os) const {
  os << "[ ";
  bool first{ true };
  SllPolyNode* aux{ get_head() };
  while (aux != NULL) {
    int inx{ aux->get_data().get_inx() };
    double val{ aux->get_data().get_val() };
    if (val > 0)
      os << (!first ? " + " : "") << val;
    else
      os << (!first ? " - " : "-") << fabs(val);
    os << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    if (inx > 1)
      os << inx;
    first = false;
    aux = aux->get_next();
  }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SllPolynomial& p) {
  p.Write(os);
  return os;
}


// Operaciones con polinomios

// FASE III
// Evaluación de un polinomio representado por lista simple
double SllPolynomial::Eval(const double x) const {
  double result{ 0.0 };
  SllPolyNode* head = this->get_head();
  while (head != NULL) {
    result += head->get_data().get_val() * pow(x, head->get_data().get_inx());
    head = head->get_next();
  }
  return result;
}

// Comparación si son iguales dos polinomios representados por listas simples
bool SllPolynomial::IsEqual(const SllPolynomial& sllpol, const double eps) const {
  bool differents = false; // sustituir con x un número cualquiera y si te dan los resultados iguales son iguales.
  SllPolyNode* head = this->get_head();
  SllPolyNode* head2 = sllpol.get_head();
  int result{ 0 };
  int result1{ 0 };
  while (head != NULL) {
    result += head->get_data().get_val() * pow(2, head->get_data().get_inx());
    head = head->get_next();
  }
  while (head2 != NULL) {
    result1 += head2->get_data().get_val() * pow(2, head2->get_data().get_inx());
    head2 = head2->get_next();
  }
  if (abs(result - result1) > eps) {
    return differents;
  }
  return !differents;
}


// FASE IV
// Generar nuevo polinomio suma del polinomio invocante mas otro polinomio
// primero get_head
//if nodo1 < nodo2, get next
void SllPolynomial::Sum(const SllPolynomial& sllpol, SllPolynomial& sllpolsum, const double eps) {
  SllPolynomial auxSllPolSum;    // lista auxiliar para guardar el resultado de la suma
  SllPolyNode* aux = get_head();   // puntero hacia los primeros nodos de la lista
  SllPolyNode* aux2 = sllpol.get_head();  // puntero hacia los primeros nodos de la lista
  pair_double_t pair;   // variable temporal de tipo pair_double_t oara almacenar el coeficiente y exponente
  double sum = 0.0;     // declaración de sum inicializada en 0
  while (aux != NULL || aux2 != NULL) {  // mientras cada uno de los nodos no sean 0
    if (aux != NULL && aux2 != NULL) {   // si los dos nodos no son 0
      if (aux->get_data().get_inx() == aux2->get_data().get_inx()) {  // si tienen los mismos exponentes se suman 
        sum = aux->get_data().get_val() + aux2->get_data().get_val(); // se guarda en la variable suma la suma de los valores de los dos nodos
        if (IsNotZero(sum, eps)) {    // si no es 0 la suma
          pair.set(sum, aux->get_data().get_inx());     // resize del pair con la suma y el exponente 
          auxSllPolSum.push_front(new SllPolyNode(pair));    // meter en la lista auxSllPolSum que declaramos una lista nueva con pair
        }
        if (aux != NULL) aux = aux->get_next();  // si el primer nodo de la primera lista es distinto de 0, pasa al siguiente nodo 
        if (aux2 != NULL) aux2 = aux2->get_next(); // si el primer nodo de la segunda lista es distinto de 0, pasa al siguiente nodo
      }
      else if (aux->get_data().get_inx() > aux2->get_data().get_inx()) {  // si el exponente de la primera lista es mayor
        sum = aux2->get_data().get_val();  // guarda en la suma solo el valor del primer nodo de la segunda lista 
        if (IsNotZero(sum, eps)) {   // si no es 0
          pair.set(sum, aux2->get_data().get_inx());  // resize del pair con el resultado de sum y el exponente de la segunda lista
          auxSllPolSum.push_front(new SllPolyNode(pair));  // mete en la lista creada la nueva lista con los valores obtenidos
        }
        if (aux2 != NULL) aux2 = aux2->get_next();  // si el nodo de la segunda lista no es 0, pasa al siguiente nodo
      }
      else {
        sum = aux->get_data().get_val();  // al contrario, guarda en la suma el valor del primer nodo de la primera lista 
        if (IsNotZero(sum, eps)) {   // si no es 0
          pair.set(sum, aux->get_data().get_inx());  // resize del pair con el resultado de sum y el exponente de la primera lista
          auxSllPolSum.push_front(new SllPolyNode(pair));  // mete en la lista creada la nueva lista con los valores obtenidos
        }

        if (aux != NULL) aux = aux->get_next();  // si el primer nodo de la primera lista es distinto de 0, pasa al siguiente nodo 
      }
    }
    else if (aux == NULL) {   // si el nodo de la primera lista es 0
      sum = aux2->get_data().get_val();  // mete en sum el nodo de la segunda lista 
      if (IsNotZero(sum, eps)) {   // si no es 0 
        pair.set(sum, aux2->get_data().get_inx());   // resize del pair con el resultado de sum y el exponente de la primera lista
        auxSllPolSum.push_front(new SllPolyNode(pair));  // mete en la lista creada la nueva lista con los valores obtenidos
      }
      if (aux2 != NULL) aux2 = aux2->get_next();   // si el nodo de la segunda lista es 0, pasa al siguiente nodo
    }
    else if (aux2 == NULL) {   // si el nodo de la segunda lista es 0
      sum = aux->get_data().get_val();  // mete en sum el nodo de la segunda lista 
      if (IsNotZero(sum, eps)) {    // si no es 0 
        pair.set(sum, aux2->get_data().get_inx());     // resize del pair con el resultado de sum y el exponente de la primera lista
        auxSllPolSum.push_front(new SllPolyNode(pair));    // mete en la lista creada la nueva lista con los valores obtenidos
      }

      if (aux != NULL) aux = aux->get_next();   // si el primer nodo de la primera lista es distinto de 0, pasa al siguiente nodo 
    }
  }

  while (!auxSllPolSum.empty()) {    // mientras la lista no este vacía
    sllpolsum.push_front(auxSllPolSum.pop_front());    // está copiando los nodos de auxSllPolSum en orden inverso a la lista sllpolsum.
  }
}



// void SllPolynomial::Sum(const SllPolynomial& sllpol, SllPolynomial& sllpolsum, const double eps) {
//   SllPolyNode* head = this->get_head();
//   SllPolyNode* head2 = sllpol.get_head();
//   SllPolyNode* primer_nodo;
//   SllPolyNode* nodo_anterior;
//   pair_double_t monomio;
//   while ((head != NULL) || (head2 != NULL)) {
//      primer_nodo = new SllPolyNode;  // no pones head porque no quiero el puntero con el nodo, quieres solo el valor del puntero

//       if (head->get_data().get_inx() < head2->get_data().get_inx()) {
//         monomio.set(head->get_data().get_val(), head->get_data().get_inx());
//         if (fabs(head->get_data().get_val() < eps)) {
//           nodo_anterior = primer_nodo;
//           sllpolsum.push_front(primer_nodo);
//           nodo_anterior = primer_nodo;
//         }
//         head = head->get_next();

//         if (head == NULL && head2 != NULL) {

//           head2 = head2->get_next();
//         }

//         else if (head != NULL && head2 == NULL) {
//           head = head->get_next();
//         }
//       }
//     }

//     if (head->get_data().get_inx() > head2->get_data().get_inx()) {

//       monomio.set(head2->get_data().get_val(), head2->get_data().get_inx());
//       if (fabs(head2->get_data().get_val() < eps)) {
//         nodo_anterior = primer_nodo;
//         sllpolsum.push_front(primer_nodo);
//         nodo_anterior = primer_nodo;

//         if (head == NULL && head2 != NULL) {
//           head2 = head2->get_next();
//         }
//         else if (head != NULL && head2 == NULL) {
//           head = head->get_next();
//         }
//       }
//       if (head->get_data().get_inx() == head2->get_data().get_inx()) {
//         double sum = head->get_data().get_val() + head2->get_data().get_val();
//         if (IsNotZero(sum, eps)) {
//           monomio.set(sum, head->get_data().get_inx());
//           sllpolsum.push_front(primer_nodo);
//           if (head == NULL && head2 != NULL) {
//             head2 = head2->get_next();
//           }
//           else if (head != NULL && head2 == NULL) {
//             head2 = head2->get_next();
//           }
//         }
//       }
//     }
//   }


// sacar el polinomio sin el primer y el último monomio
void SllPolynomial::Nodo(const SllPolynomial& p) {
  SllPolyNode* aux = get_head();
  int index{ 0 };

  pair_double_t pair;
  while (aux != nullptr) {
    pair.set(aux->get_data().get_val(), index);
    if ((pair.get_inx()) > 0) {
      std::cout << aux->get_data().get_val() << std::endl;
    }
    if (aux != nullptr) {
      aux->get_next();
    }

    else if (aux->get_next() == nullptr) {
      break;
    }
    index++;
  }
}


// sacar las posiciones impares de la lista enlazada

// void SllPolynomial::Odd2(const SllPolynomial& p) {
//   SllPolyNode* aux = get_head();s
//   int index{ 0 };
//   pair_double_t pair;
//   while (aux != NULL) {
//     pair.set(aux->get_data().get_val(), index);
//     if ((pair.get_inx()) % 2 != 0) {
//       std::cout << aux->get_data().get_val() << std::endl;
//     }
//     if (aux != NULL) aux = aux->get_next();
//     index++;
//   }
// }

// modificaciones:
// sacar los índices impares de la lista enlazada
// void SllPolynomial::Odd(const SllPolynomial& p) {
//   SllPolyNode* aux = get_head();
//   while (aux != NULL) {
//     if ((aux->get_data().get_inx()) % 2 != 0) {
//       std::cout << aux->get_data().get_val() << std::endl;
//     }
//     if (aux != NULL) aux = aux->get_next();
//   }
// }


#endif  // SLLPOLYNOMIAL_H_