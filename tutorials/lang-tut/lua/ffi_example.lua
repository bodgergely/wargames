local ffi = require("ffi")
ffi.cdef[[
int printf(const char *fmt, ...);
void* malloc(size_t);
void free(void*);
]]

function allocate(bytes)
    res = ffi.C.malloc(bytes)
    return res
end

function deallocate(pointer)
    ffi.C.free(pointer)
end

function foo(iter)
    for i=1,iter do
        p = allocate(1)
        deallocate(p)
    end
end

foo(1000000000)



