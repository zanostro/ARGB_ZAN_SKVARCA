#include <gui/entryscreen_screen/EntryScreenView.hpp>
#include <gui/entryscreen_screen/EntryScreenPresenter.hpp>
#include <gui/common/FrontendApplication.hpp>

EntryScreenPresenter::EntryScreenPresenter(EntryScreenView& v)
    : view(v)
{

}

void EntryScreenPresenter::activate()
{

}

void EntryScreenPresenter::deactivate()
{

}

void EntryScreenPresenter::transitionToScreen1()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen1ScreenNoTransition();
}

void EntryScreenPresenter::updateInitTextAlpha(uint8_t alpha)
{
    view.updateInitTextAlpha(alpha);
}
