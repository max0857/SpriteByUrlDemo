//
//  SpriteByUrl.cpp
//  CheatGame
//
//  Created by yankai.peng on 14/10/20.
//
//

#include "SpriteByUrl.h"


SpriteByUrl::SpriteByUrl(){
    
    m_defaultImageFileName="";
    
}

SpriteByUrl::~SpriteByUrl(){
    

}


SpriteByUrl* SpriteByUrl::createByUrl(const char *url){
    
    
    assert(m_defaultImageFileName=="");//必须设置正确的默认图片
    
    SpriteByUrl *spr= create(m_defaultImageFileName.c_str());
    
    return spr;
}


SpriteByUrl* SpriteByUrl::create(const char *pszFileName)
{
    SpriteByUrl *pobSprite = new SpriteByUrl();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void SpriteByUrl::setDefaultImage(const char *fileName){
    
    m_defaultImageFileName=fileName;
    
}