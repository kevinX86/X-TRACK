/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "Arduino.h"
#include "Display/Display.h"
#include "HAL/HAL.h"
#include "App/App.h"
#include "lv_examples/lv_demo.h"
#include "StackInfo/StackInfo.h"

static void setup()
{
    HAL::HAL_Init();
    Display_Init();

    App_Init();

    //lv_demo_benchmark();
    //lv_demo_widgets();
    //lv_demo_keypad_encoder();

    HAL::Power_SetEventCallback(App_Uninit);
}

static void loop()
{
    HAL::HAL_Update();
    lv_task_handler();

#if CONFIG_USE_STACK_INFO
    __IntervalExecute(
        Serial.printf(
            "Stack: Use = %0.2f%% Free = %d\r\n",
            StackInfo_GetMaxUtilization() * 100,
            StackInfo_GetMinFreeSize()
        ),
        1000
    );
#endif

    __wfi();
}

/**
  * @brief  Main Function
  * @param  None
  * @retval None
  */
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    GPIO_JTAG_Disable();
    Delay_Init();
    //ADCx_Init(ADC1);
    setup();
    for(;;)loop();
}
