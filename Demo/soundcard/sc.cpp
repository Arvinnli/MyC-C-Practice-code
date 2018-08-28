#include<iostream>
#include <stdio.h>





int main(int argc,const char* argv[]){

    MMRESULT ret;
    HMIXER   hMixer;
    MIXERLINE mxl;
    MIXERLINECONTROLS mxlctrl;
    MIXERCONTROL mxc;

    for(int deviceID = 0;1;deviceId++){
        ret = mixerOpen(&hMixer,deviceID,0,0,MIXER_OBJECTF_MIXER);
        if(ret!=MMSYSERR_NOERROR){
            std::cout << "ERR.LOG:" << __LINE__ << std::end;
            return 0;
        }
        ZeroMemory(&mxl,sizeof(MIXERLINE));
        mxl.cbStruct = sizeof(MIXERLINE);
        /* 指出需要获取的通道，
        声卡的音频输出用 MIXERLINE_COMPONENTTYPE_DST_SPEAKERS
        声卡的音频输入用 MIXERLINE_COMPONENTTYPE_DST_WAVEIN
        */
        mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
        rc = mixerGetLineInfo((HMIXEROBJ)hMixer, &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE);
        if (rc != MMSYSERR_NOERROR)
        {
            continue;
        }
         // 取得混合器设备的指定线路信息成功的话，则将连接数保存 
        DWORD   dwConnections = mxl.cConnections;
        DWORD   dwLineID = -1;
        for (DWORD i = 0; i<dwConnections;)
        {
            mxl.dwSource = i;

            // 根据SourceID获得连接的信息 
            rc = mixerGetLineInfo((HMIXEROBJ)hMixer, &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_SOURCE);

            if (MMSYSERR_NOERROR == rc)
            {
                // ①如果当前设备类型是麦克风，则跳出循环。 
                if (mxl.dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE)
                {
                    // 存储麦克风设备的ID
                    dwLineID = mxl.dwLineID;
                    break;
                }
            }
        }
        if (dwLineID == -1)
        {
            continue;
        }

        // MIXERCONTROL 结构体变量清零
        ZeroMemory(&mxc, sizeof(MIXERCONTROL));

        mxc.cbStruct = sizeof(mxc);

        ZeroMemory(&mxlc, sizeof(MIXERLINECONTROLS));

        // 控制类型为控制音量
        mxlc.cbStruct = sizeof(mxlc);
        mxlc.dwLineID = dwLineID;
        mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
        mxlc.cControls = 1;
        mxlc.pamxctrl = &mxc;
        mxlc.cbmxctrl = sizeof(mxc);

        // ②取得控制器信息
        rc = mixerGetLineControls((HMIXEROBJ)hMixer, &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);

        if (MMSYSERR_NOERROR == rc)
        {
            MIXERCONTROLDETAILS        mxcd;
            MIXERCONTROLDETAILS_SIGNED volStruct;

            ZeroMemory(&mxcd, sizeof(mxcd));

            mxcd.cbStruct = sizeof(mxcd);
            mxcd.dwControlID = mxc.dwControlID;
            mxcd.paDetails = &volStruct;
            mxcd.cbDetails = sizeof(volStruct);
            mxcd.cChannels = 1;

            //③获得音量值，取得的信息放在mxcd中
            rc = mixerGetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_GETCONTROLDETAILSF_VALUE);

            //初始化录音大小的信息   
            MIXERCONTROLDETAILS_UNSIGNED mxcdVolume_Set = { mxc.Bounds.dwMaximum * dwVolume / 100 };
            MIXERCONTROLDETAILS mxcd_Set;
            mxcd_Set.cbStruct = sizeof(MIXERCONTROLDETAILS);
            mxcd_Set.dwControlID = mxc.dwControlID;
            mxcd_Set.cChannels = 1;
            mxcd_Set.cMultipleItems = 0;
            mxcd_Set.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
            mxcd_Set.paDetails = &mxcdVolume_Set;
            //③设置录音大小
            mixerSetControlDetails((HMIXEROBJ)(hMixer),&mxcd_Set,MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE) 
            mixerClose(hMixer);
        }
    }


    return 0;
}
#ifdef JJYYJJYYJJYY
int setAudioInputVolumn(DWORD dwVolume)
{
    //初始化相关结构体
    MMRESULT          rc;
    HMIXER            hMixer;
    MIXERLINE         mxl;
    MIXERLINECONTROLS mxlc;
    MIXERCONTROL      mxc;

    //①遍历系统的混音器，直到找到麦克风的混音器，记录该设备ID
    for (int deviceID = 0; true; deviceID++)
    {
        //打开当前的混音器，deviceID为混音器的id
        rc = mixerOpen(&hMixer, deviceID, 0, 0, MIXER_OBJECTF_MIXER);

        if (MMSYSERR_NOERROR != rc)
        {
            break;
        }

        ZeroMemory(&mxl, sizeof(MIXERLINE));

        mxl.cbStruct = sizeof(MIXERLINE);
        /* 指出需要获取的通道，
        声卡的音频输出用MIXERLINE_COMPONENTTYPE_DST_SPEAKERS
        声卡的音频输入用MIXERLINE_COMPONENTTYPE_DST_WAVEIN
        */
        mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_WAVEIN;
        // 取得混合器设备的指定线路信息
        rc = mixerGetLineInfo((HMIXEROBJ)hMixer, &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE);
        if (rc != MMSYSERR_NOERROR)
        {
            continue;
        }

        // 取得混合器设备的指定线路信息成功的话，则将连接数保存 
        DWORD   dwConnections = mxl.cConnections;
        DWORD   dwLineID = -1;
        for (DWORD i = 0; i<dwConnections;)
        {
            mxl.dwSource = i;

            // 根据SourceID获得连接的信息 
            rc = mixerGetLineInfo((HMIXEROBJ)hMixer, &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_SOURCE);

            if (MMSYSERR_NOERROR == rc)
            {
                // ①如果当前设备类型是麦克风，则跳出循环。 
                if (mxl.dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE)
                {
                    // 存储麦克风设备的ID
                    dwLineID = mxl.dwLineID;
                    break;
                }
            }
        }
        if (dwLineID == -1)
        {
            continue;
        }

        // MIXERCONTROL 结构体变量清零
        ZeroMemory(&mxc, sizeof(MIXERCONTROL));

        mxc.cbStruct = sizeof(mxc);

        ZeroMemory(&mxlc, sizeof(MIXERLINECONTROLS));

        // 控制类型为控制音量
        mxlc.cbStruct = sizeof(mxlc);
        mxlc.dwLineID = dwLineID;
        mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
        mxlc.cControls = 1;
        mxlc.pamxctrl = &mxc;
        mxlc.cbmxctrl = sizeof(mxc);

        // ②取得控制器信息
        rc = mixerGetLineControls((HMIXEROBJ)hMixer, &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);

        if (MMSYSERR_NOERROR == rc)
        {
            MIXERCONTROLDETAILS        mxcd;
            MIXERCONTROLDETAILS_SIGNED volStruct;

            ZeroMemory(&mxcd, sizeof(mxcd));

            mxcd.cbStruct = sizeof(mxcd);
            mxcd.dwControlID = mxc.dwControlID;
            mxcd.paDetails = &volStruct;
            mxcd.cbDetails = sizeof(volStruct);
            mxcd.cChannels = 1;

            //③获得音量值，取得的信息放在mxcd中
            rc = mixerGetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_GETCONTROLDETAILSF_VALUE);

            //初始化录音大小的信息   
            MIXERCONTROLDETAILS_UNSIGNED mxcdVolume_Set = { mxc.Bounds.dwMaximum * dwVolume / 100 };
            MIXERCONTROLDETAILS mxcd_Set;
            mxcd_Set.cbStruct = sizeof(MIXERCONTROLDETAILS);
            mxcd_Set.dwControlID = mxc.dwControlID;
            mxcd_Set.cChannels = 1;
            mxcd_Set.cMultipleItems = 0;
            mxcd_Set.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
            mxcd_Set.paDetails = &mxcdVolume_Set;
            //③设置录音大小
            mixerSetControlDetails((HMIXEROBJ)(hMixer),&mxcd_Set,MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE) 
            mixerClose(hMixer);
        }
    }

    return -1;
}
#endif