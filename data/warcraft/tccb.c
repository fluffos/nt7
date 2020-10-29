// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("马二[2;37;0m[2;37;0m", ({"tccbb"}));        
        set("gender", "男性");                
        set("long", "马二[2;37;0m
它是偷二的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tccb");
        set("owner_name", "偷二");
        set_temp("owner", "tccb");
        set_temp("owner_name", "偷二");
        ::setup();
}
