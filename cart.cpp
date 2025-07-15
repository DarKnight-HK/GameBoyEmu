#include "cart.h"

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
