#pragma once
#include "Didax-Engine/Engine.h"
#include "FrameElement.h"

class DragAndDrop
{
public:

	DragAndDrop(const std::vector<sf::Vector2f> & itemPos, const sf::Vector2f & itemSize);

	void setMe(Didax::Entity_ptr);

	void onStart(Didax::Engine* e);

	void addItem(Didax::Entity_ptr, int pos);

	void removeItem(Didax::Entity_ptr);

	void removeItem(int pos);

	Didax::Entity_ptr getItem(int pos);

	Didax::Entity_ptr draggedItem();

	void onUpdate(Didax::Engine* e);

private:

	Didax::Engine* m_eng;
	Didax::Entity_ptr m_me{ nullptr };

	std::vector<sf::Vector2f> m_itemPositions;
	std::vector<Didax::Entity_ptr> m_items;
	sf::Vector2f m_itemSize;

	int m_dragged{ -1 };
	int m_toChange{ -1 };
	sf::Vector2i m_startingMousePos{};
	Didax::Entity_ptr m_shadow{ nullptr };
	Didax::Entity_ptr m_Marker{ nullptr };

	void onClick(Didax::Widget* , Didax::Entity_ptr i);
	void onRelease(Didax::Widget*, Didax::Entity_ptr i);
	int findDraggedReplace();
};

