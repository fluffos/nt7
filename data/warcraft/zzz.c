// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[45;1m堕落独角兽[2;37;0m[2;37;0m", ({"mengyan"}));        
        set("gender", "男性");                
        set("long", "梦魇兽[2;37;0m
它是梦魇的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zzz");
        set("owner_name", "梦魇");
        set_temp("owner", "zzz");
        set_temp("owner_name", "梦魇");
        ::setup();
}
