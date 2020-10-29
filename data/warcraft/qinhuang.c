// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老马[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "老马[2;37;0m
它是秦皇大漠的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "qinhuang");
        set("owner_name", "秦皇大漠");
        set_temp("owner", "qinhuang");
        set_temp("owner_name", "秦皇大漠");
        ::setup();
}
