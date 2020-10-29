// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m拉土车[33m[2;37;0m[2;37;0m", ({"yaozs"}));        
        set("gender", "女性");                
        set("long", "我的坐骑[2;37;0m
它是菜只的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yaoz");
        set("owner_name", "菜只");
        set_temp("owner", "yaoz");
        set_temp("owner_name", "菜只");
        ::setup();
}
