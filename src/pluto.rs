
pub const true_: u32 = 1;
pub const false_: u32 = 0;
pub const __bool_true_false_are_defined: u32 = 1;
pub const _STDINT_H: u32 = 1;
pub const _FEATURES_H: u32 = 1;
pub const _DEFAULT_SOURCE: u32 = 1;
pub const __GLIBC_USE_ISOC2X: u32 = 0;
pub const __USE_ISOC11: u32 = 1;
pub const __USE_ISOC99: u32 = 1;
pub const __USE_ISOC95: u32 = 1;
pub const __USE_POSIX_IMPLICITLY: u32 = 1;
pub const _POSIX_SOURCE: u32 = 1;
pub const _POSIX_C_SOURCE: u32 = 200809;
pub const __USE_POSIX: u32 = 1;
pub const __USE_POSIX2: u32 = 1;
pub const __USE_POSIX199309: u32 = 1;
pub const __USE_POSIX199506: u32 = 1;
pub const __USE_XOPEN2K: u32 = 1;
pub const __USE_XOPEN2K8: u32 = 1;
pub const _ATFILE_SOURCE: u32 = 1;
pub const __USE_MISC: u32 = 1;
pub const __USE_ATFILE: u32 = 1;
pub const __USE_FORTIFY_LEVEL: u32 = 0;
pub const __GLIBC_USE_DEPRECATED_GETS: u32 = 0;
pub const __GLIBC_USE_DEPRECATED_SCANF: u32 = 0;
pub const _STDC_PREDEF_H: u32 = 1;
pub const __STDC_IEC_559__: u32 = 1;
pub const __STDC_IEC_559_COMPLEX__: u32 = 1;
pub const __STDC_ISO_10646__: u32 = 201706;
pub const __GNU_LIBRARY__: u32 = 6;
pub const __GLIBC__: u32 = 2;
pub const __GLIBC_MINOR__: u32 = 33;
pub const _SYS_CDEFS_H: u32 = 1;
pub const __glibc_c99_flexarr_available: u32 = 1;
pub const __WORDSIZE: u32 = 64;
pub const __WORDSIZE_TIME64_COMPAT32: u32 = 1;
pub const __SYSCALL_WORDSIZE: u32 = 64;
pub const __LDOUBLE_REDIRECTS_TO_FLOAT128_ABI: u32 = 0;
pub const __HAVE_GENERIC_SELECTION: u32 = 1;
pub const __GLIBC_USE_LIB_EXT2: u32 = 0;
pub const __GLIBC_USE_IEC_60559_BFP_EXT: u32 = 0;
pub const __GLIBC_USE_IEC_60559_BFP_EXT_C2X: u32 = 0;
pub const __GLIBC_USE_IEC_60559_FUNCS_EXT: u32 = 0;
pub const __GLIBC_USE_IEC_60559_FUNCS_EXT_C2X: u32 = 0;
pub const __GLIBC_USE_IEC_60559_TYPES_EXT: u32 = 0;
pub const _BITS_TYPES_H: u32 = 1;
pub const __TIMESIZE: u32 = 64;
pub const _BITS_TYPESIZES_H: u32 = 1;
pub const __OFF_T_MATCHES_OFF64_T: u32 = 1;
pub const __INO_T_MATCHES_INO64_T: u32 = 1;
pub const __RLIM_T_MATCHES_RLIM64_T: u32 = 1;
pub const __STATFS_MATCHES_STATFS64: u32 = 1;
pub const __KERNEL_OLD_TIMEVAL_MATCHES_TIMEVAL64: u32 = 1;
pub const __FD_SETSIZE: u32 = 1024;
pub const _BITS_TIME64_H: u32 = 1;
pub const _BITS_WCHAR_H: u32 = 1;
pub const _BITS_STDINT_INTN_H: u32 = 1;
pub const _BITS_STDINT_UINTN_H: u32 = 1;
pub const INT8_MIN: i32 = -128;
pub const INT16_MIN: i32 = -32768;
pub const INT32_MIN: i32 = -2147483648;
pub const INT8_MAX: u32 = 127;
pub const INT16_MAX: u32 = 32767;
pub const INT32_MAX: u32 = 2147483647;
pub const UINT8_MAX: u32 = 255;
pub const UINT16_MAX: u32 = 65535;
pub const UINT32_MAX: u32 = 4294967295;
pub const INT_LEAST8_MIN: i32 = -128;
pub const INT_LEAST16_MIN: i32 = -32768;
pub const INT_LEAST32_MIN: i32 = -2147483648;
pub const INT_LEAST8_MAX: u32 = 127;
pub const INT_LEAST16_MAX: u32 = 32767;
pub const INT_LEAST32_MAX: u32 = 2147483647;
pub const UINT_LEAST8_MAX: u32 = 255;
pub const UINT_LEAST16_MAX: u32 = 65535;
pub const UINT_LEAST32_MAX: u32 = 4294967295;
pub const INT_FAST8_MIN: i32 = -128;
pub const INT_FAST16_MIN: i64 = -9223372036854775808;
pub const INT_FAST32_MIN: i64 = -9223372036854775808;
pub const INT_FAST8_MAX: u32 = 127;
pub const INT_FAST16_MAX: u64 = 9223372036854775807;
pub const INT_FAST32_MAX: u64 = 9223372036854775807;
pub const UINT_FAST8_MAX: u32 = 255;
pub const UINT_FAST16_MAX: i32 = -1;
pub const UINT_FAST32_MAX: i32 = -1;
pub const INTPTR_MIN: i64 = -9223372036854775808;
pub const INTPTR_MAX: u64 = 9223372036854775807;
pub const UINTPTR_MAX: i32 = -1;
pub const PTRDIFF_MIN: i64 = -9223372036854775808;
pub const PTRDIFF_MAX: u64 = 9223372036854775807;
pub const SIG_ATOMIC_MIN: i32 = -2147483648;
pub const SIG_ATOMIC_MAX: u32 = 2147483647;
pub const SIZE_MAX: i32 = -1;
pub const WINT_MIN: u32 = 0;
pub const WINT_MAX: u32 = 4294967295;
pub const PLUTO_CHAR_OFF: u32 = 10240;
pub type __u_char = ::std::os::raw::c_uchar;
pub type __u_short = ::std::os::raw::c_ushort;
pub type __u_int = ::std::os::raw::c_uint;
pub type __u_long = ::std::os::raw::c_ulong;
pub type __int8_t = ::std::os::raw::c_schar;
pub type __uint8_t = ::std::os::raw::c_uchar;
pub type __int16_t = ::std::os::raw::c_short;
pub type __uint16_t = ::std::os::raw::c_ushort;
pub type __int32_t = ::std::os::raw::c_int;
pub type __uint32_t = ::std::os::raw::c_uint;
pub type __int64_t = ::std::os::raw::c_long;
pub type __uint64_t = ::std::os::raw::c_ulong;
pub type __int_least8_t = __int8_t;
pub type __uint_least8_t = __uint8_t;
pub type __int_least16_t = __int16_t;
pub type __uint_least16_t = __uint16_t;
pub type __int_least32_t = __int32_t;
pub type __uint_least32_t = __uint32_t;
pub type __int_least64_t = __int64_t;
pub type __uint_least64_t = __uint64_t;
pub type __quad_t = ::std::os::raw::c_long;
pub type __u_quad_t = ::std::os::raw::c_ulong;
pub type __intmax_t = ::std::os::raw::c_long;
pub type __uintmax_t = ::std::os::raw::c_ulong;
pub type __dev_t = ::std::os::raw::c_ulong;
pub type __uid_t = ::std::os::raw::c_uint;
pub type __gid_t = ::std::os::raw::c_uint;
pub type __ino_t = ::std::os::raw::c_ulong;
pub type __ino64_t = ::std::os::raw::c_ulong;
pub type __mode_t = ::std::os::raw::c_uint;
pub type __nlink_t = ::std::os::raw::c_ulong;
pub type __off_t = ::std::os::raw::c_long;
pub type __off64_t = ::std::os::raw::c_long;
pub type __pid_t = ::std::os::raw::c_int;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct __fsid_t {
    pub __val: [::std::os::raw::c_int; 2usize],
}
#[test]
fn bindgen_test_layout___fsid_t() {
    assert_eq!(
        ::std::mem::size_of::<__fsid_t>(),
        8usize,
        concat!("Size of: ", stringify!(__fsid_t))
    );
    assert_eq!(
        ::std::mem::align_of::<__fsid_t>(),
        4usize,
        concat!("Alignment of ", stringify!(__fsid_t))
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<__fsid_t>())).__val as *const _ as usize },
        0usize,
        concat!(
            "Offset of field: ",
            stringify!(__fsid_t),
            "::",
            stringify!(__val)
        )
    );
}
pub type __clock_t = ::std::os::raw::c_long;
pub type __rlim_t = ::std::os::raw::c_ulong;
pub type __rlim64_t = ::std::os::raw::c_ulong;
pub type __id_t = ::std::os::raw::c_uint;
pub type __time_t = ::std::os::raw::c_long;
pub type __useconds_t = ::std::os::raw::c_uint;
pub type __suseconds_t = ::std::os::raw::c_long;
pub type __suseconds64_t = ::std::os::raw::c_long;
pub type __daddr_t = ::std::os::raw::c_int;
pub type __key_t = ::std::os::raw::c_int;
pub type __clockid_t = ::std::os::raw::c_int;
pub type __timer_t = *mut ::std::os::raw::c_void;
pub type __blksize_t = ::std::os::raw::c_long;
pub type __blkcnt_t = ::std::os::raw::c_long;
pub type __blkcnt64_t = ::std::os::raw::c_long;
pub type __fsblkcnt_t = ::std::os::raw::c_ulong;
pub type __fsblkcnt64_t = ::std::os::raw::c_ulong;
pub type __fsfilcnt_t = ::std::os::raw::c_ulong;
pub type __fsfilcnt64_t = ::std::os::raw::c_ulong;
pub type __fsword_t = ::std::os::raw::c_long;
pub type __ssize_t = ::std::os::raw::c_long;
pub type __syscall_slong_t = ::std::os::raw::c_long;
pub type __syscall_ulong_t = ::std::os::raw::c_ulong;
pub type __loff_t = __off64_t;
pub type __caddr_t = *mut ::std::os::raw::c_char;
pub type __intptr_t = ::std::os::raw::c_long;
pub type __socklen_t = ::std::os::raw::c_uint;
pub type __sig_atomic_t = ::std::os::raw::c_int;
pub type int_least8_t = __int_least8_t;
pub type int_least16_t = __int_least16_t;
pub type int_least32_t = __int_least32_t;
pub type int_least64_t = __int_least64_t;
pub type uint_least8_t = __uint_least8_t;
pub type uint_least16_t = __uint_least16_t;
pub type uint_least32_t = __uint_least32_t;
pub type uint_least64_t = __uint_least64_t;
pub type int_fast8_t = ::std::os::raw::c_schar;
pub type int_fast16_t = ::std::os::raw::c_long;
pub type int_fast32_t = ::std::os::raw::c_long;
pub type int_fast64_t = ::std::os::raw::c_long;
pub type uint_fast8_t = ::std::os::raw::c_uchar;
pub type uint_fast16_t = ::std::os::raw::c_ulong;
pub type uint_fast32_t = ::std::os::raw::c_ulong;
pub type uint_fast64_t = ::std::os::raw::c_ulong;
pub type intmax_t = __intmax_t;
pub type uintmax_t = __uintmax_t;
pub type uchar = ::std::os::raw::c_uchar;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct pluto_colour_t {
    pub r: u8,
    pub g: u8,
    pub b: u8,
}
#[test]
fn bindgen_test_layout_pluto_colour_t() {
    assert_eq!(
        ::std::mem::size_of::<pluto_colour_t>(),
        3usize,
        concat!("Size of: ", stringify!(pluto_colour_t))
    );
    assert_eq!(
        ::std::mem::align_of::<pluto_colour_t>(),
        1usize,
        concat!("Alignment of ", stringify!(pluto_colour_t))
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_colour_t>())).r as *const _ as usize },
        0usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_colour_t),
            "::",
            stringify!(r)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_colour_t>())).g as *const _ as usize },
        1usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_colour_t),
            "::",
            stringify!(g)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_colour_t>())).b as *const _ as usize },
        2usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_colour_t),
            "::",
            stringify!(b)
        )
    );
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct pluto_lib_t {
    pub height: i32,
    pub width: i32,
    pub old_height: i32,
    pub old_width: i32,
    pub cheight: i32,
    pub cwidth: i32,
    pub bufsize: i32,
    pub bmsize: i32,
    pub pix_colour: *mut pluto_colour_t,
    pub bitmap: *mut uchar,
    pub buffer: *mut uchar,
    pub screen_swapped: bool,
    pub is_init: bool,
    pub busy: bool,
    pub use_write: bool,
}
#[test]
fn bindgen_test_layout_pluto_lib_t() {
    assert_eq!(
        ::std::mem::size_of::<pluto_lib_t>(),
        64usize,
        concat!("Size of: ", stringify!(pluto_lib_t))
    );
    assert_eq!(
        ::std::mem::align_of::<pluto_lib_t>(),
        8usize,
        concat!("Alignment of ", stringify!(pluto_lib_t))
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).height as *const _ as usize },
        0usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(height)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).width as *const _ as usize },
        4usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(width)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).old_height as *const _ as usize },
        8usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(old_height)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).old_width as *const _ as usize },
        12usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(old_width)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).cheight as *const _ as usize },
        16usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(cheight)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).cwidth as *const _ as usize },
        20usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(cwidth)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).bufsize as *const _ as usize },
        24usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(bufsize)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).bmsize as *const _ as usize },
        28usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(bmsize)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).pix_colour as *const _ as usize },
        32usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(pix_colour)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).bitmap as *const _ as usize },
        40usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(bitmap)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).buffer as *const _ as usize },
        48usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(buffer)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).screen_swapped as *const _ as usize },
        56usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(screen_swapped)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).is_init as *const _ as usize },
        57usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(is_init)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).busy as *const _ as usize },
        58usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(busy)
        )
    );
    assert_eq!(
        unsafe { &(*(::std::ptr::null::<pluto_lib_t>())).use_write as *const _ as usize },
        59usize,
        concat!(
            "Offset of field: ",
            stringify!(pluto_lib_t),
            "::",
            stringify!(use_write)
        )
    );
}
extern "C" {
    pub static mut _pluto_pixmap: [[uchar; 2usize]; 4usize];
}
extern "C" {
    pub static mut _pluto_canvas: pluto_lib_t;
}
extern "C" {
    pub fn pluto_init_window();
}
extern "C" {
    pub fn pluto_render();
}
extern "C" {
    pub fn pluto_write_out();
}
extern "C" {
    pub fn pluto_clear();
}
extern "C" {
    pub fn pluto_clear_buffers();
}
extern "C" {
    pub fn pluto_deinit();
}
extern "C" {
    pub fn pluto_set_pix_colour(
        x: ::std::os::raw::c_int,
        y: ::std::os::raw::c_int,
        red: u8,
        green: u8,
        blue: u8,
    );
}
extern "C" {
    pub fn pluto_set_upix_colour(
        x: ::std::os::raw::c_int,
        y: ::std::os::raw::c_int,
        red: u8,
        green: u8,
        blue: u8,
    );
}
extern "C" {
    pub fn pluto_set_cpix(
        x: ::std::os::raw::c_int,
        y: ::std::os::raw::c_int,
        red: u8,
        green: u8,
        blue: u8,
    );
}
extern "C" {
    pub fn pluto_set_ucpix(
        x: ::std::os::raw::c_int,
        y: ::std::os::raw::c_int,
        red: u8,
        green: u8,
        blue: u8,
    );
}
extern "C" {
    pub fn pluto_set_pix(x: ::std::os::raw::c_int, y: ::std::os::raw::c_int);
}
extern "C" {
    pub fn pluto_set_upix(x: ::std::os::raw::c_int, y: ::std::os::raw::c_int);
}
extern "C" {
    pub fn pluto_unset_pix(x: ::std::os::raw::c_int, y: ::std::os::raw::c_int);
}
extern "C" {
    pub fn pluto_unset_upix(x: ::std::os::raw::c_int, y: ::std::os::raw::c_int);
}
extern "C" {
    pub fn pluto_save_screen();
}
extern "C" {
    pub fn pluto_restore_screen();
}
extern "C" {
    pub fn pluto_resize();
}
extern "C" {
    pub fn pluto_set_buffer_pix(
        bitmap: *mut u8,
        x: ::std::os::raw::c_int,
        y: ::std::os::raw::c_int,
    );
}
extern "C" {
    pub fn pluto_unset_buffer_pix(
        bitmap: *mut u8,
        x: ::std::os::raw::c_int,
        y: ::std::os::raw::c_int,
    );
}
extern "C" {
    pub fn pluto_set_buffer_pix_colour(
        buffer: *mut pluto_colour_t,
        x: ::std::os::raw::c_int,
        y: ::std::os::raw::c_int,
        red: u8,
        green: u8,
        blue: u8,
    );
}
extern "C" {
    pub fn pluto_set_buffer_cpix(
        bitmap: *mut u8,
        buffer: *mut pluto_colour_t,
        x: ::std::os::raw::c_int,
        y: ::std::os::raw::c_int,
        red: u8,
        green: u8,
        blue: u8,
    );
}
