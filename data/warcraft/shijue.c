// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("米粒[2;37;0m[2;37;0m", ({"mili"}));        
        set("gender", "男性");                
        set("long", "不起眼[2;37;0m
它是澄释的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "shijue");
        set("owner_name", "澄释");
        set_temp("owner", "shijue");
        set_temp("owner_name", "澄释");
        ::setup();
}
