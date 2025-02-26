#include "stdafx.h"
#include "Intshcut.h"

unsigned long long tinymt64state[2] = { 'T', 'M' };


float sz2f(const string& sz)
{
   const int len = (int)sz.length()+1;
   WCHAR * const wzT = new WCHAR[len];
   MultiByteToWideCharNull(CP_ACP, 0, sz.c_str(), -1, wzT, len);

   CComVariant var = wzT;

   float result;
   if (SUCCEEDED(VariantChangeType(&var, &var, 0, VT_R4)))
   {
      result = V_R4(&var);
      VariantClear(&var);
   }
   else
      result = 0.0f; //!! use inf or NaN instead?

   delete[] wzT;

   return result;
}

void f2sz(const float f, string& sz)
{
   CComVariant var = f;

   if (SUCCEEDED(VariantChangeType(&var, &var, 0, VT_BSTR)))
   {
      const WCHAR * const wzT = V_BSTR(&var);
      char tmp[256];
      WideCharToMultiByteNull(CP_ACP, 0, wzT, -1, tmp, 256, NULL, NULL);
      sz = tmp;
      VariantClear(&var);
   }
   else
      sz = "0.0"; //!! must this be somehow localized, i.e. . vs ,
}

void WideStrCopy(const WCHAR *wzin, WCHAR *wzout)
{
   while (*wzin) { *wzout++ = *wzin++; }
   *wzout = 0;
}

void WideStrNCopy(const WCHAR *wzin, WCHAR *wzout, const DWORD wzoutMaxLen)
{
   DWORD i = 0;
   while (*wzin && (i < wzoutMaxLen - 1)) { *wzout++ = *wzin++; i++; }
   *wzout = 0;
}

void WideStrCat(const WCHAR *wzin, WCHAR *wzout)
{
   wzout += lstrlenW(wzout);
   while (*wzin) { *wzout++ = *wzin++; }
   *wzout = 0;
}

int WideStrCmp(const WCHAR *wz1, const WCHAR *wz2)
{
   while (*wz1 != L'\0')
   {
      if (*wz1 != *wz2)
      {
         if (*wz1 > *wz2)
         {
            return 1; // If *wz2 == 0, then wz1 will return as higher, which is correct
         }
         else if (*wz1 < *wz2)
         {
            return -1;
         }
      }
      wz1++;
      wz2++;
   }
   if (*wz2 != L'\0')
   {
      return -1; // wz2 is longer - and therefore higher
   }
   return 0;
}

int WzSzStrCmp(const WCHAR *wz1, const char *sz2)
{
   while (*wz1 != L'\0')
   {
      if (*wz1++ != *sz2++)
      {
         return 1;
      }
   }
   if (*sz2 != L'\0')
   {
      return 1;
   }
   return 0;
}

int WzSzStrnCmp(const WCHAR *wz1, const char *sz2, const int count)
{
   int i = 0;

   while (*wz1 != L'\0' && i < count)
   {
      if (*wz1++ != *sz2++)
      {
         return 1;
      }
      i++;
   }
   if (*sz2 != L'\0')
   {
      return 1;
   }
   return 0;
}

LocalString::LocalString(const int resid)
{
   if (resid > 0)
      /*const int cchar =*/ LoadString(g_pvp->theInstance, resid, m_szbuffer, sizeof(m_szbuffer));
   else
      m_szbuffer[0] = 0;
}

LocalStringW::LocalStringW(const int resid)
{
   if (resid > 0)
      LoadStringW(g_pvp->theInstance, resid, m_szbuffer, sizeof(m_szbuffer)/sizeof(WCHAR));
   else
      m_szbuffer[0] = 0;
}

WCHAR *MakeWide(const string& sz)
{
   const int len = (int)sz.length()+1;
   WCHAR * const wzT = new WCHAR[len];
   MultiByteToWideCharNull(CP_ACP, 0, sz.c_str(), -1, wzT, len);

   return wzT;
}

char *MakeChar(const WCHAR * const wz)
{
   const int len = lstrlenW(wz);
   char * const szT = new char[len + 1];
   WideCharToMultiByteNull(CP_ACP, 0, wz, -1, szT, len + 1, NULL, NULL);

   return szT;
}

HRESULT OpenURL(const string& szURL)
{
   IUniformResourceLocator* pURL;

   HRESULT hres = CoCreateInstance(CLSID_InternetShortcut, NULL, CLSCTX_INPROC_SERVER, IID_IUniformResourceLocator, (void**)&pURL);
   if (!SUCCEEDED(hres))
   {
      return hres;
   }

   hres = pURL->SetURL(szURL.c_str(), IURL_SETURL_FL_GUESS_PROTOCOL);

   if (!SUCCEEDED(hres))
   {
      pURL->Release();
      return hres;
   }

   //Open the URL by calling InvokeCommand
   URLINVOKECOMMANDINFO ivci;
   ivci.dwcbSize = sizeof(URLINVOKECOMMANDINFO);
   ivci.dwFlags = IURL_INVOKECOMMAND_FL_ALLOW_UI;
   ivci.hwndParent = g_pvp->GetHwnd();
   ivci.pcszVerb = "open";
   hres = pURL->InvokeCommand(&ivci);
   pURL->Release();
   return (hres);
}

char* replace(const char* const original, const char* const pattern, const char* const replacement)
{
  const size_t replen = strlen(replacement);
  const size_t patlen = strlen(pattern);
  const size_t orilen = strlen(original);

  size_t patcnt = 0;
  const char * patloc;

  // find how many times the pattern occurs in the original string
  for (const char* oriptr = original; (patloc = strstr(oriptr, pattern)); oriptr = patloc + patlen)
    patcnt++;

  {
    // allocate memory for the new string
    const size_t retlen = orilen + patcnt * (replen - patlen);
    char * const returned = new char[retlen + 1];

    //if (returned != NULL)
    {
      // copy the original string, 
      // replacing all the instances of the pattern
      char * retptr = returned;
      const char* oriptr;
      for (oriptr = original; (patloc = strstr(oriptr, pattern)); oriptr = patloc + patlen)
      {
        const size_t skplen = patloc - oriptr;
        // copy the section until the occurence of the pattern
        strncpy(retptr, oriptr, skplen);
        retptr += skplen;
        // copy the replacement 
        strncpy(retptr, replacement, replen);
        retptr += replen;
      }
      // copy the rest of the string.
      strcpy(retptr, oriptr);
    }
    return returned;
  }
}
