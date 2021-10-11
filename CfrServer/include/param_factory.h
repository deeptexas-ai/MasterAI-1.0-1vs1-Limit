#ifndef _PARAMS_FACTORY_H_
#define _PARAMS_FACTORY_H_

#include <memory>
#include <string>
#include <vector>

enum ParamType {
  P_STRING,
  P_INT,
  P_DOUBLE,
  P_BOOLEAN
};

struct ParamValue {
  bool set;
  std::string s;
  int i;
  double d;
};

class Params {
public:
  Params(void);
  ~Params(void);
  void AddParam(const std::string &name, ParamType ptype);
  void ReadFromFile(const char *filename);
  bool IsSet(const char *name) const;
  std::string GetStringValue(const char *name) const;
  int GetIntValue(const char *name) const;
  double GetDoubleValue(const char *name) const;
  bool GetBooleanValue(const char *name) const;
  void SetIntValue(const char *name,int val);
private:
  int GetParamIndex(const char *name) const;
  void SetStringValue(const char *name,const std::string &val);

  std::vector<std::string> param_names_;
  std::vector<ParamType> param_types_;
  std::vector<ParamValue> param_values_;
};



class ParamsFactory
{
public:
    static std::unique_ptr<Params> CreateCardAbstractionParams(void);
    static std::unique_ptr<Params> CreateGameParams(void);
    static std::unique_ptr<Params> CreateBettingAbstractionParams(void);
    static std::unique_ptr<Params> CreateCFRParams(void);
private:
    ParamsFactory(/* args */){}
    ~ParamsFactory(){}
};




#endif