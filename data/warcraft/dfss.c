// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m小黄[2;37;0m[2;37;0m", ({"yellow"}));        
        set("gender", "女性");                
        set("long", "小黄龙[2;37;0m
它是东方叔叔的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dfss");
        set("owner_name", "东方叔叔");
        set_temp("owner", "dfss");
        set_temp("owner_name", "东方叔叔");
        ::setup();
}
