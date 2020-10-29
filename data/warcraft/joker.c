// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("血滴子[2;37;0m[2;37;0m", ({"xdz"}));        
        set("gender", "女性");                
        set("long", "血滴子[2;37;0m
它是封不觉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "joker");
        set("owner_name", "封不觉");
        set_temp("owner", "joker");
        set_temp("owner_name", "封不觉");
        ::setup();
}
