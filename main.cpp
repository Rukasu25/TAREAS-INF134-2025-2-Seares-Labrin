
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
        NodoAdy *nuevoNodoV=new NodoAdy;
        nuevoNodoV->id=v;
        nuevoNodoV->sig=adyacencia[u];
        adyacencia[u]=nuevoNodoV;

        NodoAdy *nuevoNodoU=new NodoAdy;
        nuevoNodoU->id=u;
        nuevoNodoU->sig=adyacencia[v];
        adyacencia[v]=nuevoNodoU;
    }

    /* ****
    * void dfs
    ******
    * Resumen Función
    * Recorrido de Búsqueda en Profundidad (DFS). Marca todos los nodos
    * alcanzables desde 'u' como visitados.
    ******
    * Input:
    * int u : El vértice actual desde donde se explora
    * bool* visitado : El array de nodos visitados
    ******
    * Returns:
    * void
    **** */
    void dfs(int u, bool* visitado) {
        // 1. Marcar el nodo actual como visitado
        visitado[u] = true;

        // 2. Recorrer todos sus vecinos (amigos)
        NodoAdy* aux = adyacencia[u];
        while (aux != NULL) {
            int v = aux->id;
            
            // 3. Si el vecino 'v' no ha sido visitado, llamarse
            //    recursivamente desde 'v'.
            if (visitado[v] == false) {
                dfs(v, visitado);
            }
            aux = aux->sig;
        }
    }

public:
    //constructor del grafo a partir de un archivo
    Grafo(string &archivo){
        fstream file;
        file.open(archivo.c_str(), ios::in);
        if(!file.is_open()){
            cout<<"Error al abrir el archivo"<<endl;
            NumVertices=0;
            adyacencia=NULL;
            return;
        }

        file>>NumVertices>>NumAristas; //rescatamos el numero de vertices y la cantidad de arcos

        adyacencia=new NodoAdy *[NumVertices];//creamos el arreglo que guarda las conexiones (grafo utilizando listas enlazadas)
        int i;
        for(i=0; i<NumVertices; i++){
            adyacencia[i]=NULL;//seteamos las cabeceras a las listas com0o null
        }

        //ahora creamos los arcos correspondientes a cada nodo
        for(i=0; i<NumAristas; i++){
            int u, v;
            file>>u>>v;
            if(u>=0 && u<NumVertices && v>=0 && v< NumVertices && u!=v){
                agregarArco(u,v);
            }
        }

        file.close();

    }


    /* ****
    * NodoAdy* sugerir_amigos
    ******
    * Resumen Función
    * Retornar una lista de usuarios que están a exactamente 2 grados de distancia del usuario dado (amigos de amigos) y que aún no son amigos directos. 
    * input:
    * int id_usuario : ID del usuario para el cual se sugieren amigos
    ******
    * Returns:
    * NodoAdy* : Lista enlazada de IDs de usuarios sugeridos como amigos
    **** */    
    NodoAdy* sugerir_amigos(int id_usuario){ 
        NodoAdy* listaSugeridos = nullptr;
        NodoAdy* amigosDirectos = adyacencia[id_usuario];

        // Marcar amigos directos
        bool* esAmigoDirecto = new bool[NumVertices]();
        for(int i = 0; i < NumVertices; i++) {
            esAmigoDirecto[i] = false;
        }
        esAmigoDirecto[id_usuario] = true; // El usuario no es su propio amigo
        NodoAdy* Nivel1 = adyacencia[id_usuario];
        while(Nivel1 != nullptr) {
            esAmigoDirecto[Nivel1->id] = true;
            Nivel1 = Nivel1->sig;
        }

        Nivel1 = adyacencia[id_usuario];
        while(Nivel1 != nullptr){
            NodoAdy* Nivel2 = adyacencia[Nivel1->id];
            while(Nivel2 != nullptr){
                if(esAmigoDirecto[Nivel2->id] == false){
                    NodoAdy* SugerenciaDeAmistad = new NodoAdy;
                    SugerenciaDeAmistad->id = Nivel2->id;
                    SugerenciaDeAmistad->sig = listaSugeridos;
                    listaSugeridos = SugerenciaDeAmistad;
                    esAmigoDirecto[Nivel2->id] = true; // se marca como sugerido para evitar duplicados

                }
                Nivel2 = Nivel2->sig;

            }
            Nivel1 = Nivel1->sig;
                
        }
        delete[] esAmigoDirecto;
        return listaSugeridos;
    
    };
    /* ****
    * int contar_comunidades
    ******
    * Resumen Función
    * Retornar el número de componentes conexas del grafo. Cada componente representa un grupo aislado de usuarios, en el que todos están conectados entre sí de alguna forma, pero no tienen conexión con otros grupos.
    * input:
    * Ninguno 
    ******
    * Returns:
    * int : cantidad de comunidades en el grafo
    **** */    
    int contar_comunidades(NodoAdy* inicio){
        NodoAdy *aux=inicio;
        int contador=0;
        bool* visitado=new bool[NumVertices];
        for(int i=0;i<NumVertices;i++){
            if (visitado[i]==false){
                contador++;
                dfs(i, visitado);
            }
        }
        delete[] visitado;
        return contador;
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








/*

//funcion Sugerir_Amigos [TIPO DE FUNCION EN DESARROLLO, POTENCIALMENTE CLASE GRAFO o LISTA]
// Retornar una lista de usuarios que están a exactamente 2 grados de distancia del usuario dado (amigos de amigos) y que aún no son amigos directos. Ejemplo: En el grafo de la Figura 1, sugerirAmigos(9) deber´ıa retornar {5, 7, 11, 12, 14}, ya que son amigos de los amigos de 9 pero no son amigos directos de 9.
int* sugerir_amigos(int id_usuario){ 
    for (int i = 0; i < datos.txt )
    
};


//funcion usuario_mas_popular, Tipo de funcion = Int.
// Identificar y retornar el ID del usuario con el mayor número de conexiones directas (mayor grado del grafo). En caso de empate, puede retornar cualquiera de los usuarios empatados. Ejemplo: En el grafo de la Figura 1, esta función debería analizar los grados de todos los nodos y retornar el usuario con más amigos, el cual corresponde a: 1, el cual tiene 6 amigos.

int usuario_mas_popular(){

};



//funcion contar_comunidades, Tipo de funcion = Int.
// Calcular el número de componentes conexas del grafo. Cada componente representa un grupo aislado de usuarios, en el que todos est´an conectados entre sí de alguna forma, pero no tienen conexión con otros grupos. Ejemplo: En el grafo de ejemplo de la Figura 1 el valor sería 1, ya que solo hay una comunidad, pero si se elimina el nodo 9, deberían contabilizarse dos comunidades.

int contar_comunidades(){

};


//funcion calcular_influencia, Tipo de funcion = int.
//Calcular el nivel de influencia de un usuario específico, definido como el número total de usuarios que puede alcanzar a través de sus amigos (amigos directos + amigos de amigos directos, sin repetici´on). Este valor representa qué tan conectado está un usuario en la red. Ejemplo: Si un usuario tiene 3 amigos directos, y estos amigos tienen en total 10 amigos únicos (excluyendo al usuario original y duplicados), su nivel de influencia sería 13. Para el caso del nodo 1, su nivel de influencia ser´ıa de 6 amigos directos + 2 amigos de amigos, con un total de influencia de 8.


int calcular_influencia(int id_usuario){

};


//funcion encontrar_puentes, Tipo de funcion = sin definir aun
//Encontrar nodos que son cruciales para conectar comunidades en el grafo. Ejemplo: En el grafo 1 la función retornaría {9}, debido a que al eliminarlo quedarán dos comunidades cuando originalmente había una.

encontrar_puentes(){

}
*/

int main(){
    cout << "Iniciando programa..." << endl;
    string archivo="datos.txt";
    Grafo grafo(archivo);
    grafo.sugerir_amigos(9);

    return 0;
}