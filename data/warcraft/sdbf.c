// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武撼天[2;37;0m[2;37;0m", ({"sdbfa"}));        
        set("gender", "女性");                
        set("long", "相当神秘[2;37;0m
它是天空六号的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "sdbf");
        set("owner_name", "天空六号");
        set_temp("owner", "sdbf");
        set_temp("owner_name", "天空六号");
        ::setup();
}
