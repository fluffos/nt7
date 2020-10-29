// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m虎头[2;37;0m[2;37;0m", ({"hutou"}));        
        set("gender", "男性");                
        set("long", "虎头[2;37;0m
它是太炫的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zztaixuan");
        set("owner_name", "太炫");
        set_temp("owner", "zztaixuan");
        set_temp("owner_name", "太炫");
        ::setup();
}
