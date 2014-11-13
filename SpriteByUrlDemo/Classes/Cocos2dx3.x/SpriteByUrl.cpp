//
//  SpriteByUrl.cpp
//  CheatGame
//
//  Created by yankai.peng on 14/10/20.
//
//

#include "SpriteByUrl.h"
#include "md5.h"


SpriteByUrl::SpriteByUrl(){
    
    m_urlMD5="";
    isDone=false;
    
}

SpriteByUrl::~SpriteByUrl(){
    

}


SpriteByUrl* SpriteByUrl::createByUrl(const char *url,const char* defaultImage){
    
    
    
    SpriteByUrl *spr= create(defaultImage);
    
    spr->setImageByUrl(url);
    
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

void SpriteByUrl::setImageByUrl(const char *url){
    
    m_urlMD5=MD5(url).toString();
    if(checkUrlImageStatus(m_urlMD5.c_str())){
        changeImage(m_urlMD5.c_str());
    }else{
        
        downloadImage(url);
        
        schedule(schedule_selector(SpriteByUrl::checkDone), 1);
        
    }
}

void SpriteByUrl::checkDone(float num){
    
    if(isDone){
        
        if(checkUrlImageStatus(m_urlMD5.c_str())){
            
            if(this->isRunning()){
                changeImage(m_urlMD5.c_str());
                unschedule(schedule_selector(SpriteByUrl::checkDone));
    
            }
        }
    }
    
}

void SpriteByUrl::changeImage(const char *fileName){
    
    std::string path = FileUtils::getInstance()->getWritablePath();
    path+=fileName;
    
    
    Image *img=new Image();
    img->initWithImageFile(path.c_str());
    Texture2D *texture=new Texture2D();
    texture->initWithImage(img);
    
//    CCTexture2D *texture= CCTextureCache::sharedTextureCache()->addImage(path.c_str());
    
    this->setTexture(texture);
    this->setTextureRect(Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));

//    delete texture;
//    delete img;
    
}


void SpriteByUrl::downloadImage(const char *url){
    
    
    SendHttpRequest(url, m_urlMD5.c_str());
}

bool SpriteByUrl::checkUrlImageStatus(const char *fileName){
    std::string path = FileUtils::getInstance()->getWritablePath();
    path+=fileName;
    
    if(FileUtils::getInstance()->isFileExist(path)) return true;
    
    return false;
}

void SpriteByUrl::SendHttpRequest(const char* url, const char* filename)
{
    HttpRequest* request = new HttpRequest();
    request->setUrl(url);
    //    request->setUrl("http://neoimaging.beareyes.com.cn/png2/ni_png_2_1518.png");
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(SpriteByUrl::HttpRequestComplete));
    request->setTag("GET IMAGE");
    request->setUserData((void *)filename);
    HttpClient::getInstance()->send(request);
//    request->release();
}

void SpriteByUrl::HttpRequestComplete(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLOG("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    CCLOG("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLOG("response failed");
        CCLOG("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    std::string path = FileUtils::getInstance()->getWritablePath();
    std::string bufffff(buffer->begin(),buffer->end());
    
    
    const char* fileName=(const char *)(response->getHttpRequest()->getUserData());
    
    //保存到本地文件
    path += fileName;
    CCLOG("path: %s",path.c_str());
    FILE *fp = fopen(path.c_str(), "wb+");
    fwrite(bufffff.c_str(), 1,buffer->size(), fp);
    fclose(fp);
    
    isDone=true;
    
}
