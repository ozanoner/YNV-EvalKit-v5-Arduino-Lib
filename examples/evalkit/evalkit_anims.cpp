
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
void EvalkitAnims::init(ECDEvalkitDisplay_t displayType)
{
    auto& evalkitDisplays = ynv::ecd::EvalkitDisplays::getInstance();
    m_displayType         = displayType;

    switch (displayType)
    {
        case ECDEvalkitDisplay_t::EVALKIT_DISP_SINGLE_SEGMENT_DISPLAY:
            m_anims[ANIM_TOGGLE] =
                std::make_unique<AnimToggle>(*static_cast<ynv::ecd::DispSingleSegment*>(evalkitDisplays[displayType]));
            m_anims[ANIM_1SEG_ON] =
                std::make_unique<Anim1SegOn>(*static_cast<ynv::ecd::DispSingleSegment*>(evalkitDisplays[displayType]));
            break;
        case ECDEvalkitDisplay_t::EVALKIT_DISP_THREE_SEGMENT_BAR_DISPLAY:
            m_anims[ANIM_TOGGLE] =
                std::make_unique<AnimToggle>(*static_cast<ynv::ecd::Disp3SegBar*>(evalkitDisplays[displayType]));
            m_anims[ANIM_3SEGBAR_COUNTER_UP] = std::make_unique<Anim3SegBarCounterUp>(
                *static_cast<ynv::ecd::Disp3SegBar*>(evalkitDisplays[displayType]));
            m_anims[ANIM_3SEGBAR_COUNTER_DOWN] = std::make_unique<Anim3SegBarCounterDown>(
                *static_cast<ynv::ecd::Disp3SegBar*>(evalkitDisplays[displayType]));
            m_anims[ANIM_3SEGBAR_POS] =
                std::make_unique<Anim3SegBarPos>(*static_cast<ynv::ecd::Disp3SegBar*>(evalkitDisplays[displayType]));
            break;
        case ECDEvalkitDisplay_t::EVALKIT_DISP_SEVEN_SEGMENT_BAR_DISPLAY:
            m_anims[ANIM_TOGGLE] =
                std::make_unique<AnimToggle>(*static_cast<ynv::ecd::Disp7SegBar*>(evalkitDisplays[displayType]));
            m_anims[ANIM_7SEGBAR_COUNTER_UP] = std::make_unique<Anim7SegBarCounterUp>(
                *static_cast<ynv::ecd::Disp7SegBar*>(evalkitDisplays[displayType]));
            m_anims[ANIM_7SEGBAR_COUNTER_DOWN] = std::make_unique<Anim7SegBarCounterDown>(
                *static_cast<ynv::ecd::Disp7SegBar*>(evalkitDisplays[displayType]));
            break;
        case ECDEvalkitDisplay_t::EVALKIT_DISP_DOT_NUMBER_DISPLAY:
            m_anims[ANIM_TOGGLE] =
                std::make_unique<AnimToggle>(*static_cast<ynv::ecd::DispDotNumber*>(evalkitDisplays[displayType]));
            m_anims[ANIM_7SEGNUM_COUNTER_UP] = std::make_unique<Anim7SegNumCounterUp>(
                *static_cast<ynv::ecd::DispDotNumber*>(evalkitDisplays[displayType]));
            m_anims[ANIM_7SEGNUM_COUNTER_DOWN] = std::make_unique<Anim7SegNumCounterDown>(
                *static_cast<ynv::ecd::DispDotNumber*>(evalkitDisplays[displayType]));
            break;
        case ECDEvalkitDisplay_t::EVALKIT_DISP_DECIMAL_NUMBER_DISPLAY:
            m_anims[ANIM_TOGGLE] =
                std::make_unique<AnimToggle>(*static_cast<ynv::ecd::DispDecimalNumber*>(evalkitDisplays[displayType]));
            m_anims[ANIM_15SEGDEC_COUNTER_UP] = std::make_unique<Anim15SegDecimalCounterUp>(
                *static_cast<ynv::ecd::DispDecimalNumber*>(evalkitDisplays[displayType]));
            m_anims[ANIM_15SEGDEC_COUNTER_DOWN] = std::make_unique<Anim15SegDecimalCounterDown>(
                *static_cast<ynv::ecd::DispDecimalNumber*>(evalkitDisplays[displayType]));
            break;
        case ECDEvalkitDisplay_t::EVALKIT_DISP_SIGNED_NUMBER_DISPLAY:
            m_anims[ANIM_TOGGLE] =
                std::make_unique<AnimToggle>(*static_cast<ynv::ecd::DispSignedNumber*>(evalkitDisplays[displayType]));
            m_anims[ANIM_15SEGSIGNED_POSITIVE_COUNTER_UP] = std::make_unique<Anim15SegSignedPositiveCounterUp>(
                *static_cast<ynv::ecd::DispSignedNumber*>(evalkitDisplays[displayType]));
            m_anims[ANIM_15SEGSIGNED_POSITIVE_COUNTER_DOWN] = std::make_unique<Anim15SegSignedPositiveCounterDown>(
                *static_cast<ynv::ecd::DispSignedNumber*>(evalkitDisplays[displayType]));
            m_anims[ANIM_15SEGSIGNED_NEGATIVE_COUNTER_UP] = std::make_unique<Anim15SegSignedNegativeCounterUp>(
                *static_cast<ynv::ecd::DispSignedNumber*>(evalkitDisplays[displayType]));
            m_anims[ANIM_15SEGSIGNED_NEGATIVE_COUNTER_DOWN] = std::make_unique<Anim15SegSignedNegativeCounterDown>(
                *static_cast<ynv::ecd::DispSignedNumber*>(evalkitDisplays[displayType]));
            break;

        default:
            break;
    }

    for (size_t i = 0; i < ANIM_CNT; i++)
    {
        if (m_anims[i] != nullptr)
        {
        }
    }
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