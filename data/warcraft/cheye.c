// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火车王[2;37;0m[2;37;0m", ({"help_nick"}));        
        set("gender", "女性");                
        set("long", "火车王[2;37;0m
它是彻夜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cheye");
        set("owner_name", "彻夜");
        set_temp("owner", "cheye");
        set_temp("owner_name", "彻夜");
        ::setup();
}
