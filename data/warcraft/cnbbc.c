// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("无自由[2;37;0m[2;37;0m", ({"neverfree"}));        
        set("gender", "男性");                
        set("long", "无自由[2;37;0m
它是徐扉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cnbbc");
        set("owner_name", "徐扉");
        set_temp("owner", "cnbbc");
        set_temp("owner_name", "徐扉");
        ::setup();
}
