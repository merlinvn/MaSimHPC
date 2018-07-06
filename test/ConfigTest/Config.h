#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>

template <typename T>
class ConfigItem {
protected:
  T value_;
public:
  //constructor
  ConfigItem() = default;
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
  ConfigItem(ConfigItem&&) noexcept = delete;

  // move assignment
  ConfigItem& operator=(ConfigItem&&) = delete;

  virtual T& operator()() {
    return value_;
  };
};


class total_time : public ConfigItem<int> {
public:	

  virtual ~total_time() {
    std::cout << "total_time destructor" << std::endl;

  }

  total_time(const int& default_value = 1000) {
	  value_ = default_value;
  }
  
};


class Config {
public:
  total_time total_time;
};

// inline int Config::total_time() const {
//   return 1000;
// }


#endif // CONFIG_H
