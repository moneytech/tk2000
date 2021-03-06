// Copyright (c) 2020 FBLabs
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "pch.h"
#include "Bus.h"
#include "Cpu6502.h"


/*************************************************************************************************/
CBus::CBus() {
	for (int i = 0; i < 0x10000; i++) {
		mDevices[i][0] = nullptr;
		mDevices[i][1] = nullptr;
	}
}

/*************************************************************************************************/
CBus::~CBus() {

}

/*************************************************************************************************/
byte CBus::readByte(const word addr) {
	if (mDevices[addr][0] == nullptr) {
		return 0xFF;
	}
	byte result = mDevices[addr][0]->read(addr);
	if (mDevices[addr][1] != nullptr) {
		result |= mDevices[addr][1]->read(addr);
	}
	return result;
}

/*************************************************************************************************/
void CBus::writeByte(const word addr, const byte data) {
	if (mDevices[addr][0] != nullptr) {
		mDevices[addr][0]->write(addr, data);
	}
	if (mDevices[addr][1] != nullptr) {
		mDevices[addr][1]->write(addr, data);
	}
}

/*************************************************************************************************/
word CBus::readWord(const word addr) {
	return readByte(addr) | readByte(addr + 1) << 8;
}

/*************************************************************************************************/
void CBus::writeWord(const word addr, const word data) {
	writeByte(addr, data & 0xFF);
	writeByte(addr + 1, data >> 8);
}

/*************************************************************************************************/
void CBus::addDevice(const char* name, CDevice *dev) {
	assert(name != nullptr);
	assert(dev != nullptr);
	mMapDevices.emplace(name, dev);
}

/*************************************************************************************************/
CDevice* CBus::getDevice(const char* name) {
	return mMapDevices[name];
}

/*************************************************************************************************/
void CBus::registerAddr(const char* name, const word addr) {
	assert(name != nullptr);
	if (mDevices[addr][0] == nullptr) {
		mDevices[addr][0] = mMapDevices[name];
	} else {
		mDevices[addr][1] = mMapDevices[name];
	}
}

/*************************************************************************************************/
void CBus::registerAddr(const char* name, const word addrStart, const word addrEnd) {
	assert(name != nullptr);
	assert(addrEnd >= addrStart);
	for (int i = addrStart; i <= addrEnd; i++) {
		if (mDevices[i][0] == nullptr) {
			mDevices[i][0] = mMapDevices[name];
		} else {
			mDevices[i][1] = mMapDevices[name];
		}
	}
}

/*************************************************************************************************/
void CBus::resetAll() {
	for (auto& dev : mMapDevices) {
		dev.second->reset();
	}
}

/*************************************************************************************************/
void CBus::updateAll() {
	for (auto& dev : mMapDevices) {
		dev.second->update();
	}
}
