// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m赤炎[2;37;0m[2;37;0m", ({"zkh"}));        
        set("gender", "男性");                
        set("long", "一团火。。。。[2;37;0m
它是鬼吹灯的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zhou");
        set("owner_name", "鬼吹灯");
        set_temp("owner", "zhou");
        set_temp("owner_name", "鬼吹灯");
        ::setup();
}
