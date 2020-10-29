// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猪可夫[2;37;0m[2;37;0m", ({"lichyaozhu"}));        
        set("gender", "男性");                
        set("long", "猪可夫[2;37;0m
它是独孤香猪的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lichyao");
        set("owner_name", "独孤香猪");
        set_temp("owner", "lichyao");
        set_temp("owner_name", "独孤香猪");
        ::setup();
}
