#include <stdlib.h>
#include <stdio.h>

char** allouer_tab_2D(int n, int m){
    char** tab;
    tab=(char**)malloc(n*sizeof(char*));
    for(int i=0;i<n;i++)
    {
        tab[i]=(char*)malloc(m*sizeof(char));
    }
    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            tab[i][j]=' ';
        }
    }
    return tab;
}

void desallouer_tab_2D(char** tab, int n){
   for(int i=0;i<n;i++)
   {
       free(tab[i]);
   }
   free(tab);
}

void afficher_tab_2D(char** tab, int n, int m){
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=m;j++)
        { 
            if(tab[i][j]!=' ')
            {
                printf("%c",tab[i][j]);
            }
        }
    }
    printf("\n");
}
    
void taille_fichier(const char* nomFichier,int* nbLig, int* nbCol){
    *nbLig=0;
    *nbCol=0;
    FILE *fp;
    int c;
    int j=0;
    int i=0;
    fp=fopen(nomFichier,"r");
    do
    {
            if(c=='\n'||c==EOF)
            {
            
                if(j>*nbCol)
                {
                    if(i==0)
                    {
                        *nbCol=j-1;
                    }
                    else
                    {
                        *nbCol=j;
                    }
                }
                i=i+1;
                j=0;
            }
            else
            {
                j=j+1;
            }
            c = fgetc (fp);
    } while(c!=EOF);
    *nbLig=i;
}
    

char** lire_fichier(const char* nomFichier){
    char** G;
    int nbLig=0;
    int nbCol=0;
    taille_fichier(nomFichier,&nbLig,&nbCol);
    G=allouer_tab_2D(nbLig,nbCol+1);
    FILE * fp;
    fp=fopen(nomFichier, "r");  
    if (fp==NULL)  perror ("Erroropening file");
    else { 
        for(int i=0; i<nbLig ; i++)
        {
            for(int j=0; j<=nbCol ; j++)  
            {   
                    fscanf (fp,"%c",&G[i][j]);
            }
        }
    }
    fclose (fp); 
    return G;
}

char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau){
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(tab[i][j]==ancien)
            {
                tab[i][j]=nouveau;
            }
        }
    }
    return tab;
}

void ecrire_fichier(const char* nomFichier, char** tab, int n, int m){
    FILE * fp;
    fp=fopen(nomFichier,"w");  
    if (fp==NULL)  perror ("Erroropening file");  
    else {
        for(int i=0; i<n ; i++)
        {
            for(int j=0; j<=m; j++)
                fprintf(fp,"%c",tab[i][j]);
        }
            fclose (fp);
    }
}
