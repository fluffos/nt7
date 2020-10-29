// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("赤炎圣凰[2;37;0m[2;37;0m", ({"feihong"}));        
        set("gender", "男性");                
        set("long", "赤炎圣凰[2;37;0m
它是毛毛细雨的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "feiheng");
        set("owner_name", "毛毛细雨");
        set_temp("owner", "feiheng");
        set_temp("owner_name", "毛毛细雨");
        ::setup();
}
