#include "MediaPlayerVlc.h"

void MediaPlayerVlc::create(){
    inst = libvlc_new(0, NULL);
    mp_alarm            = NULL;
    mp_conversastion    = NULL;
    mp_local            = NULL;
    mp_content          = NULL;

    tmp_status["last"] = 0;   // state sebelumnya
    tmp_status["now"]  = 0;   // state yang baru
}

void MediaPlayerVlc::setVolume(int val){
    libvlc_audio_set_volume(tmp,val);
}


void MediaPlayerVlc::openFile(const char* media, int type){
    tmp_play = type;
    // simpan state
    
    std::cout<<"open file before tmp_status[last] "<< tmp_status["last"] << std::endl;
    std::cout<<"open file before tmp_status[now] "<< tmp_status["now"] << std::endl;
    
    tmp_type_play = tmp_status["now"];
    tmp_status["now"]  = type;
    tmp_status["last"] = tmp_type_play; // simpan sttus sbelumnya
    
    std::cout<<"open file after tmp_status[last] "<< tmp_status["last"] << std::endl;
    std::cout<<"open file after tmp_status[now] "<< tmp_status["now"] << std::endl;

    switch (type)
    {  

        case alarm_stream:
            m           = libvlc_media_new_path (inst, media);
            mp_alarm    = libvlc_media_player_new_from_media(m);
            libvlc_media_release(m);
            tmp = mp_alarm;
            break;

        case content_stream:
            m           = libvlc_media_new_location (inst, media);
            mp_content  = libvlc_media_player_new_from_media(m);
            libvlc_media_release(m);
            tmp = mp_content;
            break;
        
        case conversation_stream:
            m                   = libvlc_media_new_location (inst, media);
            mp_conversastion    = libvlc_media_player_new_from_media(m);
            libvlc_media_release(m);
            tmp = mp_conversastion;
            break;

        case local_stream:
            m           = libvlc_media_new_path (inst, media);
            mp_local    = libvlc_media_player_new_from_media(m);
            libvlc_media_release(m);
            tmp = mp_local;
            break;

        default:
            break;
    }
}


/*
    play priority :
    1. alarm
    2. conversation
    3. local file
    4. content
*/

void MediaPlayerVlc::Play(){
    std::cout<<"play tmp_status[last]"<< tmp_status["last"] << std::endl;
    std::cout<<"play tmp_status[now]"<< tmp_status["now"] << std::endl;
    switch (tmp_play)
    {
        // 1. alarm
        case alarm_play:
            if(tmp_status["now"] == tmp_status["last"]){
               libvlc_media_player_play(mp_alarm);
            }else
            {
                if(tmp_status["last"] != 0){
                    switch (tmp_status["last"])
                        {
                        case content_play:
                            // pause content
                            tmp_status["now"] = content_play;

                            std::cout<<"pause\n";
                            libvlc_media_player_stop(mp_content);
                            libvlc_media_player_play(mp_alarm);
                            
                            usleep(3000000); // tunggu play alarm baru cek apakah sedang play atau tidak.
                            while (libvlc_media_player_is_playing(mp_alarm)){}
                            
                            std::cout<<"resume\n";
                            libvlc_media_player_play(mp_content);
                            
                            break;
                        
                        default:
                            break;
                    }
                }
            }
            
            break;

        // 2. conversation
        case conversation_play:
            if(tmp_status["now"] == tmp_status["last"]){
               libvlc_media_player_play(mp_conversastion);
            }else{
                if(tmp_status["last"] != 0){
                    switch (tmp_status["last"])
                        {
                        case content_play:
                            // pause content
                            tmp_status["now"] = content_play;
                            std::cout<<"pause\n";
                            libvlc_media_player_stop(mp_content);
                            libvlc_media_player_play(mp_conversastion);
                            
                            usleep(3000000); // tunggu play alarm baru cek apakah sedang play atau tidak.
                            while (libvlc_media_player_is_playing(mp_conversastion)){} // hold disni sampai selesai play

                            std::cout<<"resume\n";
                            libvlc_media_player_play(mp_content);
                            tmp_status["last"] = content_play;
                            break;
                        
                        default:
                            break;
                    }
                }
            }
            
            break;

        // 3. play local file audio  
        case local_play:
            if(tmp_status["now"] == tmp_status["last"]){
               libvlc_media_player_play(mp_local);
            }else{
                if(tmp_status["last"] != 0){
                    switch (tmp_status["last"])
                        {
                        case content_play:
                            // pause content
                            tmp_status["now"] = content_play;
                            std::cout<<"pause\n";
                            libvlc_media_player_stop(mp_content);
                            libvlc_media_player_play(mp_local);
                            
                            usleep(3000000); // tunggu play alarm baru cek apakah sedang play atau tidak.
                            while (libvlc_media_player_is_playing(mp_local)){} // hold disni sampai selesai play

                            std::cout<<"resume\n";
                            libvlc_media_player_play(mp_content);
                            tmp_status["last"] = content_play;
                            break;
                        
                        default:
                            break;
                    }
                }
            }
            
            break;

        // 4. content
        case content_play:
            libvlc_media_player_play(mp_content);
            break;

        default:
            break;
    }
}



