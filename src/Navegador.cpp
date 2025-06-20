#include "../include/Navegador.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <cstdint>

#ifdef _WIN32
#include <windows.h>
#include <tlhelp32.h>
#include <shellapi.h>
#elif __APPLE__
#include <CoreFoundation/CFBundle.h>
#include <ApplicationServices/ApplicationServices.h>
#include <sys/sysctl.h>
#else
// Linux y otros sistemas Unix
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <filesystem>
#endif

bool Navegador::estaNavegadorAbierto()
{
#ifdef _WIN32
    // Lista de procesos de navegadores comunes en Windows
    const std::vector<std::wstring> navegadores = {
        L"chrome.exe", L"firefox.exe", L"msedge.exe",
        L"iexplore.exe", L"opera.exe", L"brave.exe"};

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return false;

    PROCESSENTRY32W pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(hSnapshot, &pe32))
    {
        CloseHandle(hSnapshot);
        return false;
    }

    bool encontrado = false;
    do
    {
        for (const auto &nav : navegadores)
        {
            if (nav == pe32.szExeFile)
            {
                encontrado = true;
                break;
            }
        }
    } while (Process32NextW(hSnapshot, &pe32) && !encontrado);

    CloseHandle(hSnapshot);
    return encontrado;

#elif __APPLE__
    // Lista de identificadores de navegadores en macOS
    const std::vector<std::string> navegadores = {
        "com.apple.Safari", "com.google.Chrome",
        "org.mozilla.firefox", "com.operasoftware.Opera"};

    // Obtener todos los procesos en ejecución
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
    size_t size;
    sysctl(mib, 4, NULL, &size, NULL, 0);

    struct kinfo_proc *processes = (struct kinfo_proc *)malloc(size);
    sysctl(mib, 4, processes, &size, NULL, 0);

    int count = size / sizeof(struct kinfo_proc);
    bool encontrado = false;

    for (int i = 0; i < count; i++)
    {
        pid_t pid = processes[i].kp_proc.p_pid;
        char path[PROC_PIDPATHINFO_MAXSIZE];
        proc_pidpath(pid, path, sizeof(path));

        if (path[0] != '\0')
        {
            std::string processPath(path);
            for (const auto &nav : navegadores)
            {
                if (processPath.find(nav) != std::string::npos)
                {
                    encontrado = true;
                    break;
                }
            }
            if (encontrado)
                break;
        }
    }

    free(processes);
    return encontrado;

#else
    // Linux: verificar procesos mediante /proc
    for (const auto &entry : std::filesystem::directory_iterator("/proc"))
    {
        if (!entry.is_directory())
            continue;

        std::string pid = entry.path().filename();
        if (!std::all_of(pid.begin(), pid.end(), ::isdigit))
            continue;

        std::ifstream cmdlineFile(entry.path() / "cmdline");
        if (!cmdlineFile)
            continue;

        std::string cmdline;
        std::getline(cmdlineFile, cmdline);

        // Lista de navegadores comunes en Linux
        const std::vector<std::string> navegadores = {
            "chrome", "firefox", "brave", "opera", "vivaldi", "chromium"};

        for (const auto &nav : navegadores)
        {
            if (cmdline.find(nav) != std::string::npos)
            {
                return true;
            }
        }
    }
    return false;
#endif
}

bool Navegador::abrirURL(const std::string &url)
{
#ifdef _WIN32
    HINSTANCE result = ShellExecuteA(
        NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
    return reinterpret_cast<intptr_t>(result) > 32;

#elif __APPLE__
    CFURLRef cfUrl = CFURLCreateWithBytes(
        NULL, (UInt8 *)url.c_str(), url.length(),
        kCFStringEncodingUTF8, NULL);

    if (cfUrl)
    {
        LSOpenCFURLRef(cfUrl, NULL);
        CFRelease(cfUrl);
        return true;
    }
    return false;

#else
    std::string command = "xdg-open \"" + url + "\"";
    return system(command.c_str()) == 0;
#endif
}

bool Navegador::abrirURLNuevaPestana(const std::string &url)
{
#ifdef _WIN32
    // Windows usa el mismo comando para nueva pestaña
    return abrirURL(url);

#elif __APPLE__
    // macOS: intentar con AppleScript para abrir en nueva pestaña
    std::string script = "osascript -e 'tell application \"Safari\" to make new tab at end of tabs of front window with properties {URL:\"" +
                         url + "\"}'";
    if (system(script.c_str()) == 0)
        return true;

    // Fallback a método normal
    return abrirURL(url);

#else
    // Linux: intentar con comandos específicos para nueva pestaña
    const char *browser = std::getenv("BROWSER");
    if (browser)
    {
        std::string command = browser;
        if (command.find("chrome") != std::string::npos)
        {
            command += " --new-tab \"" + url + "\"";
        }
        else if (command.find("firefox") != std::string::npos)
        {
            command += " -new-tab \"" + url + "\"";
        }
        else
        {
            command += " \"" + url + "\"";
        }
        return system(command.c_str()) == 0;
    }

    // Intento con navegadores específicos
    const std::vector<std::pair<std::string, std::string>> navegadores = {
        {"google-chrome", " --new-tab"},
        {"chromium-browser", " --new-tab"},
        {"firefox", " -new-tab"},
        {"opera", " --new-tab"},
        {"brave-browser", " --new-tab"}};

    for (const auto &[nav, arg] : navegadores)
    {
        std::string command = nav + arg + " \"" + url + "\"";
        if (system(("command -v " + nav + " >/dev/null 2>&1").c_str()) == 0)
        {
            return system(command.c_str()) == 0;
        }
    }

    // Fallback a método normal
    return abrirURL(url);
#endif
}

bool Navegador::abrirURLOptimo(const std::string &url)
{
    if (estaNavegadorAbierto())
    {
        return abrirURLNuevaPestana(url);
    }
    else
    {
        return abrirURL(url);
    }
}