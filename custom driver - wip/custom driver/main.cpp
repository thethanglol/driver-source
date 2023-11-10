#include "imports.h"
#include "functions.h"

auto DriverEntry() -> const NTSTATUS
{
    dbg("Hello!\n");

    auto win32k = utils::get_kernel_module("win32k.sys");
   
    globals::hook_address = win32k + 0x674E8;
    
    dbg("NtUserAcquireInteractiveControlBackgroundAccess: %llX", globals::hook_address);

    globals::hook_pointer = *reinterpret_cast<uintptr_t*>(globals::hook_address);
    *reinterpret_cast<uintptr_t*>(globals::hook_address) = reinterpret_cast<uintptr_t>(&hooked_function);

    dbg("success lol!");

    return STATUS_SUCCESS;
}