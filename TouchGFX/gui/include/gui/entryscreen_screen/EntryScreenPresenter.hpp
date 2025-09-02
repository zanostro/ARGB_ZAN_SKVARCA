#ifndef ENTRYSCREENPRESENTER_HPP
#define ENTRYSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class EntryScreenView;

class EntryScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    EntryScreenPresenter(EntryScreenView& v);

   
    virtual void activate();

    virtual void deactivate();

    virtual ~EntryScreenPresenter() {}
    
    virtual void transitionToScreen1();
    virtual void updateInitTextAlpha(uint8_t alpha);

private:
    EntryScreenPresenter();

    EntryScreenView& view;
};

#endif // ENTRYSCREENPRESENTER_HPP
