// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("无雨虎[2;37;0m[2;37;0m", ({"wuyu"}));        
        set("gender", "男性");                
        set("long", "无雨虎[2;37;0m
它是魔无雨的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mwy");
        set("owner_name", "魔无雨");
        set_temp("owner", "mwy");
        set_temp("owner_name", "魔无雨");
        ::setup();
}
