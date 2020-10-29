// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m加菲[2;37;0m[2;37;0m", ({"jiafei"}));        
        set("gender", "男性");                
        set("long", "$MAG$加菲[2;37;0m
它是殇陌黎的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kxbb");
        set("owner_name", "殇陌黎");
        set_temp("owner", "kxbb");
        set_temp("owner_name", "殇陌黎");
        ::setup();
}
