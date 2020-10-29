// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("梅川酷子妹[2;37;0m[2;37;0m", ({"plgt"}));        
        set("gender", "男性");                
        set("long", "@miaoshu[2;37;0m
它是捣药一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ymga");
        set("owner_name", "捣药一");
        set_temp("owner", "ymga");
        set_temp("owner_name", "捣药一");
        ::setup();
}
