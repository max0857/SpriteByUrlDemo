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

using namespace std;
using namespace cocos2d;


class SpriteByUrl : public CCSprite{
    
    
    SpriteByUrl();
    ~SpriteByUrl();
    
public:
    
    /**
     设置图片未加载完成时的默认图片
     */
    static void setDefaultImage(const char *fileName);
    
    /**
     
     */
    static SpriteByUrl* createByUrl(const char* url);
    
    static SpriteByUrl* create(const char *pszFileName);
    
    void setImageByUrl(const char* url);

private:
    
    
    
    /**
     判断某个url路径指向图片是否存在缓存中
     */
    bool checkUrlImageStatus(const char *url);
    
private:
    
    static string m_defaultImageFileName;
};

#endif /* defined(__CheatGame__SpriteByUrl__) */
