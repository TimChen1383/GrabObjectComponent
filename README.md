# GrabObjectComponent

 The Grabber component let you highlight and grab an object in UE level in runtime by using physics handle. 
 
 To make the Grabber component work, you need to do follow :
- Add Grabber component to default pawn (if we play the game with default pawn)
- Set Grabber component’s “SearchScale” to the value we want as it will be the length of physics handle
- Set Grabber component’s “HighlighValue” to the value we want as it will control the highlight value when we pick an object up
- In Blueprint, connect a Keyboard Input Event to "ActionGrab" and "ActionRelease" functions so that we can grab the object when we press it
- Make sure the objects we want to grab has enable “simulate physics” and set the collision preset to “PhysicsActor”
- Add a scalar parameter called “Highlight” in the pick-up object’s material and connect to emissive. We can control the highlight value in runtime if we have the object been picked up


![Untitled](https://github.com/TimChen1383/GrabObjectComponent_UE/assets/37008451/2209406f-a989-4dd1-8ea9-395a24025295)
