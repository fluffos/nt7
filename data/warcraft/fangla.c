// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m圣火[2;37;0m[2;37;0m", ({"pets"}));        
        set("gender", "女性");                
        set("long", "好看的[2;37;0m
它是方腊的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fangla");
        set("owner_name", "方腊");
        set_temp("owner", "fangla");
        set_temp("owner_name", "方腊");
        ::setup();
}
