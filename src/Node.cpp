/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Sille Van Landschoot
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


#include <Node.h>
#include <stdio.h>
#include <stdlib.h>

void onEvent(ev_t ev)
{
    SimpleLoRaWAN::Node::onEvent(ev);
}




namespace SimpleLoRaWAN
{

Node::Node()
{
    init();
}

Node::~Node()
{

}

void Node::init()
{
    os_init();

    // reset MAC state
    LMIC_reset();
    LMIC_setDrTxpow(DR_SF7, 14);
}


void Node::send(char* data, int size)
{
    memcpy (LMIC.frame, data, size);
    LMIC_setTxData2(15, LMIC.frame, size, 0);
}


void Node::onEvent(ev_t ev)
{
    printf("Event (%d)!!!\r\n", ev);
    switch(ev) {
        case EV_JOINED:
            printf("JOINED\n\r");
            LMIC_setLinkCheckMode(0); // Link check is currently not implemented for TTN, so just disable it
            break;
        case EV_TXCOMPLETE:
            printf("TXCOMPLETE\n\r");
            break;
        default:
            break;
    }
}

void Node::process()
{
    os_runloop_once();
}

void Node::enableLinkCheck()
{
    setLinkCheck(true);
}

void Node::disableLinkCheck()
{
    setLinkCheck(false);
}

void Node::setLinkCheck(int state)
{
    LMIC_setLinkCheckMode(state);
}


} /* namespace SimpleLoRaWAN */