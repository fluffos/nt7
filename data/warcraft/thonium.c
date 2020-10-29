// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("赫拉克勒斯[2;37;0m[2;37;0m", ({"axx"}));        
        set("gender", "男性");                
        set("long", "sada[2;37;0m
它是燃料循环的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "thonium");
        set("owner_name", "燃料循环");
        set_temp("owner", "thonium");
        set_temp("owner_name", "燃料循环");
        ::setup();
}
