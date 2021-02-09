#include "DragAndDrop.h"

DragAndDrop::DragAndDrop(const std::vector<sf::Vector2f>& itemPos, const sf::Vector2f& itemSize)
{
	m_itemPositions = itemPos;
	m_items.resize(itemPos.size(), nullptr);
	m_itemSize = itemSize;
}

void DragAndDrop::setMe(Didax::Entity_ptr m)
{
	m_me = m;
}

void DragAndDrop::removeItem(int pos)
{
	if (pos >= m_items.size())
		return;
	auto item = getItem(pos);
	item->getWidget()->setWidgetEvent(Didax::Widget::CallbackType::onPress, [this, item](Didax::Widget* w) {
		item->getScript<Item>()->onClick();
	});
	item->getWidget()->setWidgetEvent(Didax::Widget::CallbackType::onRelease, [this, item](Didax::Widget* w) {
		item->getScript<Item>()->onRelease();
	});
	m_items[pos] = nullptr;
}

Didax::Entity_ptr DragAndDrop::getItem(int pos)
{
	if (pos >= m_items.size())
		return nullptr;

	return m_items[pos];
}

Didax::Entity_ptr DragAndDrop::draggedItem()
{
	if (m_dragged == -1)
		return nullptr;
	return m_items[m_dragged];
}

void DragAndDrop::onUpdate(Didax::Engine* e)
{
	auto dragged = draggedItem();
	if (dragged != nullptr)
	{
		auto dist = Didax::Input::getMousePosition() - m_startingMousePos;
		dragged->getWidget()->setPosition(sf::Vector2f(dist) + m_itemPositions[m_dragged]);
		auto newToChange = findDraggedReplace();
		if (newToChange != m_toChange)
		{
			if (newToChange == -1)
			{
				m_shadow->getWidget<Didax::Canvas>()->setTexture(dragged->getWidget<Didax::Canvas>()->getTexture());
				if (m_Marker != nullptr)
				{
					e->removeEntity(m_Marker->getName());
					m_Marker = nullptr;
				}			
			}
			else
			{
				if(m_Marker != nullptr)
					e->removeEntity(m_Marker->getName());
				m_shadow->getWidget<Didax::Canvas>()->setTexture(m_items[newToChange]->getWidget<Didax::Canvas>()->getTexture());
				m_Marker = e->addEntity();
				auto c = m_Marker->createWidget<Didax::Canvas>();
				m_Marker->setPriority(m_items[newToChange]->getPriority() + 1);
				m_me->getWidget()->addChild(c);
				c->setPosition(m_itemPositions[newToChange]);
				c->setSize(m_itemSize);
				c->setRect();
				c->setColor(sf::Color(120, 120, 50, 150));
			}
			m_toChange = newToChange;
		}	
	}
}

void DragAndDrop::onStart(Didax::Engine* e)
{
	m_eng = e;
}

void DragAndDrop::addItem(Didax::Entity_ptr item, int pos)
{
	if (pos >= m_items.size())
		return;
	if (m_items[pos] == nullptr)
	{
		m_items[pos] = item;
		item->getWidget()->setWidgetEvent(Didax::Widget::CallbackType::onPress, [this, item](Didax::Widget* w) {
			onClick(w, item);
			item->getScript<Item>()->onClick();

		});
		item->getWidget()->setWidgetEvent(Didax::Widget::CallbackType::onRelease, [this, item](Didax::Widget* w) {
			onRelease(w, item);
			item->getScript<Item>()->onRelease();
		});
		item->getWidget()->setPosition(m_itemPositions[pos]);
		item->getWidget()->setSize(m_itemSize);
		item->setPriority(m_me->getPriority() + 100);
	}
}

void DragAndDrop::removeItem(Didax::Entity_ptr item)
{
	auto it = std::find(m_items.begin(), m_items.end(), item);
	if (it == m_items.end())
		return;
	item->getWidget()->setWidgetEvent(Didax::Widget::CallbackType::onPress, [this, item](Didax::Widget* w) {
		item->getScript<Item>()->onClick();
	});
	item->getWidget()->setWidgetEvent(Didax::Widget::CallbackType::onRelease, [this, item](Didax::Widget* w) {
		item->getScript<Item>()->onRelease();
	});
	m_items[std::distance(m_items.begin(), it)] = nullptr;
}


void DragAndDrop::onClick(Didax::Widget* w, Didax::Entity_ptr i)
{
	m_startingMousePos = Didax::Input::getMousePosition();
	auto it = std::find(m_items.begin(), m_items.end(), i);
	m_dragged = std::distance(m_items.begin(), it);
	auto itemWidg = i->getWidget<Didax::Canvas>();
	i->setPriority(i->getPriority() + 2);
	m_shadow = m_eng->addEntity();
	m_shadow->setPriority(i->getPriority() - 2);
	auto c = m_shadow->createWidget<Didax::Canvas>();
	m_me->getWidget()->addChild(c);
	c->setTexture(itemWidg->getTexture());
	c->setPosition(m_itemPositions[m_dragged]);
	c->setSize(m_itemSize);
	c->setColor(sf::Color(170, 170, 170, 150));
}

void DragAndDrop::onRelease(Didax::Widget* w, Didax::Entity_ptr i)
{
	if (m_toChange == -1)
	{
		w->setPositionInTime(m_itemPositions[m_dragged], 0.1);
	}
	else
	{
		auto s = m_items[m_toChange];
		m_items[m_toChange] = i;
		i->getWidget()->setPosition(m_itemPositions[m_toChange]);
		m_items[m_dragged] = s;
		if (s != nullptr)
		{
			s->getWidget()->setPositionInTime(m_itemPositions[m_dragged], 0.1);
		}
	}
	i->setPriority(i->getPriority() - 1);
	if (m_Marker != nullptr)
	{
		m_eng->removeEntity(m_Marker->getName());
		m_Marker = nullptr;
	}
	m_dragged = -1;
	m_eng->removeEntity(m_shadow->getName());
}

int DragAndDrop::findDraggedReplace()
{
	for (int i =0; i < m_itemPositions.size(); i++)
	{
		if (i == m_dragged)
			continue;
		if (m_items[i]->getWidget()->isHovered())
			return i;
	}
	return -1;
}
