#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <dirent.h>

typedef struct {
char codeBank[4];
FILE *ptr;
} idx_file;

int m;
void clearMyArr(char *tab[]);
void matchArrays(char* cro_rio[],char* image_rio[],int cro_num,int image_num);
int main(int argc, char *argv[])
 {
 	int i=0;
 	int k=0;

 	//variables
	char get_all_line[591];
	char stringbuffer[51];
    char header[37];

    LPCSTR configuration = "./configuration.ini";
    char ini_in[100];
    char ini_out[100];
    char Cro_in[100];
    char IDX_out[100];
    char Target[100];
    char* getFirst3[126];
    char* storeDate[126];
    char rio[33];
	char *rio_ptr[126],date[11];
	char type_operation[4],   reference_operation[13];
	char indicateur_presence,    rib_client[25];
	char nom_raison[36],    adresse[51];
	char indicateur_presence_tire,    numero_cheque[8];
	char rib_client_tire[26],    nom_raison_tire[36];
	char adresse_tire[51],    montant[16];
	char date_remise[9],    code_cheque[2];
	char nature_compte[2];

	FILE *ptr, *ptr_modified;

	//lecture de pramatres
    GetPrivateProfileString("Directory", "In", 0, ini_in, 100, configuration);
    GetPrivateProfileString("Directory","Out", 0, ini_out, 100, configuration);
    GetPrivateProfileString("Directory","File_CRO_In", 0, Cro_in, 100, configuration);
    GetPrivateProfileString("Directory","File_IDX_Out", 0, IDX_out, 100, configuration);
    GetPrivateProfileString("Directory","Retour", 0, Target, 100, configuration);

    // chemin des fichiers traites
    strcat(strcat(ini_in,"/"),Cro_in);
    strcat(strcat(ini_out,"/"),IDX_out);

    // ouverture de fichier CRO
    ptr=fopen(ini_in,"r");
	ptr_modified=fopen(ini_out,"w+");

	if (ptr==NULL || ptr_modified==NULL)
	{
    	printf("Error Loading Files");
	    exit (-100);
	}


while (fgets(header,65,ptr)!=NULL){   //read the header and break to make the pointer points to the first index
    fprintf(ptr_modified,"%s\n",header);
    break;
}
	while (!feof(ptr)){   //write the information(indexes) in the EDITED .CRO File with the |||||
	       fgets(get_all_line,591,ptr);

			fgets(stringbuffer, 33, ptr);
            strcpy(rio,stringbuffer);

			if (k<126){
			rio_ptr[k]=(char*)malloc(33*sizeof(char));
			strcpy(rio_ptr[k],stringbuffer);
			getFirst3[k]=(char*)malloc(126*sizeof(char));
			memcpy(getFirst3[k],rio,3);
			}

			fgets(stringbuffer,9,ptr);
			strcpy(date,stringbuffer);

			if (k<126){
            storeDate[k]=(char*)malloc(126*sizeof(char));
            memcpy(storeDate[k],date,9);}

			fgets(stringbuffer,4,ptr);
	        strcpy(type_operation,stringbuffer);
			fgets(stringbuffer,13,ptr);
	    	strcpy(reference_operation,stringbuffer);
	    	indicateur_presence=fgetc(ptr);
			fgets(stringbuffer,25,ptr);
			strcpy(rib_client,stringbuffer);
			fgets(stringbuffer,5,ptr);
			fgets(stringbuffer,36,ptr);
			strcpy(nom_raison,stringbuffer);
			fgets(stringbuffer,51,ptr);
		    strcpy(adresse,stringbuffer);
		    indicateur_presence_tire=getc(ptr);
		    fgets(stringbuffer,8,ptr);
            strcpy(numero_cheque,stringbuffer);
            fgets(stringbuffer,25,ptr);
			strcpy(rib_client_tire,stringbuffer);
			fgets(stringbuffer,5,ptr);
			fgets(stringbuffer,36,ptr);
			strcpy(nom_raison_tire,stringbuffer);
			fgets(stringbuffer,51,ptr);
			strcpy(adresse_tire,stringbuffer);
			fgets(stringbuffer,16,ptr);
			strcpy(montant,stringbuffer);
			fgets(stringbuffer,9,ptr);
			strcpy(date_remise,stringbuffer);
            fgets(stringbuffer,2,ptr);
            strcpy(code_cheque,stringbuffer);
            fgets(stringbuffer,2,ptr);
            strcpy(nature_compte,stringbuffer);

            fprintf(ptr_modified,"%s|%s|%s|%s|%c|%s|    |%s|%s|%c|",rio,date,type_operation,reference_operation,indicateur_presence,rib_client,nom_raison,adresse,indicateur_presence_tire);
            fprintf(ptr_modified,"%s|%s|    |%s|%s|%s|%s|%s|%s|\n",numero_cheque,rib_client_tire,nom_raison_tire,adresse_tire,montant,date_remise,code_cheque,nature_compte);

            k++;
	}
k=k-1;
clearMyArr(getFirst3);   //remove duplicated sender values




//the .MAIlO file
int recto_num_mailo,verso_num_mailo;

    char header_mailo[65];
    char CRLF_header_mailo[3];
    char first40_mailo[41];
    char rio_mailo[33];
    char* rio_mailo_ptr[300];
    char date_capture_mailo[9];
    char longueur_recto_mailo[10];
    char longueur_verso_mailo[10];
    char montant_mailo[293];
    char CRLF1_mailo[3];
    char CRLF2_mailo[3];
    char CRLF3_mailo[3];
    char *all_mailo[700];

    //images
    char *image_recto,*image_verso;
    char filename_rec_mailo[100];
    char filename_ver_mailo[100];
    int ij=0,getIJ=0;

    //set all arrays to 0
memset(header_mailo,'\0',sizeof(header_mailo));
memset(CRLF_header_mailo,'\0',sizeof(CRLF_header_mailo));
memset(first40_mailo,'\0',sizeof(first40_mailo));
memset(rio_mailo,'\0',sizeof(rio_mailo));
memset(date_capture_mailo,'\0',sizeof(date_capture_mailo));
memset(longueur_recto_mailo,'\0',sizeof(longueur_recto_mailo));
memset(longueur_verso_mailo,'\0',sizeof(longueur_verso_mailo));
memset(montant_mailo,'\0',sizeof(montant_mailo));
memset(CRLF1_mailo,'\0',sizeof(CRLF1_mailo));
memset(CRLF2_mailo,'\0',sizeof(CRLF2_mailo));
memset(CRLF3_mailo,'\0',sizeof(CRLF2_mailo));
    DIR *d;
    struct dirent *dir;
    char path[]="C:\\nabil_files\\Stage_Soufiane\\Jeu_Test\\";
    char fileInPath[100];
    d = opendir(path);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)  //this will read each filename in the directory
        {

            int len=strlen(dir->d_name);
            if (len>=34){
                  sprintf(fileInPath,"%s%s",path,dir->d_name);

                FILE *ptr_mailo=fopen(fileInPath,"rb");

                if (ptr_mailo==NULL){
                     printf("Erreur");
                    exit(EXIT_FAILURE);
   }
                 //read the header_mailo and the carriage return
   fread(header_mailo, sizeof(char), 64, ptr_mailo);
   fread(CRLF_header_mailo, sizeof(char), 2, ptr_mailo);
ij=getIJ;
   while (!feof(ptr_mailo)){
   fread(first40_mailo,sizeof(char),40,ptr_mailo);
   fread(rio_mailo,sizeof(char),32,ptr_mailo);
   rio_mailo_ptr[ij]=(char*)malloc(33*sizeof(char));
   strcpy(rio_mailo_ptr[ij],rio_mailo);
   ij++;
   fread(date_capture_mailo,sizeof(char),8,ptr_mailo);
   fread(longueur_recto_mailo,sizeof(char),9,ptr_mailo);
   fread(longueur_verso_mailo,sizeof(char),9,ptr_mailo);
   recto_num_mailo=atoi(longueur_recto_mailo);
   verso_num_mailo=atoi(longueur_verso_mailo);
   fread(montant_mailo,sizeof(char),292,ptr_mailo);
   fread(CRLF1_mailo,sizeof(char),2,ptr_mailo);
image_recto=(char*)malloc((recto_num_mailo+1)*sizeof(char));
image_verso=(char*)malloc((verso_num_mailo+1)*sizeof(char));
memset(image_recto,'\0',sizeof(image_recto));
memset(image_verso,'\0',sizeof(image_verso));
fread(image_recto,sizeof(char),recto_num_mailo,ptr_mailo);
fread(CRLF2_mailo,sizeof(char),2,ptr_mailo);
fread(image_verso,sizeof(char),verso_num_mailo,ptr_mailo);
fread(CRLF3_mailo,sizeof(char),2,ptr_mailo);
free(image_recto);
free(image_verso);
}
getIJ=ij;

fclose(ptr_mailo);
        }
        }
        }

        closedir(d);
       matchArrays(rio_ptr,rio_mailo_ptr,k,getIJ);


idx_file var[m];
char currDate[9];
time_t t=time(NULL);
struct tm tm =*localtime(&t);
sprintf(currDate,"%.4d%.2d%.2d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

for (i=0;i<m;i++){
    char filename[40];
    strcpy(var[i].codeBank,*(getFirst3+i));
GetPrivateProfileString("Directory","Out", 0, ini_out, 100, configuration);
sprintf(filename,"%s/%s.%s.%d.%s.idx",ini_out,Target,var[i].codeBank,i+1,currDate);
var[i].ptr=fopen(filename,"w");
fprintf(var[i].ptr,"0|INS|%s|%.4d%s|\n",currDate,i+1,var[i].codeBank);
}

	fclose(ptr);
	fclose(ptr_modified);

strcat(strcat(ini_out,"/"),IDX_out);

ptr_modified=fopen(ini_out,"r");
if (ptr==NULL){
    printf("Error Loading File");
}
int j=1;
char getCode[4];
char code_bank_rem[4];
char codeLocal_rem[4];
char numCompte_rem[17];
char clRib_rem[4];
char code_bank_tire[4];
char codeLocal_tire[4];
char numCompte_tire[17];
char clRib_tir[4];

fgets(header,65,ptr_modified);   //read the header of the EDITED CRO File

while (!feof(ptr_modified)){   //copy the information for each bank in its own index file

   fgets(get_all_line,591,ptr_modified);

   fgets(getCode,4,ptr_modified);
   fgets(stringbuffer, 30, ptr_modified);
   sprintf(rio,"%s%s",getCode,stringbuffer);
   fgets(stringbuffer,2,ptr_modified);
   fgets(stringbuffer,9,ptr_modified);
   strcpy(date,stringbuffer);
   fgets(stringbuffer,21,ptr_modified);
   fgets(stringbuffer,4,ptr_modified);
   strcpy(code_bank_rem,stringbuffer);
   fgets(stringbuffer,4,ptr_modified);
   strcpy(codeLocal_rem,stringbuffer);
   fgets(stringbuffer,17,ptr_modified);
   strcpy(numCompte_rem,stringbuffer);
   fgets(stringbuffer,3,ptr_modified);
   strcpy(clRib_rem,stringbuffer);
   fgets(stringbuffer,7,ptr_modified);
   fgets(stringbuffer,36,ptr_modified);
   strcpy(nom_raison,stringbuffer);
   fgets(stringbuffer,2,ptr_modified);
   fgets(stringbuffer,51,ptr_modified);
   strcpy(adresse,stringbuffer);
   fgets(stringbuffer,4,ptr_modified);
   fgets(stringbuffer,8,ptr_modified);
   strcpy(numero_cheque,stringbuffer);
   fgets(stringbuffer,2,ptr_modified);
   fgets(stringbuffer,4,ptr_modified);
   strcpy(code_bank_tire,stringbuffer);
   fgets(stringbuffer,4,ptr_modified);
   strcpy(codeLocal_tire,stringbuffer);
   fgets(stringbuffer,17,ptr_modified);
   strcpy(numCompte_tire,stringbuffer);
   fgets(stringbuffer,3,ptr_modified);
   strcpy(clRib_tir,stringbuffer);
   fgets(stringbuffer,7,ptr_modified);
   fgets(stringbuffer,36,ptr_modified);
   strcpy(nom_raison_tire,stringbuffer);
   fgets(stringbuffer,2,ptr_modified);
   fgets(stringbuffer,51,ptr_modified);
   strcpy(adresse_tire,stringbuffer);
   fgets(stringbuffer,2,ptr_modified);
   fgets(stringbuffer,16,ptr_modified);
   strcpy(montant,stringbuffer);
   fgets(stringbuffer,2,ptr_modified);
   fgets(stringbuffer,9,ptr_modified);
   strcpy(date_remise,stringbuffer);
   fgets(stringbuffer,2,ptr_modified);
   fgets(stringbuffer,2,ptr_modified);
   strcpy(code_cheque,stringbuffer);
   fgets(stringbuffer,2,ptr_modified);
   fgets(stringbuffer,2,ptr_modified);
   strcpy(nature_compte,stringbuffer);

   for (i=0;i<m;i++){

    if (strcmp(getCode,var[i].codeBank)==0){

        fprintf(var[i].ptr,"1|%d|%s|%s|%s|%s|",j,rio,date,code_bank_rem,codeLocal_rem);
        fprintf(var[i].ptr,"%s|%s|%s|%s|%s|",numCompte_rem,clRib_rem,numero_cheque,code_bank_tire,codeLocal_tire);
        fprintf(var[i].ptr,"%s|%s|%s|%s|%s|",numCompte_tire,clRib_tir,montant,montant,date_remise);
        fprintf(var[i].ptr,"%s|%s|%s|%s|%s|",date,code_cheque,nature_compte,nom_raison,nom_raison_tire);
        fprintf(var[i].ptr,"%s|%s|",adresse,adresse_tire);
        fprintf(var[i].ptr,"\n");
   j++;
   break;
        }
   }
}

return 0;
}
void matchArrays(char* cro_rio[],char* image_rio[],int cro_num,int image_num){
    int i,j,h=0;;
    for (i=0;i<cro_num;i++){
    for (j=0;j<image_num;){
        if (strcmp(cro_rio[i],image_rio[j])==0){
            //printf("Images Exist for: %s\n",cro_rio[i]);
            h++;
            break;
        }
        else {j++;}
    }
}
printf("le nombre des rio ayant des fichiers image: %d",h);
}
void clearMyArr(char *arr[]){
    int n=126;
    int i,j,k;
    for (i=0;i<n;i++){
for (j=i+1;j<n;){
if (strcmp(*(arr+j),*(arr+i))==0){
for (k=j;k<n;k++){
*(arr+k)=*(arr+k+1);
}
n--;
}
else {
j++;
}
}
}
m=n;
}
