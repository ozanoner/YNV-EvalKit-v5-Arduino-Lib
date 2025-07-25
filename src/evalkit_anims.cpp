
#include "evalkit_anims.h"

#include <memory>

#include "anim_01.h"
#include "anim_02.h"
#include "anim_03.h"
#include "anim_04.h"
#include "anim_05.h"
#include "anim_06.h"
#include "anim_07.h"
#include "anim_08.h"
#include "anim_09.h"
#include "anim_10.h"
#include "anim_11.h"
#include "anim_12.h"
#include "anim_13.h"
#include "anim_14.h"
#include "anim_15.h"

namespace ynv
{
namespace anim
{
void EvalkitAnims::init(const ynv::app::AppConfig_t* appConfig)
{
    assert(appConfig != nullptr);
    assert(appConfig->displayIndex >= 0 &&
           appConfig->displayIndex < static_cast<int>(ECDEvalkitDisplay_t::EVALKIT_DISP_CNT));
    m_appConfig = appConfig;

    auto display  = ynv::ecd::EvalkitDisplays::getInstance().getDisplay();
    m_displayType = static_cast<ECDEvalkitDisplay_t>(appConfig->displayIndex);

    switch (m_displayType)
    {
        case ECDEvalkitDisplay_t::EVALKIT_DISP_SINGLE_SEGMENT_DISPLAY:
            m_anims[ANIM_TOGGLE] = std::make_unique<AnimToggle>(display);
            m_anims[ANIM_1SEG_ON] =
                std::make_unique<Anim1SegOn>(std::static_pointer_cast<ynv::ecd::DispSingleSegment>(display));
            break;
        case ECDEvalkitDisplay_t::EVALKIT_DISP_THREE_SEGMENT_BAR_DISPLAY:
            m_anims[ANIM_TOGGLE] = std::make_unique<AnimToggle>(display);
            m_anims[ANIM_3SEGBAR_COUNTER_UP] =
                std::make_unique<Anim3SegBarCounterUp>(std::static_pointer_cast<ynv::ecd::Disp3SegBar>(display));
            m_anims[ANIM_3SEGBAR_COUNTER_DOWN] =
                std::make_unique<Anim3SegBarCounterDown>(std::static_pointer_cast<ynv::ecd::Disp3SegBar>(display));
            m_anims[ANIM_3SEGBAR_POS] =
                std::make_unique<Anim3SegBarPos>(std::static_pointer_cast<ynv::ecd::Disp3SegBar>(display));
            break;
        case ECDEvalkitDisplay_t::EVALKIT_DISP_SEVEN_SEGMENT_BAR_DISPLAY:
            m_anims[ANIM_TOGGLE] = std::make_unique<AnimToggle>(display);
            m_anims[ANIM_7SEGBAR_COUNTER_UP] =
                std::make_unique<Anim7SegBarCounterUp>(std::static_pointer_cast<ynv::ecd::Disp7SegBar>(display));
            m_anims[ANIM_7SEGBAR_COUNTER_DOWN] =
                std::make_unique<Anim7SegBarCounterDown>(std::static_pointer_cast<ynv::ecd::Disp7SegBar>(display));
            break;
        case ECDEvalkitDisplay_t::EVALKIT_DISP_DOT_NUMBER_DISPLAY:
            m_anims[ANIM_TOGGLE] = std::make_unique<AnimToggle>(display);
            m_anims[ANIM_7SEGNUM_COUNTER_UP] =
                std::make_unique<Anim7SegNumCounterUp>(std::static_pointer_cast<ynv::ecd::DispDotNumber>(display));
            m_anims[ANIM_7SEGNUM_COUNTER_DOWN] =
                std::make_unique<Anim7SegNumCounterDown>(std::static_pointer_cast<ynv::ecd::DispDotNumber>(display));
            break;
        case ECDEvalkitDisplay_t::EVALKIT_DISP_DECIMAL_NUMBER_DISPLAY:
            m_anims[ANIM_TOGGLE]              = std::make_unique<AnimToggle>(display);
            m_anims[ANIM_15SEGDEC_COUNTER_UP] = std::make_unique<Anim15SegDecimalCounterUp>(
                std::static_pointer_cast<ynv::ecd::DispDecimalNumber>(display));
            m_anims[ANIM_15SEGDEC_COUNTER_DOWN] = std::make_unique<Anim15SegDecimalCounterDown>(
                std::static_pointer_cast<ynv::ecd::DispDecimalNumber>(display));
            break;
        case ECDEvalkitDisplay_t::EVALKIT_DISP_SIGNED_NUMBER_DISPLAY:
            m_anims[ANIM_TOGGLE]                          = std::make_unique<AnimToggle>(display);
            m_anims[ANIM_15SEGSIGNED_POSITIVE_COUNTER_UP] = std::make_unique<Anim15SegSignedPositiveCounterUp>(
                std::static_pointer_cast<ynv::ecd::DispSignedNumber>(display));
            m_anims[ANIM_15SEGSIGNED_POSITIVE_COUNTER_DOWN] = std::make_unique<Anim15SegSignedPositiveCounterDown>(
                std::static_pointer_cast<ynv::ecd::DispSignedNumber>(display));
            m_anims[ANIM_15SEGSIGNED_NEGATIVE_COUNTER_UP] = std::make_unique<Anim15SegSignedNegativeCounterUp>(
                std::static_pointer_cast<ynv::ecd::DispSignedNumber>(display));
            m_anims[ANIM_15SEGSIGNED_NEGATIVE_COUNTER_DOWN] = std::make_unique<Anim15SegSignedNegativeCounterDown>(
                std::static_pointer_cast<ynv::ecd::DispSignedNumber>(display));
            break;

        default:
            break;
    }

    display->printConfig();
}

EvalkitAnims::Anim_t EvalkitAnims::select(EvalkitAnims::Anim_t anim, bool forward)
{
    if (m_anims[m_currentAnim]->getState() != AnimBase::State_t::IDLE)
    {
        // If there is a running animation, do not change it.
        // User has to abort the current animation first.
        return m_currentAnim;
    }

    // no infinite loop as AnimToggle is supported by all displays
    while (m_anims[anim] == nullptr)
    {
        if (forward)
        {
            anim = static_cast<Anim_t>((anim + 1) % ANIM_CNT);
        }
        else
        {
            anim = static_cast<Anim_t>((anim + ANIM_CNT - 1) % ANIM_CNT);
        }
    }

    // Set the current animation to the selected one
    m_currentAnim = anim;
    // Update the callback for state changes
    m_anims[m_currentAnim]->registerStateChangeCallback(m_stateChangeCallback);

    return m_currentAnim;
}

EvalkitAnims::Anim_t EvalkitAnims::next()
{
    return select(static_cast<Anim_t>((m_currentAnim + 1) % ANIM_CNT));
}

EvalkitAnims::Anim_t EvalkitAnims::previous()
{
    return select(static_cast<Anim_t>((m_currentAnim + ANIM_CNT - 1) % ANIM_CNT), false);
}

}  // namespace anim
}  // namespace ynv