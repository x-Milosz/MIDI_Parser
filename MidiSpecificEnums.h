#pragma once
enum metaEvents {
	sequenceNumber = 0x00,
	textEvent = 0x01,
	copyrightNotice = 0x02,
	trackName = 0x03,
	instrumentName = 0x04,
	lyrics = 0x05,
	marker = 0x06,
	cuePoint = 0x07,
	midiChannelPrefix = 0x20,
	endOfTrack = 0x2F,
	setTempo = 0x51,
	smpteOffset = 0x54,
	timeSignature = 0x58,
	keySignature = 0x59,
	sequencerSpecific = 0x7F
};

enum channelEventFormats {
	noteOff = 0x8,
	noteOn = 0x9,
	noteAftertouch = 0xA,
	controller = 0xB,
	programChange = 0xC,
	channelAfterTouch = 0xD,
	pitchBend = 0xE
};


/*
enum controllerEventValues {
	bankSelect = 0x00,
	modulation = 0x01,
	breatheController = 0x02,
	footController = 0x04,
	portamentoTime = 0x05,
	dataEntry = 0x06,
	mainVolume = 0x07,
	balance = 0x08,
	pan = 0x0A,
	expressionController = 0x0B,
	effectControl1 = 0x0C,
	effectControl2 = 0x0D,
	generalPurpouseController1 = 0x10,
	generalPurpouseController2 = 0x11,
	generalPurpouseController3 = 0x12,
	generalPurpouseController4 = 0x13,
};
*/