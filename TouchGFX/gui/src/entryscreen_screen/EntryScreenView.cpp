#include <gui/entryscreen_screen/EntryScreenView.hpp>

EntryScreenView::EntryScreenView()
{

}

void EntryScreenView::setupScreen()
{
    EntryScreenViewBase::setupScreen();
}

void EntryScreenView::tearDownScreen()
{
    EntryScreenViewBase::tearDownScreen();
}

void EntryScreenView::updateInitTextAlpha(uint8_t alpha)
{
    InitText.setAlpha(alpha);
    InitText.invalidate();
}
