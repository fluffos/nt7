// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("傻包[2;37;0m[2;37;0m", ({"mybb"}));        
        set("gender", "男性");                
        set("long", "我的神兽[2;37;0m
它是不辣皮特的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lauzx");
        set("owner_name", "不辣皮特");
        set_temp("owner", "lauzx");
        set_temp("owner_name", "不辣皮特");
        ::setup();
}
