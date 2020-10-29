// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m实在太拉风[2;37;0m[2;37;0m", ({"xxo"}));        
        set("gender", "男性");                
        set("long", "这是一个肥嘟嘟的直流口水的白虎。[2;37;0m
它是雨菡萏的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yuhan");
        set("owner_name", "雨菡萏");
        set_temp("owner", "yuhan");
        set_temp("owner_name", "雨菡萏");
        ::setup();
}
