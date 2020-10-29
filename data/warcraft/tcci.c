// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("马九[2;37;0m[2;37;0m", ({"tccga"}));        
        set("gender", "男性");                
        set("long", "马九[2;37;0m
它是偷九的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tcci");
        set("owner_name", "偷九");
        set_temp("owner", "tcci");
        set_temp("owner_name", "偷九");
        ::setup();
}
