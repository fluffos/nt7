// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("碰碰车[2;37;0m[2;37;0m", ({"peng"}));        
        set("gender", "女性");                
        set("long", "游乐设施[2;37;0m
它是莲务的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lianwu");
        set("owner_name", "莲务");
        set_temp("owner", "lianwu");
        set_temp("owner_name", "莲务");
        ::setup();
}
