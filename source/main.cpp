#include <stdarg.h>
#include <iostream>
#include <chrono>
#include "RuntimeObjectSystem/RuntimeObjectSystem.h"
#include "RuntimeCompiler/ICompilerLogger.h"


const size_t LOGSYSTEM_MAX_BUFFER = 4096;
class StdioLogSystem : public ICompilerLogger
{
  public:
    virtual void LogError(const char * format, ...) {
      va_list args;
      va_start(args, format);
      LogInternal(stderr, format, args);
    }
    virtual void LogWarning(const char * format, ...) {
      va_list args;
      va_start(args, format);
      LogInternal(stderr, format, args);
    }
    virtual void LogInfo(const char * format, ...) {
      va_list args;
      va_start(args, format);
      LogInternal(stdout, format, args);
    }
    virtual void LogDebug(const char * format, ...) {
      va_list args;
      va_start(args, format);
      LogInternal(stdout, format, args);
    }
  protected:
    void LogInternal(FILE *out, const char * format, va_list args) {
      int result = vsnprintf(m_buff, LOGSYSTEM_MAX_BUFFER-1, format, args);
      // Make sure there's a limit to the amount of rubbish we can output
      m_buff[LOGSYSTEM_MAX_BUFFER-1] = '\0';
      fprintf(out, "%s", m_buff);
#     ifdef _WIN32
        OutputDebugStringA( m_buff );
#     endif
    }
    char m_buff[LOGSYSTEM_MAX_BUFFER];
};


int main(int argc, char **argv) {

  auto prevTime = std::chrono::high_resolution_clock::now();

  RuntimeObjectSystem objectFactory;
  objectFactory.Initialise(new StdioLogSystem(), nullptr);
  auto constructor = objectFactory.GetObjectFactorySystem()->GetConstructor("MyObject");
  MyObjectInterface *myObject = nullptr;
  if (constructor) {
    IObject *obj = constructor->construct();
    if (obj && obj->GetInterface(MyObjectInterfaceID)) {
      myObject = static_cast<MyObjectInterface *>(obj);
    }
  }

  while (true) {
    auto currTime = std::chrono::high_resolution_clock::now();
    float delta = (currTime - prevTime).count();
    prevTime = currTime;

    myObject->RunVirtualFunction();

    if (delta > 0.01) {
      continue;
    }
    if (objectFactory.GetIsCompiledComplete()) {
      objectFactory.LoadCompiledModule();
    }
    if (objectFactory.GetIsCompiling()) {
      return true;
    } else {
      objectFactory.GetFileChangeNotifier()->Update(delta);
    }
  }


//  char input;
//  do {
//    std::cout << "enter char (q to quit):" << std::endl;
//    std::cin >> input;
//  } while (input != 'q');

  return 0;
}
