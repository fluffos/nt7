// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m苹果[2;37;0m[2;37;0m", ({"apple"}));        
        set("gender", "女性");                
        set("long", "iphone5[2;37;0m
它是乔不死的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jojosld");
        set("owner_name", "乔不死");
        set_temp("owner", "jojosld");
        set_temp("owner_name", "乔不死");
        ::setup();
}
