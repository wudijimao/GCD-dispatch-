//
//  ChatClient.hpp
//  TestUI
//
//  Created by ximiao on 16/6/15.
//  Copyright © 2016年 wudijimao. All rights reserved.
//

#pragma once

#include <XDUILib.hpp>

#pragma pack push
#pragma pack (1)     /*set pack*/
//struct __attribute__((packed)) ChatPackage {
struct ChatPackage {
    uint16_t type; //0-999 底层类型 1000-19999消息类型
    char str[];
};
#pragma pack pop

//type
//0 heart beat
//1 debug mes
//1000 login
//1001 logout
//1002 simple_text




//#progma pack ()     /*cancle*/

class PackageMaker {
public:
    
};

namespace MesType {
    //low level 0 - 999
    const uint16_t cHeartBeat = 0;
    const uint16_t cDebugMes = 1;
    //login and account 1000 - 1099
    const uint16_t cLoginWithPassword = 1000; //确认成功会用相同code返回
    const uint16_t cLogout = 1001;
    const uint16_t cNoAccount = 1002;
    const uint16_t cPasswordNotCorrect = 1003;
    //mes 1100 - max
    const uint16_t cSimpleText = 1100;
};

class ChatClient {
public:
    XSocketClient client;
    std::string mUserID = "test";
    std::string mPassword = "test";
    static ChatClient&getInstance() {
        static ChatClient client;
        return client;
    }
    std::function<void(ChatClient&, std::error_code)> onLoginFinish;
    //std::function<void(ChatClient&, std::error_code)> onSimpleTextSendFinish;
    std::function<void(ChatClient&, const char*str)> onRecvSimpleText;
    void run() {
        XResource::XDataPtr data = XResource::XData::data();
        client.onConnect = [&](){
            sendLoginMes();
        };
        
        client.setOnRecvData([&](const void *dat, unsigned int size) {
            ChatPackage *package = (ChatPackage*)dat;
            std::error_code e;
            switch(package->type) {
                case MesType::cHeartBeat:
                    break;
                case MesType::cDebugMes:
                    std::cout << "debugMes:" << package->str << std::endl;
                    break;
                case MesType::cLoginWithPassword:
                    std::cout << "loginSuccess" << std::endl;
                    if (onLoginFinish) {
                        onLoginFinish(*this, e);
                    }
                    break;
                case MesType::cSimpleText:
                    if (onRecvSimpleText) {
                        onRecvSimpleText(*this, package->str);
                    }
                    std::cout << "Recv SimpleText:" << package->str << std::endl;
                    break;
            }
        });
        client.connect("138.128.201.89", 7777);
    }
    void sendLoginMes() {
        sendStr(MesType::cLoginWithPassword, mUserID.c_str(), mUserID.length());
    }
    void sendSimpleText(const char*str, long length = -1) {
        sendStr(MesType::cSimpleText, str, length);
    }
    void sendStr(uint16_t type, const char*str, long length = -1) {
        if(length < 0) {
            length = strlen(str);
        }
        uint16_t dataLen = uint16_t(length + 3);
        XResource::XDataPtr data = XResource::XData::data();
        data->resize(dataLen + 2);
        data->appendData((void*)&dataLen, 2);
        data->appendData((void*)&type, 2);
        data->appendData(str, length + 1);
        client.send(data);
    }
};