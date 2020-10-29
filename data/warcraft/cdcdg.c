// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"cdcdgpet"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是玄爆的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cdcdg");
        set("owner_name", "玄爆");
        set_temp("owner", "cdcdg");
        set_temp("owner_name", "玄爆");
        ::setup();
}
