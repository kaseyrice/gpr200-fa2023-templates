#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <ew/ewMath/transformations.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <kr/shader.h>
#include <ew/shader.h>
#include <kr/texture.h>
#include <kr/camera.h>

const int NUM_SPRITES = 3;

struct Vertex {
	float x, y, z;
	float u, v;
};

unsigned int createShader(GLenum shaderType, const char* sourceCode);
unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
unsigned int createVAO(Vertex* vertexData, int numVertices, unsigned int* indicesData, int numIndices);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
float iTime;

ew::Mat4 projection = ew::Orthographic(0.0f, SCREEN_HEIGHT/SCREEN_WIDTH,-1.0f,1.0f);

Vertex vertices[12] = {
	//x   //y  //z   //u  //v
	{-0.5, -0.5, 0.0, 0.0, 0.0}, //Bottom left
	{0.5, -0.5, 0.0, 1.0, 0.0}, //Bottom right
	{0.5,  0.5, 0.0, 1.0, 1.0}, //Top right
	{-0.5, 0.5, 0.0, 0.0, 1.0} //Top left
};

unsigned int indices[6] = {
	0, 1, 2,
	0, 2, 3
};

float triangleColor[3] = { 1.0f, 0.5f, 0.0f };
float triangleBrightness = 1.0f;
bool showImGUIDemoWindow = true;

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	//Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	kr::Shader shader("assets/vertexShader.vert", "assets/fragmentShader.frag");
	ew::Shader characterShader("assets/characterShader.vert", "assets/characterShader.frag");

	unsigned int vao = createVAO(vertices, 4, indices, 4);

	unsigned int frames[NUM_SPRITES]{
	loadTexture("assets/Char1_Sprites/7.png"),
	loadTexture("assets/Char1_Sprites/8.png"),
	loadTexture("assets/Char1_Sprites/9.png")
	};

	unsigned int char2_1 = loadTexture("assets/Char2_Sprites/7.png");
	unsigned int char2_2 = loadTexture("assets/Char2_Sprites/8.png");
	unsigned int char2_3 = loadTexture("assets/Char2_Sprites/9.png");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	int frame = 0;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(vao);
		iTime = glfwGetTime();

		if (frame >= 3)
		{
			frame = 0;
		}

		//Set uniforms
		shader.use();
		shader.setVec3("_Color", triangleColor[0], triangleColor[1], triangleColor[2]);
		shader.setFloat("_Brightness", triangleBrightness);
		shader.setFloat("iTime", iTime);
		
		characterShader.use();

		//bindCharacterTextures();
		/*
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, frames[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, frames[1]);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, frames[2]);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, char2_1);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, char2_2);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, char2_3);
		*/

		//setCharacterShaderUniforms()
		characterShader.setInt("_char1[0]", 0);
		characterShader.setInt("_char2_1", 3);
		characterShader.setInt("_char1[1]", 1);
		characterShader.setInt("_char2_2", 4);
		characterShader.setInt("_char1[2]", 2);
		characterShader.setInt("_char2_3", 5);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, frames[frame]);

		//Draw using indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		//Render UI
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");
			/*
			for (int i = 0; i < NUM_SPRITES; i++)
			{
				ImGui::PushID(i);
				characterShader.setInt("_char1[" + std::to_string(i) + "]", frames[i]);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[i]);
				ImGui::PopID();
			}
			*/
			ImGui::Checkbox("Show Demo Window", &showImGUIDemoWindow);
			ImGui::ColorEdit3("Color", triangleColor);
			ImGui::SliderFloat("Brightness", &triangleBrightness, 0.0f, 1.0f);
			ImGui::End();
			if (showImGUIDemoWindow) {
				ImGui::ShowDemoWindow(&showImGUIDemoWindow);
			}

			ImGui::Begin("Uniform Variable Settings");
			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
		frame++;
		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}

unsigned int createVAO(Vertex* vertexData, int numVertices, unsigned int* indicesData, int numIndices) {
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Define a new buffer id
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//Allocate space for + send vertex data to GPU.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices * 3, vertexData, GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex,x));
	glEnableVertexAttribArray(0);

	//UV
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, u)));
	glEnableVertexAttribArray(1);

	//Element Buffer Object (ebo)
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vertex) * numIndices, indicesData, GL_STATIC_DRAW);

	return vao;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

