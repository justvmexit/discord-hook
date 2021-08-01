#pragma once

#include <Windows.h>
#include <iostream>

#include <d3d11.h>

#define LOGGING

ULONG protection;
typedef HRESULT(__fastcall* present_scene_t)(__int64 swap_chain, unsigned int sync_interval, unsigned int flags);
typedef HRESULT(__fastcall* resize_buffers_t)(__int64, unsigned int, unsigned int, unsigned int);