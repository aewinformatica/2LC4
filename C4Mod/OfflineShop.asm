format MS64 COFF

include '%fasminc%\win64a.INC'

extrn '?CanSellItem@COfflineShop@@SA_NPEAVCItem@@@Z' as CanSellItem

public ManagePrivateStoreFilterHook

section '.data' data readable writeable

section '.text' code readable executable

proc ManagePrivateStoreFilterHook
     mov rax, [rcx+30h]
     cmp dword [rax+70h], 39h
     jnz @F
     ret
   @@:
     push rax
     push rcx
     sub rsp, 20h
     call CanSellItem
     add rsp, 20h
     cmp rax, 0
     pop rcx
     pop rax
     ret
endp
