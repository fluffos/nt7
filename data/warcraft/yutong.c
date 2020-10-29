// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m与[1;37m你[1;33m同[1;31m飞[2;37;0m[2;37;0m", ({"yutongfei"}));        
        set("gender", "男性");                
        set("long", "与你同飞[2;37;0m
它是雨桐的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yutong");
        set("owner_name", "雨桐");
        set_temp("owner", "yutong");
        set_temp("owner_name", "雨桐");
        ::setup();
}
