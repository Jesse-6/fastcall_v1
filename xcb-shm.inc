; ### XCB SHM Extension header
if ~ defined __XCB_SHM_INC_INCLUDED__
	define __XCB_SHM_INC_INCLUDED__
	define __XCB_SHM_INC_INCLUDED__

	if ~ defined __ELF_MODE_DYNAMIC__
		library 'libxcb-shm.so.0'
	end if

	ext data xcb_shm_id		; Opaque public structure at library: sized as 0 (use &xcb_shm_id to refer to it)

	ext proto xcb_shm_attach, qword, dword, dword, byte
	ext proto xcb_shm_attach_checked, qword, dword, dword, byte
	ext proto xcb_shm_detach, qword, dword
	ext proto xcb_shm_detach_checked, qword, dword
	ext proto xcb_shm_put_image, qword, dword, dword, word, word, word, word, word, word, word, word, byte, \
								 byte, byte, dword, dword
	ext proto xcb_shm_put_image_checked, qword, dword, dword, word, word, word, word, word, word, word, word, \
										 byte, byte, byte, dword, dword

end if
