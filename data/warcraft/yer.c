// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"ffcfes"}));        
        set("gender", "男性");                
        set("long", "多吃点[2;37;0m
它是炎热而然的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yer");
        set("owner_name", "炎热而然");
        set_temp("owner", "yer");
        set_temp("owner_name", "炎热而然");
        ::setup();
}
