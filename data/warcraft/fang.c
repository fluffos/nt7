// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"fzm"}));        
        set("gender", "女性");                
        set("long", "finish[2;37;0m
它是冷凌弃的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fang");
        set("owner_name", "冷凌弃");
        set_temp("owner", "fang");
        set_temp("owner_name", "冷凌弃");
        ::setup();
}
