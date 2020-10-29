// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m狂龙[2;37;0m[2;37;0m", ({"kuanglong"}));        
        set("gender", "男性");                
        set("long", "狂龙[2;37;0m
它是兮兮的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xixi");
        set("owner_name", "兮兮");
        set_temp("owner", "xixi");
        set_temp("owner_name", "兮兮");
        ::setup();
}
