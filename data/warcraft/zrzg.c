// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m立花[1;36m[1;34m瞳[1;34m[2;37;0m[2;37;0m", ({"tong"}));        
        set("gender", "女性");                
        set("long", "AV[2;37;0m
它是粽药一的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zrzg");
        set("owner_name", "粽药一");
        set_temp("owner", "zrzg");
        set_temp("owner_name", "粽药一");
        ::setup();
}
