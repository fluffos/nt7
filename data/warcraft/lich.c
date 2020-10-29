// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("拉拉[2;37;0m[2;37;0m", ({"wodegou"}));        
        set("gender", "男性");                
        set("long", "贪婪[2;37;0m
它是永生不死的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lich");
        set("owner_name", "永生不死");
        set_temp("owner", "lich");
        set_temp("owner_name", "永生不死");
        ::setup();
}
