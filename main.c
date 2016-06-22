#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
//#include "openssl/sha.h"

// variaveis para metodos
char gr1[3], gr2[3], gr3[3], ide[2], finalDate[15], finalCpf[15], finalPhone[20], salStr[20]; // Mascara de separação (grupos e identificador)

int nOption, errorUsr, force_exit, countArq;
char cpf[11], phone[11], birth[8], name[80], title[100], info[50], countArqS[3];
char nameVehicle[20], licensePlate[7], manufacturer[30], vehicleYear[4], vehicleColor[10];
float buyValue, sellValue, hodometer, salary;
struct schedule{
	int monSys, daySys, yeaSys;
	int hourSys, minSys, secSys;
	char mn[2], dy[2], yr[4];
}now, temp;
struct information{
	char fName[80], fCpf[16], fPhone[13], fBirth[10], strSalary[12], countArqS[3];
	float fSalary, cfHodometer, cfBuyValue, cfSellValue;
	char cLicense[9], cManu[30], cName[55], cYear[5], cColor[13], cHodometer[50], cBuyValue[50], cSellValue[50];

	int option, condicaoAuto, qParcela, id, countArq;
	float total, entrada, vTaxa, validacao, mensalidade, saldo, montante, potMont, vFinal;
	char entradaS[50], mensalidadeS[4], vFinalS[50], qParcelaS[5];
}client, seller, car, clientU, foundCar, foundPeople, saveSimu;

int option, condicaoAuto, qParcela, valExit, valShow = 0;
float total, entrada, vTaxa, validacao, mensalidade, saldo, montante, potMont, vFinal;
char condicaoAutoNome[5];

struct login{
	int passwordI;
    char uid[80];
    char name[30], password[30];
}varLogin, varSave, varTemp;

int main(){
	system("color 0f");
	printf("\n", setlocale(LC_ALL,""));
	login();
	/*
		char name[30];
	char pass[30]={0};
	getPassword(pass);
	strcpy(varLogin.password, varTemp.password);
	//strcpy(varLogin.password, pass);
	encryptPass(varLogin.password);
	//encryptPass();
	*/
}
COORD coord = {0, 0};
void gotoxy(int x,int y){
	coord.X = x;
    coord.Y = y; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
login(){
	system("color 0f");
	char name[30];
	char pass[30]={0};
	printf("\n\n\n\n\n\n\n\t\t******************************************\n\n");
	printf("\t\t\tUsuário:\n\n");
	printf("\t\t\tSenha:\n\n");
	printf("\t\t******************************************\n\n");
	gotoxy(32, 11); printf("_"); 
	gotoxy(32, 11); scanf("%s", &name);
	strupr(name);
	gotoxy(32, 13); printf("_"); //scanf("%s", &pass);
	gotoxy(32, 13); 
	fflush(stdin);
	strcpy(varLogin.name, name);

	getPassword(pass);
	//strcpy(varLogin.password, varTemp.password);
	strcpy(varLogin.password, varTemp.password);
	//strcpy(varLogin.password, pass);
	//encryptPass(varLogin.password);
	//encryptPass();
	validate();
}
validate(){
	char uname[30], pass[30],passwrd[30]={0},id[10],nam[30];
	int c = 0, passI;
	FILE *arq;
	arq = fopen("dbUsers.db", "r");

	if((strcmp(varLogin.name, "ADMIN") == 0) && (strcmp(varLogin.password, "123") == 0) ){
		strcpy(varLogin.uid, "_");
		c++;
		menu();
		return;
	}
	
    while(fscanf(arq,"%s %s %s\n", nam, pass, id)!=EOF){
         strcpy(nam, strupr(nam));
		 //passI = atoi(pass);
		 //printf("***************\nNam: %s\nvarLogin.name: %s\npassI: %d\nvarTemp.passwordI: %d\n\n", nam, varLogin.name, passI, varTemp.passwordI);

		 if((strcmp(varLogin.name, nam)==0) && (strcmp(varLogin.password, pass)==0)){
             strcpy(varLogin.uid, id);
             c++;
			 valShow++;
             menu();
             return;
         }
     }
    fclose(arq);
    if (c == 0){
    	system("color 0c");
    	gotoxy(25, 5);
     	printf("Informações inválidas.\n");
     	getche();
		printf("\b");
     	system("cls");
     	main();
     	return;
     }
}
getPassword(char buffer[]){
	char c;
	int pos = 0;
	do{
	c = getch();
		if(isprint(c)){
			buffer[ pos++ ] = c;
			printf("%c", '*');
		}
		else if(c == 8 && pos){
			buffer[ pos-- ] = '\0';
			printf("%s", "\b \b");
		}
	}while(c != 13);
	strcpy(varTemp.password, buffer);
}
savePass(){
	char pass1[30]={0}, pass2[30]={0};
	strcpy(info, "SENHAS");
	strcpy(pass1, ""); strcpy(pass2, ""); strcpy(varLogin.password, ""); varSave.passwordI = 0; varLogin.passwordI = 0;
	clearErrors();
	printf("Digite uma senha para o vendedor:\n");
	getPassword(pass1);
	fflush(stdin);
	if((strcmp(pass1, "") == 0) || (strlen(pass1) < 6)){
		system("color 0c");
		errorUsr++; errorUsr++;
		printf("A senha deve conter no mínimo 6 caracteres.\n");
		getche();
		printf("\b");
		fflush(stdin);
		savePass();
		return;
	}
	printf("\nDigite a senha novamente:\n");
	getPassword(pass2);
	fflush(stdin);
	printf("\n");
	if((strcmp(pass1, pass2) != 0)){
		system("color 0c");
		errorUsr++;
		printf("As senhas não são iguais.\n");
		getche();
		printf("\b");
		fflush(stdin);
		savePass();
		return;
	}
	if((strcmp(pass2, "") == 0) || (strlen(pass1) < 6)){
		system("color 0c");
		errorUsr++; errorUsr++;
		printf("A senha deve conter no mínimo 6 caracteres.\n");
		getche();
		printf("\b");
		fflush(stdin);
		savePass();
		return;
	}
	strcpy(varSave.password, pass1);
	strcpy(varLogin.password, varSave.password);
	//encryptPass(varSave.password);
	//getchar();
	fflush(stdin);
}
getDate(){
	char mon[2], day[2], yea[4], date[15];
	struct tm * timeInfo;
	time_t timeSec;
	time(&timeSec);
	timeInfo = localtime(&timeSec);
	strftime(date, 15, "%d/%m/%Y", timeInfo);
	//printf("Data do sistema: %s\n", date);

	strcpy(day, "");	strcpy(mon, "");	strcpy(yea, "");
	strncat(day, date, 2);
	strncat(mon, date +3, 2);
	strncat(yea, date +6, 4);
	
	//printf("// GETDATE\ndia: %s mes: %s ano: %s\n", day, mon, yea);
	//printf("dia: %s mes: %s ano: %s\n\n\n", day, mon, yea);
	
	// DECLARAÇÃO DE VARIÁVEIS CONVERTIDAS
	int yeaN = atoi(yea), monN = atoi(mon), dayN = atoi(day);
	//printf("int %02d %02d %d\n", dayN, monN, yeaN);		 // em int (formatado em DDMM)
	//printf("int %d %d %d\n", dayN, monN, yeaN);			// em int (não formatado em DDMM)
	//printf("string %s %s %s\n", day, mon, yea); 		   // em string (para salvar)
		// atribuindo valores a estrutura
		now.monSys 	 = ("%02d", monN);
		now.daySys	 = ("%02d", dayN);
		now.yeaSys	 = ("%d", yeaN);
		
	//printf("struct %d %d %d\n", now.daySys, now.monSys, now.yeaSys); 		   // em string (para salvar)
	//printf("FIM GETDATE***********************\n");
}
getName(char *infoMsgName){
	clearErrors();
	printf("%s\n", infoMsgName);
	char name1[80];
	fflush(stdin);
	scanf("%[^\n0-9]s", &name);
	strupr(name);
	strcpy(name1, name);
	int i = 0, x = 0, z = 0;
	int sizeStr = strlen(name);
	strcpy(info, "Nome: (NÃO UTILIZE ACENTOS)");
	if (sizeStr < 1){
		x++;
	}
	for (i=0; i<sizeStr; i++){		 				   // http://www.elcodigoascii.com.ar/caracteres-ascii-control/esc-escape-codigo-ascii-27.html
		if ((name[i] != 32)){						  // 32 = (espaço) 
			if ((name[i]) < 65 || (name[i]) > 90 ){  // 65 = "A" e 90 = "Z" Tabela ASCII - Também pode ser substituido pelo caracter.
				//printf("Caracter inválido.\n");
				x++;
			}
		}
		//printf("Ok.\n");
	}
	//printf("%i caractere(s) inválido(s)\n", x);
	while (name1[z] != '\0'){ 
		if(name1[z] == ' ')
			name1[z] = '_'; 
		z++;
	} 
	if (x != 0){
		printf("Digite apenas letras, não acentue e nem pontue.\n");
		system("color 0c");
		getche();
		printf("\b");
		//sleep(1); //getchar();
		getche();
		printf("\b");
		errorUsr++;
		getName("");
		return;
	}
	printf("%s\n", name);
	strcpy(client.fName, name);		// original
	strcpy(clientU.fName, name1);	// com underline
}
getCPF(char *infoMsgCPF){
	strcpy(gr1, ""); strcpy(gr2, ""); strcpy(gr3, ""); strcpy(ide, ""); strcpy(client.fCpf, ""); strcpy(finalCpf, "");
	clearErrors();
	strcpy(info, "CPF: (APENAS NÚMEROS)");

	printf("%s\n", infoMsgCPF);
	fflush(stdin);
	scanf("%[0-9]s", &cpf);
	fflush(stdin);
	if(strlen(cpf) == 11){
		strncat(gr1, cpf, 3);
		strncat(gr2, cpf +3, 3);
		strncat(gr3, cpf +6, 3);
		strncat(ide, cpf +9, 2);
	//	printf("\n%s \n%s \n%s \n%s \n", gr1, gr2, gr3, ide);
		printf("%s.%s.%s-%s\n", gr1, gr2, gr3, ide);
	//	printf("%s\n", cpf);
		
		strncat(finalCpf, gr1, 3);
		strncat(finalCpf, ".", 1);
		strncat(finalCpf, gr2, 3);
		strncat(finalCpf, ".", 1);
		strncat(finalCpf, gr3, 3);
		strncat(finalCpf, "-", 1);
		strncat(finalCpf, ide, 2);
	} else{
		system("color 0c");
		printf("Digite um CPF válido.\n");
		errorUsr++;
		//sleep(1); //getchar();
		getche();
		printf("\b");
		getCPF("");
		return;
	}
	strcpy(client.fCpf, "");
	strcpy(client.fCpf, cpf);
}
getBirth(char *infoMsgBirth){
	int x = 0;
	char D[2], M[2], Y[4]; // Mascara de separação DD/MM/AAAA
	strcpy(D, "");	strcpy(M, "");	strcpy(Y, "");		strcpy(finalDate, "");
	//finalDate = '';
	strcpy(info, "Data de nascimento:\n(APENAS NUMEROS NO FORMATO DDMMAAAA)");
	clearErrors();
	
	printf("%s\n", infoMsgBirth);
	scanf("%[0-9]s", &birth);
	fflush(stdin);
	//printf("data usuario: %s\n", birth);
	if(strlen(birth) == 8){
		//strings
		strncat(D, birth, 2);
	//	printf("dia usuario: %s\n", D);
		strncat(M, birth +2, 2);
	//	printf("mes usuario: %s\n", M);
		strncat(Y, birth +4, 4);
	//	printf("ano usuario: %s\n\n\n", Y);
	//	printf("Data usuario (mascara): %s/%s/%s\n", D, M, Y);
		//converção de string pra int
		int Yn = atoi(Y), Mn = atoi(M), Dn = atoi(D);
	//	printf("Data usuario (conversao): %02d/%02d/%d\n", Dn, Mn, Yn);
		getDate();
	/*
		printf("Ano atual: %d\n", now.yeaSys); 
		printf("\nAno atual: %d\nAno do usuário: %d\n", now.yeaSys, Yn);
		printf("\nDia atual: %d\nDia do usuário: %d\n", now.daySys, Dn); 
		printf("\nMês atual: %d\nMês do usuário: %d\n", now.monSys, Mn);
	*/
		if (Yn == now.yeaSys){
			if(Mn == now.monSys){
				if(Dn >= now.daySys){
					x++;
				}
			}
			if(Mn > now.monSys){
				x++;
			}
		}
		
		if(Yn < 1900 || Yn > now.yeaSys || Mn > 12 || Dn > 31 || Yn <= 0 || Mn <= 0 || Dn <= 0){
			x++;
		}
		//printf("x %d\nP2 Valores %s %s %s\n", x, &D, &M, &Y);
		//printf("P3 Valores %02d %02d %02d\n", Dn, Mn, Yn);
	}else{
		system("color 0c");
		printf("Digite uma data válida com apenas números.\n");
		errorUsr++;
		//sleep(1); //getchar();
		getche();
		printf("\b");
		fflush(stdin);
		getBirth("");
		return;
	}	
	if(x > 0){
		system("color 0c");
		printf("Digite uma data válida com apenas números.\n");
		errorUsr++;
		//sleep(1); //getchar();
		getche();
		printf("\b");
		fflush(stdin);
		getBirth("");
		return;
	}
	fflush(stdin);

	if (x==0){
		//printf("\n datafinal: %s \n", finalDate);
		strncat(finalDate, D, 2);
		strncat(finalDate, "/", 1);
		strncat(finalDate, M, 2);
		strncat(finalDate, "/", 1);
		strncat(finalDate, Y, 4);
		//printf("\nd: %s m: %s y: %s datafinal: %s \n", D,M,Y, finalDate);
		
		strcpy(client.fBirth, birth);
		printf("%s\n", finalDate);
	}
	
}
getSalary(char *infoMsgSalary){
	clearErrors();
	printf("%s\n", infoMsgSalary);
	fflush(stdin);
	scanf("%f", &salary);
	if (salary <= 0){
		errorUsr++;
		system("color 0c");
		//sleep(1); //getchar();
		getche();
		printf("\b");
		getSalary("");
		return;
	}else{
		printf("R$%.2f\n", salary);
	}
	client.fSalary = salary;
	fflush(stdin);
}
getPhone(char *infoMsgPhone){
	char ddd[2], tel1[4], tel2[5];
	strcpy(ddd, "");	strcpy(tel1, "");	strcpy(tel2, "");	strcpy(finalPhone, "");
	clearErrors();
	strcpy(info, "Telefone:\n(APENAS NUMEROS - CASO NÃO HAJA DDD, 19 SERÁ PADRÃO)");

	printf("%s\n", infoMsgPhone);
	fflush(stdin);
	scanf("%[0-9]s", &phone);
	//printf("%s\n", phone);

	if(strlen(phone) == 8){
		strcpy(ddd, "19");
		strncat(tel1, phone, 4);
		strncat(tel2, phone +4, 4);
		//printf("\ncond1 \n%s \n%s \n%s \n", ddd, tel1, tel2);
		strncat(finalPhone, "(", 1);
		strncat(finalPhone, ddd, 2);
		strncat(finalPhone, ") ", 2);
		strncat(finalPhone, tel1, 4);
		strncat(finalPhone, "-", 1);
		strncat(finalPhone, tel2, 4);
	}else if(strlen(phone) == 9){
		strcpy(ddd, "19");
		strncat(tel1, phone, 5);
		strncat(tel2, phone +5, 4);
		//printf("\ncond2 \n%s \n%s \n%s \n", ddd, tel1, tel2);
		strncat(finalPhone, "(", 1);
		strncat(finalPhone, ddd, 2);
		strncat(finalPhone, ") ", 2);
		strncat(finalPhone, tel1, 5);
		strncat(finalPhone, "-", 1);
		strncat(finalPhone, tel2, 4);
	}else if(strlen(phone) == 10){
		strncat(ddd, phone, 2);
		strncat(tel1, phone +2, 4);
		strncat(tel2, phone +6, 4);
		//printf("\ncond3 \n%s \n%s \n%s \n", ddd, tel1, tel2);
		strncat(finalPhone, "(", 1);
		strncat(finalPhone, ddd, 2);
		strncat(finalPhone, ") ", 2);
		strncat(finalPhone, tel1, 4);
		strncat(finalPhone, "-", 1);
		strncat(finalPhone, tel2, 4);
	}else if(strlen(phone) == 11){
		strncat(ddd, phone, 2);
		strncat(tel1, phone +2, 5);
		strncat(tel2, phone +7, 4);
		//printf("\ncond4 \n%s \n%s \n%s \n", ddd, tel1, tel2);
		strncat(finalPhone, "(", 1);
		strncat(finalPhone, ddd, 2);
		strncat(finalPhone, ") ", 2);
		strncat(finalPhone, tel1, 5);
		strncat(finalPhone, "-", 1);
		strncat(finalPhone, tel2, 4);
	}else{
		system("color 0c");
		printf("Digite um número válido.\n");
		errorUsr++;
		//printf("\ncond5\n");
		//sleep(1); //getchar();
		getche();
		printf("\b");
		getPhone("");
		return;
	}
	fflush(stdin);
	strcpy(client.fPhone, phone);
	//printf("\n(%s) %s-%s\n", ddd, tel1, tel2);
}
getLicensePlate(char *infoMsgLP){
	char letter[3], number[4];
	strcpy(letter, ""); strcpy(number, "");
	strcpy(info, "Placa: (XXX0000)");
	clearErrors();
	
	printf("%s\n", infoMsgLP);
	scanf("%s", &licensePlate);
	fflush(stdin);
	int i=0, x=0;
	strupr(licensePlate);
	//char sizeLetter = strlen(letter), sizeNumber = strlen(number);
	
	if (strlen(licensePlate) == 7){
		strncat(letter, licensePlate, 3);
		strncat(number, licensePlate +3, 4);
		int letterSize = strlen(letter), numberSize = strlen(number);

		if (letterSize == 3 && numberSize == 4){
			for (i=0; i<letterSize; i++){
				if ((letter[i]) < 65 || (letter[i]) > 90){
					x++;				
				}
			}
			for (i=0; i<numberSize; i++){
				if ((number[i]) < 48 || (number[i]) > 57){
					x++;
				}
			}
		}

		if (x != 0){
			system("color 0c");
			printf("Digite as 3 letras e os 4 números da placa no formato XXX0000.\n");
			errorUsr++; 
			//sleep(1); //getchar();
			getche();
			printf("\b");
			getLicensePlate("");
			return;
		}
		
	}else{
		system("color 0c");
		printf("Digite uma placa válida.\n");
		errorUsr++;
		//sleep(1); //getchar();
		getche();
		printf("\b");
		getLicensePlate("");
		return;
	}
	strcpy(car.cLicense, licensePlate);
	//fflush(stdin);
}
getManufacturer(char *infoMsgMf){
	strcpy(info, "Fabricante:");
	clearErrors();
	int z = 0;
	printf("%s\n", infoMsgMf);
	scanf("%s", &manufacturer);
	fflush(stdin);
	strupr(manufacturer);
	strcpy(car.cManu, manufacturer);		// original

	while (manufacturer[z] != '\0'){ 
		if(manufacturer[z] == ' ')
			manufacturer[z] = '_'; 
		z++;
	} 
	strcpy(clientU.cManu, manufacturer);	// com underline
	//strcpy(clientU.cManu, manufacturer);
}
getNameVehicle(char *infoMsgVehicle){
	strcpy(info, "Modelo:");
	clearErrors();
	int z = 0;
	printf("%s\n", infoMsgVehicle);
	scanf("%s", &nameVehicle);
	strupr(nameVehicle);
	fflush(stdin);
	strcpy(car.cName, nameVehicle);		// original

	while (nameVehicle[z] != '\0'){ 
		if(nameVehicle[z] == ' ')
			nameVehicle[z] = '_'; 
		z++;
	} 
	strcpy(clientU.cName, nameVehicle);	// com underline
	//strcpy(car.cName, nameVehicle);
}
getVehicleColor(char *infoMsgVC){
	strcpy(info, "Cor:");
	clearErrors();
	int z = 0;
	printf("%s\n", infoMsgVC);
	scanf("%s", &vehicleColor);
	strupr(vehicleColor);
	fflush(stdin);
	strcpy(car.cColor, vehicleColor);		// original

	while (vehicleColor[z] != '\0'){ 
		if(vehicleColor[z] == ' ')
			vehicleColor[z] = '_'; 
		z++;
	} 
	strcpy(clientU.cColor, vehicleColor);	// com underline
	//strcpy(car.cColor, vehicleColor);
}
getVehicleYear(char *infoMsgVY){
	int x = 0;
	strcpy(info, "Ano de fabricação:");
	clearErrors();
	printf("%s\n", infoMsgVY);
	scanf("%s", &vehicleYear);
	fflush(stdin);
	getDate();
	int vYear = atoi(vehicleYear);
	if(vYear < 1800 || vYear > now.yeaSys){
		x++;
	}
	if(x > 0){
		system("color 0c");
		printf("Digite uma data válida com apenas números.\n");
		errorUsr++;
		//sleep(1); //getchar();
		getche();
		printf("\b");
		fflush(stdin);
		getVehicleYear("");
		return;
	}
	strcpy(car.cYear, vehicleYear);
}
getHodometer(char *infoMsgH){
	strcpy(info, "Quilometragem:");
	clearErrors();
	printf("%s\n", infoMsgH);
	scanf("%f", &hodometer);
	fflush(stdin);
	if (hodometer < 0){
		system("color 0c");
		errorUsr++;
		printf("Valor inválido.\n");
		//sleep(1); //getchar();
		getche();
		printf("\b");
		getHodometer("");
		return;
	}else{
		car.cfHodometer = hodometer;
		printf("%.2f KMs\n", car.cfHodometer);
	}
}
getBuyValue(char *infoMsgBV){
	strcpy(info, "Valor de compra:");
	clearErrors();
	printf("%s\n", infoMsgBV);
	scanf("%f", &buyValue);
	fflush(stdin);
	if (buyValue <= 0){
		system("color 0c");
		errorUsr++;
		printf("Valor inválido.\n");
		//sleep(1); //getchar();
		getche();
		printf("\b");
		getBuyValue("");
		return;
	}else{
		car.cfBuyValue = buyValue;
		printf("R$%.2f\n", buyValue);
	}
}
getSellValue(char *infoMsgSV){
	strcpy(info, "Valor de venda:");
	clearErrors();
	printf("%s\n", infoMsgSV);
	scanf("%f", &sellValue);
	fflush(stdin);
	if (sellValue <= 0){
		system("color 0c");
		errorUsr++;
		printf("Valor inválido.\n");
		//sleep(1); //getchar();
		getche();
		printf("\b");
		getSellValue("");
		return;
	}else{
		car.cfSellValue = sellValue;
		printf("R$%.2f\n", sellValue);
	}
}

clearErrors(){
	system("color 0f");
	fflush(stdin);
	if(errorUsr > 3){
		errorUsr = 0;
		system("cls");
		printf("*************************************************\n%s\n*************************************************\n\n%s\n", &title, info);
	}
}
appendOnDB(int typeUser){
	//testes
	/*
	strcpy(client.fName, "Nome");
	strcpy(client.fCpf, "43214543873");
	strcpy(cpf, "43214543873");
	strcpy(client.fBirth, "12021997");
	strcpy(client.fPhone, "992504265");
	client.fSalary= 450.20;
	printf("\n***********************************");
	*/
	system("cls");
	printf("Por favor, confira as informações:\nNome:\t\t\t%s\nCPF:\t\t\t%s\nData de nascimento:\t%s\nTelefone:\t\t%s\nSalário:\t\tR$%.2f\n\nPressione S para salvar, C para corrigir e M para voltar ao Menu\n", client.fName, finalCpf, finalDate, finalPhone, client.fSalary);
	int nOption;
	char typeName[10];
	FILE *arq, *arq2;
	nOption = (getche());
	//printf("\n%d", nOption);

	if (nOption == 83 || nOption == 115){ //s
		if (typeUser == 1){
			arq = fopen("dbClient.db", "a+");
			getLastLine(1);
			fprintf(arq, "%i %s %s %s %s %.2f\n", countArq, clientU.fName, cpf, client.fBirth, client.fPhone, client.fSalary);
			fclose(arq);
			strcpy(typeName, "cliente");
		}else if(typeUser == 2){
			arq = fopen("dbSeller.db", "a+");
			getLastLine(3);
			fprintf(arq, "%i %s %s %s %s %.2f\n", countArq, clientU.fName, cpf, client.fBirth, client.fPhone, client.fSalary);
			fclose(arq);
			strcpy(typeName, "funcionário");
			
			arq2 = fopen("dbUsers.db", "a+");
			fprintf(arq2, "%d %s %s\n", countArq, varSave.password, clientU.fName);
			fclose(arq2);
			//userSave.passwordI
		}
	}else if(nOption == 67 || nOption == 99){ //c
		if (typeUser == 1){
			clientMenu_insert();
			return;
		}else if(typeUser == 2){
			sellerMenu_insert();
			return;
		}
	}else if(nOption == 77 || nOption == 109){ //m
		menu();
		return;
	}else{
		appendOnDB(typeUser);
		return;
	}
	printf("\nCadastro efetuado!\nPressione 1 para inserir um novo %s ou \nqualquer tecla para voltar ao Menu Principal.\n", typeName);
	nOption = (getche()-48);
	switch(nOption){
		case 1:
			if(typeUser == 1){
				clientMenu_insert();
				return;
			}else if(typeUser == 2){
				sellerMenu_insert();
				return;
			}
			return;
			break;
		default:
			menu();
			return;
			break;
	}
}
getUserDB(int opt, int optUsr, int typeCall){
	struct information ac;
	int var = 0, nOption = 0, z = 0;
	char nam[100];
	FILE *arq;
	
	if(optUsr == 1){
		arq = fopen("dbClient.db", "r");
		//getLastLine(1);
	}else if(optUsr == 2){
		arq = fopen("dbSeller.db", "r");
		//getLastLine(3);
	}
	/*
	memset(&ac.fName, 0, sizeof(ac.fName));
	memset(&ac.fCpf, 0, sizeof(ac.fCpf));
	memset(&ac.fBirth, 0, sizeof(ac.fBirth));
	memset(&ac.fPhone, 0, sizeof(ac.fPhone));
	memset(&ac.strSalary, 0, sizeof(ac.strSalary));
	memset(&nam, 0, sizeof(nam));
	*/
/*
client.fName, name ---> original
clientU.fName, name1 ---> com underline
*/
  	while(fscanf(arq,"%s %s %s %s %s %s\n", ac.countArqS, ac.fName, ac.fCpf, ac.fBirth, ac.fPhone, ac.strSalary)!=EOF){
		if(opt == 1){
			if(strcmp(clientU.fName, ac.fName)==0){
				ac.fSalary = atof(ac.strSalary);
				foundPeople.id = atoi(ac.countArqS);
				strcpy(foundPeople.countArqS, ac.countArqS);
				
				strcpy(foundPeople.fName, ac.fName);
				strcpy(clientU.fName, ac.fName);
				while (foundPeople.fName[z] != '\0'){ 
					if (foundPeople.fName[z] == '_') 
						foundPeople.fName[z] = ' '; 
					z++; 
				} 
				
				strcpy(nam, "ID: ");
				strcat(nam, foundPeople.countArqS);
				strcat(nam, "\nNome: ");
				strcat(nam, foundPeople.fName);
					//strcpy(foundPeople.fName, ac.fName);
				strcat(nam, "\nCPF: ");
				strcat(nam, ac.fCpf);
					strcpy(foundPeople.fCpf, ac.fCpf);
				strcat(nam, "\nData de Nascimento: ");
				strcat(nam, ac.fBirth);
					strcpy(foundPeople.fBirth, ac.fBirth);
				strcat(nam, "\nTelefone: ");
				strcat(nam, ac.fPhone);
					strcpy(foundPeople.fPhone, ac.fPhone);
				strcat(nam, "\nSalário: ");
				strcat(nam, ac.strSalary);
					strcpy(foundPeople.strSalary, ac.strSalary);
					foundPeople.fSalary = ac.fSalary;
				var++;
			}
		}else if(opt == 2){
			if(strcmp(client.fCpf, ac.fCpf)==0){
				ac.fSalary = atof(ac.strSalary);
				foundPeople.id = atoi(ac.countArqS);
				strcpy(foundPeople.countArqS, ac.countArqS);
				strcpy(foundPeople.fName, ac.fName);
				strcpy(clientU.fName, ac.fName);
				while (foundPeople.fName[z] != '\0'){ 
					if (foundPeople.fName[z] == '_') 
						foundPeople.fName[z] = ' '; 
					z++; 
				} 
				
				strcpy(nam, "ID: ");
				strcat(nam, foundPeople.countArqS);
				strcat(nam, "\nNome: ");
				strcat(nam, foundPeople.fName);
					//strcpy(foundPeople.fName, ac.fName);
				strcat(nam, "\nCPF: ");
				strcat(nam, ac.fCpf);
					strcpy(foundPeople.fCpf, ac.fCpf);
				strcat(nam, "\nData de Nascimento: ");
				strcat(nam, ac.fBirth);
					strcpy(foundPeople.fBirth, ac.fBirth);
				strcat(nam, "\nTelefone: ");
				strcat(nam, ac.fPhone);
					strcpy(foundPeople.fPhone, ac.fPhone);
				strcat(nam, "\nSalário: ");
				strcat(nam, ac.strSalary);
					strcpy(foundPeople.strSalary, ac.strSalary);
					foundPeople.fSalary = ac.fSalary;
				var++;
			}
		}else if(opt == 3){
			foundPeople.id = atoi(countArqS);
			if(strcmp(client.countArqS, ac.countArqS)==0){
				ac.fSalary = atof(ac.strSalary);
				foundPeople.id = atoi(countArqS);
				strcpy(foundPeople.countArqS, ac.countArqS);
				strcpy(foundPeople.fName, ac.fName);
				strcpy(clientU.fName, ac.fName);
				while (foundPeople.fName[z] != '\0'){ 
					if (foundPeople.fName[z] == '_') 
						foundPeople.fName[z] = ' '; 
					z++; 
				} 
				
				strcpy(nam, "ID: ");
				strcat(nam, foundPeople.countArqS);
				strcat(nam, "\nNome: ");
				strcat(nam, foundPeople.fName);
					//strcpy(foundPeople.fName, ac.fName);
				strcat(nam, "\nCPF: ");
				strcat(nam, ac.fCpf);
					strcpy(foundPeople.fCpf, ac.fCpf);
				strcat(nam, "\nData de Nascimento: ");
				strcat(nam, ac.fBirth);
					strcpy(foundPeople.fBirth, ac.fBirth);
				strcat(nam, "\nTelefone: ");
				strcat(nam, ac.fPhone);
					strcpy(foundPeople.fPhone, ac.fPhone);
				strcat(nam, "\nSalário: ");
				strcat(nam, ac.strSalary);
					strcpy(foundPeople.strSalary, ac.strSalary);
					foundPeople.fSalary = ac.fSalary;
				var++;
			}
		}
	}
	fclose(arq);
	


	if(typeCall == 2){
		if (var == 0){
			valExit++;
			printf("Nenhum cadastro foi encontrado. Pesquisar cliente antes?\n");
			printf("Pressione 1 para Pesquisar, 2 para tentar novamente ou\nqualquer tecla para retornar ao Menu Principal.\n");
			nOption = (getche()-48);
			printf("\n");
				switch(nOption){
				case 1:
					clientMenu_search();
					return;
					break;
				case 2:
					sellMenu();
					return;
					break;
				default:
					menu();
					return;
					break;
				}
			return;
		}else{
			return;
		}
	}
	
	if(var == 0){
		printf("Nenhum cadastro foi encontrado, deseja tentar novamente?\n");
		printf("Pressione 1 para uma nova busca ou\nqualquer tecla para retornar ao Menu Principal.\n");
	}else{
		printf("*******\n%s\n\n", nam);
		printf("Pressione 1 para uma nova busca ou\nqualquer tecla para retornar ao Menu Principal.\n");
	}
	nOption = (getche()-48);
	printf("\n");
	switch(nOption){
	case 1:
		if(optUsr == 1){
			clientMenu_search();
			return;
		}else if(optUsr == 2){
			sellerMenu_search();
			return;
		}
		return;
		break;
	default:
		menu();
		return;
		break;
	}
}
addVehicle(){
	/*
	strcpy(car.cLicense, "CJO4799");
	strcpy(car.cManu, "FIAT");
	strcpy(car.cName, "PRÊMIO");
	strcpy(car.cYear, "1986");
	strcpy(car.cColor, "BRANCO");
	car.cfHodometer = 87000.20;
	car.cfBuyValue  = 3500;
	car.cfSellValue = 5000;
	*/
	system("cls");
	printf("Por favor, confira as informações:\nPlaca:\t\t\t%s\nFabricante:\t\t%s\nModelo:\t\t\t%s\nAno de fabricação:\t%s\nCor:\t\t\t%s\nHodômetro:\t\t%.2f\nValor de compra:\tR$%.2f\nValor de venda:\t\tR$%.2f\n\n\nPressione S para salvar, C para corrigir e M para voltar ao Menu\n",
			car.cLicense, car.cManu, car.cName, car.cYear, car.cColor, car.cfHodometer, car.cfBuyValue, car.cfSellValue);
	int nOption;
	FILE *arq;
	nOption = (getche());
	if (nOption == 83 || nOption == 115){ //s
		arq = fopen("dbVehicle.db", "a+");
		getLastLine(4);
		fprintf(arq, "%i %s %s %s %s %s %.2f %.2f %.2f\n", countArq, car.cLicense, clientU.cManu, clientU.cName, car.cYear, clientU.cColor, car.cfHodometer, car.cfBuyValue, car.cfSellValue);
		fclose(arq);
	}else if(nOption == 67 || nOption == 99){ //c
		vehicleMenu_insert();
		return;
	}else if(nOption == 77 || nOption == 109){ //m
		menu();
		return;
	}else{
		addVehicle();
		return;
	}
	printf("\nCadastro efetuado!\nPressione 1 para inserir um novo veículo ou \nqualquer tecla para voltar ao Menu Principal.\n");
	nOption = (getche()-48);
	switch(nOption){
		case 1:
			vehicleMenu_insert();
			return;
			break;
		default:
			menu();
			return;
			break;
	}
}
getCarDB(int opt, int typeCall){
	struct information car1;
	int var = 0, nOption = 0, z = 0;
	char nam[100];
	FILE *arq;
	arq = fopen("dbVehicle.db", "r");
  	while(fscanf(arq,"%s %s %s %s %s %s %s %s %s\n", car1.countArqS, car1.cLicense, car1.cManu, car1.cName, car1.cYear, car1.cColor, car1.cHodometer, car1.cBuyValue, car1.cSellValue)!=EOF){
		if (opt == 1){
			if(strcmp(licensePlate, car1.cLicense)==0){
				car1.cfHodometer = atof(car1.cHodometer);
				car1.cfBuyValue  = atof(car1.cBuyValue);
				car1.cfSellValue = atof(car1.cSellValue);
				car1.id 		 = atoi(car1.countArqS);
					
				strcpy(foundCar.cManu, car1.cManu);
				while (foundCar.cManu[z] != '\0'){ 
					if (foundCar.cManu[z] == '_') 
						foundCar.cManu[z] = ' '; 
					z++; 
				}
				z=0;
				strcpy(foundCar.cName, car1.cName);
				while (foundCar.cName[z] != '\0'){ 
					if (foundCar.cName[z] == '_') 
						foundCar.cName[z] = ' '; 
					z++; 
				}
				z=0;
				strcpy(foundCar.cColor, car1.cColor);
				while (foundCar.cColor[z] != '\0'){ 
					if (foundCar.cColor[z] == '_') 
						foundCar.cColor[z] = ' '; 
					z++; 
				}

				strcpy(nam, "ID: ");
				strcat(nam, car1.countArqS);
				strcat(nam, "\nPlaca: ");
				strcat(nam, car1.cLicense);
					strcpy(foundCar.cLicense, car1.cLicense);
				strcat(nam, "\nFabricante: ");
				strcat(nam, car1.cManu);
					strcpy(foundCar.cManu, car1.cManu);
				strcat(nam, "\nModelo: ");
				strcat(nam, car1.cName);
					strcpy(foundCar.cName, car1.cName);
				strcat(nam, "\nAno: ");
				strcat(nam, car1.cYear);
					strcpy(foundCar.cYear, car1.cYear);
				strcat(nam, "\nCor: ");
				strcat(nam, car1.cColor);
					strcpy(foundCar.cColor, car1.cColor);
				strcat(nam, "\nHodômetro: ");
				strcat(nam, car1.cHodometer);
					strcpy(foundCar.cHodometer, car1.cHodometer);
					foundCar.cfHodometer = car1.cfHodometer;
				strcat(nam, " KMs\nCompra: R$");
				strcat(nam, car1.cBuyValue);
					strcpy(foundCar.cBuyValue, car1.cBuyValue);
					foundCar.cfBuyValue = car1.cfBuyValue;
				strcat(nam, "\nVenda: R$");
				strcat(nam, car1.cSellValue);
					strcpy(foundCar.cSellValue, car1.cSellValue);
					foundCar.cfSellValue = car1.cfSellValue;
				var++;
			}
		}else if (opt == 2){
			if(strcmp(car.countArqS, car1.countArqS)==0){
				car1.cfHodometer = atof(car1.cHodometer);
				car1.cfBuyValue  = atof(car1.cBuyValue);
				car1.cfSellValue = atof(car1.cSellValue);
				car1.id 		 = atoi(countArqS);
					
				strcpy(foundCar.cManu, car1.cManu);
				while (foundCar.cManu[z] != '\0'){
					if (foundCar.cManu[z] == '_') 
						foundCar.cManu[z] = ' '; 
					z++; 
				}
				z=0;
				strcpy(foundCar.cName, car1.cName);
				while (foundCar.cName[z] != '\0'){
					if (foundCar.cName[z] == '_') 
						foundCar.cName[z] = ' '; 
					z++; 
				}
				z=0;
				strcpy(foundCar.cColor, car1.cColor);
				while (foundCar.cColor[z] != '\0'){
					if (foundCar.cColor[z] == '_') 
						foundCar.cColor[z] = ' '; 
					z++; 
				}

				strcpy(nam, "ID: ");
				strcat(nam, car1.countArqS);
				strcat(nam, "\nPlaca: ");
				strcat(nam, car1.cLicense);
					strcpy(foundCar.cLicense, car1.cLicense);
				strcat(nam, "\nFabricante: ");
				strcat(nam, car1.cManu);
					strcpy(foundCar.cManu, car1.cManu);
				strcat(nam, "\nModelo: ");
				strcat(nam, car1.cName);
					strcpy(foundCar.cName, car1.cName);
				strcat(nam, "\nAno: ");
				strcat(nam, car1.cYear);
					strcpy(foundCar.cYear, car1.cYear);
				strcat(nam, "\nCor: ");
				strcat(nam, car1.cColor);
					strcpy(foundCar.cColor, car1.cColor);
				strcat(nam, "\nHodômetro: ");
				strcat(nam, car1.cHodometer);
					strcpy(foundCar.cHodometer, car1.cHodometer);
					foundCar.cfHodometer = car1.cfHodometer;
				strcat(nam, " KMs\nCompra: R$");
				strcat(nam, car1.cBuyValue);
					strcpy(foundCar.cBuyValue, car1.cBuyValue);
					foundCar.cfBuyValue = car1.cfBuyValue;
				strcat(nam, "\nVenda: R$");
				strcat(nam, car1.cSellValue);
					strcpy(foundCar.cSellValue, car1.cSellValue);
					foundCar.cfSellValue = car1.cfSellValue;
				var++;
			}
		}
	}
	fclose(arq);
	fflush(stdin);
	
	if(typeCall == 2){
		if (var == 0){
			valExit++;
			printf("Nenhum cadastro foi encontrado. Pesquisar veículo antes?\n");
			printf("Pressione 1 para Pesquisar, 2 para tentar novamente ou\nqualquer tecla para retornar ao Menu Principal.\n");
			nOption = (getche()-48);
				switch(nOption){
				case 1:
					vehicleMenu_search();
					return;
					break;
				case 2:
					sellMenu();
					return;
					break;
				default:
					menu();
					return;
					break;
				}
			return;
		}else{
			return;
		}
	}
	
	if(var == 0){
		printf("Nenhum cadastro foi encontrado, deseja tentar novamente?\n");
		printf("Pressione 1 para uma nova busca ou\nqualquer tecla para retornar ao Menu Principal.\n");
	}else{
		printf("*******\n%s\n\n", nam);
		printf("Pressione 1 para uma nova busca ou\nqualquer tecla para retornar ao Menu Principal.\n");
	}
	nOption = (getche()-48);
	switch(nOption){
	case 1:
		vehicleMenu_search();
		return;
		break;
	default:
		menu();
		return;
		break;
	}
}
saveSimulation(){
	system("cls");
	printf("Por favor, confira as informações:\nPlaca:\t\t\t%s\nNome cliente:\t\t%s\nCPF:\t\t\t%s\nValor veículo:\t\tR$%.2f\nEntrada:\t\tR$%.2f\nParcela:\t\t%d\nMensalidade:\t\tR$%.2f\nValor total:\t\tR$%.2f\n\n\nPressione S para salvar, C para corrigir e M para voltar ao Menu\n",
			saveSimu.cLicense, saveSimu.fName,  saveSimu.fCpf, saveSimu.cfSellValue,  saveSimu.entrada, saveSimu.qParcela, saveSimu.mensalidade, saveSimu.vFinal);
	int nOption;
	FILE *arq;
	nOption = (getche());
	getLastLine(2);
	if (nOption == 83 || nOption == 115){ //s
		arq = fopen("dbSell.db", "a+");
		fprintf(arq, "%i %s %s %s %.2f %.2f %d %.2f %.2f\n", countArq, saveSimu.cLicense, clientU.fName,  saveSimu.fCpf, saveSimu.cfSellValue,  saveSimu.entrada, saveSimu.qParcela, saveSimu.mensalidade, saveSimu.vFinal);
		fclose(arq);
	}else if(nOption == 67 || nOption == 99){ //c
		sellMenu_insert();
		return;
	}else if(nOption == 77 || nOption == 109){ //m
		menu();
		return;
	}else{
		saveSimulation();
		return;
	}
	printf("\nCadastro efetuado!\nPressione 1 para inserir uma nova venda ou \nqualquer tecla para voltar ao Menu Principal.\n");
	nOption = (getche()-48);
	switch(nOption){
		case 1:
			sellMenu_insert();
			return;
			break;
		default:
			menu();
			return;
			break;
	}
}
getSimulation(int opt){
	struct information getSimu;
	int var = 0, nOption = 0, z = 0;
	char nam[100];
	FILE *arq;
	arq = fopen("dbSell.db", "r");
/*
	memset(&ac.fName, 0, sizeof(ac.fName));
	memset(&ac.fCpf, 0, sizeof(ac.fCpf));
	memset(&ac.fBirth, 0, sizeof(ac.fBirth));
	memset(&ac.fPhone, 0, sizeof(ac.fPhone));
	memset(&ac.strSalary, 0, sizeof(ac.strSalary));
	memset(&nam, 0, sizeof(nam));

fprintf(arq, "%s %s %s %.2f %.2f %d %.2f %.2f\n", 
saveSimu.cLicense, saveSimu.fName,  saveSimu.fCpf, &saveSimu.cfSellValue,  saveSimu.entrada, saveSimu.qParcela, saveSimu.mensalidade, saveSimu.vFinal);
*/
  	while(fscanf(arq,"%s %s %s %s %s %s %s %s %s\n", 
  		getSimu.countArqS, getSimu.cLicense, getSimu.fName,  getSimu.fCpf, getSimu.cSellValue,  getSimu.entradaS, getSimu.qParcelaS, getSimu.mensalidadeS, getSimu.vFinalS)!=EOF){
		if(strcmp(foundCar.countArqS, getSimu.countArqS)==0){
			getSimu.entrada 	= atof(getSimu.entradaS);
			getSimu.qParcela 	= atoi(getSimu.qParcelaS);
			getSimu.mensalidade = atof(getSimu.mensalidadeS);
			getSimu.vFinal 		= atof(getSimu.vFinalS);
			getSimu.cfBuyValue  = atof(getSimu.cBuyValue);
			getSimu.cfSellValue = atof(getSimu.cSellValue);
			getSimu.countArq    = atoi(getSimu.countArqS);
			getSimu.id		    = getSimu.countArq;
			while (getSimu.fName[z] != '\0'){ 
				if (getSimu.fName[z] == '_') 
					getSimu.fName[z] = ' '; 
				z++; 
			}

			strcpy(nam, "ID: ");
			strcat(nam, getSimu.countArqS);
			strcat(nam, "\nPlaca: ");
			strcat(nam, getSimu.cLicense);
				strcpy(foundCar.cLicense, getSimu.cLicense);
			strcat(nam, "\nNome cliente: ");
			strcat(nam, getSimu.fName);
				strcpy(foundCar.fName, getSimu.fName);
			strcat(nam, "\nCPF: ");
			strcat(nam, getSimu.fCpf);
				strcpy(foundCar.fCpf, getSimu.fCpf);
			strcat(nam, "\nValor: R$");
			strcat(nam, getSimu.cSellValue);
				foundCar.cfSellValue = getSimu.cfSellValue;
			strcat(nam, "\nEntrada: R$");
			strcat(nam, getSimu.entradaS);
				foundCar.entrada = getSimu.entrada;
			strcat(nam, "\nParcela: ");
			strcat(nam, getSimu.qParcelaS);
				//strcpy(foundCar.qParcela, getSimu.qParcela);
				foundCar.qParcela = getSimu.qParcela;
			strcat(nam, "\nMensalidade: R$");
			strcat(nam, getSimu.mensalidadeS);
				//strcpy(foundCar.mensalidade, getSimu.mensalidade);
				foundCar.mensalidade = getSimu.mensalidade;
			strcat(nam, "\nValor total: R$");
			strcat(nam, getSimu.vFinalS);
				//strcpy(foundCar.vFinal, getSimu.vFinal);
				foundCar.vFinal = getSimu.vFinal;
			var++;
		}
	}
	fclose(arq);
	fflush(stdin);

	if(var == 0){
		printf("Nenhum cadastro foi encontrado, deseja tentar novamente?\n");
		printf("Pressione 1 para uma nova busca ou\nqualquer tecla para retornar ao Menu Principal.\n");
	}else{
		printf("*******\n%s\n\n", nam);
		printf("Pressione 1 para uma nova busca ou\nqualquer tecla para retornar ao Menu Principal.\n");
	}
	nOption = (getche()-48);
	switch(nOption){
	case 1:
		sellMenu_search();
		return;
		break;
	default:
		menu();
		return;
		break;
	}
}






waitESC(char *infoMsgESC){
	int key, x = 0;
	force_exit = 0;
	fflush(stdin);
	printf("%s\n", infoMsgESC);
//	printf("Pressione ESC para sair do menu.\n");
	do{
		key = getch();
		if (key == 27){ // http://www.elcodigoascii.com.ar/caracteres-ascii-control/esc-escape-codigo-ascii-27.html
			force_exit++;
			menu();
			return;
//		printf("%i\n", key);
//		printf("%d\n", key);
		//waitESC();
		} else{
			putchar(key);
			getCPF("TESTE");
			x++;
		//	strcat(key, cpf);
		}
		if(x != 0){
			key = 27;
		}
		//putchar(key);
		//if (key == ){
			
		//}
	}while(key != 27);
	//*/
}

menu(){
	system("cls");
	nOption = 0;
	int z = 0;
	char nameShow[80];
	strcat(varLogin.uid, "_");
	while (varLogin.uid[z] != '_'){
		nameShow[z] = varLogin.uid[z];
		//strcat(nameShow[z], varLogin.uid[z]);
		z++;
	} 

	if (valShow > 0){
		printf("*************************************************\nBEM VINDO, %s\n*************************************************\n\n", nameShow);
		valShow = 0;
	}else{
		strcpy(nameShow, "");
		printf("*************************************************\nBEM VINDO\n*************************************************\n\n");
	}
	printf("Escolha uma Opção:\n\n 1 - CLIENTE\n 2 - VENDEDOR \n 3 - VEÍCULOS\n 4 - VENDAS\n 5 - SAIR\n", setlocale(LC_ALL,""));
	scanf("%d", &nOption);
	fflush(stdin);
	switch(nOption){
		case 1:
			clientMenu();
			break;
		case 2:
			sellerMenu();
			break;
		case 3:
			vehicleMenu();
			break;
		case 4:
			sellMenu();
			break;
		case 5:
			exit;
			break;
		default:
			printf("Escolha uma opção valida.\n");
			getch();
			menu();
			break;
	}
}

//TELAS INICIAIS
clientMenu(){
	system("cls");
	nOption = 0;
	printf("*************************************************\nCLIENTE\n*************************************************\n\n");
	printf("Escolha uma Opção:\n\n 1 - CADASTRO\n 2 - CONSULTA\n 3 - VOLTAR\n");
	
	scanf("%d", &nOption);
	fflush(stdin);
	switch(nOption){
		case 1:
			clientMenu_insert();
			break;
		case 2:
			clientMenu_search();
			break;
		case 3:
			menu();
			break;
		default:
			printf("Escolha uma opção valida.\n");
			getch();
			clientMenu();
			break;
	}
}
sellerMenu(){
	system("cls");
	nOption = 0;
	printf("*************************************************\nVENDEDOR\n*************************************************\n\n");
	printf("Escolha uma opção:\n\n 1 - CADASTRO\n 2 - CONSULTA\n 3 - VOLTAR\n");
	
	scanf("%d", &nOption);
	fflush(stdin);
	switch(nOption){
		case 1:
			sellerMenu_insert();
			return;
			break;
		case 2:
			sellerMenu_search();
			return;
			break;
		case 3:
			menu();
			return;
			break;
		default:
			printf("Escolha uma opção valida.\n");
			getch();
			sellerMenu();
			return;
			break;
	}
}
vehicleMenu(){
	system("cls");
	nOption = 0;
	printf("*************************************************\nVEÍCULO\n*************************************************\n\n");
	printf ("Escolha uma opção:\n\n 1 - CADASTRO\n 2 - CONSULTA\n 3 - VOLTAR\n");
		
	scanf("%d", &nOption);
	fflush(stdin);
	switch(nOption){
		case 1:
			vehicleMenu_insert();
			return;
			break;
		case 2:
			vehicleMenu_search();
			return;
			break;
		case 3:
			menu();
			return;
			break;
		default:
			printf("Escolha uma opção valida.\n");
			getch();
			vehicleMenu();
			return;
			break;
	}
}
sellMenu(){
	system("cls");
	nOption = 0;
	printf("*************************************************\nVENDAS\n*************************************************\n\n");
	printf("Escolha uma opção:\n\n 1 - INICIAR\n 2 - CONSULTA\n 3 - VOLTAR\n");
	//printf("Escolha uma opção:\n\n 1 - INICIAR\n 2 - VOLTAR\n");
	scanf("%d", &nOption);
	fflush(stdin);
	switch(nOption){
		case 1:
			sellMenu_insert();
			return;
			break;
		case 2:/**/
			sellMenu_search();
			return;
			break;
		case 3:/**/
			menu();
			return;
			break;
		default:
			printf("Escolha uma opção valida.\n");
			getch();
			sellMenu();
			return;
			break;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SUB TELAS 'CLIENTE'
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
clientMenu_insert(){
	nOption = 0; errorUsr = 0;
	system("cls");
	strcpy(title, "CADASTRO CLIENTE");
	printf("*************************************************\n%s\n*************************************************\n\n", title);
	printf("Digite as informações do cliente:\n");
	
	getName("Nome:");
//	printf("\n\n%s\n\%s\n\n\n\n", name, client.fName);
	getCPF("CPF:");
	getBirth("Data de nascimento:");
	strcpy(title, "CADASTRO CLIENTE");
	getSalary("Salário:");
	getPhone("Telefone:");
	appendOnDB(1);
	return;
	//printf("%s\n%s\n%s\n%s\n%s\n%s\n", );	
	/*
	cliente.fName = ("%s", name);
	cliente.fCpf = ("%s", cpf);
	cliente.fBirth = ("%s", birth);
	cliente.fPhone = ("%s", phone);
	cliente.fSalary = ("%.2f", salary);
	printf("%s \n %s\n %s\n %s\n %s\n %s\n", cliente.fName, cliente.fCpf, cliente.fBirth, cliente.fPhone, cliente.fSalary);
	*/
}
clientMenu_search(){	
	system("cls");
	clearErrors();
	nOption = 0;
	strcpy(title, "BUSCA CLIENTE");
	printf("*************************************************\n%s\n*************************************************\n\n", title);
	
	printf("Escolha a opção de busca:\n 1 - Nome\n 2 - CPF\n 3 - ID\n 4 - Voltar\n");
	scanf("%d", &nOption);
	switch(nOption){
		case 1:
			getName("Digite o Nome do cliente:");
			getUserDB(1, 1, 0);
			break;
		case 2:
			getCPF("Digite o CPF do cliente:");
			getUserDB(2, 1, 0);
			break;
		case 3:
			printf("Digite o ID do cliente:\n");
			scanf("%s", &client.countArqS);
			getUserDB(3, 1, 0);
			break;
		case 4:
			clientMenu();
			break;
		default:
			printf("Escolha uma opção valida.");
			getch();
			clientMenu_search();
			break;
	}
}
clientMenu_update(){
	nOption = 0; errorUsr = 0;
	system("cls");
	strcpy(title, "BUSCA CLIENTE PARA ALTERAÇÃO");
	printf("*************************************************\n%s\n*************************************************\n\n", title);

	waitESC("Digite o CPF ou pressione a tecla ESC para voltar");
	if (force_exit != 0){
		return;
	}

	fflush(stdin);
	printf("%s\n\n", cpf);

printf("SISTEMA DEVERÁ OBTER INFORMAÇÕES DO CPF %s CADASTRADO\n", cpf);
		/*
		
		* CÓDIGO DE BUSCA 'CPF'
		
		*/
printf("SISTEMA DEVERÁ OBTER NOVAS INFORMAÇÕES DO CPF %s CADASTRADO PARA ATUALIZAÇÃO\n", cpf);
	
	strcpy(title, "ATUALIZAR CADASTRO CLIENTE");
	getName("Nome:");
	getCPF("CPF:");
	getBirth("Data de nascimento:");
	getSalary("Salário:");
	strcpy(title, "ATUALIZAR CADASTRO CLIENTE");
	getPhone("Telefone:");
	//appendOnDB();
printf("\n");
getch();
menu();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SUB TELAS 'VENDEDOR'
sellerMenu_insert(){
	nOption = 0; errorUsr = 0;
	system("cls");
	strcpy(title, "CADASTRO VENDEDOR");
	printf("*************************************************\n%s\n*************************************************\n\n", title);
	printf("Digite as informações do vendedor:\n");
	
	getName("Nome:");
	getCPF("CPF:");
	getBirth("Data de nascimento:");
	strcpy(title, "CADASTRO VENDEDOR");
	getSalary("Salário:");
	getPhone("Telefone:");
	savePass();
	appendOnDB(2);
	return;
	/*
printf("\n");
getch();
menu();
	*/
}
sellerMenu_search(){
	nOption = 0; errorUsr = 0;
	system("cls");
	strcpy(title, "BUSCA VENDEDOR");
	printf("*************************************************\n%s\n*************************************************\n\n", title);
	printf("Escolha a opção de busca:\n 1 - Nome\n 2 - CPF\n 3 - ID\n 4 - Voltar\n");

	scanf("%d", &nOption);
	switch(nOption){
		case 1:
			printf("Digite o nome do vendedor:\n");
			getName("Nome:");
			getUserDB(1, 2, 0);
			break;
		case 2:
			getCPF("Digite o CPF do vendedor:");
			getUserDB(2, 2, 0);
			break;
		case 3:
			printf("Digite o ID do vendedor:\n");
			scanf("%s", &client.countArqS);
			getUserDB(3, 2, 0);
			break;
		case 4:
			sellerMenu();
			break;
		default:
			printf("Escolha uma opção valida.");
			getchar();
			clientMenu_search();
			break;
	}
}
sellerMenu_update(){
	printf("*************************************************\nBUSCA VENDEDOR PARA ALTERAÇÃO\n*************************************************\n\n");
	
	//printf("Digite o CPF do vendedor:\n");
	getCPF("Digite o CPF do vendedor:");
	/*
	
	* CÓDIGO DE BUSCA 'CPF'
	
	*/
	printf("Digite as novas informações do vendedor:\nNome:\n");
	getName("Nome:");
	getCPF("CPF:");
	getBirth("Data de Nascimento:");
	getPhone("Telefone:");	
	/*
	
	* COMPARA INFORMAÇÕES
	* ATUALIZA TABELA BINÁRIA
	
	*/
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SUB TELAS 'VEÍCULOS'
vehicleMenu_insert(){
	nOption = 0; errorUsr = 0;
	system("cls");
	strcpy(title, "CADASTRO VEÍCULO");
	printf("*************************************************\n%s\n*************************************************\n\n", title);
	printf("Digite as informações do veículo:\n");
	
	getLicensePlate("Placa do veículo:");
	getManufacturer("Fabricante:");
	getNameVehicle("Modelo:");
	getVehicleYear("Ano de fabricação:");
	getVehicleColor("Cor:");
	getHodometer("Hodômetro:");
	getBuyValue("Valor de compra:");
	getSellValue("Preço de venda;");
	addVehicle();
}
vehicleMenu_search(){
	    nOption = 0; errorUsr = 0;
    system("cls");
    strcpy(title, "BUSCA VENDEDOR");
    printf("*************************************************\n%s\n*************************************************\n\n", title);
    printf("Escolha a opção de busca:\n 1 - Placa\n 2 - ID\n 3 - Voltar\n");

    scanf("%d", &nOption);
    switch(nOption){
        case 1:
            getLicensePlate("Digite a placa do veículo:");
            getCarDB(1, 0);
            return;
            break;
        case 2:
			printf("Digite o ID do veículo:\n");
			scanf("%s", &car.countArqS);
			getCarDB(2, 0);
            return;
            break;
        case 3:
            vehicleMenu();
			break;
        default:
            printf("Escolha uma opção valida.");
            getchar();
            vehicleMenu_search();
            return;
            break;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SUB TELAS 'VENDAS'
showNameClient(){
	printf("Nome:\t %s\t\t\tCPF:\t%s\n",
					foundPeople.fName,
					foundPeople.fCpf);
	printf("Dt Nasc: %s\tSalário:   %.2f\tTelefone:   %s\n\n",
					foundPeople.fBirth,
					foundPeople.fSalary,
					foundPeople.fPhone);
	strcpy(saveSimu.fName, foundPeople.fName);
	strcpy(saveSimu.fCpf, foundPeople.fCpf);
}
showInfoCar(){
	printf("Fabricante:  %s\tModelo:  %s\tPlaca: %s\tCor: %s\n",
					foundCar.cManu,
					foundCar.cName,
					foundCar.cLicense,
					foundCar.cColor);
	printf("Ano:   %s\tValor:   %.2f\tQuilometragem:  %.2f\n",
					foundCar.cYear,
					foundCar.cfSellValue,
					foundCar.cfHodometer);
	strcpy(saveSimu.cLicense, foundCar.cLicense);
	saveSimu.cfSellValue = foundCar.cfSellValue;
	saveSimu.cfHodometer = foundCar.cfHodometer;
}
sellMenu_insert(){
	valExit = 0;
	nOption = 0; errorUsr = 0; foundCar.cfSellValue = 0, valExit = 0;;
	system("cls");
	strcpy(title, "INICIAR VENDA");
	printf("*************************************************\n%s\n*************************************************\n\n", title);
	printf("CPF ou ID do cliente? (1 - CPF   |   2 - ID)\n");
	nOption = (getche()-48);
	printf("%d\n", nOption);
	switch(nOption){
			case 1:
				errorUsr = 4;
				clearErrors();
				getCPF("Digite o CPF do cliente:");
				getUserDB(2, 1, 2);
				if (valExit != 0){
					return;
				}
				valExit = 0;
				break;
			case 2:
				errorUsr = 4;
				clearErrors();
				printf("Digite o ID do cliente:\n");
				fflush(stdin);
				scanf("%s", &client.countArqS);
				fflush(stdin);
				printf("valor: %d\n", valExit);
				getUserDB(3, 1, 2);
				printf("valor: %d\n", valExit);
				if (valExit != 0){
					return;
				}
				valExit = 0;
				break;
			default:
				system("color 0c");
				printf("Digite uma opção válida.\n");
				//sleep(1); //getchar();
				getche();
				printf("\b");
				errorUsr++;
				clearErrors();
				sellMenu_insert();
				return;
				break;
	}
	if (valExit != 0){
		return;
	}
	valExit = 0;
	errorUsr = 4;
	clearErrors();
	showNameClient();

	printf("\nPlaca ou ID do veículo? (1 - Placa   |   2 - ID)\n");
	nOption = (getche()-48);
	printf("%d\n", nOption);
	switch(nOption){
			case 1:
				errorUsr = 4;
				clearErrors();
				showNameClient();
				getLicensePlate("Placa do veículo a ser comprado:");
				getCarDB(1, 2);
				if (valExit != 0){
					return;
				}
				break;
			case 2:
				errorUsr = 4;
				clearErrors();
				showNameClient();
				printf("\nDigite o ID do veículo:\n");
				scanf("%s", &car.countArqS);
				getCarDB(2, 2);
				if (valExit != 0){
					return;
				}
				break;
			default:
				system("color 0c");
				printf("Digite uma opção válida.\n");
				//sleep(1); //getchar();
				getche();
				printf("\b");
				errorUsr++;
				clearErrors();
				sellMenu_insert();
				return;
				break;
	}
	if (valExit != 0){
		return;
	}
	valExit = 0;
	errorUsr = 4;
	clearErrors();
	showNameClient();
	showInfoCar();
	getentrada();
}
sellMenu_search(){
	nOption = 0; errorUsr = 0;
	system("cls");
	strcpy(title, "PROCURAR VENDA");
	printf("*************************************************\n%s\n*************************************************\n\n", title);
	printf("Digite o protocolo da simulação:\n");
	scanf("%s", &foundCar.countArqS);
	getSimulation(1);

}

getentrada(){
    entrada = 0;
    total = foundCar.cfSellValue;
	printf("Digite o valor da entrada: \n");
	scanf("%f", &entrada);
	fflush(stdin);
	if(entrada < 0 || entrada >= total){
		system("color 0c");
		printf("Valor de entrada inválido.\n");
		errorUsr++;
		//sleep(1); //getchar();
		getche();
		printf("\b");
		clearErrors();
		showNameClient();
		showInfoCar();
		getentrada();
		return 0;
	}
	validacao = (entrada / total);
	condicao_auto();
}
condicao_auto(){
	option = 0;
	/*
	printf(" Valor total: %.2f\n Entrada: %.2f\n\n", total, entrada);
	printf("Escolha uma Opção:\n\n 1 - Novo\n 2 - Usado\n\n");
	scanf("%d", &option);
	fflush(stdin);
	*/
	if(saveSimu.cfHodometer == 0){
		option = 1;
	} else{
		option = 2;
	}
	
	switch(option){
	case 1:
		condicaoAuto = 1;
		strcpy(condicaoAutoNome, "Novo");
		parcela();
		break;
	case 2:
		condicaoAuto = 2;
		strcpy(condicaoAutoNome, "Usado");
		parcela();
		break;
	default:
		system("color 0c");
		printf("Opção válida.\n");
		errorUsr++;
		//sleep(1); //getchar();
		getche();
		printf("\b");
		clearErrors();
		showNameClient();
		showInfoCar();
		condicao_auto();
	}
}
parcela(){
	option = 0;
	printf("Entrada: %.2f\n Condição: Veículo %s\n", entrada, condicaoAutoNome);
	if(condicaoAuto == 1){
		//system("cls");
		printf("Selecione uma opção:\n 1 - 12 parcelas\t\t2 - 24 parcelas\n 3 - 36 parcelas\t\t4 - 48 parcelas\n\n");
		scanf("%d", &option);
		fflush(stdin);

		switch(option){
			case 1:
				qParcela = 12;
				break;
			case 2:
				qParcela = 24;
				break;
			case 3:
				qParcela = 36;
				break;
			case 4:
				qParcela = 48;
				break;
			default:
				system("color 0c");
				printf("Digite uma opção válida.\n");
				//sleep(1); //getchar();
				getche();
				printf("\b");
				errorUsr = 4;
				clearErrors();
				showNameClient();
				showInfoCar();
				parcela();
				return;
				break;
		}
	}
	if(condicaoAuto == 2){
		//system("cls");
		printf("Selecione uma opção:\n 1 - 12 parcelas\t\t2 - 24 parcelas\n 3 - 36 parcelas\t\t4 - 48 parcelas\n\n");
		scanf("%d", &option);
		fflush(stdin);

		switch(option){
			case 1:
				qParcela = 12;
				break;
			case 2:
				qParcela = 24;
				break;
			case 3:
				qParcela = 36;
				break;
			case 4:
				qParcela = 48;
				break;
			default:
				system("color 0c");
				printf("Digite uma opção válida.\n");
				//sleep(1); //getchar();
				getche();
				printf("\b");
				errorUsr = 4;
				clearErrors();
				showNameClient();
				showInfoCar();
				parcela();
				return;
				break;
		}
	}
	taxa();
}
taxa(){
	if(validacao == 1){
		printf("Sem financiamento.");
		if(entrada == 0){
			if(condicaoAuto == 1){
				if (qParcela == 12){
					vTaxa = 3.0;
				}
				if (qParcela == 24){
					vTaxa = 3.5;
				}
				if (qParcela == 36){
					vTaxa = 4.0;
				}
				if (qParcela == 48){
					vTaxa = 4.5;
				}
			}
			if(condicaoAuto == 2){
				if (qParcela == 12){
						vTaxa = 3.5;
				}
				if (qParcela == 24){
						vTaxa = 4.5;
				}
				if (qParcela == 36){
						vTaxa = 5.0;
				}
				if (qParcela == 48){
						vTaxa = 5.5;
				}
			}
		}
	}
///////////////////////////////////////////////////
	if (validacao >= 0.5 && validacao < 1){
		if(condicaoAuto == 1){
			if (qParcela == 12){
				vTaxa = 1.0;
			}
			if (qParcela == 24){
				vTaxa = 1.5;
			}
			if (qParcela == 36){
				vTaxa = 2.0;
			}
			if (qParcela == 48){
				vTaxa = 2.5;
			}
		}
		if(condicaoAuto == 2){
			if (qParcela == 12){
					vTaxa = 2.5;
			}
			if (qParcela == 24){
					vTaxa = 3.0;
			}
			if (qParcela == 36){
					vTaxa = 3.5;
			}
			if (qParcela == 48){
					vTaxa = 4.0;
			}
		}
	}
///////////////////////////////////////////////////
	if (validacao < 0.5){
		if(condicaoAuto == 1){
			if (qParcela == 12){
				vTaxa = 2.0;
			}
			if (qParcela == 24){
				vTaxa = 2.5;
			}
			if (qParcela == 36){
				vTaxa = 3.0;
			}
			if (qParcela == 48){
				vTaxa = 3.5;
			}
		}
		if(condicaoAuto == 2){
			if (qParcela == 12){
					vTaxa = 3.5;
			}
			if (qParcela == 24){
					vTaxa = 4.0;
			}
			if (qParcela == 36){
					vTaxa = 4.5;
			}
			if (qParcela == 48){
					vTaxa = 5.0;
			}
		}
	}
///////////////////////////////////////////////////	
	calculo();
}
calculo(){
	saldo = (total - entrada);
	potMont = pow((1+(vTaxa/100)), qParcela);
	montante = (saldo*potMont);
	mensalidade = (montante / qParcela);
	vFinal = (montante + entrada);
	
	saveSimu.saldo = saldo;
	saveSimu.vTaxa = vTaxa;
	saveSimu.entrada = entrada;
	saveSimu.qParcela = qParcela;
	saveSimu.mensalidade = mensalidade;
	saveSimu.vFinal = vFinal;

	system("cls");
	printf("Valor da taxa: %.2f\nValor do automaovel: %.2f\nValor da entrada: %.2f\nValor de cada uma das %d parcelas: %.2f\nValor total do financiamento: %.2f\n\nPressione qualquer tecla para realizar um novo financiamento.\n", vTaxa, total, entrada, qParcela, mensalidade, vFinal);
	saveSimulation();
    return;
}
getLastLine(int menuType){
	struct information getSimu, ac, car1;
	char type[15];
	int i=0;
	
	FILE *arq;
	if (menuType == 1){
		i = 0;
		strcpy(type, "do cliente");
		arq = fopen("dbClient.db", "r");
		while(fscanf(arq,"%s %s %s %s %s %s\n", countArqS, ac.fName, ac.fCpf, ac.fBirth, ac.fPhone, ac.strSalary)!=EOF){
			if(countArqS != NULL){
				i++;
			}else{
				i = 0;
			}
		}
		fclose(arq);
		//printf("Numero de linhas: %d\n", i);
		countArq = atoi(countArqS);
	}else if (menuType == 2){
		i = 0;
		strcpy(type, "da venda");
		arq = fopen("dbSell.db", "r");
		while(fscanf(arq,"%s %s %s %s %s %s %s %s %s\n", countArqS, getSimu.cLicense, getSimu.fName,  getSimu.fCpf, getSimu.cSellValue,  getSimu.entradaS, getSimu.qParcelaS, getSimu.mensalidadeS, getSimu.vFinalS)!=EOF){
			if(countArqS != NULL){
				i++;
			}else{
				i = 0;
			}
		}
		fclose(arq);
		//printf("Numero de linhas: %d\n", i);
		countArq = atoi(countArqS);
	}else if (menuType == 3){
		i = 0;
		strcpy(type, "do vendedor");
		arq = fopen("dbSeller.db", "r");
		while(fscanf(arq,"%s %s %s %s %s %s\n", countArqS, ac.fName, ac.fCpf, ac.fBirth, ac.fPhone, ac.strSalary)!=EOF){
			if(countArqS != NULL){
				i++;
			}else{
				i = 0;
			}
		}
		fclose(arq);
		//printf("Numero de linhas: %d\n", i);
		countArq = atoi(countArqS);
	}else if (menuType == 4){
		i = 0;
		strcpy(type, "do veículo");
		arq = fopen("dbVehicle.db", "r");
		while(fscanf(arq,"%s %s %s %s %s %s %s %s %s\n", countArqS, car1.cLicense, car1.cManu, car1.cName, car1.cYear, car1.cColor, car1.cHodometer, car1.cBuyValue, car1.cSellValue)!=EOF){
			if(countArqS != NULL){
				i++;
			}else{
				i = 0;
			}
		}
		fclose(arq);
		//printf("Numero de linhas: %d\n", i);
		countArq = atoi(countArqS);
	}
	countArq = i;
	countArq++;

	printf("\nO ID %s é %d", type, countArq);
}
