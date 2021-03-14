// fsutils.h
//
// Copyright (C) 2001-present, the Celestia Development Team
// Original version by Chris Laurel <claurel@shatters.net>
//
// Miscellaneous useful filesystem-related functions.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

#include <config.h>
#include <fmt/printf.h>
#include "gettext.h"
#ifdef _WIN32
#include <shlobj.h>
#include "winutil.h"
#else
#include <unistd.h>
#include <pwd.h>
#ifdef HAVE_WORDEXP
#include <wordexp.h>
#endif // HAVE_WORDEXP
#endif // !_WIN32
#include "fsutils.h"

using namespace std;

namespace celestia
{
namespace util
{

fs::path LocaleFilename(const fs::path &p)
{
    fs::path::string_type format, lang;
#ifdef _WIN32
    format = L"%s_%s%s";
    lang = CurrentCPToWide(_("LANGUAGE"));
#else
    format = "%s_%s%s";
    lang = _("LANGUAGE");
#endif
    fs::path locPath = p.parent_path() / fmt::sprintf(format, p.stem().native(), lang, p.extension().native());

    if (fs::exists(locPath))
        return locPath;

    locPath = fs::path("locale") / locPath;
    if (fs::exists(locPath))
        return locPath;

    return p;
}


fs::path PathExp(const fs::path& filename)
{
#ifdef _WIN32
    auto str = filename.native();
    if (str[0] == '~')
    {
        if (str.size() == 1)
            return HomeDir();
        if (str[1] == '\\' || str[1] == '/')
            return HomeDir() / str.substr(2);
    }

    return filename;
#elif defined(HAVE_WORDEXP)
    wordexp_t result;

    switch(wordexp(filename.c_str(), &result, WRDE_NOCMD))
    {
    case 0: // successful
        break;
    case WRDE_NOSPACE:
        // If the error was `WRDE_NOSPACE',
        // then perhaps part of the result was allocated.
        wordfree(&result);
    default: // some other error
        return filename;
    }

    if (result.we_wordc != 1)
    {
        wordfree(&result);
        return filename;
    }

    fs::path::string_type expanded(result.we_wordv[0]);
    wordfree(&result);
    return expanded;
#else
    return filename;
#endif
}

fs::path HomeDir()
{
#ifdef _WIN32
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY != WINAPI_FAMILY_APP)
    wstring p(MAX_PATH + 1, 0);
    if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_PROFILE, nullptr, 0, &p[0])))
        return fs::path(p);

    // fallback to environment variables
    const auto *s = _wgetenv(L"USERPROFILE"); // FIXME: rewrite using _wgetenv_s
    if (s != nullptr)
        return fs::path(s);

    auto *s1 = _wgetenv(L"HOMEDRIVE");
    auto *s2 = _wgetenv(L"HOMEPATH");
    if (s1 != nullptr && s2 != nullptr)
    {
        return fs::path(s1) / fs::path(s2);
    }

    // unlikely this is defined in woe but let's check
    s = _wgetenv(L"HOME");
    if (s != nullptr)
        return fs::path(s);
#endif
#else
    const auto *home = getenv("HOME");
    if (home != nullptr)
        return home;

    // FIXME: rewrite using getpwuid_r
    struct passwd *pw = getpwuid(geteuid());
    home = pw->pw_dir;
    if (home != nullptr)
        return home;
#endif

    return fs::path();
}

fs::path WriteableDataPath()
{
#ifdef _WIN32
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP)
    return "";
#else
    char s[MAX_PATH + 1];
    if (SUCCEEDED(SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, &s[0])))
        return PathExp(s) / "Celestia";

    // fallback to environment variables
    const char *p = getenv("APPDATA");
    p = p != nullptr ? p : "~\\AppData\\Roaming";
    return PathExp(p) / "Celestia";
#endif
#elif defined(__APPLE__)
    return PathExp("~/Library/Application Support/Celestia");

#else
    const char *p = getenv("XDG_DATA_HOME");
    p = p != nullptr ? p : "~/.local/share";
    return PathExp(p) / "Celestia";
#endif
}

}
}
