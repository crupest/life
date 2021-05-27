#include <WinSock2.h>
#include <Windows.h>
#include <cassert>
#include <iostream>
#include <iphlpapi.h>
#include <string>

std::wstring ToString(const SOCKET_ADDRESS &addr) {
  DWORD buffer_length = 100;
  wchar_t buffer[100];
  auto error = WSAAddressToStringW(addr.lpSockaddr, addr.iSockaddrLength, NULL,
                                   buffer, &buffer_length);
  assert(error == 0);
  return std::wstring(buffer);
}

int main() {
  WSADATA wsaData;
  int error = WSAStartup(MAKEWORD(2, 0), &wsaData);
  assert(error == 0);

  ULONG buffer_size = 100000;
  PIP_ADAPTER_ADDRESSES_LH buffer =
      (PIP_ADAPTER_ADDRESSES_LH)malloc(buffer_size);
  ULONG error2 = GetAdaptersAddresses(
      AF_INET,
      GAA_FLAG_INCLUDE_PREFIX | GAA_FLAG_INCLUDE_GATEWAYS |
          GAA_FLAG_INCLUDE_ALL_INTERFACES | GAA_FLAG_SKIP_MULTICAST,
      NULL, buffer, &buffer_size);
  assert(error2 == ERROR_SUCCESS);

  std::wcout << ToString(buffer->FirstPrefix->Address) << L"\n";
  std::wcout << buffer->FirstGatewayAddress << L"\n";

  return 0;
}
