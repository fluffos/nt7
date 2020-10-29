// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是大奇葩的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiangj");
        set("owner_name", "大奇葩");
        set_temp("owner", "xiangj");
        set_temp("owner_name", "大奇葩");
        ::setup();
}
