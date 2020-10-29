// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("波多结衣子妹[2;37;0m[2;37;0m", ({"plgb"}));        
        set("gender", "男性");                
        set("long", "@miaoshu[2;37;0m
它是捣药二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ymgb");
        set("owner_name", "捣药二");
        set_temp("owner", "ymgb");
        set_temp("owner_name", "捣药二");
        ::setup();
}
