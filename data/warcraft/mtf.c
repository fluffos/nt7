// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m风灵[2;37;0m[2;37;0m", ({"fling"}));        
        set("gender", "男性");                
        set("long", "hehe[2;37;0m
它是漫天风的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mtf");
        set("owner_name", "漫天风");
        set_temp("owner", "mtf");
        set_temp("owner_name", "漫天风");
        ::setup();
}
