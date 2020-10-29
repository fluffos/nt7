// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哦你哦[2;37;0m[2;37;0m", ({"woei"}));        
        set("gender", "男性");                
        set("long", "哦你哦[2;37;0m
它是鬼丈夫的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gzf");
        set("owner_name", "鬼丈夫");
        set_temp("owner", "gzf");
        set_temp("owner_name", "鬼丈夫");
        ::setup();
}
