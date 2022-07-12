#include "iostream"
#include "conio.h"
#include "ctype.h"
#include "stdio.h"
#include "string.h"
#include <cstdlib>
#include <windows.h>
#include <fstream>

/** Sistema de Ventas **/

using namespace std;


struct DetalleAlmacen {
	char codigo[3];
	char RUC[12];
	char material[50];
	int cantidad;
	int precio;
	int total;
};


FILE *fp;
DetalleAlmacen x;

#define tam sizeof(DetalleAlmacen)

char continuar(const char msg[])
{
	char resp;
	do{
		cout<<msg;
		cin>>resp;
		//toupper: Si está entre s y n lo convierte a su equivalente en el rango S y N
		resp=toupper(resp);
	}while(resp!='S' && resp!='N');
	return resp;
 }

void OrdenDeCompra();
void ModificarOrdenDeCompra();
void ReporteOrdenDeCompra();
void ConsultaOrdenDeCompra();

 int main()
 {
	 int op;
	 do{
		 system("cls");
		 cout<<"\t\t\t\t==================="<<endl;
		 cout<<"\t\t\t\t SISTEMA DE VENTAS"<<endl;
		 cout<<"\t\t\t\t==================="<<endl;
		 cout<<"\n\t\t\t[1] Registro Orden de Compra "<<endl;
		 cout<<"\t\t\t[2] Consulta Orden de Compra "<<endl;
		 cout<<"\t\t\t[3] Modificar Orden de Compra "<<endl;
		 cout<<"\t\t\t[4] Reporte de Orden de Compra "<<endl;
		 cout<<"\t\t\t[5] Salir "<<endl;
		 cout<<"\t\t\tIngrese Opción: ";
		 cin>>op;
		 switch(op)
		 {
		 case 1:
			 OrdenDeCompra();
			 getch(); 
			 break;
		 case 2:
			 ConsultaOrdenDeCompra();
			 getch(); 
			 break;
		 case 3:
			 ModificarOrdenDeCompra();
			 getch();
			 break;
		 case 4:
			 ReporteOrdenDeCompra();
			 getch();
			 break;
		 }
	 }while(op!=5);
	 return 0;
 }
 
 void OrdenDeCompra()
 {
	 char resp;
	 fp=fopen("SistemaVentas.dat","ab");
	 
	 do{
		 system("cls");
		 cout<<"\t\t\t\t==================="<<endl;
		 cout<<"\t\t\t\t SISTEMA DE VENTAS"<<endl;
		 cout<<"\t\t\t\t==================="<<endl;
		 cin.get();
		 cout<<"\n\n\t\t\tCódigo : ";
		 cin.getline(x.codigo,3);
		 cout<<"\n\t\t\tRUC :";
		 cin.getline(x.RUC,12);
		 cout<<"\n\t\t\tMaterial : ";
		 cin.getline(x.material,50);
		 cout<<"\n\t\t\tCantidad : ";
		 cin>>x.cantidad;
		 cout<<"\n\t\t\tPrecio : ";
		 cin>>x.precio;
		 cout<<"\n\t\t\tTotal : ";
		 x.total = x.cantidad * x.precio;
		 cout<<x.total;
		 fwrite(&x,tam,1,fp);
		 cout<<endl;
		 resp=continuar("\n\t\t\tDeseas ingresar otro registro(S/N)");
	 }while(resp=='S');
	 fclose(fp);
 } 
 
 void ConsultaOrdenDeCompra(){
	 char resp;
	 char codigo[3];
	 int enc;
	 fp=fopen("SistemaVentas.dat","rb");
	 do{
		 system("cls");
		 cout<<"\t\t\t\t==================="<<endl;
		 cout<<"\t\t\t\t SISTEMA DE VENTAS"<<endl;
		 cout<<"\t\t\t\t==================="<<endl;
		 cin.getline(codigo,3);	   
		 cout<<"\n\n\t\t\tCódigo : ";
		 cin>>codigo;
		 //fseek cuenta los caracteres
		 fseek(fp,0,0);
		 fread(&x,tam,1,fp);
		 enc=0;
		 while(!feof(fp) && enc==0)
		 {
			 if(strcmp(codigo,x.codigo)==0)
			 {
				 cout<<"\n\n\t\t\t\t\tORDEN DE COMPRA"<<endl;
				 cout<<"\n\t\t\tRUC : "<<x.RUC<<endl;
				 cout<<"\n\t\t\tMaterial : "<<x.material<<endl;
				 cout<<"\n\t\t\tCantidad : "<<x.cantidad<<endl;
				 cout<<"\n\t\t\tPrecio : "<<x.precio<<endl;
				 cout<<"\n\t\t\tTotal : "<<x.total<<endl;
				 enc=1;
			 }
			 else
				fread(&x,tam,1,fp);
		 }
		 if(enc==0)
			   cout<<"\n\t\tLa orden de compra no se encuentra..."<<endl;
		 resp=continuar("\n\t\t\tDeseas consultar otra orden (S/N)");
	 }while(resp=='S');
	 fclose(fp);
 }
  
 void ModificarOrdenDeCompra(){
	 char resp;
	 char codigo[3];
	 int enc;
	 fp=fopen("SistemaVentas.dat","rb+");
	 do{
		 system("cls");
		 cout<<"\t\t\t\t==================="<<endl;
		 cout<<"\t\t\t\t SISTEMA DE VENTAS"<<endl;
		 cout<<"\t\t\t\t==================="<<endl;
		 cin.get();
		 cout<<"\n\n\n\t\t\t Ingrese Código :";
		 cin.getline(codigo,3);
		 //fseek cuenta los caracteres
		 fseek(fp,0,0);
		 fread(&x,tam,1,fp);
		 enc=0;
		 //feof retorna un valor distinto de cero
		 while(!feof(fp) && enc==0)
		 {
			 //retorna un número entero mayor, igual, o menor que cero
			 if(strcmp(codigo,x.codigo)==0)
			 {
				 cout<<"\n\n\t\t\t\t\tORDEN DE COMPRA"<<endl;
				 cout<<"\n\t\t\tRUC : "<<x.RUC<<endl;
				 cout<<"\n\t\t\tMaterial : "<<x.material<<endl;
				 
				 cout<<"\n\t\t\t\tINGRESO DE NUEVOS DATOS"<<endl;
				 
				 cout<<"\n\t\t\t\tIngrese nueva cantidad :";
				 cin>>x.cantidad;
				 cout<<"\n\t\t\t\tIngrese nuevo precio :";
				 cin>>x.precio;
				 cout<<"\n\t\t\t\tPrecio total";
				 x.total = x.cantidad * x.precio;
				 cout<<x.total;
				 //fseek retorna un valor distinto de 0
				 fseek(fp,ftell(fp)-tam,0);
				 fwrite(&x,tam,1,fp);
				 enc=1;
			 }
			 else
				fread(&x,tam,1,fp);
		 }
		 if(enc==0)
			   cout<<"La orden de compra no se encuentra..."<<endl;
		 resp=continuar("\n\t\t\tDeseas modificar otra orden (S/N)");
	 }while(resp=='S');
	 fclose(fp);
 }
 
 void ReporteOrdenDeCompra(){
	 fp=fopen("SistemaVentas.dat","rb");
	 system("cls");
	 cout<<"\t\t\t\t==================="<<endl;
	 cout<<"\t\t\t\t SISTEMA DE VENTAS"<<endl;
	 cout<<"\t\t\t\t==================="<<endl;
	 fread(&x,tam,1,fp);
	 cout<<"\t=========================================================================";
	 cout<<"\n\t"<<"CODIGO"<<"\t"<<"RUC"<<"\t\t"<<"MATERIAL"<<"\t\t"<<"CANT"<<"\t"<<"P.U."<<"\t"<<"TOTAL"<<endl;
	 cout<<"\t=========================================================================";
	 while(!feof(fp))
	 {
		 cout<<"\n\t"<<x.codigo<<"\t"<<x.RUC<<"\t"<<x.material<<"\t"<<x.cantidad<<"\t"<<x.precio<<"\t"<<x.total<<endl;
		 fread(&x,tam,1,fp);
	 }
	 fclose(fp);
 }
 

