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

#include <cstring>
#include "Ram.h"

/*************************************************************************************************/
CRam::CRam(CBus *bus) {
	memset(mRam, 0, 65536);
	memset(mRam + 0x2000, 0xFF, 0x1000); // Simulates dirty on the screen
	memset(mRam + 0xA000, 0xFF, 0x1000); // Simulates dirty on the screen
	bus->addDevice(0x0000, 0xBFFF, this);
}

/*************************************************************************************************/
CRam::~CRam() {
}

/*************************************************************************************************/
byte CRam::read(word addr) {
	return mRam[addr];
}

/*************************************************************************************************/
void CRam::write(word addr, byte data) {
	mRam[addr] = data;
}
