// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("第三青龙[2;37;0m[2;37;0m", ({"sleepbagc"}));        
        set("gender", "男性");                
        set("long", "第三青龙[2;37;0m
它是小妖三号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaoyaoc");
        set("owner_name", "小妖三号");
        set_temp("owner", "xiaoyaoc");
        set_temp("owner_name", "小妖三号");
        ::setup();
}
