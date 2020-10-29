// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("星飞[2;37;0m[2;37;0m", ({"xingba"}));        
        set("gender", "男性");                
        set("long", "星飞[2;37;0m
它是星雨的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xingb");
        set("owner_name", "星雨");
        set_temp("owner", "xingb");
        set_temp("owner_name", "星雨");
        ::setup();
}
