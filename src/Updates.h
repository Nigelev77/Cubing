#pragma once


// Elijah : Put function declarations here so I can include them into the main file

void RenderUpdate(double delta);
void GameUpdate(double delta);

/**
 * If needed to do an init, define here and call it in main.cpp
 */

void RenderInit();
void IOInit(void* window);