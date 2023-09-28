#ifndef ADAPTERPATTERN_HPP
#define ADAPTERPATTERN_HPP

#include <iostream>

using namespace std;

namespace adapterpattern
{
    //Interface class for advanced audio player
    class IAdvancedAudioPlayer
    {
    public:
        //supported audio formats
        enum eAudioFormats
        {
            eWAV = 0,
            eAAC
        };
        virtual void playAudio(eAudioFormats audioFormat, string audioFile) = 0;
    };

    //Wav audio player
    class CWAVAudio : public IAdvancedAudioPlayer
    {
    private:
        void playWavFile(string filePath)
        {
            cout << "AdvancedAudioPlayer is playing WAV audio file" << endl;
        }
    public:

        void playAudio(eAudioFormats audioFormat, string audioFile) override
        {
            playWavFile(audioFile);
        }
    };

    //AAC audio player
    class CAACAudio : public IAdvancedAudioPlayer
    {
    private:
        void playAacFile(string filePath)
        {
            cout << "AdvancedAudioPlayer is playing AAC audio file" << endl;
        }
    public:

        void playAudio(eAudioFormats audioFormat, string audioFile) override
        {
            playAacFile(audioFile);
        }
    };


    //AudioPlayer Interfacce class
    class IAudioPlayer
    {
    public:
        virtual void play(string format, string audioFilePath) = 0;
    };

    //Adapter class
    //Derived from the interface class
    class CAdapter : public IAudioPlayer
    {
        private:
        //contains the object of the AdvancedAudioPlayer
        IAdvancedAudioPlayer* advancedPlayer;

        public:
        CAdapter()
        {
            advancedPlayer = nullptr;
        }

        //Implementation of the pure virtual function
        void play(string format, string audioFile) override
        {
            if("wav" == format)
            {
                cout<<"WAV file - passing the request to the advanced player "<<endl;
                advancedPlayer = new CWAVAudio;
                advancedPlayer->playAudio(IAdvancedAudioPlayer::eAudioFormats::eWAV, audioFile);
            }
            else if("aac" == format)
            {
                cout<<"AAC File - passing the request to the advanced player "<<endl;
                advancedPlayer = new CAACAudio;
                advancedPlayer->playAudio(IAdvancedAudioPlayer::eAudioFormats::eAAC, audioFile);
            }
            else
            {
                cerr<<" wrong audio format "<<format<<endl;
            }
        }
    };

    //Audio Player
    class CAudioPlayer : public IAudioPlayer
    {
    private:
        //Adapter instance
        CAdapter* adapter;

        //Get the apapter instance
        CAdapter* getAdapter()
        {
            if (nullptr == adapter)
            {
                adapter = new CAdapter;
            }
            return adapter;
        }

    public:
        CAudioPlayer()
        {
            adapter = nullptr;
        }
        //Implementation of the pure virtual function
        void play(string format, string audioFile) override
        {
            if ("mp3" == format)
            {
                cout << " Audioplayer is playing MP3 song " << audioFile << endl;
            }
            else
            {
                //pass the request to the adapter class for further handling
                getAdapter()->play(format, audioFile);
            }
        }
    };


    void testAdapterPattern()
    {
        //client code
        IAudioPlayer* audioPlayer = new CAudioPlayer;
        audioPlayer->play("wav","c:/audio1.wav");
        audioPlayer->play("mp3","c:/audio2.mp3");
        audioPlayer->play("aac","c:/audio3.aac");
        audioPlayer->play("mp4", "c:/audio3.aac");
    }
}

#endif