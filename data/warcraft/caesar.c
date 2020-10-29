// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("克利奥帕特拉[2;37;0m[2;37;0m", ({"axx"}));        
        set("gender", "男性");                
        set("long", "sadasdas[2;37;0m
它是凯撒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "caesar");
        set("owner_name", "凯撒");
        set_temp("owner", "caesar");
        set_temp("owner_name", "凯撒");
        ::setup();
}
