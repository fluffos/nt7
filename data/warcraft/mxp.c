// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啾啾挤挤[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "mygift[2;37;0m
它是欧派腻歪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mxp");
        set("owner_name", "欧派腻歪");
        set_temp("owner", "mxp");
        set_temp("owner_name", "欧派腻歪");
        ::setup();
}
