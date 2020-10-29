// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神仙鸟[2;37;0m[2;37;0m", ({"shengou"}));        
        set("gender", "女性");                
        set("long", "神仙鸟[2;37;0m
它是龙风的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "longfengd");
        set("owner_name", "龙风");
        set_temp("owner", "longfengd");
        set_temp("owner_name", "龙风");
        ::setup();
}
