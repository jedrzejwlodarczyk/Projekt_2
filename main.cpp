#include <iostream>
#include <string>
#include <sstream>
#include "generate.h"
#include "actions.h"
#include <unistd.h>


using namespace std;

void help(){
    cout << "Help                           Show this message" << endl;
    cout << "Print                          Print the graph in the selected representation" << endl;
    cout << "Find                           Searching for graph edges" << endl;
    cout << "Breath-first search            Breadth-first traversal" << endl;
    cout << "Depth-first search             Depth-first traversal" << endl;
    cout << "Topological-sorting Kahn       Topological sorting using Kahn's algorithm" << endl;
    cout << "Topological-sorting Tarjan     Topological sorting using Tarjan's algorithm" << endl;
    cout << "Exit                           Exits the program" << endl;
}
void choice(string action,string graphtype,int** graph,int nodes,int tablesize){
    if (action == "Help"){
            help();
    }
    else if (action == "Print"){
        if(graphtype=="matrix"){
           print_adjacency_matrix(graph,nodes);
        }
        else if(graphtype=="list"){
            print_successor_list(graph,nodes);
        }
        else if(graphtype=="table"){
            print_edge_table(graph,nodes);
        }
    }
    else if (action == "Find"){
        int from,to;
        while(true){
            cout<<"from > ";
            cin >> from;
            if(from<1){cout<<"there is no node like that"<<endl;}
            else{break;}
        }
        while(true){
            cout<<"to > ";
            cin >> to;
            if(to<1){cout<<"there is no node like that"<<endl;}
            else{break;}
        }
        if(graphtype=="matrix"){
           check_for_edges_in_matrix(graph,from,to);
        }
        else if(graphtype=="list"){
            check_for_edges_in_list(graph,nodes,from,to);
        }
        else if(graphtype=="table"){
            check_for_edges_in_table(graph,tablesize,from,to);
        }
    }
    else if (action=="Breath-first search"){
        bfs_matrix(graph,nodes,0);
    }
    else if (action=="Depth-first searcg"){
        bool* visited = new bool[nodes] {false};

        cout << "inline: ";
        for (int i = 0; i < nodes; ++i) {
            if (!visited[i]) {
                dfs_matrix(graph, i, visited, nodes);
            }
        }
        cout << endl;
    }
    else if(action == "Topological-sorting Kahn"){
        if(graphtype=="matrix"){
           kahn_matrix(graph,nodes);
        }
        else if(graphtype=="list"){
            ///
        }
        else if(graphtype=="table"){
            ///
        }
        
    }
    else if(action == "Topological-sorting Tarjan"){
        if(graphtype=="matrix"){
           tarjan_matrix(graph,nodes);
        }
        else if(graphtype=="list"){
            ///
        }
        else if(graphtype=="table"){
            ///
        }
    }
    else if (action == "Exit"){
        exit(1);
    }
    else{
        cout << "Wrong action! Type help" << endl;
    }
}

int main(int argc, char* argv[]) {
    if (string(argv[1]) != "--generate" && (string(argv[1])) != "--user-provided" ){
        cout << "try open with [--generate/--user-provided]" << endl;
    }
    
    int nodes;
    float saturation;
    string graphtype;
    int** graph=nullptr;
    int tablesize=0;


    bool is_redirected = !isatty(fileno(stdin));

    if (is_redirected){
        ostringstream oss;
        oss << cin.rdbuf(); // Odczytanie całego strumienia wejściowego

        string fileContents = oss.str(); // Pobranie zawartości do string

        istringstream iss(fileContents); // Tworzymy strumień do analizy tekstu
        string line;

        int counter=0;
        int index=0;
        int check=0;
        
            if(string(argv[1]) == "--generate"){
                while(getline(iss,line)){
                    if(counter==0){
                        graphtype=line;
                        if(graphtype!="matrix" && graphtype!="list" && graphtype!="table"){cout<<"unknown type"<<endl;exit(1);}
                    }
                    else if(counter==1){
                        nodes=stoi(line);
                        if(nodes<1){cout<<"nie poprawna ilosc wezlow"<<endl;exit(1);}
                    }
                    else if(counter==2){
                        saturation=stoi(line);
                        if(saturation<1){cout<<"nie poprawna wartosc saturacji"<<endl;}
                        else if(saturation>100){cout<<"nie poprawna wartosc saturacji"<<endl;exit(1);}
                
                        int** adjacencyMatrix = generate_adjacency_matrix(nodes, saturation);

                        if(graphtype=="list"){
                            graph=adjacencyMatrixToList(adjacencyMatrix,nodes);
                        }
                        else if(graphtype=="table"){
                            graph=adjacencyMatrixToEdges(adjacencyMatrix,nodes);
                            tablesize=countEdges(adjacencyMatrix,nodes);
                        }
                        else{
                            graph=adjacencyMatrix;
                        }
                    }
                    else{
                        string action = line;
                        choice(action,graphtype,graph,nodes,tablesize);
                    }


                    counter++;
                }
            }

            else if(string(argv[1]) == "--user-provided"){
                int** adjacencyMatrix;
                while(getline(iss,line)){
                    if(counter==0){
                        graphtype=line;
                        if(graphtype!="matrix" && graphtype!="list" && graphtype!="table"){cout<<"unknown type"<<endl;exit(1);}
                    }
                    else if(counter==1){
                        nodes=stoi(line);
                        if(nodes<1){cout<<"nie poprawna ilosc wezlow"<<endl;exit(1);}
                        adjacencyMatrix = generate_matrix_user_provided_heredoc(nodes);
                        
                    }
                    if(counter>1 && counter<=1+nodes){
                        istringstream lineStream(line);
                        int element;
                        if (line.empty()){
                            index++;
                        }
                        else{
                            while (lineStream >> element) {
                                adjacencyMatrix[index][element-1] = 1;
                            }
                            index++;
                        }
                    }

                     
                    if(counter>1+nodes){
                        if(check==0){
                            if(graphtype=="list"){
                            graph=adjacencyMatrixToList(adjacencyMatrix,nodes);
                            }
                            else if(graphtype=="table"){
                                graph=adjacencyMatrixToEdges(adjacencyMatrix,nodes);
                                tablesize=countEdges(adjacencyMatrix,nodes);
                            }
                            else{
                                graph=adjacencyMatrix;

                            }
                            check++;
                        }
                        string action = line;
                        choice(action,graphtype,graph,nodes,tablesize);
                    }

                    counter++;

                }
            }
    }
    
    else{
    
        if(string(argv[1]) == "--generate"){
            while(true){
                cout<<"type (matrix/list/table) > ";
                cin >> graphtype;
                if(graphtype!="matrix" && graphtype!="list" && graphtype!="table"){cout<<"unknown type"<<endl;}
                else{break;}
            }
            while(true){
                cout << "Podaj liczbę wierzchołków: ";
                cin >> nodes;
                if(nodes<1){cout<<"nie poprawna ilosc wezlow"<<endl;}
                else{break;}
            }
            while(true){
                cout << "Podaj nasycenie: ";
                cin >> saturation;
                if(saturation<1){cout<<"nie poprawna wartosc saturacji"<<endl;}
                else if(saturation>100){cout<<"nie poprawna wartosc saturacji"<<endl;}
                else{break;}
            }
            int** adjacencyMatrix = generate_adjacency_matrix(nodes, saturation);

            if(graphtype=="list"){
                graph=adjacencyMatrixToList(adjacencyMatrix,nodes);
            }
            else if(graphtype=="table"){
                graph=adjacencyMatrixToEdges(adjacencyMatrix,nodes);
                tablesize=countEdges(adjacencyMatrix,nodes);
            }
            else{
                graph=adjacencyMatrix;

            }
        }
        else if(string(argv[1]) == "--user-provided"){
            while(true){
                cout<<"type (matrix/list/table) > ";
                cin >> graphtype;
                if(graphtype!="matrix" && graphtype!="list" && graphtype!="table"){cout<<"unknown type"<<endl;}
                else{break;}
            }
            while(true){
                cout << "Podaj liczbę wierzchołków: ";
                cin >> nodes;
                if(nodes<1){cout<<"nie poprawna ilosc wezlow"<<endl;}
                else{break;}
            }
            cin.ignore();
            
            int** adjacencyMatrix = generate_matrix_user_provided(nodes);
            if(graphtype=="list"){
                graph=adjacencyMatrixToList(adjacencyMatrix,nodes);
            }
            else if(graphtype=="table"){
                tablesize=countEdges(adjacencyMatrix,nodes);
                graph=adjacencyMatrixToEdges(adjacencyMatrix,nodes);
            }
            else{
                graph=adjacencyMatrix;
            }
        }
        while(true){
            string action = "";
            cout << "action> ";
            cin >> action;
            choice(action,graphtype,graph,nodes,tablesize);
            }

    }

    return 0;
}


