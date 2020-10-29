// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小南[2;37;0m[2;37;0m", ({"duanxixi"}));        
        set("gender", "男性");                
        set("long", "小南[2;37;0m
它是断东河的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "duanxi");
        set("owner_name", "断东河");
        set_temp("owner", "duanxi");
        set_temp("owner_name", "断东河");
        ::setup();
}
