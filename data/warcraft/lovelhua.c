// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m麒麟真龙[2;37;0m[2;37;0m", ({"dragonn"}));        
        set("gender", "女性");                
        set("long", "魔幻兽[2;37;0m
它是神剑的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lovelhua");
        set("owner_name", "神剑");
        set_temp("owner", "lovelhua");
        set_temp("owner_name", "神剑");
        ::setup();
}
