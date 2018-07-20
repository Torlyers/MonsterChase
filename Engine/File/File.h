#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
namespace Engine
{
	uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
}
