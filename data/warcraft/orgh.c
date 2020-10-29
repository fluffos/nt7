// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "23456[2;37;0m
它是小哈密的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "orgh");
        set("owner_name", "小哈密");
        set_temp("owner", "orgh");
        set_temp("owner_name", "小哈密");
        ::setup();
}
