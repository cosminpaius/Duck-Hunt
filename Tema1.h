#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX = 0, translateY = 0, cursorX, cursorY, b1x = 0, b2x = 0, b3x = 0, l1x = 0, l2x = 0, l3x = 0;
        float scaleX, scaleY;
        float angularStep, x = 1;
        float r = 0.2f, g = 0.1f, b = 0;
        bool dead = 0, dropped = 0;

        int contor, currLevel = 0, bullets = 3, lives = 3;
        int randomX, randomY;
        float angleR;
        float fr1x, fr1y, fr2x, fr2y, fr3x, fr3y, fr4x, fr4y, pointX, pointY;
        glm::vec3 top = glm::vec3(0, 0, 0);

        float length = 180, width = 200;
        Mesh *currScore, *bodyTr, *wing1, *wing2;
    };
}   
