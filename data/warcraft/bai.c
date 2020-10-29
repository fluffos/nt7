// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m按摩器[2;37;0m[2;37;0m", ({"qlong"}));        
        set("gender", "男性");                
        set("long", "好大好长的电动按摩器[2;37;0m
它是白石茉奈的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bai");
        set("owner_name", "白石茉奈");
        set_temp("owner", "bai");
        set_temp("owner_name", "白石茉奈");
        ::setup();
}
