// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("钱大款[2;37;0m[2;37;0m", ({"golds"}));        
        set("gender", "男性");                
        set("long", "钱大款[2;37;0m
它是采花六的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "luk");
        set("owner_name", "采花六");
        set_temp("owner", "luk");
        set_temp("owner_name", "采花六");
        ::setup();
}
