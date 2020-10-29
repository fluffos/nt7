// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m九天白鹤[2;37;0m[2;37;0m", ({"bird"}));        
        set("gender", "女性");                
        set("long", "远古飞来的仙鹤。[2;37;0m
它是一个道士的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "adao");
        set("owner_name", "一个道士");
        set_temp("owner", "adao");
        set_temp("owner_name", "一个道士");
        ::setup();
}
