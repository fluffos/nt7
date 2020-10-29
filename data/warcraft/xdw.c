// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("水谷心音[2;37;0m[2;37;0m", ({"nini"}));        
        set("gender", "女性");                
        set("long", "水谷心音 于2009年在AV界出道，属于Duo Entertainment事务所.[2;37;0m
它是湛哥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xdw");
        set("owner_name", "湛哥");
        set_temp("owner", "xdw");
        set_temp("owner_name", "湛哥");
        ::setup();
}
