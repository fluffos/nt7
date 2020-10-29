// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("女优[2;37;0m[2;37;0m", ({"nvyou"}));        
        set("gender", "女性");                
        set("long", "hp[2;37;0m
它是八一八的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "byb");
        set("owner_name", "八一八");
        set_temp("owner", "byb");
        set_temp("owner_name", "八一八");
        ::setup();
}
