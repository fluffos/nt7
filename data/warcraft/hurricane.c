// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m湛蓝巨龙[2;37;0m[2;37;0m", ({"dragon"}));        
        set("gender", "男性");                
        set("long", "一头傻傻的龙。[2;37;0m
它是黑色飓风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hurricane");
        set("owner_name", "黑色飓风");
        set_temp("owner", "hurricane");
        set_temp("owner_name", "黑色飓风");
        ::setup();
}
