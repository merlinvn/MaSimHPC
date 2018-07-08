#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <utility>
#include <yaml-cpp/yaml.h>

class IConfigItem {
public:
  IConfigItem() = default;
  virtual ~IConfigItem() = default;
  IConfigItem(const IConfigItem&) = delete;
  IConfigItem& operator=(const IConfigItem&) = delete;
  IConfigItem(IConfigItem&&) = delete;
  IConfigItem& operator=(IConfigItem&&) = delete;
  virtual const std::string& name() = 0;
  virtual void set_value(const YAML::Node& node) = 0;
};

template <typename T>
class ConfigItem : public IConfigItem {
protected:
  std::string name_;
  T value_{};
public:
  //constructor
  explicit ConfigItem(std::string name, const T& default_value) : name_{std::move(name)}, value_(default_value) {}
  // ConfigItem() {
  //   std::cout << "base class constructor" << std::endl;
  // }

  // destructor
  virtual ~ConfigItem() = default;
  // virtual ~ConfigItem() {
  //   std::cout << "base class destructor" << std::endl;
  // };

  // copy constructor
  ConfigItem(const ConfigItem&) = delete;

  // copy assignment
  ConfigItem& operator=(const ConfigItem&) = delete;

  // move constructor
  ConfigItem(ConfigItem&&) = delete;

  // move assignment
  ConfigItem& operator=(ConfigItem&&) = delete;

  virtual T& operator()() {
    return value_;
  };


  void set_value(const YAML::Node& node) override {
    if (node[name_]) {
      value_ = node[name_].as<T>();
    }
    else {
      std::cout << name_ << " has default value of " << value_ << std::endl;
    }
  }

  const std::string& name() override {
    return name_;
  }
};


class Config {
  std::vector<IConfigItem*> config_items_;

public:
  ConfigItem<int> total_time{"total_time", 1000};
  ConfigItem<int> number_of_location{"number_of_location", 10};

  Config() {
    config_items_.push_back(&total_time);
    config_items_.push_back(&number_of_location);
  }

  void read_from_file(const std::string& filename);
};

inline void Config::read_from_file(const std::string& filename) {
  YAML::Node config;
  try {
    config = YAML::LoadFile(filename);
  }
  catch (YAML::BadFile& ex) {
    //FATAL??
    std::cout << filename << " not found or err when reading file..." << std::endl;
  }
  catch (YAML::Exception& ex) {
    //FATAL
    std::cout << "error: " << ex.msg << " at line " << ex.mark.line + 1 << ":" << ex.mark.column + 1 << std::endl;
  }

  for (auto& config_item : config_items_) {
	  std::cout << config_item->name()<< std::endl;
    config_item->set_value(config);
  }
}

// inline int Config::total_time() const {
//   return 1000;
// }


#endif // CONFIG_H
