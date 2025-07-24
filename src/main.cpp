#include <Geode/Geode.hpp>
#include <Geode/modify/CCLayer.hpp>

using namespace geode::prelude;

int visibleCount = 0;

void makeAllVisible(CCNode* node) {
    if (!node) return;

    if (!node->isVisible()) {
        node->setVisible(true);
        visibleCount++;
    }

    for (auto child : CCArrayExt<CCNode*>(node->getChildren())) {
        makeAllVisible(child);
    }
}

class $modify(VisibleAlls, CCLayer) {
    void onEnter() {
        CCLayer::onEnter();

        visibleCount = 0;
        makeAllVisible(this);

        log::info("Force visible called on layer {} made visible {} nodes", typeid(*this).name(), visibleCount);
    }
};