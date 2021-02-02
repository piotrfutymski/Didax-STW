#include "Asset.h"

Didax::Asset::Asset(const std::string& name)
{
	m_name = name;
}

const std::string& Didax::Asset::getName() const
{
	return m_name;
}
