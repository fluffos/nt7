// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m玉狻猊[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "这头神兽半似麒麟，半似狮子，头上长着鹿角，声若霹雳。[2;37;0m
它是独孤残的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dug");
        set("owner_name", "独孤残");
        set_temp("owner", "dug");
        set_temp("owner_name", "独孤残");
        ::setup();
}
