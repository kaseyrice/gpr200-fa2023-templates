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

const int NUM_SPRITES = 12;

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

	//Shaders (Kasey and Laura).
	kr::Shader shader("assets/vertexShader.vert", "assets/fragmentShader.frag");
	ew::Shader characterShader("assets/characterShader.vert", "assets/characterShader.frag");

	unsigned int vao = createVAO(vertices, 4, indices, 4);

	//Array containing all of the sprites (Laura).
	unsigned int frames[NUM_SPRITES]{
	loadTexture("assets/Char1_Sprites/7.png"),
	loadTexture("assets/Char1_Sprites/8.png"),
	loadTexture("assets/Char1_Sprites/9.png"),
	loadTexture("assets/Char1_Sprites/1.png"),
	loadTexture("assets/Char1_Sprites/2.png"),
	loadTexture("assets/Char1_Sprites/3.png"),
	loadTexture("assets/Char1_Sprites/4.png"),
	loadTexture("assets/Char1_Sprites/5.png"),
	loadTexture("assets/Char1_Sprites/6.png"),
	loadTexture("assets/Char1_Sprites/10.png"),
	loadTexture("assets/Char1_Sprites/11.png"),
	loadTexture("assets/Char1_Sprites/12.png")
	};

	glEnable(GL_BLEND);
	
	//Variables for the sprites, frame speed, and direction (Kasey).
	int frame = 0;
	float frameLimit = 5.0f;
	int direction = 1;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(vao);
		iTime = glfwGetTime();
		
		//Reset the sprite animation (Kasey).
		if (frame > (frameLimit * 4))
		{
			frame = 0;
		}

		//Set uniforms (Laura).
		characterShader.use();
		characterShader.setInt("_char1[0]", 0);
		characterShader.setInt("_char1[1]", 1);
		characterShader.setInt("_char1[2]", 2);
		characterShader.setInt("_char2_3", 5);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Series of if statements that determine which sprite to use depending on the frame (Kasey).
		if (frame <= frameLimit)
		{
			//Series of if statements that determine which sprite to use depending on the direction.
			if (direction == 1)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[0]);
			}
			else if (direction == 2)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[3]);
			}
			else if (direction == 3)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[6]);
			}
			else if (direction == 4)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[9]);
			}
		}
		else if (frame <= (frameLimit * 2))
		{
			if (direction == 1)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[1]);
			}
			else if (direction == 2)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[4]);
			}
			else if (direction == 3)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[7]);
			}
			else if (direction == 4)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[10]);
			}
		}
		else if (frame <= (frameLimit * 3))
		{
			if (direction == 1)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[2]);
			}
			else if (direction == 2)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[5]);
			}
			else if (direction == 3)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[8]);
			}
			else if (direction == 4)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[11]);
			}
		}
		else if (frame <= (frameLimit * 4))
		{
			if (direction == 1)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[1]);
			}
			else if (direction == 2)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[4]);
			}
			else if (direction == 3)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[7]);
			}
			else if (direction == 4)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frames[10]);
			}
		}
		

		//Draw using indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		//Render UI
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");
			ImGui::Checkbox("Show Demo Window", &showImGUIDemoWindow);
			ImGui::End();
			if (showImGUIDemoWindow) {
				ImGui::ShowDemoWindow(&showImGUIDemoWindow);
			}
			//ImGui controls for the animation speed and sprite direction (Kasey).
			ImGui::Begin("Sprite Animation Settings");
			ImGui::SliderFloat("Speed", &frameLimit, 0.0f, 10.0f);
			ImGui::SliderInt("Direction", &direction, 0.0f, 4.0f);
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

