#include <vlc/vlc.h>
#include <map>
#include <iostream>
#include <unistd.h>

class MediaPlayerVlc{
    private :
        /* data */
        libvlc_instance_t *inst;

        libvlc_media_player_t *mp_alarm;
        libvlc_media_player_t *mp_conversastion;
        libvlc_media_player_t *mp_local;
        libvlc_media_player_t *mp_content;
        libvlc_media_player_t *tmp;
        

        libvlc_media_list_player_t *mpl;
        libvlc_media_t *m;

        enum type_stream{
            alarm_stream = 1,
            conversation_stream,
            local_stream,
            content_stream,
        };

        std::map<std::string, int> tmp_status; // tmp_status[0] => state sebelumnya. tmp_status[1] => state terbaru
        int tmp_play = 0;
        int tmp_type_play = 0;
        enum type_play{
            alarm_play = 1,
            conversation_play,
            local_play,
            content_play
        };

        bool alarm = false;
        bool conversation = false;
        bool local = false;
        bool content = false;

    
    public :
        void create();
        void openFile(const char* media, int type);
        void Play();
        void pause(const char* media);
        void stop(const char* media);
        void resume(const char* media);
        void setVolume(int val);      
};


/*
    m       => media vlc
    mp      => media player vlc
    mpl     => media player list
    inst    => instance vlc 
*/