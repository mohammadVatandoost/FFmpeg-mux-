#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

extern "C"{ //here the call to the wrapper with extern keyword
 #include "wrapper.h"
}
using namespace std;

void err_to_string(int errCode) {
    char error_mesg[1024];
    av_strerror(errCode ,error_mesg, 1024  );
    cerr << "err:"<<error_mesg<<endl;
}

int getVideofps(AVFormatContext *pAVFormatContext) {
    int VideoStreamIndx = -1;
    /* find first stream */
    for(int i=0; i<pAVFormatContext->nb_streams ;i++ )
    {
    if( pAVFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO )
    /* if video stream found then get the index */
    {
      VideoStreamIndx = i;
      break;
    }
    }


     /* if video stream not availabe */
     if((VideoStreamIndx) == -1)
     {
       std::cout<<"video streams not found"<<std::endl;
       return -1;
     }
     /* get video fps */
     cout<<"r_frame_rate den:"<< pAVFormatContext->streams[VideoStreamIndx]->r_frame_rate.den
        << ", num:"<<pAVFormatContext->streams[VideoStreamIndx]->r_frame_rate.num <<endl;
     cout<<"avg_frame_rate den:"<< pAVFormatContext->streams[VideoStreamIndx]->avg_frame_rate.den
        << ", num:"<<pAVFormatContext->streams[VideoStreamIndx]->avg_frame_rate.num <<endl;
     pAVFormatContext->streams[VideoStreamIndx]->r_frame_rate.num = 247;
     pAVFormatContext->streams[VideoStreamIndx]->r_frame_rate.den = 10;
//     pAVFormatContext->streams[VideoStreamIndx]->avg_frame_rate.num = 247;
//     pAVFormatContext->streams[VideoStreamIndx]->avg_frame_rate.den = 10;
     int videoFPS = av_q2d(pAVFormatContext->streams[VideoStreamIndx]->r_frame_rate);
     std::cout<<"fps :"<<videoFPS <<", avg fps:" <<std::endl;
     return 0;
}

int setVideoFps(AVFormatContext *pAVFormatContext) {
    int VideoStreamIndx = -1;
    /* find first stream */
    for(int i=0; i<pAVFormatContext->nb_streams ;i++ )
    {
    if( pAVFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO )
    /* if video stream found then get the index */
    {
      VideoStreamIndx = i;
      break;
    }
    }


     /* if video stream not availabe */
     if((VideoStreamIndx) == -1)
     {
       std::cout<<"video streams not found"<<std::endl;
       return -1;
     }
     pAVFormatContext->streams[VideoStreamIndx]->r_frame_rate.num = 247;
     pAVFormatContext->streams[VideoStreamIndx]->r_frame_rate.den = 10;
//     pAVFormatContext->streams[VideoStreamIndx]->avg_frame_rate.num = 247;
//     pAVFormatContext->streams[VideoStreamIndx]->avg_frame_rate.den = 10;
     int videoFPS = av_q2d(pAVFormatContext->streams[VideoStreamIndx]->r_frame_rate);
//     std::cout<<"fps :"<<videoFPS <<", avg fps:" <<std::endl;
     return 0;
}

int setAudioParameters(AVFormatContext *pAVFormatContext) {
    int audioStreamIndx = -1;
    /* find first stream */
    for(int i=0; i<pAVFormatContext->nb_streams ;i++ )
    {
    if( pAVFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO )
    /* if video stream found then get the index */
    {
      audioStreamIndx = i;
      break;
    }
    }


     /* if video stream not availabe */
     if((audioStreamIndx) == -1)
     {
       std::cout<<"video streams not found"<<std::endl;
       return -1;
     }
     cout<< pAVFormatContext->streams[audioStreamIndx]->r_frame_rate.num <<", "
            << pAVFormatContext->streams[audioStreamIndx]->r_frame_rate.den <<", "
               << pAVFormatContext->streams[audioStreamIndx]->avg_frame_rate.num <<", "
               << pAVFormatContext->streams[audioStreamIndx]->avg_frame_rate.den <<", "<<endl;
//     pAVFormatContext->streams[audioStreamIndx]->r_frame_rate.num = 247;
//     pAVFormatContext->streams[audioStreamIndx]->r_frame_rate.den = 10;
//     pAVFormatContext->streams[VideoStreamIndx]->avg_frame_rate.num = 247;
//     pAVFormatContext->streams[VideoStreamIndx]->avg_frame_rate.den = 10;
     int audioFPS = av_q2d(pAVFormatContext->streams[audioStreamIndx]->r_frame_rate);
     std::cout<<"audio fps :"<<audioFPS <<", avg fps:" <<std::endl;
     return 0;
}

int main()
{
    cout << "Hello World!" << endl;
    AVOutputFormat *ofmt = NULL;
    //Input AVFormatContext and Output AVFormatContext
    AVFormatContext *ifmt_ctx_v = NULL, *ifmt_ctx_a = NULL,*ofmt_ctx = NULL;
    int ret, i;
    const char *in_filename_v = "1.h264";
    const char *in_filename_a = "1.pcm";

    AVInputFormat *v_format = new AVInputFormat();
    v_format->name = "h264";
//    v_format->codec_tag = "0000000000000000";
    v_format->raw_codec_id = 27;
    v_format->extensions = "h26l,h264,264,avc";
//    v_format->read_header()
    // read video input
    if ((ret = avformat_open_input(&ifmt_ctx_v, in_filename_v, NULL, NULL)) < 0) {
        cerr << "Could not open video input file." << endl;
        return -1;
    }
    if ((ret = avformat_find_stream_info(ifmt_ctx_v, 0)) < 0) {
        cerr <<  "Failed to retrieve input stream information" << endl;
        return -1;
    }

    // set video frq
    setVideoFps(ifmt_ctx_v);

    // read audio input
    AVInputFormat *audio_format = new AVInputFormat();
    ifmt_ctx_a = avformat_alloc_context();
    audio_format->name = "1.pcm";
    audio_format->raw_codec_id = AV_CODEC_ID_PCM_S16LE;
    audio_format->long_name = NULL;
    if ((ret = avformat_open_input(&ifmt_ctx_a, in_filename_a, audio_format, NULL)) < 0) {
//            printf( "Could not open audio input file.");
        cerr<< "Could not open audio input file. err:"<< ret<< endl;
        return -1;
    }
    if ((ret = avformat_find_stream_info(ifmt_ctx_a, 0)) < 0) {
        cerr<< "Failed to retrieve Audio input stream information"<< endl;
        return -1;;
    }

    // set audio frq
    setAudioParameters(ifmt_ctx_a);


    cout<< "v_format:"<<ifmt_ctx_v->iformat->name <<", "<< ifmt_ctx_v->iformat->codec_tag<<", "<< ifmt_ctx_v->iformat->raw_codec_id<<endl;
    cout<<"extensions:"<< ifmt_ctx_v->iformat->extensions<< ", long_name:"<< ifmt_ctx_v->iformat->long_name<<", "<<endl;
//    cout<< ifmt_ctx_v->video_codec->supported_samplerates<< ", " <<endl;
     getVideofps(ifmt_ctx_v);
    AVInputFormat *v_format2 = ifmt_ctx_v->iformat->next;
    if(v_format2 == NULL) {
        cout<< "iformat->next is NUll"<<endl;
    } else {
        cout<< "iformat->next is not NUll"<<endl;
    }
    while(v_format2 != NULL ) {
        cout<< "==========="<<endl;
        cout<< "v_format2:"<<v_format2->name <<", "<< v_format2->codec_tag<<", "<< v_format2->raw_codec_id<<endl;
        cout<<"extensions:"<< v_format2->extensions<< ", long_name:"<< v_format2->long_name<<", "<<endl;
        cout<< "==========="<<endl;
        v_format2 = v_format2->next;
    }
    AVDeviceInfoList *device_list = NULL;
//    int err2 = avdevice_list_devices(ifmt_ctx_v, &device_list);

     int err2 = avdevice_list_input_sources(ifmt_ctx_v->iformat, nullptr, nullptr, &device_list);
      err_to_string(err2);
//    ifmt_ctx_v->iformat->get_device_list(ifmt_ctx_a, device_list);
//    char error_mesg[1024];
//    int size = 0;
//    size_t errorSize = 0 ;
//    cout<< "err2:"<< err2<<endl;
//    cout<< "device list readed err2:"<<av_strerror(err2 ,error_mesg, 1024  )<<endl; //av_strerror
//    cout<< "error_mesg :"<<error_mesg<<endl;
//    if(size > 0) {
//        cout<< "error_mesg:"<<error_mesg<<endl ;
//    }
//    cout<< "nb_devices:"<<device_list->nb_devices<<endl;
    printf("===========Input Information==========\n");
    av_dump_format(ifmt_ctx_v, 0, in_filename_v, 0);
    av_dump_format(ifmt_ctx_a, 0, in_filename_a, 0);
    printf("======================================\n");
    return 0;
}
