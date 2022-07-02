/*
    Nombre del proyecto de diseño del curso de idioma c: sistema de simulación de cajero automático
	 Autor: Shi Ruiwen 
	 Especialidad: Ingeniería de software (Business Intelligence) 
	 Hora: 2018.2.27 
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h> 
#define N sizeof(struct Account)
#define M sizeof(struct Money)
 struct Account // Información de la cuenta 
{
	 char name [10]; // Apodo de la cuenta 
	 char contraseña [18]; // contraseña 
	 struct Account * next; // Campo de puntero 
};
typedef struct Account Acc;
typedef Acc *Accp;
 
 struct Money // Money 
{
	float money;
	 char time [10]; // Hora
	 char date [10]; // fecha 
	struct Money *next;
};
typedef struct Money mon;
typedef mon *monp;
 
 // Área de declaración de funciones 
 void HideCursor (); // Ocultar el cursor
 void toxy (int x, int y); // Mueve el cursor a las coordenadas X, Y
 void color (short x); // Establecer el color
 void menu (); // Menú 
 Accp ff (); // Leer el contenido del archivo  
 void signin (); // Iniciar sesión o registrarse 
 void login (); // Registrar cuenta 
 void logon (); // Inicio de sesión de cuenta   
 void correct_password (); // Modificar contraseña
 void add_money (); // Depositar 
 void find_money (); // Consulta 
 void get_money (); // Retirar dinero
 void transfer_money (); // transferencia
 void save_account (Accp p); // Guarda el contenido apuntado por p en el archivo
 void save_money (monp p); // Guarda el contenido apuntado por p en el archivo 
 float Sum (); // Encuentra el saldo 
 void over (); // Salir del sistema  
 void list (); // Detalles de la factura 
monp ss();
 
 
 char _name [20], _ contraseña [18]; // Las variables globales recuerdan la cuenta de inicio de sesión actual 
 
void color(short x)
{
	if(x>=0&&x<=15)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	}
} 
 
 void HideCursor () // Ocultar el cursor
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
 
 void toxy (int x, int y) // Mueve el cursor a las coordenadas X, Y
{
COORD pos = { x , y };
HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(Out, pos); 
}
 
 Accp ff () // Muestra el contenido del archivo con la cuenta a la lista vinculada
{
	 ARCHIVO * fp; // Puntero de archivo 
	int n=0;
	Accp head=NULL;
	Accp p2,p;
	 fp = fopen ("cuenta", "a +"); // Abre el archivo en modo de solo lectura 
	if(fp==NULL)
	{
		printf("cannot open file\n");
	}
	else
	{
		 while (! feof (fp)) // Juzgar si la marca de posición del archivo se ha movido al final del archivo 
		{
		   n++;
		   	 p = (Accp) malloc (N); // Aplicar un espacio de la memoria 
		    fread (p, N, 1, fp); // Asignar el contenido del archivo apuntado por fp ap 
		   if(n==1)
		   {
		      head=p;
		      p2=p;
		    }
		     else // Crea una lista vinculada 
		    {
		    	p2->next=p;
		    	p2=p;
			}
	    }
	    p2->next=NULL;
	}
         fclose (fp); // Cerrar el archivo 
         return head; // return head puntero 
}
 
 void menu () // Menú 
{
	 system ("cls"); // Limpiar la pantalla  
	do{
		 color (14); // Mira el color cómodo
		char t;
		toxy(50,5);
		 printf ("Sistema de simulación de cajeros automáticos");
		toxy(50,6);
		 printf ("La cuenta actual es:% s", _ nombre);
		toxy(48,8);
		 printf ("| 1. Retirar dinero |");
		toxy(48,10);
		 printf ("| 2. Transferir |");
		toxy(48,12);
		 printf ("| 3. Balance |");
		toxy(48,14);
		 printf ("| 4. Detalles |");
		toxy(48,16);
		 printf ("| 5. Depositar |");
		toxy(48,18);
		 printf ("| 6. Modificar contraseña |"); 
		toxy(48,20);
		 printf ("| 7.Salir del sistema |");
		 t = getch (); // Usando la función sin eco, ingrese t, no necesita presionar manualmente la tecla enter 
		switch(t)
		{
			case '1':get_money();break; 
			case '2':transfer_money();break;
			case '3':find_money();break;
			case '4':list();break; 
			case '5':add_money();break;
			case '6':amend_password();break;
			case '7':over();break;
			default :;break;
		}
         } while (1); // Siempre cierto 
}
 
 void signin () // Iniciar sesión o registrarse 
{
	system("cls");
	color(12); 
	 HideCursor (); // Ocultar el cursor
	char t;
	toxy(50,5);
	 printf ("Sistema de simulación de cajeros automáticos");
	toxy(44,8);
	printf("----------------------------");
	toxy(45,10);
	printf ("Por favor ingrese (1: iniciar sesión; 2: registrarse)");
	toxy(44,12);
	printf("----------------------------");
	while(1)
	{
		t=getch();
		switch(t)
		{
			case '1':logon();break;
			case '2':login();break;
			default :break;
		}
	}
}
 
 void logon () // Inicio de sesión de cuenta 
{ 
	 system ("cls"); // Limpiar la pantalla 
	 color (10); // Establecer el color 
	Accp p,head;    
	 head = ff (); // Llama a la función, el valor de retorno es el puntero del nodo principal 
    do{
	    p=head;
	    char t,c,k;
	    int i=0;;
		toxy(50,5);
		 printf ("Sistema de simulación de cajeros automáticos");
		toxy(45,6);
		printf("***************************");
		toxy(45,8);
		 printf ("Estado de inicio de sesión");
		toxy(45,10);
		 printf ("* Por favor ingrese su número de cuenta:");
		gets(_name);
		toxy(45,12);
		 printf ("* Por favor ingrese su contraseña:");
		 for (;;) // Aquí está la operación de ingresar la contraseña sin eco 
		{
			 k = getch (); // Ingrese k 
			 if (k == '\ r') // Si la entrada k es un retorno de carro, salta del bucle 
			{
				break;
			}
			 else if (k == '\ b') // Si la entrada k es la tecla de borrar 
			{
				 if (i> 0) // Si la contraseña no se ha eliminado por completo 
				{
					printf("\b");
					printf(" ");
					printf("\b");
					i--;
				}
			}
			 else // Si la entrada k no es la tecla borrar ni la tecla enter 
			{
				 _password [i] = k; // Asignar el valor de k a _password [i]; 
				 printf ("*"); // salida * para proteger la privacidad del usuario 
				 i ++; // Suma 1 al número de dígitos de la contraseña 
			}
		}
		_password[i]='\0';
		 while (p! = NULL && strcmp (p-> name, _name)! = 0) // Recorre la lista vinculada para encontrar la cuenta de la cuenta ingresada actualmente 
		{
			p=p->next;
		}
		 if (p! = NULL) // Si p no está vacío 
		{
	    	 if (strcmp (p-> contraseña, _ contraseña) == 0) // Si la contraseña ingresada es correcta 
			{
				toxy(48,16);
				 printf ("Iniciando sesión ...");
				 Dormir (500); // Pausa durante 0,5 segundos
				system("cls");
				color(10);
				toxy(48,10);
				 printf ("¡Inicio de sesión exitoso!");
				 break; // fuera del bucle
			}
			 else // Si la contraseña ingresada es incorrecta
			{ 
				toxy(48,16);
				 printf ("Iniciando sesión ...");
				Sleep(500);
				system("cls");
				color(10);
				toxy(46,8);
				printf("-------------------------");
				toxy(46,9);
				printf("|                       |");
				toxy(46,10);
				 printf ("| Contraseña incorrecta! ¿Desea continuar? |");
				toxy(46,12);
				 printf ("| 1. Sí 2. No |");
				toxy(46,13);
				printf("|                       |");
				toxy(46,14);
				printf("-------------------------");
				while(1)
				{
					 t = getch (); // Ingrese t    
					if(t=='1')          
					{
						 system ("cls"); // Limpiar la pantalla 
						color(10); 
						break;
					}
					 else if (t == '2') // Si la entrada t es n, ingrese a la interfaz de inicio 
					{
						signin();break;
					}
				}
			} 
	   }
	    else // Si p está vacío, el número de cuenta ingresado es incorrecto 
	   {
	   	    toxy(48,16);
	   	     printf ("Iniciando sesión ...");
	   	    Sleep(500);
	   	    system("cls");
	   	    color(10);
	   	    toxy(46,8);
	   	    printf("-------------------------");
	   	    toxy(46,9);
	   	    printf("|                       |");
	   		toxy(46,10);
			 printf ("| Error de cuenta. ¿Desea continuar? |");
			toxy(46,11);
			printf("|                       |");
			toxy(46,12);
			 printf ("| 1. Sí 2. No |"); 
			toxy(46,13);
			printf("|                       |");
			toxy(46,14);
			printf("-------------------------");
			 while (1) // Bucle sin fin para evitar la interferencia de otros botones 
			{
				c=getch();
				if(c=='1')
				{  
					system("cls");
					color(10);
					break;
				}
				else if(c=='2')
				{
					signin();break;
				}
			}
	   }
         } while (1); // Siempre cierto 
       Dormir (500); // Pausa durante 0,5 segundos 
       menu (); // La cuenta y contraseña son correctas, ingrese al menú principal 
}
 
 void login () // registrar cuenta 
{
	
	system("cls");
	color(10); 
	Accp p1;
	 p1 = (Accp) malloc (N); // Aplicar un espacio de la memoria 
	do{
		color(10);
		char name[20],password[18],againpassword[18],c,k;
		int i=0;; 
		toxy(50,5);
		 printf ("Sistema de simulación de cajeros automáticos");
		toxy(45,6);
		printf("**************************");
		toxy(45,8);
		 printf ("Registrando");
		toxy(45,10);
		 printf ("* Por favor ingrese el número de cuenta:");
		gets(name);
		toxy(45,12);
		 printf ("* Por favor ingrese la contraseña:");
		 for (;;) // Aquí está la operación de ingresar la contraseña sin eco 
		{
			 k = getch (); // Ingrese k 
			 if (k == '\ r') // Si la entrada k es un retorno de carro, salta del bucle 
			{
				break;
			}
			 else if (k == '\ b') // Si la entrada k es la tecla de borrar 
			{
				 if (i> 0) // Si la contraseña no se ha eliminado por completo 
				{
					printf("\b");
					printf(" ");
					printf("\b");
					i--;
				}
			}
			 else // Si la entrada k no es la tecla borrar ni la tecla enter 
			{
				 contraseña [i] = k; // Asignar el valor de k a _ contraseña [i]; 
				 printf ("*"); // salida * para proteger la privacidad del usuario 
				 i ++; // Suma 1 al número de dígitos de la contraseña 
			}
		}
		password[i]='\0';
		i=0;
		toxy(45,14);
		 printf ("* Confirma tu contraseña:");
		 for (;;) // Aquí está la operación de ingresar la contraseña sin eco 
		{
			 k = getch (); // Ingrese k 
			if (k == '\ r') // Si la entrada k es un retorno de carro, salta del bucle 
			{
				break;
			}
			 else if (k == '\ b') // Si la entrada k es la tecla de borrar 
			{
				 if (i> 0) // Si la contraseña no se ha eliminado por completo 
				{
					printf("\b");
					printf(" ");
					printf("\b");
					i--;
				}
			}
			 else // Si la entrada k no es la tecla borrar ni la tecla enter 
			{
				 againpassword [i] = k; // Asignar el valor de k a _password [i]; 
				 printf ("*"); // salida * para proteger la privacidad del usuario 
				 i ++; // Suma 1 al número de dígitos de la contraseña 
			}
		}
		againpassword[i]='\0';
		 if (strcmp (password, againpassword) == 0) // Si las dos contraseñas ingresadas son correctas 
		{
			strcpy(p1->name,name);
			strcpy(p1->password,password);
			toxy(48,16);
			 printf ("Registrando ...");
			Sleep(500);
			system("cls");
			color(12);
			toxy(48,10);
			 printf ("¡Registrado correctamente!");
			 Dormir (500); // Pausa durante 0,5 segundos 
			 break; // fuera del bucle 
		}
		 else // Si las dos contraseñas ingresadas son diferentes 
		{
			toxy(48,16);
			 printf ("Registrando ...");
			Sleep(500);
			system("cls");
			color(12);
			toxy(46,8);
			printf("-----------------------------");
			toxy(46,9);
			printf("|                           |");
			toxy(46,10);
			 printf ("| ¡Registro fallido! ¿Desea continuar con el registro? |");
			toxy(46,11);
			printf("|                           |");
			toxy(46,12);
			 printf ("| 1. Sí 2. No |"); 
			toxy(46,13);
			printf("|                           |");
			toxy(46,14);
			printf("-----------------------------");
			while(1)
			{
				c=getch();
				if(c=='1')
				{
					system("cls");
					color(12);
					break;
				}
				else if(c=='2')
				{
					signin();
					break;
				}
			}
		}
	 } while (1); // Siempre cierto 
	 save_account (p1); // llamar a la función para almacenar el contenido apuntado por p1 en el archivo 
	toxy(48,12);
	 printf ("Iniciar sesión automáticamente por ti ...");
	Sleep(500);
	 menu (); // Ingrese al menú principal después de un registro exitoso 
}
 
 
 /*Cambia la contraseña 
 El método es estúpido, aquí está la información de la cuenta almacenada en el archivo
 Salida en una lista vinculada, recorra la lista vinculada, encuentre el número de cuenta actualmente conectado, modifique la p-> contraseña del nodo,
 Luego guarde la lista enlazada modificada en el archivo Debe tenerse en cuenta que el contenido del archivo debe guardarse después de la modificación.
 Vacío*/ 
 void modified_password () // Modificar contraseña 
{ 
	 system ("cls"); // Limpiar la pantalla 
	 color (14); // Mira el color cómodo 
	HideCursor();  
	 Accp p, head; // Ocultar el cursor, lucir más cómodo 
	head=ff();
	FILE *fp;
    do
    {
    	color(14);
    	     HideCursor (); // Ocultar el cursor, lucir cómodo 
    	p=head;
    	char password[18],newpassword[18],t,k;
    	int i=0;
    	     toxy (50,5); // Mueve el cursor a la posición con coordenadas (50,5) 
		 printf ("Sistema de simulación de cajeros automáticos");
		toxy(50,8);
		 printf ("Modificar contraseña");
		toxy(48,10);
		 printf ("Introduzca la contraseña anterior:");
		 for (;;) // Aquí está la operación de ingresar la contraseña sin eco 
		{
			 k = getch (); // Ingrese k 
			 if (k == '\ r') // Si la entrada k es un retorno de carro, salta del bucle 
			{
				break;
			}
			 else if (k == '\ b') // Si la entrada k es la tecla de borrar 
			{
				 if (i> 0) // Si la contraseña no se ha eliminado por completo 
				{
					printf("\b");
					printf(" ");
					printf("\b");
					i--;
				}
			}
			 else // Si la entrada k no es la tecla borrar ni la tecla enter 
			{
				 contraseña [i] = k; // Asignar el valor de k a _ contraseña [i]; 
				 printf ("*"); // salida * para proteger la privacidad del usuario 
				 i ++; // Suma 1 al número de dígitos de la contraseña 
			}
		}
		password[i]='\0';
		i=0;
		toxy(48,12);
		 printf ("Introduzca una nueva contraseña:");
		 for (;;) // Aquí está la operación de ingresar la contraseña sin eco 
		{
			 k = getch (); // Ingrese k 
			 if (k == '\ r') // Si la entrada k es un retorno de carro, salta del bucle 
			{
				break;
			}
			 else if (k == '\ b') // Si la entrada k es la tecla de borrar 
			{
				 if (i> 0) // Si la contraseña no se ha eliminado por completo 
				{
					printf("\b");
					printf(" ");
					printf("\b");
					i--;
				}
			}
			 else // Si la entrada k no es la tecla borrar ni la tecla enter 
			{
				 newpassword [i] = k; // Asignar el valor de k a _password [i]; 
				 printf ("*"); // salida * para proteger la privacidad del usuario 
				 i ++; // Suma 1 al número de dígitos de la contraseña 
			}
		}
		newpassword[i]='\0';
		 while (p! = NULL && strcmp (p-> name, _name)! = 0) // recorre la lista vinculada para encontrar la cuenta de la cuenta de inicio de sesión actual 
		{
			p=p->next;
		}
		 if (p! = NULL) // Si p no está vacío 
		{
			if (strcmp (p-> contraseña, contraseña) == 0) // Si la contraseña anterior se ingresó correctamente 
			{
				 strcpy (p-> contraseña, nueva contraseña); // Cambia la contraseña anterior por la nueva contraseña 
				 break; // fuera del bucle 
			}
			 else // Si la contraseña anterior se ingresa incorrectamente 
			{
				system("cls");
				color(12);
				toxy(46,8);
				printf("--------------------------");
				toxy(46,9);
				printf("|                        |");
				toxy(46,10);
				 printf ("| ¡Contraseña incorrecta! ¿Continuar? |");
				toxy(46,11);
				printf("|                        |");
				toxy(46,12);
				 printf ("| 1. Sí 2. No |");
				toxy(46,13);
				printf("|                        |");
				toxy(46,14);
				printf("--------------------------");
				while(1)
				{
					 t = getch (); // Ingrese t 
					if(t=='1')
					{
						system("cls");
						color(12);
						break;
					}
					else if(t=='2')
					  menu();
				}
			}
		}
	 } while (1); // Siempre cierto 
	 p = head-> next; // hacer que p apunte al segundo nodo 
	 fp = fopen ("cuenta", "w"); // Primero vacíe el contenido del archivo original y luego escriba la información modificada en el archivo 
	if(fp==NULL)
	{
		printf("cannot open file\n");
	}
	 if (fwrite (head, N, 1, fp)! = 1) // Escribe los datos apuntados por head en el archivo apuntado por fp 
	{
		printf("file write error\n");
	}
	 fclose (fp); // Cerrar el archivo 
	 fp = fopen ("cuenta", "a"); // Abra el archivo de la cuenta agregando 
	 while (p! = NULL) // Ejecuta el cuerpo del bucle si p no está vacío 
	{
		 if (fwrite (p, N, 1, fp)! = 1) // Escribe una estructura de datos de tamaño N apuntado por p en el archivo apuntado por fp 
	    {
		printf("file write error\n");
	    }
	     p = p-> siguiente; // hacer que p apunte al siguiente nodo 
	}
	 fclose (fp); // Cerrar el archivo 
	toxy(48,14);
	 printf ("¡Modificado con éxito! Saltando ...");
	 Dormir (500); // Pausa durante 0,5 segundos 
}
 
 
 void save_account (Accp p1) // Almacena el contenido apuntado por p1 en el archivo 
{
	 ARCHIVO * fp; // Puntero de archivo 
	 fp = fopen ("cuenta", "a"); // Abre el archivo agregando 
	if(fp==NULL)
	{
		printf("cannot open file\n");
	}
	 if (fwrite (p1, N, 1, fp)! = 1) // Escribe una estructura de datos de tamaño N apuntada por p1 en el archivo apuntado por fp 
	{
		printf("file write error\n");
	}
	 fclose (fp); // Cerrar el archivo 
}
 
 void add_money () // Depositar 
{
	do
	{
		 system ("cls"); // Limpiar la pantalla 
		color(11);
		monp p;
		char t; 
		char time[10],date[10];
		 p = (monp) malloc (M); // Solicita un espacio de la memoria 
		toxy(48,8);
		 printf ("Por favor ingrese la cantidad que necesita depositar:");
		scanf("%f",&p->money);
		 getchar (); // absorber la tecla enter 
		_tzset(); 
        _strtime(time);      
        strcpy(p->time,time);
        _strdate(date);
		strcpy(p->date,date);   
		toxy(48,10);
		 printf ("En funcionamiento, espere ...");
		Sleep(500);
		save_money(p);
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		 printf ("| Guardado correctamente. ¿Desea continuar? |");
		toxy(46,12);
		 printf ("| 1. Sí 2. No |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)
		{
			t=getch();
			if(t=='1')
			{
				break;
			}
			else if(t=='2')
			{
				menu();
			}
		}
	}while(1);
}
 
 void find_money () // Consultar saldo 
{
	system("cls");
	color(13);
	float sum=0;
	sum=Sum();
	toxy(46,12);
	 printf ("El saldo es:% f", suma);
	toxy(46,16);
	 printf ("Presione cualquier tecla para regresar al menú principal");
	getch();
	menu(); 
}
 
 void get_money () // Retirar dinero 
{
	do
	{
		system("cls");
		color(11);
		monp p;
		float money,sum;
		char t;
		char time[10],date[10];
		toxy(46,12);
		 printf ("Ingrese la cantidad que desea retirar:");
		scanf("%f",&money); 
		 getchar (); // Absorbe la tecla enter 
		sum=Sum();
		 if (dinero> suma) // Si la cantidad a tomar es mayor que el saldo 
		{
			toxy(46,14);
			 printf ("Saldo insuficiente, ¡vuelve a ingresar!");
			Sleep(500);
			 continuar; // Finalizar este ciclo 
		}
		 p = (monp) malloc (M); // Solicita un espacio de la memoria 
		_tzset(); 
        _strtime(time);      
        strcpy(p->time,time);
        _strdate(date);
		strcpy(p->date,date);  
		p->money=-money;
		save_money(p);      
		toxy(46,14);
		 printf ("En funcionamiento, espere ...");
		Sleep(500);
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		 printf ("| Retiro exitoso! ¿Quieres continuar? |");
		toxy(46,12);
		 printf ("| 1. Sí 2. No |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)
		{
			t=getch();
			if(t=='1')
			{
				break;
			}
			else if(t=='2')
			{
				menu();break;
			}
		}
	}while(1);
	
}
 
 void list () // Detalle 
{
	system("cls");
	color(10);
	monp head,p;
	int i=10;
	head=ss();
	p=head;
	toxy(50,5);
	 printf ("Sistema de simulación de cajeros automáticos");
	toxy(54,6);
	 printf ("Detalles de la factura");
	toxy(30,7);
	printf("-------------------------------------------------------------");
	toxy(31,8);
	 printf ("Cantidad Hora Fecha");
	toxy(30,9);
	printf("-------------------------------------------------------------");
	while(p!=NULL)
	{
		toxy(30,i);
		if(p->money>=0)
		{
			printf("+%f                %-24s%s",p->money,p->time,p->date);
		}
		else
		{
			printf("%f                %-24s%s",p->money,p->time,p->date);
		}
		p=p->next;
		i++;
	}
	toxy(50,i);
	printf ("Por favor presione cualquier tecla para regresar al menú principal");
	getch();
	menu();
}
 
 void transfer_money () // transferencia 
{
	do
	{
		system("cls");
		color(10);
		FILE *fp1;
		monp p,head,p1;
		float money,sum=0;
		char name[20],t;
		char time[10],date[10];
		toxy(46,12);
		 printf ("Ingrese la cuenta que desea transferir:");
		gets(name);
		toxy(46,14);
		 printf ("Ingrese la cantidad que desea transferir:");
		scanf("%f",&money);
		 getchar (); // absorber la tecla enter 
		sum=Sum();
		 if (dinero> suma) // Si el monto a transferir es mayor que el saldo 
		{
			toxy(46,16);
			 printf ("¡Saldo insuficiente!");
			Sleep(500);
			 continuar; // Finalizar este ciclo 
		 } 
		 fp1 = fopen (name, "rb"); // Abre el archivo binario llamado name en modo de solo lectura  
		 if (fp1 == NULL) // Si el archivo no existe 
		{
			toxy(46,16);
			 printf ("¡La cuenta no existe!");
			fclose(fp1);
			Sleep(500);
			continue;
		}
		 fp1 = fopen (nombre, "ab"); // Abra el archivo binario llamado nombre añadiendo  
		 p = (monp) malloc (M); // Solicita un espacio de la memoria 
		p->money=-money;
		_tzset(); 
        _strtime(time);      
        strcpy(p->time,time);
        _strdate(date);
		strcpy(p->date,date);  
		save_money(p);
		p1=(monp)malloc(M);
		p1->money=money;
		strcpy(p1->time,time);
		strcpy(p1->date,date);
		 if (fwrite (p1, M, 1, fp1)! = 1) // almacena un nodo de tamaño M apuntado por p1 en el archivo apuntado por fp1 
		{
			 printf ("Error de transferencia, inténtalo de nuevo");
			continue;
		}
		fclose(fp1);
		toxy(46,18);
		 printf ("En funcionamiento, espere ...");
		Sleep(500);
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		 printf ("| ¡La transferencia se realizó correctamente! ¿Desea continuar? |");
		toxy(46,12);
		 printf ("| 1. Sí 2. No |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)
		{
			t=getch();
			if(t=='1')
			{
				break;
			}
			else if(t=='2')
			{
				menu(); 
			}
		}
 
	}while(1);
}
 
float Sum()
{
	monp head=NULL,p;
	float sum=0;
	head=ss();
	p=head;
	while(p!=NULL)
	{
		 suma + = p-> dinero; // suma 
		p=p->next;
	}
	if(head==NULL)
		sum=0;
	return sum;
}
 
 monp ss () // Encuentra el equilibrio 
{
	 ARCHIVO * fp; // Puntero de archivo 
	monp p,head=NULL,p2,pre=NULL;
	int n=0;
	//float sum=0;
	 fp = fopen (_name, "ab +"); // Abre el archivo binario llamado _name en modo de solo lectura 
	if(fp==NULL)
	{
		printf("cannot open file");
	}
	else
	{
		 while (! feof (fp)) // Determine si la marca se mueve al final del archivo 
		{
			n++;
			 p = (monp) malloc (M); // Solicita un espacio de la memoria 
			 fread (p, M, 1, fp); // asigna una sección de tamaño M en el archivo al que apunta fp ap 
			if(n==1)
			{
				head=p;
				p2=p;
			}
			 else // Crea una lista vinculada 
			{
				pre=p2;
				p2->next=p;
				p2=p;
			}
			p2->next=NULL;
		}
	}
	 fclose (fp); // Cerrar el archivo 
	if(pre!=NULL)
		pre->next=NULL;
	 return (head); // devuelve el valor de la suma 
}
 
 void save_money (monp p) // Guarde el contenido apuntado por p en el archivo 
{
	 ARCHIVO * fp; // Puntero de archivo 
	 fp = fopen (_name, "ab"); // Abra el archivo binario llamado _name agregando 
	if(fp==NULL)
	{
		printf("cannot open file");
	}
	 if (fwrite (p, M, 1, fp)! = 1) // Almacena el contenido de tamaño M apuntado por p en el archivo apuntado por fp 
	{
		printf("write error");
	}
	 fclose (fp); // Cerrar el archivo  
}
 
 void over () // Salir del software 
{
	char t;
	toxy(48,11);
	printf("-----------------------");
	toxy(48,12);
	 printf ("| ¿Está seguro de que desea salir? |");
	toxy(48,14);
	 printf ("| 1. Confirmar 2. Cancelar |");
	toxy(48,15);
	printf("-----------------------");
	while(1)
	{
		 t = getch (); // Ingrese t
		switch(t)
		{
			case '1':
			system("cls");
		    color(6);
			toxy(48,10);
			 printf ("Saliendo de forma segura ...");
			 Sleep (1000); // Pausa durante 1 segundo 
			system("cls");
			color(8);
			toxy(48,10);
			 printf ("El software se ha cerrado de forma segura");
			toxy(48,12);
			 printf ("¡Gracias por usar!");
			toxy(48,14);
			printf("by-by^_^");
			 exit (0); break; // finaliza el programa 
			case '2':
			 menu (); break; // Llamar a la función y entrar al menú 
			default :break;
		}
	}
}
 
 main () // Función principal clara y concisa ~~~ 
{
	 signin (); // Función de llamada 
}