#include "terrain.h"
/* Generated by CDV */
#ifdef _MSC_VER
#include <wtypes.h>
#include <winbase.h>
#include <windef.h>
#include <wingdi.h>
#endif
#include<stdio.h>
#include<GL/gl.h>

GLuint loadtga ( const char* filename );
GLfloat GLfloatData[4];
GLdouble GLdoubleData[4];
GLuint GLtexture[2];

GLuint loadtgadisplayCDV ( const char* filename )
{
    FILE* fp;
    char magic[12];
    unsigned char header[6];
    int imageSize;
    GLenum type;
    char temp;
    int i;
    int bpp,width,height;
    GLint textureId;
    int globalWidth = 1;
    int globalHeight = 1;
    char* imageData;
    char* imageTmp;
    if(!(fp = fopen(filename, "rb"))) return 0;
    if(!fread(&magic, 12, 1, fp)) return 0;
    if(!fread(&header, 6, 1, fp)) return 0;
    bpp = header[4];
    width  = header[1] * 256 + header[0];
    height = header[3] * 256 + header[2];
    if(width <= 0 || height <= 0) return 0;
    if(bpp != 24 && bpp != 32) return 0;
    imageSize = width * height * (bpp / 8);
    imageData = (char *)malloc(sizeof(char) * imageSize);
    if(imageData == NULL) return 0;
    if(!fread(imageData, imageSize, 1, fp)) { free(imageData); return 0; }
    for(i = 0; i < imageSize; i += bpp / 8) {
    temp = imageData[i];
    imageData[i] = imageData[i + 2];
    imageData[i + 2] = temp; }
    if(bpp == 32) for(i=0;i<imageSize;i+=4) imageData[i+3]=255-imageData[i+3];
    fclose(fp);
    while (width>globalWidth) globalWidth*=2;
    while (height>globalHeight) globalHeight*=2;
    glEnable( GL_TEXTURE_2D );
    //glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ROW_LENGTH,globalWidth);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    if(bpp == 24) type=GL_RGB; else type=GL_RGBA;
    imageTmp = (char *)malloc(sizeof(char)*globalWidth*globalHeight*4);
    if (imageTmp==NULL) return 0;
    glTexImage2D(GL_TEXTURE_2D,0,type,globalWidth,globalHeight,0,
    type,GL_UNSIGNED_BYTE,imageTmp);
    free (imageTmp );
    glPixelStorei(GL_UNPACK_ROW_LENGTH,width);
    glTexSubImage2D(GL_TEXTURE_2D,0, 0,0, width, height,
    type ,GL_UNSIGNED_BYTE, imageData );
    free(imageData);
    return textureId;
}

void displayCDVTextures( void )
{
    GLtexture[0]= loadtgadisplayCDV( "textures\\herbe.tga");
    GLtexture[1]= loadtgadisplayCDV( "textures\\filet.tga");
}

void displayCDVDisplayList( void )
{
}

void displayCDV( void )
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glEnable ( GL_NORMALIZE );
    glDepthMask ( GL_TRUE );
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
    glPointSize ( 1.0f );
    glLineWidth ( 1.0f );
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix ();
    glColor3f(1,1,1);
    glEnable( GL_TEXTURE_2D );
    /* BIND TEXTURE */
    glBindTexture(GL_TEXTURE_2D, GLtexture[0]);
    glBegin(GL_QUADS);
    glTexCoord2f (100,0);
    glVertex3f(10,-10,0);
    glTexCoord2f (100,100);
    glVertex3f(10,10,0);
    glTexCoord2f (0,100);
    glVertex3f(-10,10,0);
    glTexCoord2f (0,0);
    glVertex3f(-10,-10,0);
    glEnd();
    glDisable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    glDepthMask (GL_FALSE);
    glEnable( GL_TEXTURE_2D );
    glColor4f(1,1,1,0.4);
    /* BIND TEXTURE */
    glBindTexture(GL_TEXTURE_2D, GLtexture[1]);
    glBegin(GL_QUADS);
    glTexCoord2f (0,0);
    glVertex3f(-0.7,-0.7,0.1);
    glTexCoord2f (1,0);
    glVertex3f(-0.7,1.5,0.1);
    glTexCoord2f (1,1);
    glVertex3f(-0.7,1.5,0.5);
    glTexCoord2f (0,1);
    glVertex3f(-0.7,-0.7,0.5);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f (0,0);
    glVertex3f(-0.7,1.5,0.1);
    glTexCoord2f (1,0);
    glVertex3f(0.7,1.5,0.1);
    glTexCoord2f (1,1);
    glVertex3f(0.7,1.5,0.5);
    glTexCoord2f (0,1);
    glVertex3f(-0.7,1.5,0.5);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f (0,0);
    glVertex3f(0.7,1.5,0.1);
    glTexCoord2f (1,0);
    glVertex3f(0.7,-0.7,0.1);
    glTexCoord2f (1,1);
    glVertex3f(0.7,-0.7,0.5);
    glTexCoord2f (0,1);
    glVertex3f(0.7,1.5,0.5);
    glEnd();
    glDisable( GL_TEXTURE_2D );
    glDepthMask (GL_TRUE);
    glDisable( GL_BLEND );
    glPopMatrix ();
}
terrain::terrain()
{


}
