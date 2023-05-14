#pragma once

#include "VGL/Core.h"

#include <vector>
#include <stdexcept>

namespace VGL
{
	typedef const char* VGLExtension;

	typedef class VGLExtensionList
	{
	public:
		VGLExtensionList() = default;

		VGLExtensionList(std::initializer_list<VGLExtension> extensions)
			: m_Extensions(extensions)
		{ }

		void Add(VGLExtension extension) { m_Extensions.push_back(extension); }
		void AddList(std::vector<VGLExtension> extensions) { m_Extensions.insert(m_Extensions.end(), extensions.begin(), extensions.end()); }

		size_t Size() const { return m_Extensions.size(); }
		VGLExtension* Data() { return m_Extensions.data(); }

		VGLExtension& operator[](uint32_t index)
		{
			if (index >= m_Extensions.size() || index < 0)
				throw std::out_of_range("The index is out of bounds of the extension list");

			return m_Extensions[index];
		}
	private:
		std::vector<VGLExtension> m_Extensions;
	} ExtensionList;
}

#define vglCreateExtension() VGL::ExtensionList()
