#include "MeshViewer.h"

using namespace irr;
using namespace scene;
using namespace core;

InteractiveModelViewer::InteractiveModelViewer(ISceneManager* smgr)
    : sceneManager(smgr), modelNode(nullptr) {
}

void InteractiveModelViewer::setModel(const io::path& modelPath, vector2di position) {
    if (modelNode) {
        modelNode->remove();
    }
    modelNode = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh(modelPath));
    vector3df p = sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates(position, sceneManager->getActiveCamera()).end;
    vector3df generalPosition = vector3df(p.X, p.Y, 30); // 30 = TestValue for 3d model's distance to camera

}

void InteractiveModelViewer::setAnimationFrames(s32 begin, s32 end) {
    if (!modelNode) return;

    IAnimatedMeshSceneNode* animatedNode = dynamic_cast<IAnimatedMeshSceneNode*>(modelNode);
    if (animatedNode) {
        animatedNode->setFrameLoop(begin, end);
    }
}

void InteractiveModelViewer::setRotation(const vector3df& rotation) {
    if (modelNode) {
        modelNode->setRotation(rotation);
    }
}

ISceneNode* InteractiveModelViewer::getSceneNode() {
    return modelNode;
}
