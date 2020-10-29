// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小眼[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "小眼[2;37;0m
它是艾蒿糕的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nnt");
        set("owner_name", "艾蒿糕");
        set_temp("owner", "nnt");
        set_temp("owner_name", "艾蒿糕");
        ::setup();
}
