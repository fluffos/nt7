// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[35m南无阿弥陀佛[2;37;0m[2;37;0m", ({"azhes"}));        
        set("gender", "男性");                
        set("long", "虚竹的坐骑[2;37;0m
它是竹子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "azhe");
        set("owner_name", "竹子");
        set_temp("owner", "azhe");
        set_temp("owner_name", "竹子");
        ::setup();
}
