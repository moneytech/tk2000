

#include "Keyboard.h"

/*
 *   TK2000 Keyboard Matrix
 *   ======================
 *
 *                         KBIN
 *             0   1   2   3   4   5
 *         0       B   V   C   X   Z
 *     K   1  SHFT G   F   D   S   A
 *     B   2  " "  T   R   E   W   Q
 *     O   3  LFT  5   4   3   2   1
 *     U   4  RGT  6   7   8   9   0
 *     T   5  DWN  Y   U   I   O   P
 *         6  UP   H   J   K   L   :
 *         7  RTN  N   M   ,   .   ?
*/


/*************************************************************************************************/
CKeyboard::CKeyboard(CBus *bus) {
	bus->addDevice(0xC000, 0xC01F, this);
	bus->addDevice(0xC05E, 0xC05F, this);
}

/*************************************************************************************************/
byte CKeyboard::read(word addr) {
	if (mKbOutCtrl) {
		return (mCtrl ? 1 : 0);
	} else if (mKbOut == 1 && mShift) {
		return 1;
	}
	byte result = 0;
	for (int l = 0; l < 8; l++) {
		if (mKbOut & (1 << l)) {
			result |= mMatrix[l];
		}
	}

	return result;
}

/*************************************************************************************************/
void CKeyboard::write(word addr, byte data) {
	if (addr == 0xC05E) {
		mKbOutCtrl = false;
		return;
	} else if (addr == 0xC05F) {
		mKbOutCtrl = true;
		return;
	}
	mKbOut = data;
}

/*************************************************************************************************/
void CKeyboard::update(unsigned long cycles) {

}

/*************************************************************************************************/
void CKeyboard::reset() {
	for (int i = 0; i < 8; i++) {
		mMatrix[i] = 0;
	}
	mCtrl = false;
	mShift = false;
}

/*************************************************************************************************/
void CKeyboard::processEvent(SDL_KeyboardEvent e) {

	if (e.repeat) {
		return;
	}
	mShift = e.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT);
	bool down = e.state == SDL_PRESSED;

	switch (e.keysym.sym){

	case SDLK_LCTRL:
	case SDLK_RCTRL:
		mCtrl = down;
		break;

	case SDLK_a:
		if (down) {
			mMatrix[1] |= 1 << 5;
		} else {
			mMatrix[1] &= ~(1 << 5);
		}
		return;

	case SDLK_b:
		if (down) {
			mMatrix[0] |= 1 << 1;
		} else {
			mMatrix[0] &= ~(1 << 1);
		}
		return;

	case SDLK_c:
		if (down) {
			mMatrix[0] |= 1 << 3;
		} else {
			mMatrix[0] &= ~(1 << 3);
		}
		return;

	case SDLK_d:
		if (down) {
			mMatrix[1] |= 1 << 3;
		} else {
			mMatrix[1] &= ~(1 << 3);
		}
		return;

	case SDLK_e:
		if (down) {
			mMatrix[2] |= 1 << 3;
		} else {
			mMatrix[2] &= ~(1 << 3);
		}
		return;

	case SDLK_f:
		if (down) {
			mMatrix[1] |= 1 << 2;
		} else {
			mMatrix[1] &= ~(1 << 2);
		}
		return;

	case SDLK_g:
		if (down) {
			mMatrix[1] |= 1 << 1;
		} else {
			mMatrix[1] &= ~(1 << 1);
		}
		return;

	case SDLK_h:
		if (down) {
			mMatrix[6] |= 1 << 1;
		} else {
			mMatrix[6] &= ~(1 << 1);
		}
		return;

	case SDLK_i:
		if (down) {
			mMatrix[5] |= 1 << 3;
		} else {
			mMatrix[5] &= ~(1 << 3);
		}
		return;

	case SDLK_j:
		if (down) {
			mMatrix[6] |= 1 << 2;
		} else {
			mMatrix[6] &= ~(1 << 2);
		}
		return;

	case SDLK_k:
		if (down) {
			mMatrix[6] |= 1 << 3;
		} else {
			mMatrix[6] &= ~(1 << 3);
		}
		return;

	case SDLK_l:
		if (down) {
			mMatrix[6] |= 1 << 4;
		} else {
			mMatrix[6] &= ~(1 << 4);
		}
		return;

	case SDLK_m:
		if (down) {
			mMatrix[7] |= 1 << 2;
		} else {
			mMatrix[7] &= ~(1 << 2);
		}
		return;

	case SDLK_n:
		if (down) {
			mMatrix[7] |= 1 << 1;
		} else {
			mMatrix[7] &= ~(1 << 1);
		}
		return;

	case SDLK_o:
		if (down) {
			mMatrix[5] |= 1 << 4;
		} else {
			mMatrix[5] &= ~(1 << 4);
		}
		return;

	case SDLK_p:
		if (down) {
			mMatrix[5] |= 1 << 5;
		} else {
			mMatrix[5] &= ~(1 << 5);
		}
		return;

	case SDLK_q:
		if (down) {
			mMatrix[2] |= 1 << 5;
		} else {
			mMatrix[2] &= ~(1 << 5);
		}
		return;

	case SDLK_r:
		if (down) {
			mMatrix[2] |= 1 << 2;
		} else {
			mMatrix[2] &= ~(1 << 2);
		}
		return;

	case SDLK_s:
		if (down) {
			mMatrix[1] |= 1 << 4;
		} else {
			mMatrix[1] &= ~(1 << 4);
		}
		return;

	case SDLK_t:
		if (down) {
			mMatrix[2] |= 1 << 1;
		} else {
			mMatrix[2] &= ~(1 << 1);
		}
		return;

	case SDLK_u:
		if (down) {
			mMatrix[5] |= 1 << 2;
		} else {
			mMatrix[5] &= ~(1 << 2);
		}
		return;

	case SDLK_v:
		if (down) {
			mMatrix[0] |= 1 << 2;
		} else {
			mMatrix[0] &= ~(1 << 2);
		}
		return;

	case SDLK_w:
		if (down) {
			mMatrix[2] |= 1 << 4;
		} else {
			mMatrix[2] &= ~(1 << 4);
		}
		return;

	case SDLK_x:
		if (down) {
			mMatrix[0] |= 1 << 4;
		} else {
			mMatrix[0] &= ~(1 << 4);
		}
		return;

	case SDLK_y:
		if (down) {
			mMatrix[5] |= 1 << 1;
		} else {
			mMatrix[5] &= ~(1 << 1);
		}
		return;

	case SDLK_z:
		if (down) {
			mMatrix[0] |= 1 << 5;
		} else {
			mMatrix[0] &= ~(1 << 5);
		}
		return;

	case SDLK_1:
	case SDLK_KP_1:
		if (down) {
			mMatrix[3] |= 1 << 5;
		} else {
			mMatrix[3] &= ~(1 << 5);
		}
		return;

	case SDLK_2:
	case SDLK_KP_2:
		if (down) {
			mMatrix[3] |= 1 << 4;
		} else {
			mMatrix[3] &= ~(1 << 4);
		}
		return;

	case SDLK_3:
	case SDLK_KP_3:
		if (down) {
			mMatrix[3] |= 1 << 3;
		} else {
			mMatrix[3] &= ~(1 << 3);
		}
		return;

	case SDLK_4:
	case SDLK_KP_4:
		if (down) {
			mMatrix[3] |= 1 << 2;
		} else {
			mMatrix[3] &= ~(1 << 2);
		}
		return;

	case SDLK_5:
	case SDLK_KP_5:
		if (down) {
			mMatrix[3] |= 1 << 1;
		} else {
			mMatrix[3] &= ~(1 << 1);
		}
		return;

	case SDLK_6:
	case SDLK_KP_6:
		if (down) {
			mMatrix[4] |= 1 << 1;
		} else {
			mMatrix[4] &= ~(1 << 1);
		}
		return;

	case SDLK_7:
	case SDLK_KP_7:
		if (down) {
			mMatrix[4] |= 1 << 2;
		} else {
			mMatrix[4] &= ~(1 << 2);
		}
		return;

	case SDLK_8:
	case SDLK_KP_8:
		if (down) {
			mMatrix[4] |= 1 << 3;
		} else {
			mMatrix[4] &= ~(1 << 3);
		}
		return;

	case SDLK_9:
	case SDLK_KP_9:
		if (down) {
			mMatrix[4] |= 1 << 4;
		} else {
			mMatrix[4] &= ~(1 << 4);
		}
		return;

	case SDLK_0:
	case SDLK_KP_0:
		if (down) {
			mMatrix[4] |= 1 << 5;
		} else {
			mMatrix[4] &= ~(1 << 5);
		}
		return;

	case SDLK_COMMA:
		if (down) {
			mMatrix[7] |= 1 << 3;
		} else {
			mMatrix[7] &= ~(1 << 3);
		}
		return;

	case SDLK_PERIOD:
	case SDLK_KP_PERIOD:
		if (down) {
			mMatrix[7] |= 1 << 4;
		} else {
			mMatrix[7] &= ~(1 << 4);
		}
		return;

	case SDLK_COLON:
		if (down) {
			mMatrix[6] |= 1 << 5;
		} else {
			mMatrix[6] &= ~(1 << 5);
		}
		return;

	case SDLK_QUESTION:
		if (down) {
			mMatrix[7] |= 1 << 5;
		} else {
			mMatrix[7] &= ~(1 << 5);
		}
		return;

	case SDLK_EXCLAIM:
		if (down) {
			mMatrix[3] |= 1 << 5;
		} else {
			mMatrix[3] &= ~(1 << 5);
		}
		mShift = true;
		return;

	case SDLK_SEMICOLON:
		if (down) {
			mMatrix[6] |= 1 << 5;
		} else {
			mMatrix[6] &= ~(1 << 5);
		}
		mShift = !mShift;
		break;

	case SDLK_QUOTE:
		if (down) {
			mMatrix[4] |= 1 << 2;
		} else {
			mMatrix[4] &= ~(1 << 2);
		}
		mShift = true;
		return;

	case SDLK_QUOTEDBL:
		if (down) {
			mMatrix[3] |= 1 << 4;
		} else {
			mMatrix[3] &= ~(1 << 4);
		}
		mShift = true;
		return;

	case SDLK_HASH:
		if (down) {
			mMatrix[3] |= 1 << 3;
		} else {
			mMatrix[3] &= ~(1 << 3);
		}
		mShift = true;
		return;

	case SDLK_DOLLAR:
		if (down) {
			mMatrix[3] |= 1 << 2;
		} else {
			mMatrix[3] &= ~(1 << 2);
		}
		mShift = true;
		return;

	case SDLK_PERCENT:
		if (down) {
			mMatrix[3] |= 1 << 1;
		} else {
			mMatrix[3] &= ~(1 << 1);
		}
		mShift = true;
		return;

	case SDLK_AMPERSAND:
		if (down) {
			mMatrix[4] |= 1 << 1;
		} else {
			mMatrix[4] &= ~(1 << 1);
		}
		mShift = true;
		return;

	case SDLK_LEFTPAREN:
		if (down) {
			mMatrix[4] |= 1 << 3;
		} else {
			mMatrix[4] &= ~(1 << 3);
		}
		mShift = true;
		return;

	case SDLK_RIGHTPAREN:
		if (down) {
			mMatrix[4] |= 1 << 4;
		} else {
			mMatrix[4] &= ~(1 << 4);
		}
		mShift = true;
		return;

	case SDLK_SLASH:
	case SDLK_KP_DIVIDE:
		if (down) {
			mMatrix[7] |= 1 << 5;
		} else {
			mMatrix[7] &= ~(1 << 5);
		}
		mShift = !mShift;
		return;

	case SDLK_EQUALS:
		if (down) {
			mMatrix[5] |= 1 << 4;
		} else {
			mMatrix[5] &= ~(1 << 4);
		}
		mShift = true;
		return;

	case SDLK_MINUS:
	case SDLK_KP_MINUS:
		if (down) {
			mMatrix[5] |= 1 << 3;
		} else {
			mMatrix[5] &= ~(1 << 3);
		}
		mShift = true;
		return;

	case SDLK_PLUS:
	case SDLK_KP_PLUS:
		if (down) {
			mMatrix[5] |= 1 << 5;
		} else {
			mMatrix[5] &= ~(1 << 5);
		}
		mShift = true;
		return;

	case SDLK_ASTERISK:
	case SDLK_KP_MULTIPLY:
		if (down) {
			mMatrix[4] |= 1 << 5;
		} else {
			mMatrix[4] &= ~(1 << 5);
		}
		mShift = true;
		return;

	case SDLK_CARET:
		if (down) {
			mMatrix[6] |= 1 << 3;
		} else {
			mMatrix[6] &= ~(1 << 3);
		}
		mShift = true;
		return;

	case SDLK_AT:
		if (down) {
			mMatrix[6] |= 1 << 4;
		} else {
			mMatrix[6] &= ~(1 << 4);
		}
		mShift = true;
		return;

	case SDLK_UP:
		if (down) {
			mMatrix[6] |= 1 << 0;
		} else {
			mMatrix[6] &= ~(1 << 0);
		}
		return;

	case SDLK_DOWN:
		if (down) {
			mMatrix[5] |= 1 << 0;
		} else {
			mMatrix[5] &= ~(1 << 0);
		}
		return;

	case SDLK_LEFT:
	case SDLK_BACKSPACE:
		if (down) {
			mMatrix[3] |= 1 << 0;
		} else {
			mMatrix[3] &= ~(1 << 0);
		}
		return;

	case SDLK_RIGHT:
		if (down) {
			mMatrix[4] |= 1 << 0;
		} else {
			mMatrix[4] &= ~(1 << 0);
		}
		return;

	case SDLK_RETURN:
	case SDLK_KP_ENTER:
		if (down) {
			mMatrix[7] |= 1 << 0;
		} else {
			mMatrix[7] &= ~(1 << 0);
		}
		return;

	case SDLK_SPACE:
		if (down) {
			mMatrix[2] |= 1 << 0;
		} else {
			mMatrix[2] &= ~(1 << 0);
		}
		return;
	}
}
