// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m黄金圣龙[2;37;0m[2;37;0m", ({"shenlong"}));        
        set("gender", "男性");                
        set("long", "一头黄金圣龙[2;37;0m
它是上官小木的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "celi");
        set("owner_name", "上官小木");
        set_temp("owner", "celi");
        set_temp("owner_name", "上官小木");
        ::setup();
}
