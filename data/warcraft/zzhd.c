// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m青龙[2;37;0m[2;37;0m", ({"lppk"}));        
        set("gender", "男性");                
        set("long", "$HIY$青龙[2;37;0m
它是恒物恒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zzhd");
        set("owner_name", "恒物恒");
        set_temp("owner", "zzhd");
        set_temp("owner_name", "恒物恒");
        ::setup();
}
