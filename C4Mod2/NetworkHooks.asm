format MS64 COFF

include '%fasminc%\win64a.INC'

extrn '__imp_GetTickCount'				 as GetTickCount:qword
extrn '?PacketIn@CPacketFilter@@SA_KPEAVCSocket@@PEAEK@Z' as PacketIn

public PacketInHook

section '.data' data readable writeable

section '.text' code readable executable

proc PacketInHook
     sub    rsp, 20h
     call   [GetTickCount]
     mov    edi, eax
     mov    rcx, rsi		 ;socket
     movsxd r8,  r14d		 ;size
     lea    rdx, [r8+r13]	 ;packet
     movzx  r8,  word [r8+r13-2]
     call   PacketIn
     add    rsp, 20h
     cmp    rax, 0
     je @F
     mov [rsp], rax		 ;blocked packet
   @@:
     ret
endp
