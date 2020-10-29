// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("沃尔沃[2;37;0m[2;37;0m", ({"woow"}));        
        set("gender", "男性");                
        set("long", "沃尔沃[2;37;0m
它是武当兄弟的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "fofo");
        set("owner_name", "武当兄弟");
        set_temp("owner", "fofo");
        set_temp("owner_name", "武当兄弟");
        ::setup();
}
