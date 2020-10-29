// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("王兽[2;37;0m[2;37;0m", ({"shoushou"}));        
        set("gender", "女性");                
        set("long", "王兽[2;37;0m
它是静三的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jingc");
        set("owner_name", "静三");
        set_temp("owner", "jingc");
        set_temp("owner_name", "静三");
        ::setup();
}
