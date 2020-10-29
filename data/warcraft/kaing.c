// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m翡翠玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "通体如翡翠美玉铸成的通灵生物[2;37;0m
它是雷柯德的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "kaing");
        set("owner_name", "雷柯德");
        set_temp("owner", "kaing");
        set_temp("owner_name", "雷柯德");
        ::setup();
}
