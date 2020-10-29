// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m青菜马[2;37;0m[2;37;0m", ({"horsea"}));        
        set("gender", "男性");                
        set("long", "青菜马[2;37;0m
它是阿多七的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "adonisg");
        set("owner_name", "阿多七");
        set_temp("owner", "adonisg");
        set_temp("owner_name", "阿多七");
        ::setup();
}
