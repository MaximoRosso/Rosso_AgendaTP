 #include "agenda.h"

bool hayEspacio(sAgenda* miAgenda) {
    return (miAgenda->CantMaxima - miAgenda->CantContactos > 0);
}

/**
 * @brief Función agregar contacto a la agenda
 * @return Error: ErrAgrEspacio, sino ExitoAgregar
 */
eAgrContacto agregarContacto(sAgenda* miAgenda, sContacto miContacto) {
    if (!hayEspacio(miAgenda))
        return eAgrContacto::ErrAgrEspacio;

    miAgenda->CantContactos++;
    miAgenda->misContactos[miAgenda->CantContactos - 1] = miContacto;
    // miAgenda->*(misContactos + i )
    return eAgrContacto::ExitoAgregar;
}

/**
 * @brief Función actualiza el contacto con los datos recibidos dentro de sContacto
 * @return Error: ErrUpdContacto, ErrUpdIndex, sino ExitoModificar
 */
eUpdContacto actualizarContacto(sAgenda* miAgenda, sContacto miContacto) {
    sContacto* aux = miAgenda->misContactos,
             * ultimo = (miAgenda->misContactos) + miAgenda->CantContactos - 1;
    while(true) {
        if ((aux->Nombre == miContacto.Nombre && aux->Apellido == miContacto.Apellido) ||
            (aux->Correo == miContacto.Correo)) {
            *aux = miContacto;
            return eUpdContacto::ExitoModificar;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return eUpdContacto::ErrUpdContacto;
}
/**
 * @brief Función actualiza el contacto en el indice indicado con los datos recibidos dentro de sContacto
 * @return Error: ErrUpdContacto, ErrUpdIndex, sino ExitoModificar
 */
eUpdContacto actualizarContacto(sAgenda* miAgenda, u_int indexContacto, sContacto miContacto) {
    if (indexContacto >= miAgenda->CantMaxima)//el indice pasado esta fuera del rango de la cant de contactos
        return eUpdContacto::ErrUpdIndex;

    sContacto* aux = miAgenda->misContactos + indexContacto;

    if ((aux->Nombre == miContacto.Nombre && aux->Apellido == miContacto.Apellido) ||
        (aux->Correo == miContacto.Correo)) {
        *aux = miContacto;
        return eUpdContacto::ExitoModificar;
    }

    return eUpdContacto::ErrUpdContacto;
}

/**
 * @brief Función remueve al contacto indicado por nombre y apellido
 * @return Error: ErrSrchValor, ErrSrchIndex, sino ExitoBuscar
 */
eRmContacto removerContacto(sAgenda* miAgenda, str Nombre, str Apellido) {
    sContacto* aux = miAgenda->misContactos,
        * ultimo = (miAgenda->misContactos) + miAgenda->CantContactos - 1;
    while(true) {
        if ((aux->Nombre == Nombre && aux->Apellido == Apellido)) {
            *aux = ContactoNulo;
            return eRmContacto::ExitoRemover;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return eRmContacto::ErrRmNomApe;
}
/**
 * @brief Función remueve al contacto indicado por sContacto
 * @return Error: ErrSrchValor, ErrSrchIndex, sino ExitoBuscar
 */
eRmContacto removerContacto(sAgenda* miAgenda, sContacto miContacto) {
    sContacto* aux = miAgenda->misContactos,
        * ultimo = (miAgenda->misContactos) + miAgenda->CantContactos - 1;
    while(true) {
        if ((aux->Nombre == miContacto.Nombre && aux->Apellido == miContacto.Apellido) ||
            (aux->Correo == miContacto.Correo)) {
            *aux = ContactoNulo;
            return eRmContacto::ExitoRemover;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return eRmContacto::ErrRmContacto;
}
/**
 * @brief Función remueve al contacto indicado por indice
 * @return Error: ErrSrchValor, ErrSrchIndex, sino ExitoBuscar
 */
eRmContacto removerContacto(sAgenda* miAgenda, u_int indexContacto) {
    if (indexContacto >= miAgenda->CantMaxima)
        return eRmContacto::ErrRmIndex;

    sContacto* aux = miAgenda->misContactos + indexContacto;
    *aux = ContactoNulo;
    return eRmContacto::ExitoRemover;
}

eRmContacto removerContacto(sAgenda* miAgenda, eGrupo grupoContacto) {//ESTA ES LA REMOVER POR GRUPO

    sContacto* aux = miAgenda->misContactos,
        * ultimo = (miAgenda->misContactos) + miAgenda->CantContactos - 1;// sirve para saber cuantos son porque con esto tengo apuntada la 1era pos y la ultima

    while(true) {
        if (aux->Grupo == grupoContacto) {//busco el contacto que tenga el mismo grupo que el pasado a la funcion
            *aux = ContactoNulo;
            return eRmContacto::ExitoRemover;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return eRmContacto::ErrRmGrupo;
}
/**
 * @brief Función de buscar contacto por Nombre Y Apellido o email
 * @return Error: Nullptr, sino Contacto
 */
sContacto buscarContacto(sAgenda* miAgenda, str valorBusqueda) {
    sContacto* aux = miAgenda->misContactos,
        * ultimo = (miAgenda->misContactos) + miAgenda->CantContactos - 1;
    while(true) {
        if (((aux->Nombre + " " + aux->Apellido) == valorBusqueda) ||
            (aux->Correo == valorBusqueda)) {
            return *aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return ContactoNulo;
}
/**
 * @brief Función de buscar contacto por indice
 * @return Error: Nullptr, sino Contacto
 */
sContacto buscarContacto(sAgenda* miAgenda, u_int indexContacto) {
    return indexContacto >= miAgenda->CantContactos - 1 ? ContactoNulo : miAgenda->misContactos[indexContacto];//LO HAGO DIRECTAMENTE TODO EN UNA LINEA CON EL IF TERNARIO
}

void OrdenarPorApellido(sAgenda* miAgenda) {
    sContacto* ultimoContacto = miAgenda->misContactos + miAgenda->CantContactos - 1;

    for(u_int i = 0; i < miAgenda->CantContactos - 1; i++) {
        sContacto& Actual = miAgenda->misContactos[i]; // *(miAgenda->misContactos + i)
        char Ape1 = (Actual.Apellido[0] >= 'A' && Actual.Apellido[0] <= 'Z') ?
                        Actual.Apellido[0] + ('a' - 'A') : Actual.Apellido[0];
        for(sContacto* miContacto = miAgenda->misContactos; miContacto == ultimoContacto; miContacto++) {
            char Ape2 = (miContacto->Apellido[0] >= 'A' && miContacto->Apellido[0] <= 'Z') ?
                            miContacto->Apellido[0] + ('a' - 'A') : miContacto->Apellido[0];

            if(Ape1 > Ape2) {
                sContacto aux = Actual;
                Actual = *miContacto;
                *miContacto = aux;
            }
        }
    }
}

void ListarPorGrupo(sAgenda miAgenda, sAgrupar*& Agrupados) {
    Agrupados = new sAgrupar[5];
    for(u_int i = 0; i < eGrupo::UNIVERSIDAD; i++) {
        Agrupados[i].contactos = new sContacto[6];
        Agrupados[i].tam = 6;
        Agrupados[i].actual = 0;
        Agrupados[i].Grupito = Grupos[i];
    }
    sContacto* Ultimo = miAgenda.misContactos + miAgenda.CantContactos;

    for(u_int i = 0; i < eGrupo::UNIVERSIDAD; i++) {
        for(sContacto* miContacto = miAgenda.misContactos; miContacto != Ultimo; miContacto++) {
            if(miContacto->Grupo == i) {
                if(Agrupados[i].actual == Agrupados[i].tam) {
                    Agrupados[i].contactos = resizeContactos(Agrupados[i].contactos, Agrupados[i].tam, Agrupados[i].tam + BLK);
                    Agrupados[i].tam += BLK;
                }

                Agrupados[i].contactos[Agrupados[i].actual] = *miContacto;
                Agrupados[i].actual++;
            }
        }
    }
    delete Agrupados;
}

//IMPRIMIR POR GRUPO REQUERIDO//
ePrContacto imprimirGrupo(sAgenda *miAgenda, eGrupo Grupo){
    sContacto* aux = miAgenda->misContactos,
        * ultimo = (miAgenda->misContactos) + miAgenda->CantContactos - 1;
    while(true){
        if(aux->Grupo == Grupo){//busco los que pertenezcan al grupo que se busca imprimir
            std::cout<< miAgenda->misContactos->Nombre<< miAgenda->misContactos->Apellido<<std::endl;//imprimo sus datos
            return ePrContacto :: ExitoPrint;//devuelvo que se pudo imprimir
        }
        if(aux == ultimo)
            return ePrContacto :: ErrPrContacto;// no se encontro nadie para imprimir
        aux++;//incremento para avanzar de direccion de memoria
    }
}

ePrContacto imprimirGrupo(sAgenda *miAgenda){
    sContacto* aux = miAgenda->misContactos,
        * ultimo = (miAgenda->misContactos) + miAgenda->CantContactos - 1;
    int i ,contador;
    i=contador=0;
    while(true){

        if(aux->Grupo == i){
            std::cout<< miAgenda->misContactos->Nombre<< miAgenda->misContactos->Apellido<<std::endl;//imprimo sus datos
            contador++;//cuento que imprimio
            return ePrContacto :: ExitoPrint;//devuelvo que se pudo imprimir
            if(aux == ultimo){// si llegue al final
                aux=miAgenda->misContactos;//vuelvo a la cabeza
                i++;// cambio de grupo
            }
        }
        if(contador == 0)//no imprimio nunca a nadie
            return ePrContacto :: ErrPrContacto;// no se imprimio
    }

}






