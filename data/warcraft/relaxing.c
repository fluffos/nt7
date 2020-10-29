// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m潜龙[2;37;0m[2;37;0m", ({"qianlong"}));        
        set("gender", "男性");                
        set("long", "上天入地 无所不及[2;37;0m
它是闲来无事的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "relaxing");
        set("owner_name", "闲来无事");
        set_temp("owner", "relaxing");
        set_temp("owner_name", "闲来无事");
        ::setup();
}
