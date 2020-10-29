// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("七号[2;37;0m[2;37;0m", ({"cafe"}));        
        set("gender", "女性");                
        set("long", "七号[2;37;0m
它是咖啡七号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "nntcafe");
        set("owner_name", "咖啡七号");
        set_temp("owner", "nntcafe");
        set_temp("owner_name", "咖啡七号");
        ::setup();
}
