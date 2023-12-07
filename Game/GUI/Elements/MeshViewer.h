#ifndef INTERACTIVEMODELVIEWER_H
#define INTERACTIVEMODELVIEWER_H

#include <irrlicht.h>

namespace irr {
    namespace scene {

        class InteractiveModelViewer {
        public:
            explicit InteractiveModelViewer(ISceneManager* smgr);

            void setModel(const io::path& modelPath, irr::core::vector2di position);
            void setAnimationFrames(s32 begin, s32 end);
            void setRotation(const core::vector3df& rotation);
            ISceneNode* getSceneNode();

        private:
            ISceneManager* sceneManager;
            IAnimatedMeshSceneNode* modelNode;
        };

    } // end namespace scene
} // end namespace irr

#endif // INTERACTIVEMODELVIEWER_H
