#pragma once
#ifndef _UI_ELEMENT_H
#define _UI_ELEMENT_H


//PREGUNTAR QUE NARISES HAY QUE PONER

namespace std {
	class string;
}

class UIElement
{

private:
	UIElement();

	//Entidad de la interfaz
	//CEGUI:Window* elementInterface;
public:

	~UIElement();

	//Metodos iguales que una entidad/transform

	void setPos(int x, int y);
	void setSize(int x,int y);
	void setText(std::string text);

	//Transparencia del objeto
	void setAlpha();

	//No creo que vayamos a necesitarlo
	//inline void getAlpha();

	bool isActive();
	void setActive(bool valor);

	//Hacemos como las entidades y le metemos hijos y que hereden de un padre X?
	//Hay metodos en Cegui que sirven para saber facilmete si una ventana es objeto de otra etc
};

#endif _UI_ELEMENT_H