#include "cart.h"
#include "constants.h"
#include <cstdint>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>

// Constructor

RomHeader::RomHeader()
    : newLicCode(0), sgbFlag(0), type(0), romSize(0), ramSize(0), destCode(0),
      licCode(0), version(0), checksum(0), globalChecksum(0), title("") {
  entry.fill(0);
  logo.fill(0);
}

// Entry
const std::array<uint8_t, 4> &RomHeader::getEntry() const { return entry; }
void RomHeader::setEntry(const std::array<uint8_t, 4> &e) { entry = e; }

// Logo
const std::array<uint8_t, 48> &RomHeader::getLogo() const { return logo; }
void RomHeader::setLogo(const std::array<uint8_t, 48> &l) { logo = l; }

// Title
const std::string &RomHeader::getTitle() const { return title; }
void RomHeader::setTitle(const std::string &t) {
  if (t.size() <= 16) {
    title = t;
  } else {
    title = t.substr(0, 16);
  }
}

// New License Code
uint16_t RomHeader::getNewLicCode() const { return newLicCode; }
void RomHeader::setNewLicCode(uint16_t code) { newLicCode = code; }

// SGB Flag
uint8_t RomHeader::getSgbFlag() const { return sgbFlag; }
void RomHeader::setSgbFlag(uint8_t flag) { sgbFlag = flag; }

// Type
uint8_t RomHeader::getType() const { return type; }
void RomHeader::setType(uint8_t t) { type = t; }

// ROM Size
uint8_t RomHeader::getRomSize() const { return romSize; }
void RomHeader::setRomSize(uint8_t size) { romSize = size; }

// RAM Size
uint8_t RomHeader::getRamSize() const { return ramSize; }
void RomHeader::setRamSize(uint8_t size) { ramSize = size; }

// Destination Code
uint8_t RomHeader::getDestCode() const { return destCode; }
void RomHeader::setDestCode(uint8_t code) { destCode = code; }

// License Code
uint8_t RomHeader::getLicCode() const { return licCode; }
void RomHeader::setLicCode(uint8_t code) { licCode = code; }

// Version
uint8_t RomHeader::getVersion() const { return version; }
void RomHeader::setVersion(uint8_t v) { version = v; }

// Checksum
uint8_t RomHeader::getChecksum() const { return checksum; }
void RomHeader::setChecksum(uint8_t cksum) { checksum = cksum; }

// Global Checksum
uint16_t RomHeader::getGlobalChecksum() const { return globalChecksum; }
void RomHeader::setGlobalChecksum(uint16_t cksum) { globalChecksum = cksum; }

///////////////////////////////Cart//////////////////////////////////////////

// Constructer
Cart::Cart(const std::string &fname, std::vector<uint8_t> &&data)
    : filename(fname), romData(std::move(data)) {
  parseHeader();
}

// Parse Header

void Cart::parseHeader() {
  if (romData.size() >= 0x150) {
    header = std::make_unique<RomHeader>();

    // Manually parse each field
    // Entry (4 bytes) - from 0x100 to 0x103
    std::array<uint8_t, 4> entryData;
    std::memcpy(entryData.data(), romData.data() + 0x100, 4);
    header->setEntry(entryData);

    // Logo (48 bytes) - from 0x104 to 0x133
    std::array<uint8_t, 48> logoData;
    std::memcpy(logoData.data(), romData.data() + 0x104, 48);
    header->setLogo(logoData);

    // Title (16 bytes) - from 0x134 to 0x143
    // Note: Title can be less than 16 bytes and null-terminated
    char titleBuffer[16];
    std::memcpy(titleBuffer, romData.data() + 0x134, 16);
    header->setTitle(std::string(titleBuffer, strnlen(titleBuffer, 16)));

    // New License Code (2 bytes) - from 0x144 to 0x145
    header->setNewLicCode(
        *reinterpret_cast<const uint16_t *>(romData.data() + 0x144));

    // SGB Flag (1 byte) - 0x146
    header->setSgbFlag(*(romData.data() + 0x146));

    // Type (1 byte) - 0x147
    header->setType(*(romData.data() + 0x147));

    // ROM Size (1 byte) - 0x148
    header->setRomSize(*(romData.data() + 0x148));

    // RAM Size (1 byte) - 0x149
    header->setRamSize(*(romData.data() + 0x149));

    // Destination Code (1 byte) - 0x14A
    header->setDestCode(*(romData.data() + 0x14A));

    // Old License Code (1 byte) - 0x14B
    header->setLicCode(*(romData.data() + 0x14B));

    // Version (1 byte) - 0x14C
    header->setVersion(*(romData.data() + 0x14C));

    // Checksum (1 byte) - 0x14D
    header->setChecksum(*(romData.data() + 0x14D));

    // Global Checksum (2 bytes) - from 0x14E to 0x14F
    header->setGlobalChecksum(
        *reinterpret_cast<const uint16_t *>(romData.data() + 0x14E));
  }
}

std::string_view RomHeader::getCartTypeString() {
  if (type <= 0x22) {
    return GameboyConstants::ROM_TYPES[type];
  }
  return "UNKNOWN";
}

std::string_view RomHeader::getLicCodeString() {
  auto it = GameboyConstants::LIC_CODE.find(licCode);
  if (it != GameboyConstants::LIC_CODE.end()) {
    return it->second;
  }
  return "UNKNOWN";
}

bool Cart::load_cart(std::string cart) {
  this->filename = cart;

  std::ifstream file(cart, std::ios::binary | std::ios::ate);

  if (!file.is_open()) {
    std::cerr << "No such file found" << std::endl;
    return false;
  }

  std::cout << "[+] Opened " << this->filename << std::endl;
  // Read the file size as the pointer is at the end
  std::streamsize size = file.tellg();
  // Set the pointer to the beginning
  file.seekg(0, std::ios::beg);

  this->romData.resize(size);
  // Convert the binary data to vector<uint8_t>
  file.read(reinterpret_cast<char *>(this->romData.data()), size);
  parseHeader();

  std::cout << "Cartridge Loaded\n";
  std::cout << "Title    : " << this->header->getTitle();
  std::cout << "Type     : " << this->header->getCartTypeString();
  std::cout << "ROM Size : " << this->header->getRomSize();
  std::cout << "RAM Size : " << this->header->getRamSize();
  std::cout << "LIC Code : " << this->header->getLicCodeString();
  std::cout << "ROM Vers : " << this->header->getVersion();

  uint16_t x = 0;
  for (uint16_t i = 0x0134; i <= 0x014C; i++) {
    x = x - this->romData[i] - 1;
  }

  std::cout << "Checksum : " << this->header->getChecksum() << "\n";
  (x & 0xFF) ? std::cout << "PASSED" : std::cout << "FAILED";
  std::cout << std::endl;

  return true;
}
