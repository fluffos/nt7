// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙宝宝[2;37;0m[2;37;0m", ({"longbaby"}));        
        set("gender", "男性");                
        set("long", "龙宝宝[2;37;0m
它是刑天的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xingtian");
        set("owner_name", "刑天");
        set_temp("owner", "xingtian");
        set_temp("owner_name", "刑天");
        ::setup();
}
