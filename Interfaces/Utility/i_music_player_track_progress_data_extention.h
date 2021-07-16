#pragma once

#include <QtCore>

#include "i_music_player_track_data_extention.h"

#define IMusicPlayerTrackProgressDataExtention_EXTENTION_PROPERTY \
	Q_PROPERTY(int progress READ progress) \

class IMusicPlayerTrackProgressDataExtention : public IMusicPlayerTrackDataExtention
{
public:
	IMusicPlayerTrackProgressDataExtention_EXTENTION_PROPERTY
	virtual int progress() = 0;
};
Q_DECLARE_INTERFACE(IMusicPlayerTrackProgressDataExtention, "IMusicPlayerTrackProgressDataExtention/1.0")
