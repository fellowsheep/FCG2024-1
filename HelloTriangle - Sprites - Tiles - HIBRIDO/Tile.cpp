#include "Tile.h"

void Tile::inicializar(GLuint texID, int nRows, int nCols, glm::vec3 pos, glm::vec3 escala, float angulo, glm::vec3 cor)
{
    this->pos = pos;
    this->escala.x = escala.x / (float) nFrames;
	this->escala.y = escala.y / (float) nAnimations;
    this->angulo = angulo;
	this->texID = texID;
	this->nRows = nRows;
	this->nCols = nCols;

    nAnimations = 1;
    nFrames = 1;

	offsetTex.s = 1.0/ (float) nCols;
	offsetTex.t = 1.0/ (float) nRows; 
	cor.r = 1.0;
	cor.g = 0.0;
	cor.b = 1.0;
    //Especificação da geometria da sprite (quadrado, 2 triangulos)

    float th = 1.0;
    float tw = 2.0;

    glm::vec3 A, B, C, D;
    A = glm::vec3(-tw/2.0, 0.0,0.0);
    B = glm::vec3(0.0, th/2.0, 0.0);
    C = glm::vec3(tw/2.0, 0.0,0.0);
    D = glm::vec3(0.0, -th/2.0,0.0);


    GLfloat vertices[] = {
		//x   y    z    r      g      b      s    t
		A.x, A.y, A.z, cor.r, cor.g, cor.b, 0.0, 0.5,
        B.x, B.y, B.z, cor.r, cor.g, cor.b, 0.5, 1.0,
        D.x, D.y, D.z, cor.r, cor.g, cor.b, 0.5, 0.0,
        B.x, B.y, B.z, cor.r, cor.g, cor.b, 0.5, 1.0,
        C.x, C.y, C.z, cor.r, cor.g, cor.b, 1.0, 0.5,
        D.x, D.y, D.z, cor.r, cor.g, cor.b, 0.5, 0.0
	};

	GLuint VBO;
	//Gera��o do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conex�o (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Gera��o do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de v�rtices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localiza��o no shader * (a localiza��o dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se est� normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo layout 0 - Posição - 3 valores dos 8 que descrevem o vértice
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo layout 1 - Cor - 3 valores dos 8 que descrevem o vértice
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Atributo layout 2 - Coordenada de textura - 2 valores dos 8 que descrevem o vértice
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6* sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// Observe que isso � permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de v�rtice 
	// atualmente vinculado - para que depois possamos desvincular com seguran�a
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	vel = 2.0;

	iAnimation = 0;
	iFrame = 0;

	getAABB();

	colidiu = false;
}

void Tile::atualizar()
{
	shader->Use();
	
	//Calculando o quanto teremos que deslocar nas coordenadas de textura
	float offsetTexFrameS = 0.0; 
	float offsetTexFrameT = 0.0; 
	shader->setVec2("offsetTex",offsetTexFrameS,offsetTexFrameT);

    glm::mat4 model = glm::mat4(1); //matriz identidade
    model = glm::translate(model, pos);
	model = glm::rotate(model,glm::radians(angulo), glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, escala);
    shader->setMat4("model", glm::value_ptr(model));

	shaderDebug->Use();
	shaderDebug->setVec2("offsetTex",offsetTexFrameS,offsetTexFrameT);
	shaderDebug->setMat4("model", glm::value_ptr(model));

}

void Tile::desenhar()
{
    Tile::atualizar();

	shader->Use();
	glBindTexture(GL_TEXTURE_2D, texID); //Conectando com a textura


    glBindVertexArray(VAO); //Conectando ao buffer de geometria

	// Poligono Preenchido - GL_TRIANGLES
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, 0);

	shaderDebug->Use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 6);

    glBindVertexArray(0); //desconectando o buffer de geometria

}