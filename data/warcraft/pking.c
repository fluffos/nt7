// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m狂[1;37m风[1;31m骤[1;32m雨[2;37;0m[2;37;0m", ({"kuangfeng"}));        
        set("gender", "男性");                
        set("long", "狂风骤雨[2;37;0m
它是笑傲江湖的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pking");
        set("owner_name", "笑傲江湖");
        set_temp("owner", "pking");
        set_temp("owner_name", "笑傲江湖");
        ::setup();
}
