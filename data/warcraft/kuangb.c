// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大会[2;37;0m[2;37;0m", ({"along"}));        
        set("gender", "男性");                
        set("long", "大概[2;37;0m
它是狂二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kuangb");
        set("owner_name", "狂二");
        set_temp("owner", "kuangb");
        set_temp("owner_name", "狂二");
        ::setup();
}
