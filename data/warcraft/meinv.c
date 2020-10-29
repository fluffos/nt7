// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小红马[2;37;0m[2;37;0m", ({"ooo"}));        
        set("gender", "男性");                
        set("long", "没啥描述的随便玩的[2;37;0m
它是美女爽爽的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "meinv");
        set("owner_name", "美女爽爽");
        set_temp("owner", "meinv");
        set_temp("owner_name", "美女爽爽");
        ::setup();
}
