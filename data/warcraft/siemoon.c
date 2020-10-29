// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m嗜[1;31m血[1;33m族[2;37;0m[2;37;0m", ({"renblood"}));        
        set("gender", "男性");                
        set("long", "嗜血族座骑[2;37;0m
它是西蒙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "siemoon");
        set("owner_name", "西蒙");
        set_temp("owner", "siemoon");
        set_temp("owner_name", "西蒙");
        ::setup();
}
