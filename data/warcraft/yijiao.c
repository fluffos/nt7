// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿三[2;37;0m[2;37;0m", ({"ttt"}));        
        set("gender", "男性");                
        set("long", "阿三[2;37;0m
它是易姣的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yijiao");
        set("owner_name", "易姣");
        set_temp("owner", "yijiao");
        set_temp("owner_name", "易姣");
        ::setup();
}
