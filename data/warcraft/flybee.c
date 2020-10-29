// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火[2;37;0m[2;37;0m", ({"huo"}));        
        set("gender", "男性");                
        set("long", "会喷火的大鸟[2;37;0m
它是大飞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "flybee");
        set("owner_name", "大飞");
        set_temp("owner", "flybee");
        set_temp("owner_name", "大飞");
        ::setup();
}
