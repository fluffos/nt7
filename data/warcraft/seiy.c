// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"seiyl"}));        
        set("gender", "男性");                
        set("long", "火红色，相当华丽的一只大型鸟（？）类[2;37;0m
它是雨裳的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "seiy");
        set("owner_name", "雨裳");
        set_temp("owner", "seiy");
        set_temp("owner_name", "雨裳");
        ::setup();
}
