// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO prevent double-speed input due to dual control
}

void UTankMovementComponent::IntendTurnRight(float Throw) {

	if (!LeftTrack || !RightTrack) { return; }
	RightTrack->SetThrottle(-Throw);
	LeftTrack->SetThrottle(Throw);
	// TODO prevent double-speed input due to dual control
}


