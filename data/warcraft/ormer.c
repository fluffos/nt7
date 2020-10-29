// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m龙宝贝[2;37;0m[2;37;0m", ({"celia"}));        
        set("gender", "女性");                
        set("long", "漂亮、可爱、又善良的龙宝贝[2;37;0m
它是鲍清扬的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ormer");
        set("owner_name", "鲍清扬");
        set_temp("owner", "ormer");
        set_temp("owner_name", "鲍清扬");
        ::setup();
}
