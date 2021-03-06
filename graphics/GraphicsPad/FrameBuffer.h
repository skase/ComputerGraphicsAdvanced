#pragma once
#include "GL\glew.h"
#include "TextureManager.h"

class FrameBuffer {
protected:
	void init_ColorTexture(GLsizei width, GLsizei height, bool comparison);
	void init_DepthTexture(GLsizei width, GLsizei height, bool comparison);
	void init_DepthTexture(GLsizei width, GLsizei height, bool comparison,GLint TexUnitID);
	void init_SelectionColorTexture();
	void init_DepthTexture_3D(GLsizei width, GLsizei height,bool comparison);
	void init_DepthTexture_3D(GLsizei width, GLsizei height, bool comparison, GLint TexUnitID);
	void Delete_ColorTex();
	void Delete_DepthTex_3D();
	void Delete_DepthTex();

	static std::vector<GLint> FreeTexUnit;

public:
	GLuint id;
	Texture* ColorTexture;
	Texture* DepthTexture;
	Texture3D* DepthTexture_3D;
	static GLint count;

	FrameBuffer() :
		id(0), ColorTexture(nullptr), DepthTexture(nullptr),DepthTexture_3D(nullptr) {}
	~FrameBuffer()
	{
		if (ColorTexture)
			Delete_ColorTex();
		if (DepthTexture)
			Delete_DepthTex();
		if (DepthTexture_3D)
			Delete_DepthTex_3D();
		/*glDeleteFramebuffers(1, &id);
		id = 0;*/
	}

	void init(GLsizei width, GLsizei height);
	void SelectionInit();
	void PointLight_Shadow_Init(GLsizei width, GLsizei height);
	void DirectLight_Shadow_Init(GLsizei width, GLsizei height);
	void PointLight_Shadow_Change(GLsizei width, GLsizei height, GLint TexUnitId);
	void DirectLight_Shadow_Change(GLsizei width, GLsizei height, GLint TexUnitId);

	static GLint fetchValidTexUnit();
	static GLint getEmptyTexUnit();

	void UpdateTexSize(GLsizei width, GLsizei height);
	
};
