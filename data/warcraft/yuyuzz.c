// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞机[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "飞机[2;37;0m
它是掏柏油的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yuyuzz");
        set("owner_name", "掏柏油");
        set_temp("owner", "yuyuzz");
        set_temp("owner_name", "掏柏油");
        ::setup();
}
