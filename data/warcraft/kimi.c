// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("依衣[2;37;0m[2;37;0m", ({"kik"}));        
        set("gender", "女性");                
        set("long", "依衣[2;37;0m
它是王依的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kimi");
        set("owner_name", "王依");
        set_temp("owner", "kimi");
        set_temp("owner_name", "王依");
        ::setup();
}
