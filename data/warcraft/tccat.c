// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m菜问[2;37;0m[2;37;0m", ({"jinhu"}));        
        set("gender", "男性");                
        set("long", "菜问[2;37;0m
它是祷菜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tccat");
        set("owner_name", "祷菜");
        set_temp("owner", "tccat");
        set_temp("owner_name", "祷菜");
        ::setup();
}
