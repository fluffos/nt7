// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"sleepba"}));        
        set("gender", "男性");                
        set("long", "无[2;37;0m
它是米壹的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lvzhida");
        set("owner_name", "米壹");
        set_temp("owner", "lvzhida");
        set_temp("owner_name", "米壹");
        ::setup();
}
