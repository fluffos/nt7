// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m风龙[2;37;0m[2;37;0m", ({"feng"}));        
        set("gender", "男性");                
        set("long", "风龙[2;37;0m
它是狂风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kuangfeng");
        set("owner_name", "狂风");
        set_temp("owner", "kuangfeng");
        set_temp("owner_name", "狂风");
        ::setup();
}
