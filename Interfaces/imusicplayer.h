#pragma once

#include <QtCore>

class IMusicPlayer
{
	Q_PROPERTY(int trackIndex READ trackIndex WRITE setTrackIndex NOTIFY trackIndexChanged)
	
public:
	virtual int trackIndex() = 0;
	virtual void setTrackIndex(int trackIndex) = 0;
	
public slots:
	Q_INVOKABLE virtual void play() = 0;
	Q_INVOKABLE virtual void next() = 0;
	Q_INVOKABLE virtual void prev() = 0;
	Q_INVOKABLE virtual void addTracks(QString paths) = 0;
	Q_INVOKABLE virtual void removeTrack(int index) = 0;

signals:
	void trackIndexChanged(int trackIndex);
};
Q_DECLARE_INTERFACE(IMusicPlayer, "IMusicPlayer/1.0")
