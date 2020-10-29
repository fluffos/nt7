// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m无[2;37;0m[1;33m毛[2;37;0m[1;31m鸡[2;37;0m[2;37;0m[2;37;0m", ({"wumaoji"}));        
        set("gender", "女性");                
        set("long", "这是一只被拔了毛的小母鸡[2;37;0m
它是暴走矮人的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "baozou");
        set("owner_name", "暴走矮人");
        set_temp("owner", "baozou");
        set_temp("owner_name", "暴走矮人");
        ::setup();
}
