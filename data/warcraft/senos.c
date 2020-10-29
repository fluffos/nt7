// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大块头[2;37;0m[2;37;0m", ({"hoho"}));        
        set("gender", "男性");                
        set("long", "一大坨[2;37;0m
它是笑青的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "senos");
        set("owner_name", "笑青");
        set_temp("owner", "senos");
        set_temp("owner_name", "笑青");
        ::setup();
}
