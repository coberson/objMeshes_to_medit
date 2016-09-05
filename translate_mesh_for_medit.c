//
//  translate_mesh_for_medit.c
//  
//
//  Created by Chantal Oberson Ausoni on 15/09/2015.
//
// translate *.obj meshes in *.mesh form for visualization with medit
//
// example: ./a.out spot/spot_triangulated.obj
// output: spot_triangulated.mesh

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE* meshtt; // the mesh to translate
    FILE* fmesh;
    FILE* fsol;
    char *filename;
    char *suff;
    char *newname;
    char *pch;
    char c;
    char line[80];
    int nv=0;
    int nf=0;
    int t1,t2,t3,t4,t5,t6;
    float x,y,z;
    int yes;
    
    
    if (argc<2)
    {
        printf("File name awaited");
        exit(EXIT_FAILURE);
    }
    
    filename=argv[1];
    
    meshtt=fopen(filename,"r");
    
    while(fgets(line, 80, meshtt) != NULL)
    {
        if (line[0]=='v'&& line[1]!='t') nv = nv+1;
        if (line[0]=='f') nf = nf+1;
        /* get a line, up to 80 chars from fr.  done if NULL */
        //sscanf (line, "%ld", &elapsed_seconds);
        /* convert the string to a long int */
        //printf ("%ld\n", elapsed_seconds);
    }
    
    printf("Read file %s, %d vertices %d faces\n",filename,nv,nf);
    
    pch = strtok (filename,".");
    suff = pch;
    
    newname=strcat(suff,".mesh");
    fmesh=fopen(newname,"w");
    printf("Creation of file %s\n",filename);
    //newname=strcat(suff,".sol");
    //fsol=fopen(newname,"w");
    //printf("Creation of file %s\n",filename);
    
    
    fprintf (fmesh,"MeshVersionFormatted 2\n Dimension\n\t3\n Vertices\n\t%d\n", nv);
    //fprintf (fsol,"MeshVersionFormatted 2\n Dimension\n\t3\n SolAtVertices\n\t%d\n 1 1\n", nv);
    
    fseek ( meshtt , 0 , SEEK_SET );
    while(fgets(line, 80, meshtt) != NULL)
    {
        if (line[0]=='v' && line[1]!='t')
        {
          sscanf (line, "%c %f %f %f", &c,&x,&y,&z);
          //printf("%f %f %f 1\n", x,y,z);
          fprintf (fmesh,"%f %f %f 1\n", x,y,z);
            
        }
        if (line[0]=='f')
        {
            fprintf (fmesh,"Triangles\n\t%d\n",nf);
            pch=strchr(line,'/');
            if (pch==NULL)
            {
                sscanf (line, "%c %d %d %d", &c,&t1,&t3,&t5);
            }
            else
            {
                sscanf (line, "%c %d/%d %d/%d %d/%d", &c,&t1,&t2,&t3,&t4,&t5,&t6);
            }
            //printf ("%d %d %d 1\n", t1,t3,t5);
            fprintf (fmesh,"%d %d %d 1\n", t1,t3,t5);
            while(fgets(line, 80, meshtt) != NULL)
            {
                pch=strchr(line,'/');
                if (pch==NULL)
                {
                    sscanf (line, "%c %d %d %d", &c,&t1,&t3,&t5);
                }
                else
                {
                    sscanf (line, "%c %d/%d %d/%d %d/%d", &c,&t1,&t2,&t3,&t4,&t5,&t6);
                }
                //printf ("%d %d %d 1\n", t1,t3,t5);
                fprintf (fmesh,"%d %d %d 1\n", t1,t3,t5);
            }
        }
    }

}