#pragma once
#pragma once
#include<Windows.h>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include"FreeImage.h"
#include"Imagx.h"
#include"glm.h"
class ObjectLoader{
public:
	ObjectLoader(){}
	/*
	�u��Τ@�i�K��
	objpath : ������|�W��
	texpath : �K�ϸ��|�W�١A���ݶK�϶�NULL
	unit_flag : �O�_�}��glmUnitize()�\��
	mode : GLM_...��render�Ѽƿﶵ
	textrue,smooth,material...
	*/
	ObjectLoader(char* objpath,char* texpath,GLboolean unit_flag,GLuint mode){
		genIndex(1);
		//GL_FALSE menas load image as only a textrue
		if(texpath!=NULL){
			Imagx texImg = Imagx(texpath,1,GL_FALSE);
			texIndex = texImg.getTexIndex();
		}
		model = myReadOBJ(objpath,unit_flag);
		compileDisplayList(dpIndex,mode);
		glmDelete(model);
	}
	~ObjectLoader(){}

	void drawObj(GLuint index){
		if(model){
			glCallList(index);
		}
		else{
			printf("model is null\n");
		}
	}

	void progress(){
	
	}

	GLuint getDpIndex(){return dpIndex;}
	GLuint getTexIndex(){return texIndex;}
	/*GLuint getDpNum(){return dp_num;}*/

private:
	GLMmodel* model;
	GLuint dpIndex=0;
	GLuint texIndex=0;
	/*GLuint dp_num=0;*/

	/*
	gen texture and display indeics;
	*/
	void genIndex(GLsizei di){
		dpIndex = glGenLists(di);
	}

	/*
	compile one loaded object
	*/
	void compileDisplayList(GLuint index,GLuint mode){
		if(index){
			glNewList(index,GL_COMPILE);
			{
				glEnable(GL_TEXTURE_2D);
				glPushMatrix();
				{

					if(GLM_TEXTURE)glBindTexture(GL_TEXTURE_2D, texIndex);
					glmDraw(model,mode);
				}
				glPopMatrix();
				glDisable(GL_TEXTURE_2D);
			}
			glEndList();
		}
		else{
			printf("compileDisplayList: dpIndex is 0\n");
		}
	}
};