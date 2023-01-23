#pragma once

#include "GLFW/glfw3.h"
#include "InputData.h"
/**
 * put all your shit in here
 *
 *
 */

 // Caller: Lawan, Implementer: Elijah
 /*
  * @param data : buffer of data for faces
  * @param dim : dim x dim face
  */
int UpdateCubeData(void* data, int dim);

void UpdateInputs(INPUTS* newInputs);
void UpdateMouse(MOUSE_INPUTS* newMouse);