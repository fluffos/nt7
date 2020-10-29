// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m拖拉机[1;37m[2;37;0m[2;37;0m", ({"tlj"}));        
        set("gender", "男性");                
        set("long", "马[2;37;0m
它是雷兹副的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lei");
        set("owner_name", "雷兹副");
        set_temp("owner", "lei");
        set_temp("owner_name", "雷兹副");
        ::setup();
}
