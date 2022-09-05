#ifndef CUSTOMEFFECT_H
#define CUSTOMEFFECT_H

#include <Qt3DRender/QEffect>

class CustomEffect : public Qt3DRender::QEffect
{
public:
    explicit CustomEffect(Qt3DCore::QNode *parent = nullptr);
};

#endif // CUSTOMEFFECT_H
