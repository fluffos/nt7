// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m神龙[2;37;0m[2;37;0m", ({"shou"}));        
        set("gender", "男性");                
        set("long", "一条龙，哇好大。[2;37;0m
它是淡定人生的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dupengdc");
        set("owner_name", "淡定人生");
        set_temp("owner", "dupengdc");
        set_temp("owner_name", "淡定人生");
        ::setup();
}
