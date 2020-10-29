// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞龟[2;37;0m[2;37;0m", ({"flyturtle"}));        
        set("gender", "男性");                
        set("long", "飞龟[2;37;0m
它是武当四侠的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "wudangiii");
        set("owner_name", "武当四侠");
        set_temp("owner", "wudangiii");
        set_temp("owner_name", "武当四侠");
        ::setup();
}
