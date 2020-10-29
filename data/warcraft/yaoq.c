// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m拉土车[33m[2;37;0m[2;37;0m", ({"yaoqs"}));        
        set("gender", "女性");                
        set("long", "我的坐骑[2;37;0m
它是菜同的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yaoq");
        set("owner_name", "菜同");
        set_temp("owner", "yaoq");
        set_temp("owner_name", "菜同");
        ::setup();
}
