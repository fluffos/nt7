// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include "localtime.h"

inherit ROOM;

string day_event()
{ 
        return NATURE_D->outdoor_room_event();
}

void create()
{
        set("short", "观潮台");
      set("long", @LONG
这是一座颇有点破旧的高台，前面是一望无际的大海。远远望去大海
浩淼，万里无波，海天一线处一道白线滚滚而来，渐近渐快，稍后洪涛汹
涌，白浪连山，倾刻之间已至台下，惊涛骇浪狠狠打在台基上。你顿时感
觉立足不稳，摇摇欲坠，不禁脸上变色，为这天地之威所深深撼动。
LONG );

        set("exits", ([
                "southdown" : __DIR__"beach",
        ]));

        set("outdoors", "taohua");
        set("guanchao", 1);
        set("coor/x", 9040);
        set("coor/y", -2990);
        set("coor/z", 10);
        setup();
}

string long() 
{
        string msg;

        msg  = "这是一座颇有点破旧的高台，前面是一望无际的大海。";

        if (day_event() == "event_dawn" || day_event() == "event_evening")
        {
                msg += "远远望去大海浩淼，万里无波，海天一线处一道白线滚滚而来，渐近渐快，稍后";
                msg += "洪涛汹涌，白浪连山，倾刻之间已至台下，惊涛骇浪狠狠打在台基上。你顿时感觉";
                msg += "立足不稳，摇摇欲坠，不禁脸上变色，为这天地之威所深深撼动。";

        } else 
        {
                msg += "你登高而远望，但见长天一碧，万里无波，当真是“海阔凭鱼跃，天高";
                msg += "任鸟飞”。当此景象，你深吸一口气，只觉胸腹之间清气充盈，轻飘";
                msg += "飘的似乎就要乘风而去。";
        }

        return sort_string(msg, 64, 4); 
}