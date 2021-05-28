/*
    Copyright 2019-2021 natinusala
    Copyright 2021 XITRIX

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <borealis/views/dialog.hpp>
#include <borealis/views/label.hpp>
#include <borealis/core/application.hpp>
#include <borealis/core/i18n.hpp>

using namespace brls::literals;

// TODO: different open animation?

namespace brls
{

const std::string dialogXML = R"xml(
    <brls:Box
        width="auto"
        height="auto"
        axis="column"
        justifyContent="center"
        alignItems="center"
        backgroundColor="@theme/brls/backdrop">

        <brls:AppletFrame
            id="brls/dialog/applet"
            width="720"
            height="auto"
            headerHidden="true"
            footerHidden="true"
            cornerRadius="4"
            backgroundColor="@theme/brls/background">

            <brls:Box
                width="auto"
                height="auto"
                grow="1"
                axis="column">

                <brls:Box
                    id="brls/dialog/container"
                    width="auto"
                    height="auto"
                    grow="1"
                    axis="column"/>

                <brls:Button
                    id="brls/dialog/button3"
                    width="auto"
                    height="72"
                    axis="column"
                    focusable="true"
                    justifyContent="center"
                    alignItems="center"
                    lineTop="2px"
                    lineColor="@theme/brls/sidebar/separator"
                    highlightCornerRadius="6"
                    fontSize="@style/brls/dialog/fontSize"
                    style="borderless"
                    textColor="@theme/brls/accent"
                    text="Continue"
                    visibility="gone"/>

                <brls:Box
                    width="auto"
                    height="72"
                    axis="row"
                    alignItems="stretch"
                    lineTop="2px"
                    lineColor="@theme/brls/sidebar/separator"
                    visibility="gone">

                    <brls:Button
                        id="brls/dialog/button2"
                        width="auto"
                        height="auto"
                        grow="1"
                        focusable="true"
                        justifyContent="center"
                        alignItems="center"
                        highlightCornerRadius="6"
                        text="Continue"
                        style="borderless"
                        lineRight="2px"
                        lineColor="@theme/brls/sidebar/separator"
                        fontSize="@style/brls/dialog/fontSize"
                        textColor="@theme/brls/accent"
                        visibility="gone"/>

                    <brls:Button
                        id="brls/dialog/button1"
                        width="auto"
                        height="auto"
                        grow="1"
                        focusable="true"
                        justifyContent="center"
                        alignItems="center"
                        highlightCornerRadius="6"
                        text="Continue"
                        style="borderless"
                        fontSize="@style/brls/dialog/fontSize"
                        textColor="@theme/brls/accent"/>

                </brls:Box>
            
            </brls:Box>

        </brls:AppletFrame>

    </brls:Box>
)xml";

Dialog::Dialog(Box* contentView)
{
    this->inflateFromXMLString(dialogXML);
    container->addView(contentView);
}

Dialog::Dialog(std::string text)
{
    Style style = Application::getStyle();
    
    Label* label = new Label();
    label->setText(text);
    label->setFontSize(style["brls/dialog/fontSize"]);
    label->setHorizontalAlign(HorizontalAlign::CENTER);
    
    Box* box = new Box();
    box->addView(label);
    box->setAlignItems(AlignItems::CENTER);
    box->setJustifyContent(JustifyContent::CENTER);
    box->setPadding(style["brls/dialog/paddingTopBottom"], style["brls/dialog/paddingLeftRight"], style["brls/dialog/paddingTopBottom"], style["brls/dialog/paddingLeftRight"]);
    
    new (this) Dialog(box);
    
    appletFrame->registerAction(
        "brls/hints/back"_i18n, BUTTON_B, [this](View* view) {
            if (cancelable)
                this->dismiss();
            return cancelable;
        },
        false, SOUND_BACK);
}

void Dialog::addButton(std::string label, GenericEvent::Callback cb)
{
    if (this->buttons.size() >= 3)
        return;

    DialogButton* button = new DialogButton();
    button->label        = label;
    button->cb           = cb;

    this->buttons.push_back(button);

    this->rebuildButtons();
}

void Dialog::open()
{
    Application::pushActivity(new Activity(this));
}

void Dialog::close()
{
    Box::dismiss();
}

void Dialog::setCancelable(bool cancelable)
{
    this->cancelable = cancelable;
}

void Dialog::rebuildButtons()
{
    if (this->buttons.size() > 0)
    {
        button1->getParent()->setVisibility(Visibility::VISIBLE);
        
        button1->setVisibility(Visibility::VISIBLE);
        button1->setText(buttons[0]->label);
        button1->registerClickAction([this](View* view) {
            buttons[0]->cb(view);
            return true;
        });
    }
    
    if (this->buttons.size() > 1)
    {
        button2->setVisibility(Visibility::VISIBLE);
        button2->setText(buttons[1]->label);
        button2->registerClickAction([this](View* view) {
            buttons[1]->cb(view);
            return true;
        });
    }
    
    if (this->buttons.size() > 2)
    {
        button3->setVisibility(Visibility::VISIBLE);
        button3->setText(buttons[2]->label);
        button3->registerClickAction([this](View* view) {
            buttons[2]->cb(view);
            return true;
        });
    }
}

AppletFrame* Dialog::getAppletFrame()
{
    return appletFrame;
}

Dialog::~Dialog()
{
    
}

} // namespace brls
