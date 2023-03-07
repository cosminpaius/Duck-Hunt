#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */



Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

bool inside(float xs, float ys, int length, int width, int xp, int yp) {
    if (xp <= xs + length && xp >= xs && yp >= ys && yp <= ys + width)
        return true;
    return false;
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    //scoate cursorul
    window->HidePointer();
    contor = 0;

    // pozitia de start
    //srand(time(NULL));
    randomX = rand() % 1280; //1280 720
    randomY = rand() % 300;

    if (randomX < 640) {
        angleR = (rand() % 110) / (float)100 + M_PI / 10;
    }
    else {
        angleR = (rand() % 110) / (float)100 + 6 * M_PI/10;
    }
    

    // Initialize tx and ty (the translation steps)
    translateX = 1;
    translateY = 1;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

{
    Mesh* redcircle1 = object2D::CreateCircle("redcircle1", top, glm::vec3(0.8f, 0.004f, 0.005f), 20, true);
    AddMeshToList(redcircle1);

    Mesh* redcircle2 = object2D::CreateCircle("redcircle2", top, glm::vec3(0.8f, 0.004f, 0.005f), 20, true);
    AddMeshToList(redcircle2);

    Mesh* redcircle3 = object2D::CreateCircle("redcircle3", top, glm::vec3(0.8f, 0.004f, 0.005f), 20, true);
    AddMeshToList(redcircle3);
}

{
    Mesh* head = object2D::CreateCircle("head", top, glm::vec3(0.008f, 0.250f, 0.008f), 30, true);
    AddMeshToList(head);
    
    bodyTr = object2D::CreateTriangle("bodyTr", top, length, glm::vec3(r, g, b), true);
    AddMeshToList(bodyTr);

    length = 75;
    wing1 = object2D::CreateTriangle("wing1", top, length, glm::vec3(r, g, b), true);
    AddMeshToList(wing1);

    wing2 = object2D::CreateTriangle("wing2", top, length, glm::vec3(r, g, b), true);
    AddMeshToList(wing2);

    length = 35;
    Mesh* beak = object2D::CreateTriangle("beak", top, length, glm::vec3(1, 1.f, 0.2f), true);
    AddMeshToList(beak);
}

    length = 2500;
    Mesh* grass = object2D::CreateRectangle("grass", top, length, width, glm::vec3(0.29f, 0.765f, 0.322f), true);
    AddMeshToList(grass);

{
    length = 50, width = 25;
    Mesh* bullet1 = object2D::CreateRectangle("bullet1", top, length, width, glm::vec3(0.3f, 0.3f, 0.3f), true);
    AddMeshToList(bullet1);

    Mesh* bullet2 = object2D::CreateRectangle("bullet2", top, length, width, glm::vec3(0.3f, 0.3f, 0.3f), true);
    AddMeshToList(bullet2);

    Mesh* bullet3 = object2D::CreateRectangle("bullet3", top, length, width, glm::vec3(0.3f, 0.3f, 0.3f), true);
    AddMeshToList(bullet3);
}

{
    length = 215, width = 180;
    Mesh* birdframe = object2D::CreateRectangle("birdframe", top, length, width, glm::vec3(1.f, 1.f, 1.f), false);
    AddMeshToList(birdframe);
}

{
    length = 40, width = 10;
    Mesh* cursor1 = object2D::CreateRectangle("cursor1", top, length, width, glm::vec3(1.f, 0.f, 0.f), true);
    AddMeshToList(cursor1);

    length = 40, width = 10;
    Mesh* cursor2 = object2D::CreateRectangle("cursor2", top, length, width, glm::vec3(1.f, 0.f, 0.f), true);
    AddMeshToList(cursor2);
}
    length = 150, width = 40;
    Mesh* wireframe = object2D::CreateRectangle("wireframe", top, length, width, glm::vec3(1.f, 1.f, 1.f), false);
    AddMeshToList(wireframe);
    
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.529f, 0.808f, 0.99f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    //srand((unsigned int)time(NULL));
    translateX += deltaTimeSeconds * cos(angleR) * (currLevel + 30) * 5*x;
    translateY += deltaTimeSeconds * sin(angleR) * (currLevel + 30) * 5*x;

    if (currLevel == -30) {
        l1x = l2x = l3x = 10000;
        b1x = b2x = b3x = 10000;
        angleR = 0;
        currLevel = -30;
        translateX = translateY = 0;
        randomX = 640;
        randomY = 400;
    }

    if (translateX + randomX > 1230) {
        // corner case coliziune perete
        translateX = -randomX + 1180;
        angleR = M_PI - angleR;
        contor++;
    }
    else if (translateX + randomX < 25) {
        // corner case coliziune perete
        translateX = -randomX + 25;
        angleR = M_PI - angleR;
        contor++;
    }
    if (translateY + randomY < 30) {
        // corner case coliziune perete
        translateY = -randomY + 30;
        angleR = 2 * M_PI - angleR;
        contor++;
        if (dead == 1) {
            dead = 0;
            contor = 0;
            randomX = rand() % 1280; //1280 720
            randomY = rand() % 300;
            if (randomX < 640) {
                angleR = (rand() % 110) / (float)100 + M_PI / 10;
                translateX = translateY = 0;
            }
            else {
                angleR = (rand() % 110) / (float)100 + 6*M_PI / 10;
                translateX = translateY = 0;
            }
            // bonus culoare random
            r = (rand() % 901 + 100) / 1000.0f;
            g = (rand() % 901 + 100) / 1000.0f;
            b = (rand() % 901 + 100) / 1000.0f;
            bodyTr = object2D::CreateTriangle("bodyTr", top, 180, glm::vec3(r, g, b), true);
            AddMeshToList(bodyTr);
            wing1 = object2D::CreateTriangle("wing1", top, 75, glm::vec3(r, g, b), true);
            AddMeshToList(wing1);
            wing2 = object2D::CreateTriangle("wing2", top, 75, glm::vec3(r, g, b), true);
            AddMeshToList(wing2);
        }
    }else if(translateY + randomY > 750){
        translateY = -randomY + 750;
        contor++;
        if (dropped == 1) {
            dropped = 0;
            contor = 0;
            randomX = rand() % 1280;
            randomY = rand() % 300;
            if (randomX < 640) {
                angleR = (rand() % 110) / (float)100 + M_PI / 10;
                translateX = translateY = 0;
            }
            else {
                angleR = (rand() % 110) / (float)100 + 6 * M_PI / 10;
                translateX = translateY = 0;
            }
            r = (rand() % 901 + 100) / 1000.0f;
            g = (rand() % 901 + 100) / 1000.0f;
            b = (rand() % 901 + 100) / 1000.0f;
            // bonus culoare random
            bodyTr = object2D::CreateTriangle("bodyTr", top, 180, glm::vec3(r, g, b), true);
            AddMeshToList(bodyTr);
            wing1 = object2D::CreateTriangle("wing1", top, 75, glm::vec3(r, g, b), true);
            AddMeshToList(wing1);
            wing2 = object2D::CreateTriangle("wing2", top, 75, glm::vec3(r, g, b), true);
            AddMeshToList(wing2);
        }
        else {
            angleR = 2 * M_PI - angleR;
        }
    }

    // lives
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(30 + l1x, 680);
    RenderMesh2D(meshes["redcircle1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(80 + l2x, 680);
    RenderMesh2D(meshes["redcircle2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(130 + l3x, 680);
    RenderMesh2D(meshes["redcircle3"], shaders["VertexColor"], modelMatrix);

    // grass
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    // head
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Scale(scaleX, scaleY);
    modelMatrix *= transform2D::Translate(translateX, translateY);

    modelMatrix *= transform2D::Translate(randomX, randomY);
    modelMatrix *= transform2D::Rotate(angleR);

    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);


    //body
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Scale(scaleX, scaleY);
    modelMatrix *= transform2D::Translate(translateX, translateY);

    modelMatrix *= transform2D::Translate(randomX, randomY);
    modelMatrix *= transform2D::Rotate(angleR);
    modelMatrix *= transform2D::Translate(-randomX, -randomY);

    modelMatrix *= transform2D::Translate(randomX + 20, randomY);
    RenderMesh2D(meshes["bodyTr"], shaders["VertexColor"], modelMatrix);
    
    //wing 1
    angularStep += deltaTimeSeconds / 1.5;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Scale(scaleX, scaleY);
    modelMatrix *= transform2D::Translate(translateX, translateY);

    modelMatrix *= transform2D::Translate(randomX, randomY);
    modelMatrix *= transform2D::Rotate(angleR);
    modelMatrix *= transform2D::Translate(-randomX, -randomY);

    modelMatrix *= transform2D::Translate(randomX - 65, randomY + 90);
    modelMatrix *= transform2D::Rotate(M_PI / 2);
    
    // rotate wing
    modelMatrix *= transform2D::Translate(-95, -19);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(95, 19);

    RenderMesh2D(meshes["wing1"], shaders["VertexColor"], modelMatrix);

    // wing 2
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Scale(scaleX, scaleY);
    modelMatrix *= transform2D::Translate(translateX, translateY);

    modelMatrix *= transform2D::Translate(randomX, randomY);
    modelMatrix *= transform2D::Rotate(angleR);
    modelMatrix *= transform2D::Translate(-randomX, -randomY);

    modelMatrix *= transform2D::Translate(randomX - 65, randomY - 90);
    modelMatrix *= transform2D::Rotate(-M_PI / 2);

    //rotate wing
    modelMatrix *= transform2D::Translate(-95, 19);
    modelMatrix *= transform2D::Rotate(-angularStep);
    modelMatrix *= transform2D::Translate(95, -19);
    RenderMesh2D(meshes["wing2"], shaders["VertexColor"], modelMatrix);

    if (angularStep >= M_PI_4) {
        angularStep = 0;
    }
    
    // beak
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Scale(scaleX, scaleY);
    modelMatrix *= transform2D::Translate(translateX, translateY);

    modelMatrix *= transform2D::Translate(randomX, randomY);
    modelMatrix *= transform2D::Rotate(angleR);
    modelMatrix *= transform2D::Translate(-randomX, -randomY);

    modelMatrix *= transform2D::Translate(randomX + 55, randomY - 10);
    
    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

    // bullet
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(40 + b1x, 600);
    modelMatrix *= transform2D::Rotate(M_PI / 2);
    RenderMesh2D(meshes["bullet1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(80 + b2x, 600);
    modelMatrix *= transform2D::Rotate(M_PI / 2);
    RenderMesh2D(meshes["bullet2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(120 + b3x, 600);
    modelMatrix *= transform2D::Rotate(M_PI / 2);
    RenderMesh2D(meshes["bullet3"], shaders["VertexColor"], modelMatrix);

    //ScoreBar
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1100, 650);
    RenderMesh2D(meshes["wireframe"], shaders["VertexColor"], modelMatrix);
    currScore = object2D::CreateRectangle("currScore", top, currLevel, width, glm::vec3(0.f, 0.f, 0.66f), true);
    AddMeshToList(currScore);
    RenderMesh2D(meshes["currScore"], shaders["VertexColor"], modelMatrix);

    //frame
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Scale(scaleX, scaleY);
    modelMatrix *= transform2D::Translate(translateX, translateY);

    modelMatrix *= transform2D::Translate(randomX, randomY);
    modelMatrix *= transform2D::Rotate(angleR);
    modelMatrix *= transform2D::Translate(-randomX, -randomY);
    
    modelMatrix *= transform2D::Translate(randomX - 160, randomY - 90);
    //RenderMesh2D(meshes["birdframe"], shaders["VertexColor"], modelMatrix);
    
    //cursor
    modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(cursorX + 20, cursorY + 5);
    modelMatrix *= transform2D::Rotate(M_PI_4);
    modelMatrix *= transform2D::Translate(-cursorX - 20, -cursorY - 5);
    
    modelMatrix *= transform2D::Translate(cursorX, cursorY);
    RenderMesh2D(meshes["cursor1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(cursorX + 20, cursorY + 5);
    modelMatrix *= transform2D::Rotate(M_PI_4 + M_PI_2);
    modelMatrix *= transform2D::Translate(-cursorX - 20, -cursorY - 5);

    modelMatrix *= transform2D::Translate(cursorX, cursorY);

    RenderMesh2D(meshes["cursor2"], shaders["VertexColor"], modelMatrix);

    if (contor == 5) {
        lives--;
        angleR = M_PI_2;
        contor = 0;
        dropped = 1;
    }


    if (bullets == 3) {
        b1x = b2x = b3x = 0;
    }
    else if (bullets == 2) {
        b3x = 10000;
    }
    else if (bullets == 1) {
        b2x = 10000;
    }
    else {
        b1x = 10000;
    }
    if (lives == 3) {
        l1x = l2x = l3x = 0;
    }
    else if (lives == 2) {
        l3x = 10000;
    }
    else if (lives == 1) {
        l2x = 10000;
    }
    else if (lives == 0) {
        l1x = 10000;
        b1x = b2x = b3x = 10000;
        angleR = 0;
        if (currLevel == 150) {
            randomX = 450;
            randomY = 250;
        }
        else {
            randomX = 640;
            randomY = 400;
        }
        currLevel = -30;
        translateX = translateY = 0;
    }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    cursorX = mouseX - 17;
    cursorY = 715 - mouseY;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    int boss = 0;
    // Add mouse button press event
    if (button == 1 && lives != 0 && dead == 0 && dropped == 0) {
        if (bullets != 0)
            bullets--;
        
        // calculeaza punctul rotit
        pointX = (mouseX - randomX - translateX) * cos(-angleR) - (720 - mouseY - randomY - translateY) * sin(-angleR) + randomX + translateX;
        pointY = (mouseX - randomX - translateX) * sin(-angleR) + (720 - mouseY - randomY - translateY) * cos(-angleR) + randomY + translateY;

        // verific daca se afla in arie
        if (inside(randomX - 160 + translateX, randomY - 90 + translateY, 215, 180, pointX, pointY)) {
            angleR = 3 * M_PI / 2;
            dead = 1;
            bullets = 3;
            currLevel += 30;
            if (currLevel > 150) {
                angleR = 0;
                currLevel = -30;
                translateX = translateY = 0;
            }
        }

        if (bullets == 0) {
            lives--;
            dropped = 1;
            bullets = 3;
            angleR = M_PI_2;
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
