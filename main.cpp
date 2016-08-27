#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <stdlib.h>     /* atoi */
#include <sstream>
using namespace std;
typedef struct Prova Prova;     //Renomear uma struct
typedef struct GabaritoF GabaritoF;
typedef struct aprovado aprovado;
typedef struct provaPesos provaPesos;
typedef struct campusCursos campusCursos;
struct Prova{
    string id;
    string curso;
    string campus;
    string linEx;
    string resposta;
    vector<int> pontuacaoParcial;
    int pontuacao=0;
};
struct provaPesos{
    string idCurso;
    string pesos;
};
struct aprovado{
    string id;
    string curso;
    string campus;
    int pontuacaototal;
};
struct campusCursos{
    string idCampus;
    string idCurso;
    string vagas;
};
struct GabaritoF{
    string Prova;
    string lingEx;
    string resposta;
};



vector<Prova>ProvaPrimeiro;  // Torna-se global
vector<aprovado>classificadoProvas;
vector<Prova>ProvaSegundo;
vector<GabaritoF> GabaritoFinal;
vector<provaPesos> pesosProva;
vector<campusCursos> vagasCampus;
void lerPesos(){
    fstream pesos;
    string linha;
    pesos.open("pesos.txt",ios::in);
        while(pesos.good()){
        getline(pesos, linha);
        provaPesos aux;
        aux.idCurso = linha.substr(0,2);
        aux.pesos = linha.substr(3,10);
        //cout << "IDCURSO: " << aux.idCurso << endl;
        //cout << "PESO: " << aux.pesos << endl;
        pesosProva.push_back(aux);
        }
    pesos.close();
}
void lerVagas(){
    fstream vagas;
    string linha;
    vagas.open("vagas.txt",ios::in);
        while(vagas.good()){
        getline(vagas, linha);
        campusCursos aux;
        aux.idCampus = linha.substr(0,1);
        aux.idCurso = linha.substr(2,2);
        aux.vagas = linha.substr(5,2);
        vagasCampus.push_back(aux);
        }
    vagas.close();
}
int corrigirEtapa(string resposta, string respostaGabarito, int de, int ate){
    int pontos = 0;
    for (int t=de;t<ate;t++){
        if (resposta[t] == respostaGabarito[t]){
            pontos++;
    }
    }
    return pontos;
}
void corrigirProva1(){
    for (int i=0; i<ProvaPrimeiro.size();i++){
        for (int y=0; y<GabaritoFinal.size();y++){
            if (ProvaPrimeiro[i].linEx == GabaritoFinal[y].lingEx){
                string resposta = ProvaPrimeiro[i].resposta;
                string respostaGabarito = GabaritoFinal[y].resposta;
                ProvaPrimeiro[i].pontuacaoParcial.push_back(corrigirEtapa(resposta, respostaGabarito, 0,10));
                ProvaPrimeiro[i].pontuacaoParcial.push_back(corrigirEtapa(resposta, respostaGabarito, 10,40));
            }
        }
    }
}
void corrigirProva2(){
    for (int i=0; i<ProvaSegundo.size();i++){
                string resposta = ProvaSegundo[i].resposta;
                string respostaGabarito = GabaritoFinal[2].resposta;
                        ProvaSegundo[i].pontuacaoParcial.push_back(corrigirEtapa(resposta, respostaGabarito, 0,8));
                        ProvaSegundo[i].pontuacaoParcial.push_back(corrigirEtapa(resposta, respostaGabarito, 8,15));
                        ProvaSegundo[i].pontuacaoParcial.push_back(corrigirEtapa(resposta, respostaGabarito, 15,22));
                        ProvaSegundo[i].pontuacaoParcial.push_back(corrigirEtapa(resposta, respostaGabarito, 22,30));
                        ProvaSegundo[i].pontuacaoParcial.push_back(corrigirEtapa(resposta, respostaGabarito, 30,38));
                        ProvaSegundo[i].pontuacaoParcial.push_back(corrigirEtapa(resposta, respostaGabarito, 38,46));
                        ProvaSegundo[i].pontuacaoParcial.push_back(corrigirEtapa(resposta, respostaGabarito, 46,53));
                        ProvaSegundo[i].pontuacaoParcial.push_back(corrigirEtapa(resposta, respostaGabarito, 53,60));
                }
    }

void compararProva(){
    for (int i =0;i<ProvaPrimeiro.size();i++){
            int pontosPrimeira;
            for (int t=0;t<ProvaPrimeiro[i].pontuacaoParcial.size();t++){
                pontosPrimeira = pontosPrimeira + ProvaPrimeiro[i].pontuacaoParcial[t];
            }
        if (pontosPrimeira>= 12){
            for (int y=0;y<ProvaSegundo.size();y++){
                    int pontosSegundo;
                        for (int t=0;t<ProvaSegundo[y].pontuacaoParcial.size();t++){
                            pontosSegundo = pontosSegundo + ProvaSegundo[i].pontuacaoParcial[t];
                        }
                if (ProvaSegundo[y].id == ProvaPrimeiro[i].id){
                    if (pontosSegundo>=18){
                        aprovado aux;
                        aux.campus = ProvaPrimeiro[i].campus;
                        aux.curso = ProvaPrimeiro[i].curso;
                        aux.id = ProvaPrimeiro[i].id;
                        aux.pontuacaototal = ProvaPrimeiro[i].pontuacao + ProvaSegundo[y].pontuacao;
                        classificadoProvas.push_back(aux);
                    }
                }

            }
        }
    }
}
vector<aprovado> ordenar(vector<aprovado> provas){
    for (int i=0; i<provas.size();i++){
        for (int y=1; y<provas.size();y++){
            if (provas[y].pontuacaototal <= provas[i].pontuacaototal){
                aprovado aux;
                aux = provas[i];
                provas[i] = provas[y];
                provas[y] = aux;
            }

        }

    }
    return provas;
}

void lerProva1(){
    fstream Prova1;
    string linha;
    Prova1.open("prova1.txt",ios::in);
        while(Prova1.good()){
            getline(Prova1, linha);
            Prova aux;
            aux.campus = linha.substr(0,1);
            aux.curso = linha.substr(1,2);
            aux.id = linha.substr(3,6);
            aux.linEx = linha.substr(9,1);
            aux.resposta = linha.substr(10,40);
            //cout << "AUXCAMPUS : " << aux.campus << endl;
            //cout << "AUXCURSO : " << aux.curso << endl;
            //cout << "AUXID : " << aux.id << endl;
            //cout << "AUXLINEX : " << aux.linEx << endl;
            //cout << "AUXRES : " << aux.resposta << endl;
            ProvaPrimeiro.push_back(aux);
        }
    Prova1.close();
}
void lerProva2(){
    fstream Prova2;
    string linha;
    Prova2.open("prova2.txt",ios::in);
        while(Prova2.good()){
            getline(Prova2, linha);
            Prova aux;
            aux.campus = linha.substr(0,1);
            aux.curso = linha.substr(1,2);
            aux.id = linha.substr(3,6);
            aux.linEx = linha.substr(9,1);
            aux.resposta = linha.substr(10,60);
            //cout << "AUXCAMPUS : " << aux.campus << endl;
            //cout << "AUXCURSO : " << aux.curso << endl;
            //cout << "AUXID : " << aux.id << endl;
            //cout << "AUXLINEX : " << aux.linEx << endl;
            //cout << "AUXRES : " << aux.resposta << endl;
            ProvaSegundo.push_back(aux);

        }
    Prova2.close();
}

void Gabarito(){
    fstream Gabarito;
    string linha;
    Gabarito.open("gabarito.txt",ios::in);
        while(Gabarito.good()){
            getline(Gabarito, linha);
            GabaritoF aux;
            aux.lingEx = linha.substr(2,1);
            aux.Prova = linha.substr(0,2);
            aux.resposta = linha.substr(3);
            cout << "AUXLINEX : " << aux.lingEx << endl;
            cout << "AUXRES : " << aux.resposta << endl;
            cout << "PROVA : " << aux.Prova << endl;
            GabaritoFinal.push_back(aux);
        }
    Gabarito.close();
}
void imprimirProva(vector<Prova> provas){
    for (int i=0;i<provas.size();i++){
            Prova aux;
    aux = provas[i];
            cout << "AUXCAMPUS : " << aux.campus << endl;
            cout << "AUXCURSO : " << aux.curso << endl;
            cout << "AUXID : " << aux.id << endl;
            cout << "AUXLINEX : " << aux.linEx << endl;
            cout << "AUXRES : " << aux.resposta << endl;
            cout << "pontuacao parcial: ";
            for (int y=0;y<aux.pontuacaoParcial.size();y++){
                cout << aux.pontuacaoParcial[y] << ";";

            }
            cout << endl;
            cout << "pontuacao: " << aux.pontuacao << endl;
    }
}
void imprimirclassificados(vector<aprovado> provas){
    for (int i=0;i<provas.size();i++){
            aprovado aux;
            aux = provas[i];
            cout << "AUXCAMPUS : " << aux.campus << endl;
            cout << "AUXCURSO : " << aux.curso << endl;
            cout << "AUXID : " << aux.id << endl;
            cout << "pontuacao: " << aux.pontuacaototal << endl;
    }
}
vector<aprovado> separarCurso(int curso, int campus){
    vector<aprovado> cursos;
    stringstream cursoS;
    stringstream campusS;
    if (curso < 10){
        cursoS << "0" << curso;
    }else{
    cursoS << curso;
    }
    campusS << campus;
    for (int i=0;i<classificadoProvas.size();i++){

    //cout << "CURSO: " <<cursoS.str() << endl;
    //cout << "CURSO CLASSIFICADO: " <<classificadoProvas[i].curso << endl;
    //cout << "CAMPUS: " <<campusS.str() << endl;
        if (classificadoProvas[i].curso == cursoS.str()){
            if (classificadoProvas[i].campus == campusS.str()){
                    //cout << "ENTRO" << endl;
                cursos.push_back(classificadoProvas[i]);
            }
        }
    }
    return cursos;
}
void separarCampus(){
    classificadoProvas = ordenar(classificadoProvas);
    string cursosCampus[29] = {"Administracao - Noturno - 80 Vagas","Ciencias Contabeis - Noturno - 32 Vagas","Ciencias Contabeis - Noturno - 80 Vagas","Ciencias Contabeis - Noturno - 32 Vagas","Geografia - Noturno - 32 Vagas","Matematica - Noturno - 40 Vagas","Pedagogia - Vespertino - 32 Vagas","Pedagogia - Noturno - 32 Vagas","Ciências Biológicas  - Noturno - 32Vagas","Direito - Noturno - 63Vagas"," - Educação Físicas (Licenciatura) Noturno - 36Vagas","Educação Física (Bacharelado) - Noturno - 36Vagas","Filosofia - Noturno - 45 Vagas"," Fisioterapia  - Integral - 36 Vagas","História  - Vespertino - 20 Vagas","História  - Noturno - 32 Vagas"," Letras Portugues/Espanhol   - Noturno - 32 Vagas","Letras Portugues/Inglês   - Noturno - 32 Vagas","Matematica   - Noturno - 40 Vagas"," Odontologia  - Integral - 36 Vagas","Pedagogia  - Vespertino - 40 Vagas","Pedagogia  - Noturno - 40 Vagas","Agrinomia - Integral  - 40 Vagas","Ciência  da Computação  - Integral  - 28 Vagas","Ciências Biológicas (Licenciatura/Bacharelado) - Integral  - 40 Vagas","Enfermagem  - Integral - 32 Vagas","Medicina Veterinária  - Integral  - 40 Vagas","Sistemas de Informação  - Noturno - 28 Vagas"};
    ofstream clm;
    clm.open("clm.csv",ios::out);
    clm << "CAMPUS LUIZ MENEGUEL" << endl;
    clm.close();
    ofstream cp;
    cp.open("ccp.csv",ios::out);
    cp << "CAMPUS CORNELIO PROCOPIO" << endl;
    cp.close();
    ofstream jc;
    jc.open("cj.csv",ios::out);
    jc << "CAMPUS JACAREZINHO" << endl;
    jc.close();
            //bandeirantes clm
            for (int i=24;i<=29;i++){
            clm.open("clm.csv",ios::app);
            vector<aprovado> cursos = separarCurso(i,3);
            clm << "CURSO: ;" << cursosCampus[i-1] << endl;
            clm << "IDENTIFICACAO;PONTUACAO;CLASSIFICACAO" << endl;
            for (int y=0;y<cursos.size();y++){
                aprovado aux = cursos[y];
                int totalInserido=0;
                bool classificado=false;
                clm << aux.id << ";" << aux.pontuacaototal;
                for (int e=0;e<vagasCampus.size();e++){
                        stringstream iString;
                        iString << i-1;
                        int vagas = atoi(vagasCampus[e].vagas.c_str());
                    if (vagasCampus[e].idCampus == iString.str()){
                        if (vagas >= totalInserido){
                                classificado = true;
                        }
                    }
                }
                if (classificado == true){
                    clm << ";CLASSIFICADO" << endl;
                    totalInserido++;
                }else{
                clm << ";DESCLASSIFICADO" << endl;
                }
            }
            clm << endl;
            clm.close();
            }
                        //cp
            for (int i=1;i<=9;i++){
            cp.open("ccp.csv",ios::app);
            vector<aprovado> cursos = separarCurso(i,1);
            cp << "CURSO: ;" << cursosCampus[i-1] << endl;
            cp << "IDENTIFICACAO;PONTUACAO;CLASSIFICACAO" << endl;
            for (int y=0;y<cursos.size();y++){
                    int totalInserido=0;
                aprovado aux = cursos[y];
                cp << aux.id << ";" << aux.pontuacaototal;
                bool classificado = false;
                for (int e=0;e<vagasCampus.size();e++){
                        stringstream iString;
                        int vagas = atoi(vagasCampus[e].vagas.c_str());
                        iString << i-1;
                    if (vagasCampus[e].idCampus == iString.str()){
                        if (vagas >= totalInserido){
                                classificado = true;
                        }
                    }
                }
                if (classificado == true){
                    cp << ";CLASSIFICADO" << endl;
                    totalInserido++;
                }else{
                cp << ";DESCLASSIFICADO" << endl;
                }
            }
                cp << endl;
                cp.close();
            }


            //jacarezin

            for (int i=10;i<23;i++){
            jc.open("cj.csv",ios::app);
            vector<aprovado> cursos = separarCurso(i,2);
            jc << "CURSO: ;" << cursosCampus[i-1] << endl;
            jc << "IDENTIFICACAO;PONTUACAO;CLASSIFICACAO" << endl;
            for (int y=0;y<cursos.size();y++){
                aprovado aux = cursos[y];
                int totalInserido = 0;
                bool classificado = false;
                jc<< aux.id << ";" << aux.pontuacaototal;
                for (int e=0;e<vagasCampus.size();e++){
                        stringstream iString;
                        iString << i-1;
                        int vagas = atoi(vagasCampus[e].vagas.c_str());
                    if (vagasCampus[e].idCampus == iString.str()){
                        if (vagas >= totalInserido){
                                classificado = true;
                        }
                    }
                }
                if (classificado == true){
                    jc << ";CLASSIFICADO" << endl;
                    totalInserido++;
                }else{
                jc << ";DESCLASSIFICADO" << endl;
                }
            }
                jc << endl;
                jc.close();
            }

            //aprovado aux = classificadoProvas[i];
                //jc << aux.curso << ";" << aux.id << ";" << aux.pontuacaototal << endl;

}
int calculoPeso(string peso, int acerto){
    int pesos = atoi(peso.c_str());
    return pesos*acerto;
}
void calcularPesosPrimeira(){
    for (int i=0; i< ProvaPrimeiro.size();i++){
        for (int e=0;e<pesosProva.size();e++){
                    if (ProvaPrimeiro[i].curso == pesosProva[e].idCurso){
                        for (int a=0; a<=1;a++){
                            for (int t=0;t<ProvaPrimeiro[i].pontuacaoParcial.size();t++){
                                    //cout << "PESO -> " << pesosProva[e].pesos.substr(a,1) << endl;
                            //cout << "PONTUACAO PARCIAL -> " << ProvaPrimeiro[i].pontuacaoParcial[t] << endl;
                        ProvaPrimeiro[i].pontuacao = ProvaPrimeiro[i].pontuacao + calculoPeso(pesosProva[e].pesos.substr(a,1), ProvaPrimeiro[i].pontuacaoParcial[t]);
                            }
                        }
            }
        }
    }
}
void calcularPesosSegunda(){
    for (int i=0; i< ProvaSegundo.size();i++){
        for (int e=0;e<pesosProva.size();e++){
                    if (ProvaSegundo[i].curso == pesosProva[e].idCurso){
                        for (int a=2; a<10;a++){
                            for (int t=0;t<ProvaSegundo[i].pontuacaoParcial.size();t++){
                                    //cout << "PESO -> " << pesosProva[e].pesos.substr(a,1) << endl;
                            //cout << "PONTUACAO PARCIAL -> " << ProvaSegundo[i].pontuacaoParcial[t] << endl;
                        ProvaSegundo[i].pontuacao = ProvaSegundo[i].pontuacao + calculoPeso(pesosProva[e].pesos.substr(a,1), ProvaSegundo[i].pontuacaoParcial[t]);
                            }
                        }
            }
        }
    }
}
int main(){
lerProva1();
lerProva2();
lerPesos();
lerVagas();
Gabarito();
corrigirProva1();
corrigirProva2();
calcularPesosPrimeira();
//imprimirProva(ProvaPrimeiro);
calcularPesosSegunda();
//imprimirProva(ProvaSegundo);
cout << "APROVADOS" << endl;
compararProva();
//imprimirclassificados(classificadoProvas);
separarCampus();
}
