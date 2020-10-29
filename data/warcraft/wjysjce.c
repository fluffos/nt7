// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("座机[2;37;0m[2;37;0m", ({"zuoji"}));        
        set("gender", "男性");                
        set("long", "座机[2;37;0m
它是啊以的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wjysjce");
        set("owner_name", "啊以");
        set_temp("owner", "wjysjce");
        set_temp("owner_name", "啊以");
        ::setup();
}
