// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("墨鱼[2;37;0m[2;37;0m", ({"mql"}));        
        set("gender", "女性");                
        set("long", "墨鱼噢[2;37;0m
它是舒克的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ulianl");
        set("owner_name", "舒克");
        set_temp("owner", "ulianl");
        set_temp("owner_name", "舒克");
        ::setup();
}
