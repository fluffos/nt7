// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m曦[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "男性");                
        set("long", "两只老虎两只老虎跑的快，跑的快。[2;37;0m
它是魔刀的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "modao");
        set("owner_name", "魔刀");
        set_temp("owner", "modao");
        set_temp("owner_name", "魔刀");
        ::setup();
}
