#include <iostream>
#include "MediaPlayerVlc.h"


enum{
    alarm_stream = 1,
    conversation_stream,
    local_stream,
    content_stream,
}listType;

int main(){
    const char* link1 = "http://live2.indostreamserver.com:8018/stream/1/"; // streamming online
    const char* link2 = "audio/alarm.mp3"; //play audio local
    const char* link3 = "http://52.74.108.24:40510/respond/d42cdeaa7b76e3b7b495efc3499c69f3"; // url conversation

    MediaPlayerVlc Player;
    Player.create();
    
    
    Player.openFile(link1,content_stream);
    Player.Play();

    Player.setVolume(50);

    usleep(10000000);
    Player.openFile(link2, alarm_stream);
    Player.Play();

    usleep(10000000);
    Player.openFile(link3, conversation_stream);
    Player.Play();

    usleep(10000000);
    Player.openFile(link3, conversation_stream);
    Player.Play();

    usleep(10000000);
    Player.openFile(link2, alarm_stream);
    Player.Play();


    while(true){} // hold biar jalan terus
}