// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("云心[2;37;0m[2;37;0m", ({"tofly"}));        
        set("gender", "男性");                
        set("long", "无[2;37;0m
它是独孤云的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yumio");
        set("owner_name", "独孤云");
        set_temp("owner", "yumio");
        set_temp("owner_name", "独孤云");
        ::setup();
}
