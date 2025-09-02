#ifndef ENTRYSCREENVIEW_HPP
#define ENTRYSCREENVIEW_HPP

#include <gui_generated/entryscreen_screen/EntryScreenViewBase.hpp>
#include <gui/entryscreen_screen/EntryScreenPresenter.hpp>

class EntryScreenView : public EntryScreenViewBase
{
public:
    EntryScreenView();
    virtual ~EntryScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    void updateInitTextAlpha(uint8_t alpha);
protected:
};

#endif // ENTRYSCREENVIEW_HPP
