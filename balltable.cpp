#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "balltable.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//ball tables

GLint calc_ind2(GLint b, GLint c, GLint resol_size) {
    return ((c*(2*resol_size+3-c))/2)+b;
}

/*
 * 根据三角形A(ax,ay,az)，B(bx,by,bz)，C(cx,cy,cz)三点坐标及
 * 分辨率获取所有像素点坐标
 */
void Triangle(GLfloat ax, GLfloat ay, GLfloat az,
		GLfloat bx, GLfloat by, GLfloat bz,
		GLfloat cx, GLfloat cy, GLfloat cz,
        GLint resol_size, GLint &iv, GLint &ii, GLint &it,
		GLfloat *vertices,GLint *indices,GLfloat *texcoord) {

	GLint c=0,b=0;
	GLfloat orient=99;
	GLint ivstart=iv/3;

    for (c=0;c<=resol_size;c++) {
        for (b=0;b<=resol_size-c;b++) {
            //获取三角形三边按分辨率等分点的坐标
            GLfloat temp_x=ax+((b+0.0)/(resol_size+0.0))*(bx-ax)+((c+0.0)/(resol_size+0.0))*(cx-ax);
            GLfloat temp_y=ay+((b+0.0)/(resol_size+0.0))*(by-ay)+((c+0.0)/(resol_size+0.0))*(cy-ay);
            GLfloat temp_z=az+((b+0.0)/(resol_size+0.0))*(bz-az)+((c+0.0)/(resol_size+0.0))*(cz-az);


            GLfloat distance=sqrt(temp_x*temp_x+temp_y*temp_y+temp_z*temp_z);
            temp_x=temp_x/distance;
            temp_y=temp_y/distance;
            temp_z=temp_z/distance;

            //顶点数组
			vertices[iv++]=temp_x; 
			vertices[iv++]=temp_y; 
			vertices[iv++]=temp_z; 

            GLfloat angle=atan(temp_x/temp_y)/M_PI;
            if (temp_x==0 && temp_y==0) angle=orient;
            if (!angle) angle=0;
            if (temp_y<0) angle+=1;
            else if (temp_x<0) angle+=2;
			if (orient!=99) {
                while (angle<orient-0.5) {angle+=1;}
                while (angle>orient+0.5) {angle-=1;}
			}
            orient=angle;

            //纹理坐标
            texcoord[it++]=angle;
			texcoord[it++]=acos(temp_z)/M_PI-1;
		}
	}

    for (c=0;c<resol_size;c++) {
        for (b=0;b<resol_size-c;b++) {
			if (c!=0) {
                indices[ii++]=ivstart+calc_ind2(b,c,resol_size);
                indices[ii++]=ivstart+calc_ind2(b+1,c-1,resol_size);
                indices[ii++]=ivstart+calc_ind2(b+1,c,resol_size);
			}
            indices[ii++]=ivstart+calc_ind2(b,c,resol_size);
            indices[ii++]=ivstart+calc_ind2(b+1,c,resol_size);
            indices[ii++]=ivstart+calc_ind2(b,c+1,resol_size);
		}
	}
}

/*
 * init Ball vertex data
 *
 */
void initializeBallTables(GLint resol_size) {

    if (resol_size<1) resol_size=1;  //Display resolution
    if (resol_size>29) resol_size=29;

	/*
	   GLfloat a=atan(1/1)/M_PI;
	   GLfloat b=atan(-1/1)/M_PI;
	   GLfloat c=atan(-1/-1)/M_PI;
	   GLfloat d=atan(1/-1)/M_PI;
	   printf("%f %f %f %f\n",a,b,c,d);
	   */

    GLfloat a=sqrt(0.8);       // 0.8944271
    GLfloat b=sqrt(0.2);       // 0.4472136
    GLfloat c=a*sin(0.4*M_PI); // 0.8506508
    GLfloat d=a*cos(0.4*M_PI); // 0.2763932
    GLfloat e=a*sin(0.8*M_PI); // 0.5257311
    GLfloat f=a*cos(0.8*M_PI); // 0.7236068

    for (GLint A=1;A<=resol_size;A+=2) {

        if (!ball_vertices[A]) {
			//printf("%i ",A);fflush(stdout);
			ball_vertices[A] = (GLfloat*) malloc (20*3*(A+1)*(A+2)*sizeof(GLfloat)/2);
			ball_indices[A] = (GLint*) malloc (20*3*A*A*sizeof(GLint));
			ball_texcoord[A] = (GLfloat*) malloc (20*(A+1)*(A+2)*sizeof(GLfloat));

			GLint iv=0,ii=0,it=0;

            Triangle(a,0,b,d,c,b,0,0,1,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//1
            Triangle(d,c,b,f,e,b,0,0,1,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//2
            Triangle(f,e,b,f,-e,b,0,0,1,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//3
            Triangle(f,-e,b,d,-c,b,0,0,1,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//4
            Triangle(d,-c,b,a,0,b,0,0,1,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//5

            Triangle(-f,-e,-b,-f,e,-b,a,0,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//6
            Triangle(a,0,b,-f,e,-b,d,c,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//7
            Triangle(-f,e,-b,-d,c,-b,d,c,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//8
            Triangle(d,c,b,-d,c,-b,f,e,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//9
            Triangle(-d,c,-b,-a,0,-b,f,e,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//10
            Triangle(f,e,b,-a,0,-b,f,-e,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//11
            Triangle(-a,0,-b,-d,-c,-b,f,-e,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//12
            Triangle(f,-e,b,-d,-c,-b,d,-c,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//13
            Triangle(-d,-c,-b,-f,-e,-b,d,-c,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//14
            Triangle(d,-c,b,-f,-e,-b,a,0,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//15

            Triangle(-f,e,-b,0,0,-1,-d,c,-b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//16
            Triangle(-d,c,-b,0,0,-1,-a,0,-b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//17
            Triangle(-a,0,-b,0,0,-1,-d,-c,-b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//18
            Triangle(-d,-c,-b,0,0,-1,-f,-e,-b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//19
            Triangle(-f,-e,-b,0,0,-1,-f,e,-b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//20

			GLint gespart=0;

			for (GLint test=0;test<ii;test++) {
				for (GLint vergleich=0;vergleich<test;vergleich++) {
					if (ball_vertices[A][3*ball_indices[A][test]+0]==ball_vertices[A][3*ball_indices[A][vergleich]+0] &&
							ball_vertices[A][3*ball_indices[A][test]+1]==ball_vertices[A][3*ball_indices[A][vergleich]+1] &&
							ball_vertices[A][3*ball_indices[A][test]+2]==ball_vertices[A][3*ball_indices[A][vergleich]+2]) {
						if (ball_texcoord[A][2*ball_indices[A][test]+0]==ball_texcoord[A][2*ball_indices[A][vergleich]+0] &&
								ball_texcoord[A][2*ball_indices[A][test]+1]==ball_texcoord[A][2*ball_indices[A][vergleich]+1]) {
							ball_indices[A][test]=ball_indices[A][vergleich];
							gespart++;
							break;
						} else {
							/*
							   printf("%f %f\n%f %f\n%f %f\n%f %f\n%f %f\n\n",
							   ball_vertices[A][3*ball_indices[A][test]+0],ball_vertices[A][3*ball_indices[A][vergleich]+0],
							   ball_vertices[A][3*ball_indices[A][test]+1],ball_vertices[A][3*ball_indices[A][vergleich]+1],
							   ball_vertices[A][3*ball_indices[A][test]+2],ball_vertices[A][3*ball_indices[A][vergleich]+2],
							   ball_texcoord[A][2*ball_indices[A][test]+0],ball_texcoord[A][2*ball_indices[A][vergleich]+0],
							   ball_texcoord[A][2*ball_indices[A][test]+1],ball_texcoord[A][2*ball_indices[A][vergleich]+1]);
							   */
						}
					}
				}
			}
			//printf("gespart: %i\n",gespart);
		}
	}
}
