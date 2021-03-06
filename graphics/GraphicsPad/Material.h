#pragma once
#include <ShaderCompiler.h>
#include <Camera.h>
#include <glm\gtc\matrix_transform.hpp>
#include "cyTriMesh.h"
#include <TextureManager.h>

class Transform;
class Light;
class Mesh;


class Material : public File
{
protected:
	//std::string name;
	float Ka[3];	//!< Ambient color
	float Kd[3];	//!< Diffuse color
	float Ks[3];	//!< Specular color
	float Tf[3];	//!< Transmission color
	float Ns;		//!< Specular exponent
	float Ni;		//!< Index of refraction
	int   illum;	//!< Illumination model
	Texture*  map_Ka;	//!< Ambient color texture map
	Texture*  map_Kd;	//!< Diffuse color texture map
	Texture*  map_Ks;	//!< Specular color texture map
	Texture*  map_Ns;	//!< Specular exponent texture map
	Texture*  map_d;	//!< Alpha texture map
	Texture*  map_bump;	//!< Bump texture map
	Texture*  map_disp;	//!< Displacement texture map

	Texture* newmap;	//just for implement the mirror conveniently for now. I will add customized properties to material later.

	Mesh* mesh;

	std::string   PathName;

	std::vector<Pass*> PassArray;

	void _PutInScene(QMouseEvent* e);
	void _PutInObjProperties(QMouseEvent* e);
	void _DisplayProperties();
	
public:
	Material(std::string Materialname = "Material", char* Vshaderfilename = "Default\\ShaderFile\\DefaultVertexShader.glsl", char* Fshaderfilename = "Default\\ShaderFile\\DefaultFragmentShader.glsl");
	Material(Mesh * M, cyTriMesh::Mtl & mat, char* path_name);
	Material(const Material& mat);

	friend class MatPropertiesWidget;

	~Material();
	void ExecuteEveryPass(int firstface, int facecount,Transform* transform, Object* cam,Light* light);
	void ReCompileShaders();
	void set_PathName(std::string path_name) { PathName = path_name; }
	void set_Ka(float a, float b, float c) { Ka[0] = a; Ka[1] = b; Ka[2] = c;}
	void set_Kd(float a, float b, float c) { Kd[0] = a; Kd[1] = b; Kd[2] = c;}
	void set_Ks(float a, float b, float c) { Ks[0] = a; Ks[1] = b; Ks[2] = c; }
	void set_Ns(float a) { Ns = a; }
	void BindMesh(Mesh* msh) { mesh = msh; }
	Mesh* getMesh() const { return mesh; }
	std::string	getName() const { return filename; }
	void BindDiffuseMap(Texture* tex) { map_Kd = tex; }
	void BindAmbientMap(Texture* tex) { map_Ka = tex; }
	void BindSpecularMap(Texture* tex) { map_Ks = tex; }
	void setAmbientFactor(glm::vec3 value) { Ka[0] = value.x; Ka[1] = value.y;Ka[2] = value.z;}
	
//	Texture* get_map_Kd() const { return map_Kd; }

	glm::mat4 MirrorCamMatrix;   //just for implement the mirror conveniently for now. I will add customized properties to material later.
	void Bind_newmap_FBOTexUnit(Texture * tex);

	static glm::vec3 AmbientColor;

private:
	void Add_Zihao_MVP(Pass* pass, Transform* transform,Object* cam,Light* light);
	void Add_Light_Uniform(Pass* pass,Light* light);
	void Add_Default_Parameter(Pass* pass);
	void BindTex_Shader(GLint UniformLocation, int& Tex_Unit_number,Texture* map);
	void FeedShader_tex(GLint UniformLocation, int& Tex_Unit_number, Texture* map, Texture* DefaultTex);
	void _ReleaseTex(Texture* tex);
};

