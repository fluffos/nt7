// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m仙鹤[2;37;0m[2;37;0m", ({"cay"}));        
        set("gender", "男性");                
        set("long", "$HIW$仙鹤[2;37;0m
它是张仲景的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zhongjing");
        set("owner_name", "张仲景");
        set_temp("owner", "zhongjing");
        set_temp("owner_name", "张仲景");
        ::setup();
}
