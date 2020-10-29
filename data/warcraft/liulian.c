// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("云霄飞车[2;37;0m[2;37;0m", ({"yunxiao"}));        
        set("gender", "女性");                
        set("long", "好玩的游乐设施[2;37;0m
它是留连的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "liulian");
        set("owner_name", "留连");
        set_temp("owner", "liulian");
        set_temp("owner_name", "留连");
        ::setup();
}
