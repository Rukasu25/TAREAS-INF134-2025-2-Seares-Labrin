#include<iostream>
#include<fstream>
#include<string>

using namespace std;


/* ****
* struct NodoAdy
******
* Resumen Estructura:
* Representa un nodo en la lista de adyacencia del grafo, que contiene el ID del vértice adyacente y un puntero al siguiente nodo en la lista.
**** */
struct NodoAdy{
    int id;
    NodoAdy *sig;
};

/* ****
* class Grafo
******
* Resumen Clase:
* Representa un grafo no dirigido utilizando listas de adyacencia. Proporciona métodos para agregar aristas,
* realizar búsquedas en profundidad (DFS), sugerir amigos, contar comunidades, calcular influencia de usuarios,
* identificar usuarios populares y encontrar puntos de articulación (puentes) en el grafo.
**** */
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

    /* ****
    * void encontrarPuentesDFS
    ******
    * Resumen Función
    * este es un dfs que me ayudará a encontrar aquellos nodos que son puntos de articulación
    ******
    * Input:
    * int u: vértice actual
    * bool* visitado: array de vértices visitados
    * int* tiempoDescubrimiento: tiempos de descubrimiento en DFS
    * int* low: valores low para encontrar componentes
    * int* padre: padres en el árbol DFS
    * bool* esArticulacion: marca nodos de articulación
    * int& tiempo: contador de tiempo
    ******
    * Returns:
    * void
    **** */
    void encontrarPuentesDFS(int u, bool* visitado, int* tiempoDescubrimiento, int* low, int* padre, bool* esArticulacion, int& tiempo) {
        int hijos=0;
    
        //marcar el nodo actual como visitado
        visitado[u]=true;
    
        //inicializar tiempo de descubrimiento y valor low
        tiempoDescubrimiento[u]= low[u]= ++tiempo;
    
        //recorrer todos los vértices adyacentes
        NodoAdy* aux=adyacencia[u];
        while (aux != nullptr) {
        int v=aux->id;
        
            if (!visitado[v]) {
                hijos++;
                padre[v]= u;
            
            //llamada recursiva para v
                encontrarPuentesDFS(v, visitado, tiempoDescubrimiento, low, padre, esArticulacion, tiempo);
            
            //revisar si el subárbol con raíz en v tiene conexión con ancestros de u
                low[u]=(low[u] < low[v]) ? low[u] : low[v];
            
            // u es nodo de articulación en los siguientes casos:
            
                if(padre[u] == -1 && hijos > 1){
                    esArticulacion[u]=true;
                }
            
                if(padre[u] != -1 && low[v] >= tiempoDescubrimiento[u]){
                    esArticulacion[u]=true;
                }
            }
        
            //actualizar low value de u para los ancestros
            else if(v != padre[u]){
                low[u]=(low[u] < tiempoDescubrimiento[v]) ? low[u] : tiempoDescubrimiento[v];
            }
        
            aux=aux->sig;
        }
    }   

public:
    /* ****
    * Grafo
    ******
    * Resumen Función
    * Constructor del grafo a partir de un archivo
    * *****
    */
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
    * ~Grafo
    ******
    * Resumen Función
    * Destructor del grafo, libera la memoria utilizada por las listas enlazadas
    * 
    **** */
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
        
        if (0 > id_usuario || id_usuario >= NumVertices) {
            return nullptr; // ID de usuario inválido
        }
        NodoAdy* listaSugeridos = nullptr;
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
    int contar_comunidades(){
        int contador=0;
        bool* visitado=new bool[NumVertices];
        for(int i=0;i<NumVertices;i++){
            visitado[i]= false;
        }
        for(int i=0; i<NumVertices; i++){
            if (visitado[i]==false){
                contador++;
                dfs(i, visitado);
            }
        }
        delete[] visitado;
        return contador;
    }

    /* ****
    * int Calcular_Influencia
    ******
    * Resumen Función
    * Calcular el nivel de influencia de un usuario específico, definido como el número total de usuarios que puede alcanzar a través de sus amigos (amigos directos + amigos de amigos directos, sin repetición).
    * input:
    * int id_usuario : ID del usuario para el cual se calcula la influencia
    ******
    * Returns:
    * int : nivel de influencia del usuario
    **** */  
    int Calcular_Influencia(int id_usuario){
        if (id_usuario < 0 || id_usuario >= NumVertices) return -1;
        bool* visitado= new bool[NumVertices];
        for (int i= 0; i<NumVertices; i++){
            visitado[i]= false;
        }

        visitado[id_usuario]= true;

        int influencia = 0;
        //amigos directos
        NodoAdy* Nivel1 = adyacencia[id_usuario];
        while(Nivel1 != nullptr){
            int amigo = Nivel1->id;
            if(!visitado[amigo]){
                visitado[amigo]= true;
                influencia++;
            }
            Nivel1 = Nivel1->sig;
        }
        //amigos de amigos
        Nivel1 = adyacencia[id_usuario];
        while(Nivel1 != nullptr){
            NodoAdy* Nivel2 = adyacencia[Nivel1->id];
            while(Nivel2 != nullptr){
                int amigoDeAmigo = Nivel2->id;
                if(!visitado[amigoDeAmigo]){
                    visitado[amigoDeAmigo]= true;
                    influencia++;
                }
                Nivel2 = Nivel2->sig;
            }
            Nivel1 = Nivel1->sig;
        }
        delete[] visitado;
        return influencia;

    }


    /* ****
    * int usuario_mas_popular
    ******
    * Resumen Función
    * retorna el id del usuario más popular 
    * input:
    * sin inputs
    ******
    * Returns:
    * int
    **** */
    int usuario_mas_popular(){
        if (NumVertices==0) return -1;
        int mas_vecinos=0;
        int id_popular=0;

        for(int i=0; i< NumVertices; i++){
            int count=0;//este es un contador auxiliar para contar los vecinos de cada nodo
            NodoAdy *aux=adyacencia[i]; //creo un nodo auxiliar recorrer la lista enlazada
            
            while(aux !=nullptr){
                count++;
                aux=aux->sig;
            }
            if(count>mas_vecinos){
                mas_vecinos=count;
                id_popular=i;
            }

            
        }
        return id_popular;
    }

    /* ****
    * NodoAdy* encontrar_puentes
    ******
    * Resumen Función
    * retorna una lista con los nodos que son puntos de articulación en el grafo
    * input:
    * sin inputs
    ******
    * Returns:
    * NodoAdy*
    **** */
    NodoAdy* encontrar_puentes(){
        if(NumVertices==0) return nullptr;

        //ahora usaremos el dfs especial para ver nodos de articulacion (nodos que al eliminarlos hacen que mi grafo sea desconexo)
        bool *visitado=new bool[NumVertices];
        int *tiempoDescubrimiento=new int[NumVertices];
        int *low=new int[NumVertices];
        int *padre=new int[NumVertices];
        bool *esArticulacion=new bool[NumVertices];

        //inicializamos los arreglos
        for(int i=0; i<NumVertices; i++){
            visitado[i]=false;
            padre[i]=-1;
            esArticulacion[i]=false;
        }

        int tiempo=0;

        //ahora se aplica el dfs ese para cada nodo
        for(int i=0; i<NumVertices; i++){
            if(visitado[i]==false) encontrarPuentesDFS(i, visitado, tiempoDescubrimiento, low, padre, esArticulacion, tiempo);
        }

        //luego se buscan los nodos de articulación
        NodoAdy* listapuentes = nullptr;
        for(int i = 0; i<NumVertices; i++){
            if(esArticulacion[i]){
                NodoAdy* resultado = new NodoAdy;
                resultado->id = i;
                resultado->sig = listapuentes;
                listapuentes= resultado;
            }
        }

        delete[] visitado;
        delete[] tiempoDescubrimiento;
        delete[] low;
        delete[] padre;
        delete[] esArticulacion;

        return listapuentes; //si no se llega a encontrar nodos de articulación, se retornará como un nullptr

    }

    /* ****
    * int nVertex
    ******
    * Resumen Función
    * Retorna el número de vértices en el grafo.
    * input:
    * Ninguno
    * ******
    * Returns:
    * int : número de vértices en el grafo
    **** */
    int nVertex(){
        return NumVertices;
    }
    
    /* ****
    * bool existenciaNodo
    ******
    * Resumen Función
    * Verifica si un nodo con el ID dado existe en el grafo.
    * input:
    * int id : ID del nodo a verificar
    * ******
    * Returns:
    * bool : true si el nodo existe, false en caso contrario
    **** */

    bool existenciaNodo(int id){
        return id >= 0 && id < NumVertices; //version ultrasimplificada
    }
};

/* ****
* void Menu
******
* Resumen Función:
* Interfaz de usuario para interactuar con el grafo, dependiendo de la opcion escogida se llama a una funcion distinta del grafo
* input:
* Grafo &grafo : referencia al grafo con el que se interactuará
* returns:
* void
**** */
void Menu(Grafo &grafo){    //esta es la interfaz del usuario
    cout<<"---SANSABOOK---\n"<<endl;
    int opcion;
    do{
        cout<<"1. Sugerencia de Amigos"<<endl;
        cout<<"2. Usuario Más Popular"<<endl;
        cout<<"3. Contar Comunidades"<<endl;
        cout<<"4. Influencia Usuario"<<endl;
        cout<<"5. Cantidad de Puentes"<<endl;
        cout<<"0. Salir"<<endl;

        cout<<"\nElige una Opción: "; cin>>opcion;

        if(opcion==1){
            int id;

            cout<<"Escribe un usuario: "; cin>>id;
            bool existe = grafo.existenciaNodo(id);
            NodoAdy *aux= grafo.sugerir_amigos(id);

            if(existe==false) cout<<"usuario no encontrado"<<endl;
            else if(aux==NULL){
                cout<<"no se pueden sugerir amigos"<<endl;
            }
            else{
                NodoAdy* it = aux;
                bool first = true;
                cout << "{";
                while (it != nullptr) {
                    if (!first) cout << ", ";
                    cout << it->id;
                    first = false;
                    NodoAdy* tmp = it;
                    it = it->sig;
                    delete tmp; // liberar nodo retornado por sugerir_amigos
                }
                cout << "}" << endl;
            }
        }

        if(opcion==2){
            cout<<grafo.usuario_mas_popular()<<endl;
        }

        if(opcion==3){
            cout<<grafo.contar_comunidades()<<endl;
        }

        if(opcion==4){
            int id;
            cout<<"Ingresa un usuario: "; cin>>id;
            bool existe=grafo.existenciaNodo(id);

            if(!existe) cout<<"usuario no encontrado"<<endl;
            else{
                cout<<grafo.Calcular_Influencia(id)<<endl;
            }
        }

        if(opcion==5){
            NodoAdy* puentes = grafo.encontrar_puentes();
            if(puentes == nullptr){
                cout << "no existen puentes en el grafo" << endl;
            } else {
                cout << "{";
                NodoAdy* it = puentes;
                bool primero = true;
                while(it != nullptr){
                    if(!primero) cout << ", ";
                    cout << it->id;
                    primero = false;
                    NodoAdy* temp = it;
                    it = it->sig;
                    delete temp; // liberar nodo retornado por encontrar_puentes
                }
                cout << "}" << endl; 
            }
        }

    }while(opcion!=0);
}

/* ****
* int main
******
* resumen Función: funcion principal que inicializa el grafo, define el archivo para ser abierto y llama al menú de interacción con el usuario
* input: ninguno
* returns: int
**** */
int main(){

    string archivo="datos.txt";
    Grafo grafo(archivo);
    Menu(grafo);

    return 0;
}