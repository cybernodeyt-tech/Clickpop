#include <Geode/Geode.hpp>
#include <Geode/modify/CCTouchDispatcher.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <algorithm>
#include <Geode/modify/PlayLayer.hpp>
#include <algorithm>
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

class $modify(ScarePlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obj) {
        bool wasDead = m_player1 && m_player1->m_isDead;
        PlayLayer::destroyPlayer(player, obj);
        if (wasDead || !m_player1 || !m_player1->m_isDead) return;

        auto scene = CCDirector::get()->getRunningScene();
        auto spr = CCSprite::create("flag.png"_spr);
        if (!scene || !spr) return;
        auto win = CCDirector::get()->getWinSize();
        auto cs = spr->getContentSize();
        float s = std::max(win.width / cs.width, win.height / cs.height);
        spr->setPosition({win.width / 2.f, win.height / 2.f});
        spr->setScale(0.1f * s);
        scene->addChild(spr, 100000);
        spr->runAction(CCSequence::create(
            CCScaleTo::create(0.06f, s),
            CCDelayTime::create(0.45f),
            CCFadeOut::create(0.2f),
            CCRemoveSelf::create(),
            nullptr));
    }
};

class $modify(ScarePlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obj) {
        bool wasDead = m_player1 && m_player1->m_isDead;
        PlayLayer::destroyPlayer(player, obj);
        if (wasDead || !m_player1 || !m_player1->m_isDead) return;

        auto scene = CCDirector::get()->getRunningScene();
        auto spr = CCSprite::create("flag.png"_spr);
        if (!scene || !spr) return;
        auto win = CCDirector::get()->getWinSize();
        auto cs = spr->getContentSize();
        float s = std::max(win.width / cs.width, win.height / cs.height);
        spr->setPosition({win.width / 2.f, win.height / 2.f});
        spr->setScale(0.1f * s);
        scene->addChild(spr, 100000);
        spr->runAction(CCSequence::create(
            CCScaleTo::create(0.06f, s),
            CCDelayTime::create(0.45f),
            CCFadeOut::create(0.2f),
            CCRemoveSelf::create(),
            nullptr));
    }
};
