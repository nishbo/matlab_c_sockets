CPP = g++
CPPFLAGS = -O2

WINCPP = cl
WINCOMMON=/O2 /EHsc /MT

OBJDIR = ../obj
BINDIR = ../bin


socket.obj:
	$(WINCPP) /c socket.cpp /Fo$(OBJDIR)/socket.obj $(WINCOMMON)

crossplatform_win.obj:
	$(WINCPP) /c crossplatform_win.cpp /Fo$(OBJDIR)/crossplatform_win.obj $(WINCOMMON)

socket_api.obj:
	$(WINCPP) /c socket_api.cpp /Fo$(OBJDIR)/socket_api.obj $(WINCOMMON)

cpp_server.obj:
	$(WINCPP) /c cpp_server.cpp /Fo$(OBJDIR)/cpp_server.obj $(WINCOMMON)

cpp_server: socket.obj crossplatform_win.obj socket_api.obj cpp_server.obj
	$(WINCPP) /Fe$(BINDIR)/cpp_server.exe $(OBJDIR)/cpp_server.obj $(OBJDIR)/socket_api.obj $(OBJDIR)/socket.obj $(OBJDIR)/crossplatform_win.obj $(WINCOMMON)


paths:
	mkdir -p $(subst /,\,$(OBJDIR))
	mkdir -p $(subst /,\,$(BINDIR))

all: paths cpp_server


clean:
	rm -f $(OBJDIR)/*.obj *.obj *.exp *.lib *.mexw64.manifest *.dll

clean_exe:
	rm -f $(BINDIR)/*.exe
