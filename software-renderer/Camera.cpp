//
//  Camera.cpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 5/12/15.
//  Copyright © 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera()
{
}

Camera::~Camera()
{
}

glm::vec3 Camera::getPosition()
{
    return position;
}

void Camera::setPosition(glm::vec3 position)
{
    this->position = position;
}

glm::vec3 Camera::getTarget()
{
    return target;
}

void Camera::setTarget(glm::vec3 target)
{
    this->target = target;
}