/**
  * @file   main.cpp
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  main.cpp runs our unit tests
  * and forms as an easy to follow fully documented
  * tutorial as to the use of each part of
  * the GameAudio(OpenALWrapper)
*/

// C++ Includes
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <vector>
#include <limits>

// GAMEAUDIO Includes
#include "GameAudio.h"

// GAMECONTECT Includes
#include "AudioManager.h"

// XMP Includes
#include <xmp.h>

// GLOBALS
// Make the AudioSystem
AudioSystem audioSystem;
// Make the AudioManager
AudioManager audioManager;

// UNIT TEST FUNCTIONS
// Sound Unit Test
void soundUnitTest();
// Sound2D Unit Test
void sound2DUnitTest();
// Sound3D Unit Test
void sound3DUnitTest();
// Stream Unit Test
void streamUnitTest();
// Stream2D Unit Test
void stream2DUnitTest();
// Stream3D Unit Test
void stream3DUnitTest();
// Music Unit Test
void musicUnitTest();
// Capture Test
void captureTest();

// Entry Point
int main(int argc, char* argv[])
{
    // Send a message to the console
    std::cout << "NOTICE: Init AudioSystem" << std::endl;
    std::cout << std::endl;

    // Initialise the AudioSystem
    if (audioSystem.init() == false)
    {
        // Failure
        return -1;
    }

    // UNIT TESTS
    // Run Sound Unit Test
    soundUnitTest();
    // Run Sound2D Unit Test
    sound2DUnitTest();
    // Run Sound3D Unit Test
    sound3DUnitTest();
    // Run Stream Unit Test
    streamUnitTest();
    // Run Stream2D Unit Test
    stream2DUnitTest();
    // Run Stream3D Unit Test
    stream3DUnitTest();
    // Run Music Unit Test
    musicUnitTest();
    // Run Capture Test NOTE: Outside of my spec for a simple GameAudio(OpenAL Wrapper)
    captureTest();

    // ShutDown the Audio System
    audioSystem.shutdown();

    // Send a message to the console
    std::cout << std::endl;
    std::cout << "NOTICE: Shutdown AudioSystem" << std::endl;

    // return
    return 0;
}

void soundUnitTest()
{
    // Send a message to the console
    std::cout << "PERFORMING SOUND UNIT TEST" << std::endl;
    std::cout << std::endl;
    std::cout << "Loading Sound...";
    // Grab a SoundBuffer
    SoundBuffer* pSoundBuffer = audioManager.getSoundBuffer("media/sounds/bensound-betterdays.ogg");
    // If our SoundBuffer is invalid
    if (pSoundBuffer == 0)
    {
        // Send a message to the console
        std::cout << "Failure" << std::endl;
        // Return
        return;
    }
    // Send a message to the console
    std::cout << "Success" << std::endl;
    // Make a Sound
    Sound sound;
    // Set the SoundBuffer
    sound.setSoundBuffer(pSoundBuffer);
    // Set Looping
    sound.setLooping(true);
    // Play Sound
    sound.play();
    // Send a mesaage to the console
    std::cout << "Press Space to Stop this Unit Test" << std::endl;
    // Psuedo Main Loop
    while(true)
    {
        // Update Sound
        sound.update(1.0f / 60.0f);
        // When Sound is finished (impossible when looping)
        if (sound.isPlaying() == false)
        {
            // Break from our loop
            break;
        }
        // If a key was pressed
        if (kbhit() == true)
        {
            // Grab the Keypressed
            char ch = getch();
            // If key was space then break
            if (ch == 32)
                break;
         }
    }
    // Stop the Sound
    sound.stop();
    // Clear the Sound
    sound.clear();
    // Free the Sound
    sound.free();
    // Clear the AudioManager
    audioManager.clear();
    // Send a message to the console
    std::cout << "TEST COMPLETE" << std::endl;
}

void sound2DUnitTest()
{
    // Send a message to the console
    std::cout << "PERFORMING SOUND2D UNIT TEST" << std::endl;
    std::cout << std::endl;
    std::cout << "Loading Sound...";
    // Grab a SoundBuffer
    SoundBuffer* pSoundBuffer = audioManager.getSoundBuffer("media/sounds/positionalSound.wav");
    // If our SoundBuffer is invalid
    if (pSoundBuffer == 0)
    {
        // Send a message to the console
        std::cout << "Failure" << std::endl;
        // Return
        return;
    }
    // Send a message to the console
    std::cout << "Success" << std::endl;
    // Make a Sound2D
    Sound2D sound2D;
    // Set the SoundBuffer
    sound2D.setSoundBuffer(pSoundBuffer);
    // Set Looping
    sound2D.setLooping(true);
    // Set Spacial Position
    sound2D.setPosition(100.0f, 0.0f);
    // Set Min Volume
    sound2D.setMinVolume(0.0f);
    // Set Max Volume
    sound2D.setMaxVolume(1.0f);
    // Play the Sound2D
    sound2D.play();
    // Set reference distance
    sound2D.setReferenceDistance(1);
    // Set Roll off
    sound2D.setRollOff(50.0f);
    // Set Max Distance
    //sound2D.setMaxDistance(100);
    // Set the Position of the listener
    audioSystem.setListenerPosition(0.0f, 0.0f);
    // unit test variable to control sound movement
    float theta = 0.0f;
    // Send a mesaage to the console
    std::cout << "Press Space to Stop this Unit Test" << std::endl;
    // Psuedo Main Loop
    while (true)
    {
        // Interpolate theta
        theta = theta + 0.00005f;
        // Set the Sound's position
        sound2D.setPosition(cos(theta) * 100, 0.0f);
        // Send a message to the console
        //std::cout << cos(theta) * 100 << std::endl;
        // Update the Sound2D
        sound2D.update(1.0f / 60.0f);
        // When Sound2D is finished (impossible when looping)
        if (sound2D.isPlaying() == false)
        {
            // Break from our loop
            break;
        }
        // If a key was pressed
        if (kbhit() == true)
        {
            // Grab the Keypressed
            char ch = getch();
            // If key was space then break
            if (ch == 32)
                break;
         }
    }
    // Stop the Sound2D
    sound2D.stop();
    // Clear the Sound2D
    sound2D.clear();
    // Free the Sound2D
    sound2D.free();
    // Clear the AudioManager
    audioManager.clear();
    // Send a message to the console
    std::cout << "TEST COMPLETE" << std::endl;
}

void sound3DUnitTest()
{
    // Send a message to the console
    std::cout << "PERFORMING SOUND3D UNIT TEST" << std::endl;
    std::cout << std::endl;
    std::cout << "Loading Sound...";
    // Grab a SoundBuffer
    SoundBuffer* pSoundBuffer = audioManager.getSoundBuffer("media/sounds/positionalSound.wav");
    // If our SoundBuffer is invalid
    if (pSoundBuffer == 0)
    {
        // Send a message to the console
        std::cout << "Failure" << std::endl;
        // Return
        return;
    }
    // Send a message to the console
    std::cout << "Success" << std::endl;
    // Make a Sound3D
    Sound3D sound3D;
    // Set the SoundBuffer
    sound3D.setSoundBuffer(pSoundBuffer);
    // Set Looping
    sound3D.setLooping(true);
    // Set Spacial Position
    sound3D.setPosition(100.0f, 0.0f, 0.0f);
    // Set Min Volume
    sound3D.setMinVolume(0.0f);
    // Set Max Volume
    sound3D.setMaxVolume(1.0f);
    // Play the Sound3D
    sound3D.play();
    // Set the Listener Positoin
    audioSystem.setListenerPosition(0.0f, 0.0f);
    // Set reference distance
    sound3D.setReferenceDistance(1);
    // Set Roll off
    sound3D.setRollOff(50.0f);
    // Set Max Distance
    //sound2D.setMaxDistance(100);
    // unit test variable to control sound movement
    float theta = 0.0f;
    // Send a mesaage to the console
    std::cout << "Press Space to Stop this Unit Test" << std::endl;
    // Psuedo Main Loop
    while (true)
    {
        // Interpolate theta
        theta = theta + 0.00005f;
        // Set the Sound's position
        sound3D.setPosition(cos(theta) * 100.0f, 0.0f, sin(theta) * 100.0f);
        // Send a message to the console
        //std::cout << cos(theta) * 100.0f << ", 0.0f, " << sin(theta) * 100.0f << std::endl;
        // Update the Sound3D
        sound3D.update(1.0f / 60.0f);
        // When Sound3D is finished (impossible when looping)
        if (sound3D.isPlaying() == false)
        {
            // Break from our loop
            break;
        }
        // If a key was pressed
        if (kbhit() == true)
        {
            // Grab the Keypressed
            char ch = getch();
            // If key was space then break
            if (ch == 32)
                break;
         }
    }
    // Stop Sound3D
    sound3D.stop();
    // Clear Sound3D
    sound3D.clear();
    // Free Sound3D
    sound3D.free();
    // Clear the AudioManager
    audioManager.clear();
    // Send a message to the console
    std::cout << "TEST COMPLETE" << std::endl;
}

void streamUnitTest()
{
    // Send a message to the console
    std::cout << "PERFORMING STREAM UNIT TEST" << std::endl;
    std::cout << std::endl;
    // Make a Stream
    Stream stream;
    // Load a stream
    if (stream.load("media/sounds/bensound-jazzyfrenchy.ogg") == false)
    {
        // Send a message to the console
        std::cout << "ERROR: Unable to open file" << std::endl;
        // Return
        return;
    }
    // Set Looping
    stream.setLooping(true);
    // Play Stream
    stream.play();
    // Set Sound Volume
    audioSystem.setSoundVolume(1.0f);
    // Send a mesaage to the console
    std::cout << "Press Space to Stop this Unit Test" << std::endl;
    // Psuedo Main Loop
    while (true)
    {
        // Update Stream
        stream.update(1.0f / 60.0f);
        // When Stream is finished (impossible when looping)
        if (stream.isPlaying() == false)
        {
            // Break from our loop
            break;
        }
        // If a key was pressed
        if (kbhit() == true)
        {
            // Grab the Keypressed
            char ch = getch();
            // If key was space then break
            if (ch == 32)
                break;
         }
    }
    // Stop Stream
    stream.stop();
    // Clear Stream
    stream.clear();
    // Free Stream
    stream.free();
    // Send a message to the console
    std::cout << "TEST COMPLETE" << std::endl;
}

void stream2DUnitTest()
{
    // Send a message to the console
    std::cout << "PERFORMING STREAM2D UNIT TEST" << std::endl;
    std::cout << std::endl;
    // Make a Stream2D
    Stream2D stream2D;
    // Try and load our stream
    if (stream2D.load("media/sounds/positionalSound.wav") == false)
    {
        // Send a message to the console
        std::cout << "ERROR: Failed to load file" << std::endl;
        // Failure
        return;
    }
    // Set Looping
    stream2D.setLooping(true);
    // Set Spacial Position
    stream2D.setPosition(100.0f, 0.0f);
    // Set Min Volume
    stream2D.setMinVolume(0.0f);
    // Set Max Volume
    stream2D.setMaxVolume(1.0f);
    // Play Stream2D
    stream2D.play();
    // Set the Listener position
    audioSystem.setListenerPosition(0.0f, 0.0f);
    // Set reference distance
    stream2D.setReferenceDistance(1);
    // Set Roll off
    stream2D.setRollOff(50.0f);
    // Set Max Distance
    //stream2D.setMaxDistance(100);
    // unit test variable to control sound movement
    float theta = 0.0f;
    //// Set Sound Volume
    //audioSystem.setSoundVolume(1.0f);
    // Send a mesaage to the console
    std::cout << "Press Space to Stop this Unit Test" << std::endl;
    // Psuedo Main Loop
    while (true)
    {
        // Interpolate theta
        theta = theta + 0.00005f;
        // Set the Sound's position
        stream2D.setPosition(cos(theta) * 100.0f, 0.0f);
        // Send a message to the console
        //std::cout << cos(theta) * 100.0f << std::endl;
        // Update Stream2D
        stream2D.update(1.0f / 60.0f);
        // When Stream is finished (impossible when looping)
        if (stream2D.isPlaying() == false)
        {
            // Break from our loop
            break;
        }
        // If a key was pressed
        if (kbhit() == true)
        {
            // Grab the Keypressed
            char ch = getch();
            // If key was space then break
            if (ch == 32)
                break;
         }
    }
    // Stop Stream2D
    stream2D.stop();
    // Clear Stream2D
    stream2D.clear();
    // Free Stream2D
    stream2D.free();
    // Send a message to the console
    std::cout << "TEST COMPLETE" << std::endl;
}

void stream3DUnitTest()
{
    // Send a message to the console
    std::cout << "PERFORMING STREAM3D UNIT TEST" << std::endl;
    std::cout << std::endl;
    // Make a Stream3D
    Stream3D stream3D;
    // Try and load the Stream
    if (stream3D.load("media/sounds/positionalSound.wav") == false)
    {
        // Send a message to the console
        std::cout << "ERROR: Failed to load file" << std::endl;
        // Failure
        return;
    }
    // Set Looping
    stream3D.setLooping(true);
    // Set Spacial Position
    stream3D.setPosition(0.0f, 0.0f, 0.0f);
    // Set Min Volume
    stream3D.setMinVolume(0.0f);
    // Set Max Volume
    stream3D.setMaxVolume(1.0f);
    // Play the Stream3D
    stream3D.play();
    // Set the Listener position
    audioSystem.setListenerPosition(0.0f, 0.0f);
    // Set reference distance
    stream3D.setReferenceDistance(1);
    // Set Roll off
    stream3D.setRollOff(50.0f);
    // Set Max Distance
    //stream3D.setMaxDistance(100);
    // unit test variable to control sound movement
    float theta = 0.0f;
    // Set Sound Volume
    audioSystem.setSoundVolume(1.0f);
    // Send a mesaage to the console
    std::cout << "Press Space to Stop this Unit Test" << std::endl;
    // Psuedo Main Loop
    while(true)
    {
        // Interpolate theta
        theta = theta + 0.00005f;
        // Set the Sound's position
        stream3D.setPosition(cos(theta) * 100.0f, 0.0f, sin(theta) * 100.0f);
        // Send a message to the console
        //std::cout << cos(theta) * 100.0f << ", 0.0f, " << sin(theta) * 100.0f << std::endl;
        // Update our Stream3D
        stream3D.update(1.0f / 60.0f);
        // When Stream3D is finished (impossible when looping)
        if (stream3D.isPlaying() == false)
        {
            // Break from our loop
            break;
        }
        // If a key was pressed
        if (kbhit() == true)
        {
            // Grab the Keypressed
            char ch = getch();
            // If key was space then break
            if (ch == 32)
                break;
         }
    }
    // Stop Stream3D
    stream3D.stop();
    // Clear Stream3D
    stream3D.clear();
    // Free Stream3D
    stream3D.free();
    // Send a message to the console
    std::cout << "TEST COMPLETE" << std::endl;
}

void musicUnitTest()
{
     // Send a message to the console
    std::cout << "PERFORMING MUSIC UNIT TEST" << std::endl;
    std::cout << std::endl;
    // Make Music
    Music music;
    // Set Looping
    music.setLooping(false);
    // Try and Load the Music
    //if (music.load("media/music/ShortLoop.xm") == false)
    if (music.load("media/music/Level5.mod") == false)
    {
        // Send a message to the console
        std::cout << "ERROR: Failed to load file" << std::endl;
        // Failure
        return;
    }
    // Play the Music
    music.play();
    // Mute the Music
    music.mute();
    // Set the Volume of the Music
    music.setVolume(1.0f);
    // Unmute hte Music
    music.unmute();
    /* NOTE: On my system I would get mangled music from having volume anything other than one :(
        this isn't my fault! */
    // Set music Volume
    audioSystem.setMusicVolume(1.0f);
    // Send a mesaage to the console
    std::cout << "Press Space to Stop this Unit Test" << std::endl;
    // Psuedo Main Loop
    while(true)
    {
        // Update the music
        music.update(1.0f / 60.0f);
        // When Music is finished (impossible when looping)
        if (music.isPlaying() == false)
        {
            // Break from our loop
            break;
        }
        // If a key was pressed
        if (kbhit() == true)
        {
            // Grab the Keypressed
            char ch = getch();
            // If key was space then break
            if (ch == 32)
                break;
         }
    }
    // Stop Music
    music.stop();
    // Clear Music
    music.clear();
    // Free Music
    music.free();
    // Send a message to the console
    std::cout << "TEST COMPLETE" << std::endl;
}

void captureTest()
{
     // Send a message to the console
    std::cout << "PERFORMING AUDIO CAPTURE UNIT TEST" << std::endl;
    std::cout << std::endl;
    // Grab the Capture Device
    CaptureDevice* pCaptureDevice = audioSystem.getAudioCaptureDevice(0);
    // Validate Capture Device
    if (pCaptureDevice == 0)
    {
        // Send a message to the console
        std::cout << "ERROR: Unable to find recording device" << std::endl;
        // Failure
        return;
    }

    if (pCaptureDevice->open(OpenALGlobals::frequency, AL_FORMAT_STEREO16, 1024) == false)
    {
        // Send a message to the console
        std::cout << "ERROR: Unable to open Audio Device" << std::endl;
        // Failure
        return;
    }
    // Start recording
    pCaptureDevice->start();
    // Stop Recording
    pCaptureDevice->stop();
    // Allocate our buffer
    char* pBuffer = new char[OpenALGlobals::frequency * sizeof(short int) * 2];
    // Grab the Samples from the Device (comes back as pcm short int)
    pCaptureDevice->captureSamples(pBuffer, OpenALGlobals::frequency);
    // Close Capture Device
    pCaptureDevice->close();
    /* NOTE: Saving or playing back the PCM Data is beyong the scope
        of what I setout to do building this wrapper */
    // Send a message to the console
    std::cout << std::endl;
    std::cout << "TEST COMPLETE" << std::endl;
}
