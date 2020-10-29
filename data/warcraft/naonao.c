// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m屁屁[2;37;0m[2;37;0m", ({"lyly"}));        
        set("gender", "男性");                
        set("long", "噗嗤！[2;37;0m
它是楚阎王的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "naonao");
        set("owner_name", "楚阎王");
        set_temp("owner", "naonao");
        set_temp("owner_name", "楚阎王");
        ::setup();
}
