//
//  SpriteByUrl.h
//  CheatGame
//
//  Created by yankai.peng on 14/10/20.
//
//

#ifndef __CheatGame__SpriteByUrl__
#define __CheatGame__SpriteByUrl__

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
using namespace cocos2d;
using namespace extension;

class SpriteByUrl : public CCSprite{
    
    
    SpriteByUrl();
    ~SpriteByUrl();
    
public:
    
    
    /**
     
     */
    static SpriteByUrl* createByUrl(const char* url,const char* defaultImage);
    
    static SpriteByUrl* create(const char *pszFileName);
    
    void setImageByUrl(const char* url);

private:
    
    
    
    /**
     判断某个url路径指向图片是否存在缓存中
     */
    bool checkUrlImageStatus(const char *fileName);
    
    void downloadImage(const char *url);
    
    
    void changeImage(const char* fileName);
    
    void SendHttpRequest(const char* url,const char* filename);
    void HttpRequestComplete(CCHttpClient *sender, CCHttpResponse *response);
    
    void checkDone();
    
private:
    
    string m_urlMD5;
    bool isDone;
};

#endif /* defined(__CheatGame__SpriteByUrl__) */
