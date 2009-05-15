#ifndef __CLASSHANDLER_H
#define __CLASHANDLER_H

#include "include/types.h"
#include "include/ClassLibrary.h"

#include "objclass/objclass.h"

#include "common/Cond.h"


class OSD;


class ClassHandler
{
  OSD *osd;

public:
  class ClassData;

  struct ClassMethod {
    struct ClassHandler::ClassData *cls;
    string name;
    cls_method_call_t func;

    void unregister();
  };

  struct ClassData {
    enum { 
      CLASS_UNKNOWN, 
      //CLASS_UNLOADED, 
      CLASS_LOADED, 
      CLASS_REQUESTED, 
      //CLASS_ERROR
    } status;
    version_t version;
    ClassImpl impl;
    void *handle;
    bool registered;
    map<string, ClassMethod> methods_map;

    ClassData() : status(CLASS_UNKNOWN), version(-1), handle(NULL), registered(false) {}
    ~ClassData() { }

    ClassMethod *register_method(const char *mname,
                          cls_method_call_t func);
    void unregister_method(ClassMethod *method);
  };
  map<nstring, ClassData> classes;

  void load_class(const nstring& cname);

  ClassHandler(OSD *_osd) : osd(_osd) {}

  bool get_class(const nstring& cname);
  void resend_class_requests();

  void handle_class(MClass *m);

  ClassData *register_class(const char *cname);
  void unregister_class(ClassData *cls);

};


#endif
