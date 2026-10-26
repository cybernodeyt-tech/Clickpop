#include <Geode/Geode.hpp>
#include <Geode/modify/CCTouchDispatcher.hpp>
#include <cstdlib>
#include <ctime>

using namespace geode::prelude;

class $modify(PopDispatcher, CCTouchDispatcher) {
    void touches(CCSet* touches, CCEvent* event, unsigned int type) {
        if (type == 0) {
            static bool seeded = false;
            if (!seeded) { std::srand((unsigned)std::time(nullptr)); seeded = true; }

            auto touch = static_cast<CCTouch*>(touches->anyObject());
            auto scene = CCDirector::get()->getRunningScene();
            if (touch && scene) {
                bool flag = std::rand() % 2 == 0;
                auto spr = CCSprite::create(flag ? "flag.png"_spr : "person.png"_spr);
                if (spr) {
                    float target = 70.f / spr->getContentSize().height;
                    spr->setPosition(touch->getLocation());
                    spr->setScale(0.f);
                    scene->addChild(spr, 99999);
                    spr->runAction(CCSequence::create(
                        CCEaseBackOut::create(CCScaleTo::create(0.15f, target)),
                        CCDelayTime::create(0.5f),
                        CCFadeOut::create(0.25f),
                        CCRemoveSelf::create(),
                        nullptr));
                }
            }
        }
        CCTouchDispatcher::touches(touches, event, type);
    }
};
