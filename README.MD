# VPinball - ScottKirvan/VPinball Fork

## building for Windows 10, VS2019

- Install [Legacy DirectX](https://docs.microsoft.com/en-us/windows/win32/directx-sdk--august-2009-)
- You will get an error during install - that's ok - just cancel out - you DO NOT need this to finish, but...
- if you want to get the legacy DirectX installed anyway, see:  https://docs.microsoft.com/en-US/troubleshoot/windows/win32/s1023-error-when-you-install-directx-sdk
- Project should build
---

running x64\VPinballX.exe will fail.  The following dlls are missing: FreeImage64.dll, bass64.dll, SciLexerVP64.dll

These DLLs are found, precompiled, in the repository:  dll/x64 directory.  Just copy them to your x64/Debug or Release folders (depending on which you're using)

copy scripts folder to x64/Debug
