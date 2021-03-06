#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int id;
    char nombre[30];
    char domicilio[30];
    char localidad[30];
    int eliminado;   // indica 1 o 0 si el cliente fue eliminado
} stCliente;
typedef struct
{
    int id_cliente;
    char usuario[20];
    int pass[2][5];
    int eliminado;  // indica 1 o 0 si el cliente fue eliminado
} stUsuario;
typedef struct
{
    int id_cliente;
    char usuario[20];
    char pass[10];
} stUsuarioListado;
int escribirusuario(stUsuario buf[],char archivo2[],int validos)
{
    int i=0;
    FILE *archi;

    if(archi=fopen(archivo2,"rb")==NULL)
    {
        archi=fopen(archivo2,"wb");

    }
    else
    {
        archi=fopen(archivo2,"ab");
    }
    if(archi!=NULL)
    {
        for(i=0; i<validos; i++)
        {

            fwrite(&buf[i],sizeof(stUsuario),1,archi);
        }
    }
    fclose(archi);
}
int escribircliente(stCliente buf[],char archivo1[],int validos)
{
    int i=0;
    FILE *archi;

    if(archi=fopen(archivo1,"rb")==NULL)
    {
        archi=fopen(archivo1,"wb");

    }
    else
    {
        archi=fopen(archivo1,"ab");
    }
    if(archi!=NULL)
    {
        for(i=0; i<validos; i++)
        {

            fwrite(&buf[i],sizeof(stCliente),1,archi);
        }
    }
    fclose(archi);
}
int crearid(char archivo1[])
{
    int id=0;
    FILE *archi;
    stCliente buf;

    archi=fopen(archivo1,"rb");

    if(archi==NULL)
    {
        id=1;
    }
    else
    {
        fseek(archi, sizeof(stCliente)*(-1), SEEK_END);
        fread(&buf,sizeof(stCliente),1, archi);
        id=buf.id+1;
    }
    fclose(archi);
    return id;

}
stUsuario cargarusuario(char archivo2[],int ultimoID)
{
    stUsuario buf;
    stCliente buf2;



    printf("Id del usuario %d \n",ultimoID);
    buf.id_cliente = ultimoID;


    printf("Ingrese el usuario:\n");
    fflush(stdin);
    gets(&buf.usuario);





    return buf;

}
stCliente cargarcliente(char archivo1[], int ultimoID)
{
    stCliente buf;


    printf("Id del cliente %d\n",ultimoID);

    buf.id = ultimoID;

    printf("Ingrese el nombre del cliente \n");
    fflush(stdin);
    gets(&buf.nombre);

    printf("Ingrese el domicilio del cliente: \n");
    fflush(stdin);
    gets(&buf.domicilio);


    printf("Ingrese la localidad del cliente \n");
    fflush(stdin);
    gets(&buf.localidad);



    return buf;
}
int cargarestructura(stUsuario buf2[],stCliente buf[],char archivo1[],char archivo2[])
{
    int i=0;

    char letra='s';

    int ultimoID = crearid(archivo1);

    while(letra=='s')
    {
        buf[i]=cargarcliente(archivo1,ultimoID);
        buf2[i]=cargarusuario(archivo2,ultimoID);

        ultimoID++;
        printf("Desea cargar  otro cliente/usuario ? \n");
        fflush(stdin);
        scanf("%c",&letra);
        i++;

    }
    return i;

}
void mostrarlistado(char archivo2[])
{
    stUsuario buf;
    FILE *archi;

    archi=fopen(archivo2,"rb");



    if(archi==NULL)
    {
        printf("No se encuentra ningun usuario en el archivo \n");

    }
    else
    {
        while(fread(&buf,sizeof(stUsuario),1,archi)>0)
        {
            printf("%ID:%d\n", buf.id_cliente);
            printf("Usuario: %s\n",buf.usuario);
            printf("Contraseña:%c \n",buf.pass); ///NO FUNKAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        }
    }
    fclose(archi);
}
int passescriptada(char archivo2[])
{
    stUsuario buf;
    int cantidad=0;
    char pass[10];
    int pass2[10];
    int matriz[2][5];
    int i=0;
    int k=0;
    int f=0;
    int c=0;

    printf("Ingrese la contraseña del usuario: \n");
    fflush(stdin);
    scanf("%s",&pass);

    cantidad=strlen(pass);

    if(cantidad!=10)
    {
        printf("Error,la password no contiene 10 caracteres \n");
    }
    else
    {
        for(i=0; i<10; i++)
        {
            pass[i]=tolower(pass[i]);
            pass2[i]=pass[i]; ///Transforma las letras mayusculas en miniscula

            if(pass2[i]>=97 && pass2[i]<=122)
            {
                pass2[i]=pass2[i]-96;   ///Cambio los valores de las letras de ascii a (a=1,b=2,c=3,.....)
            }

        }
}

   for(f=0;f<2;f++)
   {
       for(c=0;c<5;c++)
       {
           matriz[f][c]=pass2[k];
           printf(" %d ",matriz[f][c]);    ///Paso los elemento del arreglo pass2 a la matriz
           k++;
       }
       printf("\n");
   }

}



int main()
{

    /*char archivo1[15]="clientes.dat";

    stCliente cli[10];
    stUsuario usu[10];
    int validos=cargarestructura(usu,cli,archivo1,archivo2);
    escribircliente(cli,archivo1,validos);
    escribircliente(usu,archivo2,validos);
    mostrarlistado(archivo2);*/
    char archivo2[15]="usuarios.dat";
    passescriptada(archivo2);


    /*int opcion=0;
    printf("1-Administracion de clientes:\n2-Ingreso con user y pass:\nIngrese la opcion que desea ejecutar:");
    fflush(stdin);
    scanf("%d", &opcion);

    switch(opcion)
    {
    case 1:
        printf("1-Submenu administracion de clientes:\n ");
        printf("1-Alta:\n 2-Baja:\n 3-Modificacion:\n 4-Consultas:\n 5-Listados:\nIngrese una opcion:");
        fflush(stdin);
        scanf("%d",&opcion);
        switch(opcion)
        {
        case 1:
            printf("Alta\n");
            break;
        case 2:
            printf("Baja\n");
            break;
        case 3:
            printf("Modificacion\n");
            break;
        case 4:
            printf("Consultas\n");
            break;
        case 5:
            printf("Listados\n Sub-menu listados de clientes(ordenar)\n 1-Por ID:\n 2-Por apellido:\n 3-Por domicilio;\n\n Ingrese opcion:");
            fflush(stdin);
            scanf("%d", &opcion);
            switch(opcion)
            {
            case 1:
                printf("Por ID\n");
                break;
            case 2:
                printf("Por apellido\n");
                break;
            case 3:
                printf("Por domicilio\n");
                break;

            default:
                printf("Comando Incorrecto:\n");
                break;
            }
        default:
            printf("Comando Incorrecto:");
            break;
        }
    break;
    case 2:
        printf("2-Ingreso con user y pass\n");
        break;
    default:
        printf("Comando Incorrecto:\n");
        break;

    }



    /// Para la eliminacion usar fseek -1 fseek(archi,(-1),sizeof(),seek_cur
    /// Abrir R+B para uqe deje el cursor al inicio tanto para leer como para escribir ( ͡° ͜ʖ ͡°)*/

    return 0;
}
