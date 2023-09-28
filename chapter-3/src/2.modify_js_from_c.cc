#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/libplatform/libplatform.h"
#include "include/v8-context.h"
#include "include/v8-initialization.h"
#include "include/v8-isolate.h"
#include "include/v8-local-handle.h"
#include "include/v8-primitive.h"
#include "include/v8-script.h"

int main(int argc, char* argv[]) {
  v8::V8::InitializeICUDefaultLocation(argv[0]);
  v8::V8::InitializeExternalStartupData(argv[0]);
  std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
  v8::V8::InitializePlatform(platform.get());
  v8::V8::Initialize();

  v8::Isolate::CreateParams create_params;
  create_params.array_buffer_allocator =
      v8::ArrayBuffer::Allocator::NewDefaultAllocator();
  v8::Isolate* isolate = v8::Isolate::New(create_params);
  {
    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope handle_scope(isolate);
    v8::Local<v8::Context> context = v8::Context::New(isolate);
    v8::Context::Scope context_scope(context);

    /** 
    --------------------------------
      here comes our code    
    --------------------------------
    */

    // Define and initialize a JavaScript variable
    v8::Local<v8::String> source = v8::String::NewFromUtf8Literal(isolate, "var myVar = 'We are getting something interesting here';");
    v8::Local<v8::Script> script = v8::Script::Compile(context, source).ToLocalChecked();
    script->Run(context).ToLocalChecked();

    // Access JavaScript variable from C++
    v8::Local<v8::String> variable_name = v8::String::NewFromUtf8(isolate, "myVar", v8::NewStringType::kNormal).ToLocalChecked();
    v8::Local<v8::Value> js_variable = context->Global()->Get(context, variable_name).ToLocalChecked();
    v8::String::Utf8Value utf8(isolate, js_variable);
    std::string value = std::string(*utf8);

    std::cout << "Value from JavaScript: " << value << std::endl;

    // Modify the JavaScript variable from C++
    v8::Local<v8::String> new_value = v8::String::NewFromUtf8Literal(isolate, "New value from C++");
    context->Global()->Set(context, variable_name, new_value).FromJust();

    // Re-access the modified JavaScript variable
    js_variable = context->Global()->Get(context, variable_name).ToLocalChecked();
    v8::String::Utf8Value new_utf8(isolate, js_variable);
    std::string new_value_str = std::string(*new_utf8);

    std::cout << "Modified value from JavaScript: " << new_value_str << std::endl;

    /** 
    --------------------------------
      end of our code
    --------------------------------
    */
  }

  isolate->Dispose();
  v8::V8::Dispose();
  v8::V8::DisposePlatform();
  delete create_params.array_buffer_allocator;
  return 0;
}