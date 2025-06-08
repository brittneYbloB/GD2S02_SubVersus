/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : CResourceObject.cpp
Description : Implementation for base resource object class
Authors : Brittney Smith, Manu
**************************************************************************/

#include "CResourceObject.h"

/**************************************************************************
* CResourceObject: Base class constructor
* @parameters:
* @return:
***************************************************************************/
CResourceObject::CResourceObject()
{
	// Initialise some values
	m_isCollected = false;
	m_resourceValue = 0;
}

/**************************************************************************
* ~CResourceObject: Destructor
* @parameters:
* @return:
***************************************************************************/
CResourceObject::~CResourceObject()
{
}

/**************************************************************************
* RecieveImpact: receive damage -> mark for destroy
* @parameters: damage (float) amount
* @return:
***************************************************************************/
void CResourceObject::RecieveImpact(float _damage)
{
	m_markedForDestroy = true;
}