#pragma once
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class RomHeader {
private:
  std::array<uint8_t, 4> entry;
  std::array<uint8_t, 48> logo;
  std::string title;

  uint16_t newLicCode;
  uint8_t sgbFlag;
  uint8_t type;
  uint8_t romSize;
  uint8_t ramSize;
  uint8_t destCode;
  uint8_t licCode;
  uint8_t version;
  uint8_t checksum;
  uint16_t globalChecksum;

public:
  // Constructors
  RomHeader();

  // Entry
  const std::array<uint8_t, 4> &getEntry() const;
  void setEntry(const std::array<uint8_t, 4> &e);

  // Logo
  const std::array<uint8_t, 48> &getLogo() const;
  void setLogo(const std::array<uint8_t, 48> &l);

  // Title
  const std::string &getTitle() const;
  void setTitle(const std::string &t);

  // New License Code
  uint16_t getNewLicCode() const;
  void setNewLicCode(uint16_t code);

  // SGB Flag
  uint8_t getSgbFlag() const;
  void setSgbFlag(uint8_t flag);

  // Type
  uint8_t getType() const;
  void setType(uint8_t t);

  // ROM Size
  uint8_t getRomSize() const;
  void setRomSize(uint8_t size);

  // RAM Size
  uint8_t getRamSize() const;
  void setRamSize(uint8_t size);

  // Destination Code
  uint8_t getDestCode() const;
  void setDestCode(uint8_t code);

  // License Code
  uint8_t getLicCode() const;
  void setLicCode(uint8_t code);

  // Version
  uint8_t getVersion() const;
  void setVersion(uint8_t v);

  // Checksum
  uint8_t getChecksum() const;
  void setChecksum(uint8_t cksum);

  // Global Checksum
  uint16_t getGlobalChecksum() const;
  void setGlobalChecksum(uint16_t cksum);
  std::string_view getCartTypeString();

  std::string_view getLicCodeString();
};

class Cart {
private:
  std::string filename;
  std::vector<uint8_t> romData;
  std::unique_ptr<RomHeader> header;

public:
  const std::string &getFilename() const { return filename; }
  void setFilename(const std::string &fname) { filename = fname; }
  void cart_write(uint16_t address, uint8_t value);
  uint8_t cart_read(uint16_t address);
  const std::vector<uint8_t> &getRomData() const { return romData; }
  void setRomData(std::vector<uint8_t> &&data) {
    romData = std::move(data);
    parseHeader();
  }

  bool load_cart(std::string cart);

  const RomHeader *getHeader() const { return header.get(); }

private:
  void parseHeader();
};
