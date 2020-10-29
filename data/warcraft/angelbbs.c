// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m神[1;31m兽[1;36m青[1;35m龙[2;37;0m[2;37;0m", ({"xboss"}));        
        set("gender", "男性");                
        set("long", "这是一只九天十地菩萨摇头怕怕霹雳精光远古神兽之青龙。[2;37;0m
它是五毒教主的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "angelbbs");
        set("owner_name", "五毒教主");
        set_temp("owner", "angelbbs");
        set_temp("owner_name", "五毒教主");
        ::setup();
}
