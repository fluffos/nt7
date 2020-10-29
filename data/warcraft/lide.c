// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞行者[2;37;0m[2;37;0m", ({"lxa"}));        
        set("gender", "男性");                
        set("long", "飞行者[2;37;0m
它是炼云的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lide");
        set("owner_name", "炼云");
        set_temp("owner", "lide");
        set_temp("owner_name", "炼云");
        ::setup();
}
