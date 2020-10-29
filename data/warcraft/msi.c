// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m齐天[2;37;0m[2;37;0m", ({"qitian"}));        
        set("gender", "女性");                
        set("long", "齐天[2;37;0m
它是鼠标的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "msi");
        set("owner_name", "鼠标");
        set_temp("owner", "msi");
        set_temp("owner_name", "鼠标");
        ::setup();
}
