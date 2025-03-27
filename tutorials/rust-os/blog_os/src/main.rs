#![no_std]
#![no_main]

use core::panic::PanicInfo;

/// This function is called on panic.
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

fn fibonacci(n: i32) -> i32 {
    if n == 0 {
        return 0;
    }
    if n == 1 {
        return 1;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

#[no_mangle]
pub extern "C" fn _start() -> ! {
    let f = fibonacci(10);
    unsafe {
        (&f as *const i32).read_volatile();
    }
    loop {}
}
