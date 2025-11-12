
/* || MENSAJE PARA PATOSTARR ||*/
/* IMPLEMENTAR CLASES DE GRAFO PARA CORRECTO FUNCIONAMIENTO DE CODIGO */
#include<iostream>
#include<fstream>
#include<string>

using namespace std;


//se crea el struct nodo
struct NodoAdy{
    int id;
    NodoAdy *sig;
};

//se implementa la clase grafo
class Grafo{
private:
    int NumVertices;
    int NumAristas;
    NodoAdy **adyacencia; //este es arreglo de listas enlazadas

    /* ****
    * void agregarArco
    ******
    * Resumen Función
    * Agrega una arista no dirigida entre u y v (agrega v a lista de u, y u a lista de v)
    ******
    * Input:
    * int u : vértice origen
    * int v : vértice destino
    ******
    * Returns:
    * void
    **** */
    void agregarArco(int u, int v){
        NodoAdy *aux=new NodoAdy;
        aux->id=v;
        aux->sig=adyacencia[u];
        adyacencia[u]=aux;

        aux->id=u;
        aux->sig=adyacencia[v];
        adyacencia[v]=aux;
    }

public:
    //constructor del grafo a partir de un archivo
    Grafo(string &archivo){
        fstream file;
        file.open("archivo", ios::in);
        if(!file.is_open()){
            NumVertices=0;
            adyacencia=NULL;
            return;
        }

        file>>NumVertices>>NumAristas; //rescatamos el numero de vertices y la cantidad de arcos

        adyacencia=new NodoAdy *[NumAristas];//creamos el arreglo que guarda las conexiones (grafo utilizando listas enlazadas)
        int i;
        for(i=0; i<NumVertices; i++){
            adyacencia[i]=NULL;//seteamos las cabeceras a las listas com0o null
        }

        //ahora creamos los arcos correspondientes a cada nodo
        for(i=0; i<NumVertices; i++){
            int u, v;
            file>>u>>v;
            if(u>=0 && u<NumVertices && v>=0 && v< NumAristas && u!=v){
                agregarArco(u,v);
            }
        }

        file.close();

    }

    //destructor
    ~Grafo(){
        if(adyacencia==NULL) return;

        for(int i=0; i<NumVertices;i++){
            NodoAdy *aux=adyacencia[i];
            while(aux !=NULL){
                NodoAdy* temp=aux;
                aux=aux->sig;
                delete temp;
                
            }
        }
        delete[] adyacencia;
    }
    

};










//funcion Sugerir_Amigos [TIPO DE FUNCION EN DESARROLLO, POTENCIALMENTE CLASE GRAFO o LISTA]
// Retornar una lista de usuarios que están a exactamente 2 grados de distancia del usuario dado (amigos de amigos) y que aún no son amigos directos. Ejemplo: En el grafo de la Figura 1, sugerirAmigos(9) deber´ıa retornar {5, 7, 11, 12, 14}, ya que son amigos de los amigos de 9 pero no son amigos directos de 9.
lista sugerir_amigos(int id_usuario){
    //IMPLEMENTAR FUNCION
};


//funcion usuario_mas_popular, Tipo de funcion = Int.
// Identificar y retornar el ID del usuario con el mayor número de conexiones directas (mayor grado del grafo). En caso de empate, puede retornar cualquiera de los usuarios empatados. Ejemplo: En el grafo de la Figura 1, esta función debería analizar los grados de todos los nodos y retornar el usuario con más amigos, el cual corresponde a: 1, el cual tiene 6 amigos.

int usuario_mas_popular(){
    //IMPLEMENTAR FUNCION
};



//funcion contar_comunidades, Tipo de funcion = Int.
// Calcular el número de componentes conexas del grafo. Cada componente representa un grupo aislado de usuarios, en el que todos est´an conectados entre sí de alguna forma, pero no tienen conexión con otros grupos. Ejemplo: En el grafo de ejemplo de la Figura 1 el valor sería 1, ya que solo hay una comunidad, pero si se elimina el nodo 9, deberían contabilizarse dos comunidades.

int contar_comunidades(){
    //IMPLEMENTAR FUNCION
};


//funcion calcular_influencia, Tipo de funcion = int.
//Calcular el nivel de influencia de un usuario específico, definido como el número total de usuarios que puede alcanzar a través de sus amigos (amigos directos + amigos de amigos directos, sin repetici´on). Este valor representa qué tan conectado está un usuario en la red. Ejemplo: Si un usuario tiene 3 amigos directos, y estos amigos tienen en total 10 amigos únicos (excluyendo al usuario original y duplicados), su nivel de influencia sería 13. Para el caso del nodo 1, su nivel de influencia ser´ıa de 6 amigos directos + 2 amigos de amigos, con un total de influencia de 8.


int calcular_influencia(int id_usuario){
    //IMPLEMENTAR FUNCION
};


//funcion encontrar_puentes, Tipo de funcion = sin definir aun
//Encontrar nodos que son cruciales para conectar comunidades en el grafo. Ejemplo: En el grafo 1 la función retornaría {9}, debido a que al eliminarlo quedarán dos comunidades cuando originalmente había una.

encontrar_puentes(){
    //IMPLEMENTAR FUNCION
}


int main(){
    int id_usuario;

    return 0;
}