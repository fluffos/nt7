// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m鼓浪屿[2;37;0m[2;37;0m", ({"qwe"}));        
        set("gender", "男性");                
        set("long", "Amoy is the best![2;37;0m
它是鹭岛的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "amoy");
        set("owner_name", "鹭岛");
        set_temp("owner", "amoy");
        set_temp("owner_name", "鹭岛");
        ::setup();
}
