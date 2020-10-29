// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[47;1m[1;34m星云锁涟[2;37;0m[2;37;0m", ({"foyuan"}));        
        set("gender", "男性");                
        set("long", "  [2;37;0m
它是超女的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "supergirl");
        set("owner_name", "超女");
        set_temp("owner", "supergirl");
        set_temp("owner_name", "超女");
        ::setup();
}
