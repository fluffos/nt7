// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m操[1;35m你[1;37m马[2;37;0m[2;37;0m", ({"aliass"}));        
        set("gender", "男性");                
        set("long", "这只神兽[2;37;0m
它是丐中丐的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "alias");
        set("owner_name", "丐中丐");
        set_temp("owner", "alias");
        set_temp("owner_name", "丐中丐");
        ::setup();
}
