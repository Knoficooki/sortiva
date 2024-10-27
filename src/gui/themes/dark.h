//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// StyleAsCode exporter v2.0 - Style data exported as a values array            //
//                                                                              //
// USAGE: On init call: GuiLoadStyleDark();                                   //
//                                                                              //
// more info and bugs-report:  github.com/raysan5/raygui                        //
// feedback and support:       ray[at]raylibtech.com                            //
//                                                                              //
// Copyright (c) 2020-2023 raylib technologies (@raylibtech)                    //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#define DARK_STYLE_PROPS_COUNT  8

// Custom style name: dark
static const GuiStyleProp darkStyleProps[DARK_STYLE_PROPS_COUNT] = {
    { 0, 0, 0x7b7b7bff },    // DEFAULT_BORDER_COLOR_NORMAL 
    { 0, 1, 0x595959ff },    // DEFAULT_BASE_COLOR_NORMAL 
    { 0, 2, 0xdededeff },    // DEFAULT_TEXT_COLOR_NORMAL 
    { 0, 9, 0x232323ff },    // DEFAULT_BORDER_COLOR_DISABLED 
    { 0, 10, 0x606060ff },    // DEFAULT_BASE_COLOR_DISABLED 
    { 0, 11, 0x9f9f9fff },    // DEFAULT_TEXT_COLOR_DISABLED 
    { 0, 18, 0x68cbd0ff },    // DEFAULT_LINE_COLOR 
    { 0, 19, 0x262626ff },    // DEFAULT_BACKGROUND_COLOR 
};

// Style loading function: dark
static void GuiLoadStyleDark(void)
{
    // Load style properties provided
    // NOTE: Default properties are propagated
    for (int i = 0; i < DARK_STYLE_PROPS_COUNT; i++)
    {
        GuiSetStyle(darkStyleProps[i].controlId, darkStyleProps[i].propertyId, darkStyleProps[i].propertyValue);
    }

    //-----------------------------------------------------------------

    // TODO: Custom user style setup: Set specific properties here (if required)
    // i.e. Controls specific BORDER_WIDTH, TEXT_PADDING, TEXT_ALIGNMENT
}
