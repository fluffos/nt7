// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m断[1;33m念[1;32m剑[2;37;0m[2;37;0m", ({"cannian"}));        
        set("gender", "女性");                
        set("long", "一把破剑[2;37;0m
它是花千骨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hqg");
        set("owner_name", "花千骨");
        set_temp("owner", "hqg");
        set_temp("owner_name", "花千骨");
        ::setup();
}
