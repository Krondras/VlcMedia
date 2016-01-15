// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IMediaVideoTrack.h"
#include "VlcMediaTrack.h"


struct FLibvlcMediaPlayer;
struct FLibvlcTrackDescription;
class FRHITexture;
class IMediaStream;


class FVlcMediaVideoTrack
	: public FVlcMediaTrack
	, public IMediaVideoTrack
{
public:

	/**
	 * Creates and initializes a new instance.
	 *
	 * @param InPlayer The VLC media player instance that owns this track.
	 * @param Descr The track description.
	 */
	FVlcMediaVideoTrack(FLibvlcMediaPlayer* InPlayer, FLibvlcTrackDescription* Descr);

	/** Virtual destructor. */
	virtual ~FVlcMediaVideoTrack();

public:

	// IMediaVideoTrack interface

	virtual uint32 GetBitRate() const override;
	virtual FIntPoint GetDimensions() const override;
	virtual float GetFrameRate() const override;
	virtual IMediaStream& GetStream() override;

#if WITH_ENGINE
	virtual void BindTexture(FRHITexture* Texture) override;
	virtual void UnbindTexture(FRHITexture* Texture) override;
#endif

public:

	// IMediaStream interface

    virtual bool Disable() override;
    virtual bool Enable() override;
    virtual bool IsEnabled() const override;

private:

	/** Handles cleanup callback from VLC. */
	static void HandleVideoCleanup(void* Opaque);

	/** Handles the display callback from VLC. */
	static void HandleVideoDisplay(void* Opaque, void* Picture);

	/** Handles the buffer lock callback from VLC. */
	static void* HandleVideoLock(void* Opaque, void** Planes);

	/** Handles video setup callbacks from VLC. */
	static uint32 HandleVideoSetup(void** Opaque, ANSICHAR* Chroma, uint32* Width, uint32* Height, uint32* Pitches, uint32* Lines);

	/** Handles the buffer unlock callback from VLC. */
	static void HandleVideoUnlock(void* Opaque, void* Picture, void* const* Planes);

private:

	/** The video's dimensions. */
	FIntPoint Dimensions;

	/** Buffer to write frame data to. */
	TArray<uint8> FrameBuffer;

	/** Last delta time. */
	FTimespan LastDelta;

	/** The track's cached name. */
	FString Name;

	/** The video track's ID. */
	int32 VideoTrackId;
};
