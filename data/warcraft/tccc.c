// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("马三[2;37;0m[2;37;0m", ({"tcccc"}));        
        set("gender", "男性");                
        set("long", "马三[2;37;0m
它是偷三的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tccc");
        set("owner_name", "偷三");
        set_temp("owner", "tccc");
        set_temp("owner_name", "偷三");
        ::setup();
}
