// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("散散[2;37;0m[2;37;0m", ({"toflying"}));        
        set("gender", "男性");                
        set("long", "散散[2;37;0m
它是散神的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "sann");
        set("owner_name", "散神");
        set_temp("owner", "sann");
        set_temp("owner_name", "散神");
        ::setup();
}
