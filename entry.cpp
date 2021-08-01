#include <imports.hpp>

resize_buffers_t resize_buffers_original;
present_scene_t present_scene_original;

/**
* Presents/renders the image.
* @param swap_chain The swap chain needed to draw.
* @param sync_interval Specifies synchronization of frame presentation.
* @param flags Drawing flags, DXGI_PRESENT.
* @return Status returned by the original present scene gotten from discord
*/
HRESULT __fastcall present_scene_hook(__int64 swap_chain, unsigned int sync_interval, unsigned int flags)
{
#ifdef LOGGING
    std::printf("present_scene_hook called\n   swap_chain = %p\n   sync_interval = %i\n   flags = %i\n", swap_chain, sync_interval, flags);
#endif
    return present_scene_original(swap_chain, sync_interval, flags);
}

/**
* Resize buffers hook called whenever you resize window.
* @param swap_chain The swap chain needed to do trickery.
* @param buffer_count Buffers in swap chain.
* @param width The new width of the window.
* @param height The new height of the window.
* @return Status returned by the original resize buffers gotten by discord.
*/
HRESULT __fastcall resize_buffers_hook(__int64 swap_chain, unsigned int buffer_count, unsigned int width, unsigned int height)
{
#ifdef LOGGING
    std::printf("resize_buffers_hook called\n   swap_chain = %p\n   buffer_count = %i\n   size = %ix%i\n", swap_chain, buffer_count, width, height);
#endif
    return resize_buffers_original(swap_chain, buffer_count, width, height);
}

bool __stdcall DllMain(HMODULE hodule, ULONG reason, PVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
#ifdef LOGGING
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
#endif

        std::uint64_t DiscordHook64 = reinterpret_cast<std::uint64_t>(GetModuleHandle("DiscordHook64.dll"));
        DXGI_PRESENT_ALLOW_TEARING;
        /*
        Hooking the present scene function with da MEGA elite 1337 .data swap
        */
        present_scene_original = *reinterpret_cast<present_scene_t*>(DiscordHook64 + 0x1B3080); // PresentSceneOriginal
        
        *reinterpret_cast<present_scene_t*>(DiscordHook64 + 0x1B3080) = present_scene_hook; // PresentSceneOriginal

#ifdef LOGGING
        std::printf("present scene swap successful\n   original = %p\n   new = %p\n", present_scene_original, *reinterpret_cast<present_scene_t*>(DiscordHook64 + 0x1B3080));
#endif
  
        /*
        Hooking the resize buffers function with da elite 1337 .data swap
        */
        resize_buffers_original = *reinterpret_cast<resize_buffers_t*>(DiscordHook64 + 0x1B30A8); // ResizeBuffersOriginal

        *reinterpret_cast<resize_buffers_t*>(DiscordHook64 + 0x1B30A8) = resize_buffers_hook; // ResizeBuffersOriginal

#ifdef LOGGING
        std::printf("resize buffers swap successful\n   original = %p\n   new = %p\n", resize_buffers_original, *reinterpret_cast<present_scene_t*>(DiscordHook64 + 0x1B30A8));
#endif
    }
    return TRUE;
}

